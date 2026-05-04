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
   input  wire                aclk,
   input  wire                aresetn,

   if_axi.slave               axi_slv_if,
   if_axil.master             axil_mst_if
);

localparam ADDR_WIDTH  = axi_slv_if.ADDR_WIDTH;
localparam DATA_WIDTH  = axi_slv_if.DATA_WIDTH;
localparam ID_WIDTH    = axi_slv_if.ID_WIDTH;
localparam STRB_WIDTH  = DATA_WIDTH / 8;

// AXI protocol constant widths (from interface)
localparam LEN_WIDTH   = axi_slv_if.LEN_WIDTH;         // 8
localparam SIZE_WIDTH  = axi_slv_if.SIZE_WIDTH;        // 3
localparam PROT_WIDTH  = axi_slv_if.PROT_WIDTH;        // 3
localparam RESP_WIDTH  = axi_slv_if.RESP_WIDTH;        // 2
localparam BURST_WIDTH = axi_slv_if.BURST_TYPE_WIDTH;  // 2

initial begin
   if (DATA_WIDTH != 32 && DATA_WIDTH != 64)
      $error("axi2axil: DATA_WIDTH must be 32 or 64, got %0d", DATA_WIDTH);
   if (axi_slv_if.ADDR_WIDTH != axil_mst_if.ADDR_WIDTH)
      $error("axi2axil: ADDR_WIDTH mismatch (%0d vs %0d)",
             axi_slv_if.ADDR_WIDTH, axil_mst_if.ADDR_WIDTH);
   if (axi_slv_if.DATA_WIDTH != axil_mst_if.DATA_WIDTH)
      $error("axi2axil: DATA_WIDTH mismatch (%0d vs %0d)",
             axi_slv_if.DATA_WIDTH, axil_mst_if.DATA_WIDTH);
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
always_ff @(posedge aclk or negedge aresetn) begin
   if (!aresetn)
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
         if (axi_slv_if.awvalid)
            wr_nstate = W_ISSUE;
         else
            wr_nstate = W_IDLE;
      end

      W_ISSUE:
      begin
         if (wr_wpend && axil_mst_if.awready && axil_mst_if.wready)
            wr_nstate = W_BRESP;
         else
            wr_nstate = W_ISSUE;
      end

      W_BRESP:
      begin
         if (axil_mst_if.bvalid && wr_wlast_q)
            wr_nstate = W_DONE;
         else if (axil_mst_if.bvalid)
            wr_nstate = W_ISSUE;
         else
            wr_nstate = W_BRESP;
      end

      W_DONE:
      begin
         if (axi_slv_if.bready)
            wr_nstate = W_IDLE;
         else
            wr_nstate = W_DONE;
      end
   endcase
end

// data registers
always_ff @(posedge aclk or negedge aresetn) begin
   if (!aresetn) begin
      wr_addr  <= '0;
      wr_len   <= '0;
      wr_size  <= '0;
      wr_burst <= '0;
      wr_id    <= '0;
      wr_prot  <= '0;
   end else if (wr_state == W_IDLE && axi_slv_if.awvalid) begin
      wr_addr  <= axi_slv_if.awaddr;
      wr_len   <= axi_slv_if.awlen;
      wr_size  <= axi_slv_if.awsize;
      wr_burst <= axi_slv_if.awburst;
      wr_id    <= axi_slv_if.awid;
      wr_prot  <= axi_slv_if.awprot;
   end
end

always_ff @(posedge aclk or negedge aresetn) begin
   if (!aresetn) begin
      wr_wdata_q <= '0;
      wr_wstrb_q <= '0;
      wr_wlast_q <= 1'b0;
   end else if (wr_state == W_ISSUE && !wr_wpend && axi_slv_if.wvalid) begin
      wr_wdata_q <= axi_slv_if.wdata;
      wr_wstrb_q <= axi_slv_if.wstrb;
      wr_wlast_q <= axi_slv_if.wlast;
   end
end

always_ff @(posedge aclk or negedge aresetn) begin
   if (!aresetn)
      wr_beat <= '0;
   else if (wr_state == W_IDLE && axi_slv_if.awvalid)
      wr_beat <= '0;
   else if (wr_state == W_BRESP && axil_mst_if.bvalid && !wr_wlast_q)
      wr_beat <= wr_beat + 1'b1;
end

always_ff @(posedge aclk or negedge aresetn) begin
   if (!aresetn) begin
      wr_resp <= 2'b00;
      wr_err  <= 1'b0;
   end else if (wr_state == W_IDLE && axi_slv_if.awvalid) begin
      wr_resp <= 2'b00;
      wr_err  <= 1'b0;
   end else if (wr_state == W_BRESP && axil_mst_if.bvalid) begin
      if (axil_mst_if.bresp != 2'b00) wr_err <= 1'b1;
      wr_resp <= axil_mst_if.bresp;
   end
end

always_ff @(posedge aclk or negedge aresetn) begin
   if (!aresetn)
      wr_wpend <= 1'b0;
   else if (wr_state == W_IDLE && axi_slv_if.awvalid)
      wr_wpend <= 1'b0;
   else if (wr_state == W_ISSUE && !wr_wpend && axi_slv_if.wvalid)
      wr_wpend <= 1'b1;
   else if (wr_state == W_ISSUE && wr_wpend && axil_mst_if.awready && axil_mst_if.wready)
      wr_wpend <= 1'b0;
end

// axi-slave interface assigns
assign axi_slv_if.awready = (wr_state == W_IDLE);
assign axi_slv_if.wready  = (wr_state == W_ISSUE) && !wr_wpend;
assign axi_slv_if.bvalid  = (wr_state == W_DONE);
assign axi_slv_if.bresp   = wr_err ? 2'b10 : wr_resp;
assign axi_slv_if.bid     = wr_id;

// axil-slave interface assigns
assign wr_beat_addr = calc_beat_addr(wr_addr, wr_len, wr_size, wr_burst, wr_beat);
assign axil_mst_if.awaddr  = wr_beat_addr;
assign axil_mst_if.awprot  = wr_prot;
assign axil_mst_if.awvalid = (wr_state == W_ISSUE) && wr_wpend;
assign axil_mst_if.wdata   = wr_wdata_q;
assign axil_mst_if.wstrb   = wr_wstrb_q;
assign axil_mst_if.wvalid  = (wr_state == W_ISSUE) && wr_wpend;
assign axil_mst_if.bready  = (wr_state == W_BRESP);

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
always_ff @(posedge aclk or negedge aresetn) begin
   if (!aresetn)
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
         if (axi_slv_if.arvalid)
            rd_nstate = R_ISSUE;
         else
            rd_nstate = R_IDLE;
      end

      R_ISSUE:
      begin
         if (axil_mst_if.arready)
            rd_nstate = R_WAIT;
         else
            rd_nstate = R_ISSUE;
      end

      R_WAIT:
      begin
         if (axil_mst_if.rvalid)
            rd_nstate = R_PRESENT;
         else
            rd_nstate = R_WAIT;
      end

      R_PRESENT:
      begin
         if (axi_slv_if.rready && rd_dvalid && rd_last)
            rd_nstate = R_IDLE;
         else if (axi_slv_if.rready && rd_dvalid)
            rd_nstate = R_ISSUE;
         else
            rd_nstate = R_PRESENT;
      end
   endcase
end

// data registers
always_ff @(posedge aclk or negedge aresetn) begin
   if (!aresetn) begin
      rd_addr  <= '0;
      rd_len   <= '0;
      rd_size  <= '0;
      rd_burst <= '0;
      rd_id    <= '0;
      rd_prot  <= '0;
   end else if (rd_state == R_IDLE && axi_slv_if.arvalid) begin
      rd_addr  <= axi_slv_if.araddr;
      rd_len   <= axi_slv_if.arlen;
      rd_size  <= axi_slv_if.arsize;
      rd_burst <= axi_slv_if.arburst;
      rd_id    <= axi_slv_if.arid;
      rd_prot  <= axi_slv_if.arprot;
   end
end

always_ff @(posedge aclk or negedge aresetn) begin
   if (!aresetn) begin
      rd_rdata_q <= '0;
      rd_rresp_q <= 2'b00;
   end else if (rd_state == R_WAIT && axil_mst_if.rvalid) begin
      rd_rdata_q <= axil_mst_if.rdata;
      rd_rresp_q <= axil_mst_if.rresp;
   end
end

always_ff @(posedge aclk or negedge aresetn) begin
   if (!aresetn)
      rd_beat <= '0;
   else if (rd_state == R_IDLE && axi_slv_if.arvalid)
      rd_beat <= '0;
   else if (rd_state == R_PRESENT && axi_slv_if.rready && rd_dvalid && !rd_last)
      rd_beat <= rd_beat + 1'b1;
end

always_ff @(posedge aclk or negedge aresetn) begin
   if (!aresetn)
      rd_dvalid <= 1'b0;
   else if (rd_state == R_IDLE && axi_slv_if.arvalid)
      rd_dvalid <= 1'b0;
   else if (rd_state == R_WAIT && axil_mst_if.rvalid)
      rd_dvalid <= 1'b1;
   else if (rd_state == R_PRESENT && axi_slv_if.rready && rd_dvalid)
      rd_dvalid <= 1'b0;
end

// axi-slave interface assigns
assign rd_beat_addr = calc_beat_addr(rd_addr, rd_len, rd_size, rd_burst, rd_beat);
assign rd_last = (rd_beat >= rd_len);

assign axi_slv_if.arready = (rd_state == R_IDLE);
assign axi_slv_if.rvalid  = rd_dvalid;
assign axi_slv_if.rdata   = rd_rdata_q;
assign axi_slv_if.rresp   = rd_rresp_q;
assign axi_slv_if.rid     = rd_id;
assign axi_slv_if.rlast   = rd_dvalid && rd_last;

// axil-master interface assigns
assign axil_mst_if.araddr  = rd_beat_addr;
assign axil_mst_if.arprot  = rd_prot;
assign axil_mst_if.arvalid = (rd_state == R_ISSUE);
assign axil_mst_if.rready  = (rd_state == R_WAIT);

endmodule

`resetall
