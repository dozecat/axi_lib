//*****************************************************************************
// Copyright (C) 2026 dozecat. All rights reserved.
// SPDX-License-Identifier: MIT
//
// File:        axi2axil.sv
// Description: AXI4 to AXI4-Lite Bridge
// Repository:  https://github.com/dozecat/axi_lib.git
//
// Converts AXI4 burst transactions into multiple AXI4-Lite single-beat
// accesses. Supports FIXED, INCR and WRAP burst types.
// Single outstanding transaction; processes one beat at a time.
//
// Modification History:
// Ver   Who       Date        Changes
// ----  ----  ----------  ----------------------------------------------------
// 1.0         2026/5/4    Initial release
//*****************************************************************************
`timescale 1ns / 1ps
`default_nettype none

module axi2axil (
   input  wire                clk,
   input  wire                rst,

   if_axi.slave               s_axi_if,
   if_axil.master             m_axil_if
);

localparam ADDR_WIDTH  = s_axi_if.ADDR_WIDTH;
localparam DATA_WIDTH  = s_axi_if.DATA_WIDTH;
localparam ID_WIDTH    = s_axi_if.ID_WIDTH;
localparam STRB_WIDTH  = DATA_WIDTH / 8;

// AXI protocol constant widths (from interface)
localparam LEN_WIDTH   = s_axi_if.LEN_WIDTH;         // 8
localparam SIZE_WIDTH  = s_axi_if.BURST_SIZE_WIDTH;        // 3
localparam PROT_WIDTH  = s_axi_if.PROT_WIDTH;        // 3
localparam RESP_WIDTH  = s_axi_if.RESP_WIDTH;        // 2
localparam BURST_WIDTH = s_axi_if.BURST_TYPE_WIDTH;  // 2

initial begin
   if (DATA_WIDTH != 32 && DATA_WIDTH != 64)
      $error("axi2axil: DATA_WIDTH must be 32 or 64, got %0d", DATA_WIDTH);
   if (s_axi_if.ADDR_WIDTH != m_axil_if.ADDR_WIDTH)
      $error("axi2axil: ADDR_WIDTH mismatch (%0d vs %0d)",
             s_axi_if.ADDR_WIDTH, m_axil_if.ADDR_WIDTH);
   if (s_axi_if.DATA_WIDTH != m_axil_if.DATA_WIDTH)
      $error("axi2axil: DATA_WIDTH mismatch (%0d vs %0d)",
             s_axi_if.DATA_WIDTH, m_axil_if.DATA_WIDTH);
end

// Beat address calculation
function automatic [ADDR_WIDTH-1:0] calc_beat_addr (
   input [ADDR_WIDTH-1:0]  base,
   input [LEN_WIDTH-1:0]   len,
   input [SIZE_WIDTH-1:0]  size,
   input [BURST_WIDTH-1:0] burst,
   input [LEN_WIDTH-1:0]   beat
);
   logic [ADDR_WIDTH-1:0] offset;
   logic [ADDR_WIDTH-1:0] wrap_bytes;

   offset = beat << size;
   case (burst)
      2'b01: calc_beat_addr = base + offset;
      2'b10: begin
         wrap_bytes = (len + 1) << size;
         calc_beat_addr = (base & ~(wrap_bytes - 1)) |
                          ((base + offset) & (wrap_bytes - 1));
      end
      default: calc_beat_addr = base;
   endcase
endfunction

//*****************************************************************************
// Write channel
//*****************************************************************************
// write path signals
wire  [ADDR_WIDTH       -1:0]    wr_beat_addr;
reg   [ADDR_WIDTH       -1:0]    wr_addr;
reg   [LEN_WIDTH        -1:0]    wr_len;
reg   [SIZE_WIDTH       -1:0]    wr_size;
reg   [BURST_WIDTH      -1:0]    wr_burst;
reg   [ID_WIDTH         -1:0]    wr_id;
reg   [PROT_WIDTH       -1:0]    wr_prot;
reg   [LEN_WIDTH        -1:0]    wr_beat;
reg   [RESP_WIDTH       -1:0]    wr_resp;
reg                              wr_err;
reg   [DATA_WIDTH       -1:0]    wr_wdata_q;
reg   [STRB_WIDTH       -1:0]    wr_wstrb_q;
reg                              wr_wlast_q;
reg                              wr_wpend;

// Write path FSM — three-stage
enum logic [1:0] {
   W_IDLE  = 0,
   W_ISSUE = 1,
   W_BRESP = 2,
   W_DONE  = 3
} wr_state, wr_nstate;

// state register
always_ff @(posedge clk or posedge rst) begin
   if (rst)
      wr_state <= W_IDLE;
   else
      wr_state <= wr_nstate;
end

// next state
always_comb begin
   wr_nstate = wr_state;
   case (wr_state)
      W_IDLE:
      begin
         if (s_axi_if.awvalid)
            wr_nstate = W_ISSUE;
         else
            wr_nstate = W_IDLE;
      end

      W_ISSUE:
      begin
         if (wr_wpend && m_axil_if.awready && m_axil_if.wready)
            wr_nstate = W_BRESP;
         else
            wr_nstate = W_ISSUE;
      end

      W_BRESP:
      begin
         if (m_axil_if.bvalid && wr_wlast_q)
            wr_nstate = W_DONE;
         else if (m_axil_if.bvalid)
            wr_nstate = W_ISSUE;
         else
            wr_nstate = W_BRESP;
      end

      W_DONE:
      begin
         if (s_axi_if.bready)
            wr_nstate = W_IDLE;
         else
            wr_nstate = W_DONE;
      end
   endcase
end

// data registers
always_ff @(posedge clk or posedge rst) begin
   if (rst) begin
      wr_addr  <= '0;
      wr_len   <= '0;
      wr_size  <= '0;
      wr_burst <= '0;
      wr_id    <= '0;
      wr_prot  <= '0;
   end else if (wr_state == W_IDLE && s_axi_if.awvalid) begin
      wr_addr  <= s_axi_if.awaddr;
      wr_len   <= s_axi_if.awlen;
      wr_size  <= s_axi_if.awsize;
      wr_burst <= s_axi_if.awburst;
      wr_id    <= s_axi_if.awid;
      wr_prot  <= s_axi_if.awprot;
   end
end

always_ff @(posedge clk or posedge rst) begin
   if (rst) begin
      wr_wdata_q <= '0;
      wr_wstrb_q <= '0;
      wr_wlast_q <= 1'b0;
   end else if (wr_state == W_ISSUE && !wr_wpend && s_axi_if.wvalid) begin
      wr_wdata_q <= s_axi_if.wdata;
      wr_wstrb_q <= s_axi_if.wstrb;
      wr_wlast_q <= s_axi_if.wlast;
   end
end

always_ff @(posedge clk or posedge rst) begin
   if (rst)
      wr_beat <= '0;
   else if (wr_state == W_IDLE && s_axi_if.awvalid)
      wr_beat <= '0;
   else if (wr_state == W_BRESP && m_axil_if.bvalid && !wr_wlast_q)
      wr_beat <= wr_beat + 1'b1;
end

always_ff @(posedge clk or posedge rst) begin
   if (rst) begin
      wr_resp <= 2'b00;
      wr_err  <= 1'b0;
   end else if (wr_state == W_IDLE && s_axi_if.awvalid) begin
      wr_resp <= 2'b00;
      wr_err  <= 1'b0;
   end else if (wr_state == W_BRESP && m_axil_if.bvalid) begin
      if (m_axil_if.bresp != 2'b00) wr_err <= 1'b1;
      wr_resp <= m_axil_if.bresp;
   end
end

always_ff @(posedge clk or posedge rst) begin
   if (rst)
      wr_wpend <= 1'b0;
   else if (wr_state == W_IDLE && s_axi_if.awvalid)
      wr_wpend <= 1'b0;
   else if (wr_state == W_ISSUE && !wr_wpend && s_axi_if.wvalid)
      wr_wpend <= 1'b1;
   else if (wr_state == W_ISSUE && wr_wpend && m_axil_if.awready && m_axil_if.wready)
      wr_wpend <= 1'b0;
end

// axi-slave interface assigns
assign s_axi_if.awready = (wr_state == W_IDLE);
assign s_axi_if.wready  = (wr_state == W_ISSUE) && !wr_wpend;
assign s_axi_if.bvalid  = (wr_state == W_DONE);
assign s_axi_if.bresp   = wr_err ? 2'b10 : wr_resp;
assign s_axi_if.bid     = wr_id;

// axil-slave interface assigns
assign wr_beat_addr = calc_beat_addr(wr_addr, wr_len, wr_size, wr_burst, wr_beat);
assign m_axil_if.awaddr  = wr_beat_addr;
assign m_axil_if.awprot  = wr_prot;
assign m_axil_if.awvalid = (wr_state == W_ISSUE) && wr_wpend;
assign m_axil_if.wdata   = wr_wdata_q;
assign m_axil_if.wstrb   = wr_wstrb_q;
assign m_axil_if.wvalid  = (wr_state == W_ISSUE) && wr_wpend;
assign m_axil_if.bready  = (wr_state == W_BRESP);

//*****************************************************************************
// Read channel
//*****************************************************************************
// read path signals
wire  [ADDR_WIDTH       -1:0]    rd_beat_addr;
wire                               rd_last;
reg   [ADDR_WIDTH       -1:0]    rd_addr;
reg   [LEN_WIDTH        -1:0]    rd_len;
reg   [SIZE_WIDTH       -1:0]    rd_size;
reg   [BURST_WIDTH      -1:0]    rd_burst;
reg   [ID_WIDTH         -1:0]    rd_id;
reg   [PROT_WIDTH       -1:0]    rd_prot;
reg   [LEN_WIDTH        -1:0]    rd_beat;
reg   [DATA_WIDTH       -1:0]    rd_rdata_q;
reg   [RESP_WIDTH       -1:0]    rd_rresp_q;
reg                              rd_dvalid;

// Read path FSM — three-stage
enum logic [1:0] {
   R_IDLE    = 0,
   R_ISSUE   = 1,
   R_WAIT    = 2,
   R_PRESENT = 3
} rd_state, rd_nstate;

// state register
always_ff @(posedge clk or posedge rst) begin
   if (rst)
      rd_state <= R_IDLE;
   else
      rd_state <= rd_nstate;
end

// next state
always_comb begin
   rd_nstate = rd_state;
   case (rd_state)
      R_IDLE:
      begin
         if (s_axi_if.arvalid)
            rd_nstate = R_ISSUE;
         else
            rd_nstate = R_IDLE;
      end

      R_ISSUE:
      begin
         if (m_axil_if.arready)
            rd_nstate = R_WAIT;
         else
            rd_nstate = R_ISSUE;
      end

      R_WAIT:
      begin
         if (m_axil_if.rvalid)
            rd_nstate = R_PRESENT;
         else
            rd_nstate = R_WAIT;
      end

      R_PRESENT:
      begin
         if (s_axi_if.rready && rd_dvalid && rd_last)
            rd_nstate = R_IDLE;
         else if (s_axi_if.rready && rd_dvalid)
            rd_nstate = R_ISSUE;
         else
            rd_nstate = R_PRESENT;
      end
   endcase
end

// data registers
always_ff @(posedge clk or posedge rst) begin
   if (rst) begin
      rd_addr  <= '0;
      rd_len   <= '0;
      rd_size  <= '0;
      rd_burst <= '0;
      rd_id    <= '0;
      rd_prot  <= '0;
   end else if (rd_state == R_IDLE && s_axi_if.arvalid) begin
      rd_addr  <= s_axi_if.araddr;
      rd_len   <= s_axi_if.arlen;
      rd_size  <= s_axi_if.arsize;
      rd_burst <= s_axi_if.arburst;
      rd_id    <= s_axi_if.arid;
      rd_prot  <= s_axi_if.arprot;
   end
end

always_ff @(posedge clk or posedge rst) begin
   if (rst) begin
      rd_rdata_q <= '0;
      rd_rresp_q <= 2'b00;
   end else if (rd_state == R_WAIT && m_axil_if.rvalid) begin
      rd_rdata_q <= m_axil_if.rdata;
      rd_rresp_q <= m_axil_if.rresp;
   end
end

always_ff @(posedge clk or posedge rst) begin
   if (rst)
      rd_beat <= '0;
   else if (rd_state == R_IDLE && s_axi_if.arvalid)
      rd_beat <= '0;
   else if (rd_state == R_PRESENT && s_axi_if.rready && rd_dvalid && !rd_last)
      rd_beat <= rd_beat + 1'b1;
end

always_ff @(posedge clk or posedge rst) begin
   if (rst)
      rd_dvalid <= 1'b0;
   else if (rd_state == R_IDLE && s_axi_if.arvalid)
      rd_dvalid <= 1'b0;
   else if (rd_state == R_WAIT && m_axil_if.rvalid)
      rd_dvalid <= 1'b1;
   else if (rd_state == R_PRESENT && s_axi_if.rready && rd_dvalid)
      rd_dvalid <= 1'b0;
end

// axi-slave interface assigns
assign rd_beat_addr = calc_beat_addr(rd_addr, rd_len, rd_size, rd_burst, rd_beat);
assign rd_last = (rd_beat >= rd_len);

assign s_axi_if.arready = (rd_state == R_IDLE);
assign s_axi_if.rvalid  = rd_dvalid;
assign s_axi_if.rdata   = rd_rdata_q;
assign s_axi_if.rresp   = rd_rresp_q;
assign s_axi_if.rid     = rd_id;
assign s_axi_if.rlast   = rd_dvalid && rd_last;

// axil-master interface assigns
assign m_axil_if.araddr  = rd_beat_addr;
assign m_axil_if.arprot  = rd_prot;
assign m_axil_if.arvalid = (rd_state == R_ISSUE);
assign m_axil_if.rready  = (rd_state == R_WAIT);

endmodule

`resetall
