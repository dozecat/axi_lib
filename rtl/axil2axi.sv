//*****************************************************************************
// Copyright (C) 2026 dozecat. All rights reserved.
// SPDX-License-Identifier: MIT
//
// File:        axil2axi.sv
// Description: AXI4-Lite to AXI4 Bridge
// Repository:  https://github.com/dozecat/axi_lib.git
//
// Converts AXI4-Lite single-beat transactions into AXI4 single-beat
// transactions (len=0, burst=FIXED). AXI4-Lite signals without direct
// AXI4-Lite equivalents (ID, burst, cache, etc.) are set to default values.
// Single outstanding transaction; processes one beat at a time.
//
// Modification History:
// Ver   Who       Date        Changes
// ----  ----  ----------  ----------------------------------------------------
// 1.0         2026/5/4    Initial release
//*****************************************************************************
`timescale 1ns / 1ps
`default_nettype none

module axil2axi (
   input  wire                clk,
   input  wire                rst,

   if_axil.slave              s_axil_if,
   if_axi.master              m_axi_if
);

localparam ADDR_WIDTH  = s_axil_if.ADDR_WIDTH;
localparam DATA_WIDTH  = s_axil_if.DATA_WIDTH;
localparam ID_WIDTH    = m_axi_if.ID_WIDTH;
localparam STRB_WIDTH  = DATA_WIDTH / 8;

localparam LEN_WIDTH   = 8;
localparam SIZE_WIDTH  = 3;
localparam PROT_WIDTH  = 3;
localparam RESP_WIDTH  = 2;
localparam BURST_WIDTH = 2;

// calculate AXI AW/AR size (bytes per beat)
localparam SIZE_VAL = $clog2(STRB_WIDTH);

initial begin
   if (DATA_WIDTH != 32 && DATA_WIDTH != 64)
      $error("axil2axi: DATA_WIDTH must be 32 or 64, got %0d", DATA_WIDTH);
   if (s_axil_if.ADDR_WIDTH != m_axi_if.ADDR_WIDTH)
      $error("axil2axi: ADDR_WIDTH mismatch (%0d vs %0d)",
             s_axil_if.ADDR_WIDTH, m_axi_if.ADDR_WIDTH);
   if (s_axil_if.DATA_WIDTH != m_axi_if.DATA_WIDTH)
      $error("axil2axi: DATA_WIDTH mismatch (%0d vs %0d)",
             s_axil_if.DATA_WIDTH, m_axi_if.DATA_WIDTH);
end

//*****************************************************************************
// Write channel
//*****************************************************************************
// write path signals
reg   [ADDR_WIDTH       -1:0]    w_addr;
reg   [PROT_WIDTH       -1:0]    w_prot;
reg   [DATA_WIDTH       -1:0]    w_data;
reg   [STRB_WIDTH       -1:0]    w_strb;
reg   [RESP_WIDTH       -1:0]    w_resp;

// Write path FSM — three-stage
enum logic [1:0] {
   W_IDLE  = 0,
   W_WAIT  = 1,   // AW received, wait for W
   W_ISSUE = 2,   // issue AXI4 AW+W
   W_BRESP = 3    // wait for AXI4 B
} w_state, w_nstate;

// state register
always_ff @(posedge clk or posedge rst) begin
   if (rst)
      w_state <= W_IDLE;
   else
      w_state <= w_nstate;
end

// next state
always_comb begin
   w_nstate = w_state;
   case (w_state)
      W_IDLE:
      begin
         if (s_axil_if.awvalid && s_axil_if.wvalid)
            w_nstate = W_ISSUE;
         else if (s_axil_if.awvalid)
            w_nstate = W_WAIT;
         else
            w_nstate = W_IDLE;
      end

      W_WAIT:
      begin
         if (s_axil_if.wvalid)
            w_nstate = W_ISSUE;
         else
            w_nstate = W_WAIT;
      end

      W_ISSUE:
      begin
         if (m_axi_if.awready && m_axi_if.wready)
            w_nstate = W_BRESP;
         else
            w_nstate = W_ISSUE;
      end

      W_BRESP:
      begin
         if (m_axi_if.bvalid)
            w_nstate = W_IDLE;
         else
            w_nstate = W_BRESP;
      end
   endcase
end

// data registers
always_ff @(posedge clk or posedge rst) begin
   if (rst) begin
      w_addr <= '0;
      w_prot <= '0;
   end else if (w_state == W_IDLE && s_axil_if.awvalid) begin
      w_addr <= s_axil_if.awaddr;
      w_prot <= s_axil_if.awprot;
   end
end

always_ff @(posedge clk or posedge rst) begin
   if (rst) begin
      w_data <= '0;
      w_strb <= '0;
   end else if ((w_state == W_IDLE && s_axil_if.wvalid) ||
                (w_state == W_WAIT && s_axil_if.wvalid)) begin
      w_data <= s_axil_if.wdata;
      w_strb <= s_axil_if.wstrb;
   end
end

always_ff @(posedge clk or posedge rst) begin
   if (rst)
      w_resp <= 2'b00;
   else if (w_state == W_BRESP && m_axi_if.bvalid)
      w_resp <= m_axi_if.bresp;
end

// axi-lite slave interface assigns
assign s_axil_if.awready = (w_state == W_IDLE);
assign s_axil_if.wready  = (w_state == W_IDLE) || (w_state == W_WAIT);
assign s_axil_if.bvalid  = (w_state == W_BRESP) && m_axi_if.bvalid;
assign s_axil_if.bresp   = (w_state == W_BRESP) ? m_axi_if.bresp : 2'b00;

// axi master interface assigns
assign m_axi_if.awaddr   = w_addr;
assign m_axi_if.awprot   = w_prot;
assign m_axi_if.awvalid  = (w_state == W_ISSUE);
assign m_axi_if.awlen    = 8'd0;
assign m_axi_if.awsize   = SIZE_VAL;
assign m_axi_if.awburst  = 2'b00;  // FIXED
assign m_axi_if.awcache  = 4'd0;
assign m_axi_if.awlock   = 1'b0;
assign m_axi_if.awqos    = 4'd0;
assign m_axi_if.awregion = 4'd0;
assign m_axi_if.awid     = {ID_WIDTH{1'b0}};

assign m_axi_if.wdata    = w_data;
assign m_axi_if.wstrb    = w_strb;
assign m_axi_if.wvalid   = (w_state == W_ISSUE);
assign m_axi_if.wlast    = 1'b1;
assign m_axi_if.wid      = {ID_WIDTH{1'b0}};

assign m_axi_if.bready   = (w_state == W_BRESP);

//*****************************************************************************
// Read channel
//*****************************************************************************
// read path signals
reg   [ADDR_WIDTH       -1:0]    r_addr;
reg   [PROT_WIDTH       -1:0]    r_prot;
reg   [DATA_WIDTH       -1:0]    r_data;
reg   [RESP_WIDTH       -1:0]    r_resp;
reg                              r_dvalid;

// Read path FSM — three-stage
enum logic [1:0] {
   R_IDLE    = 0,
   R_ISSUE   = 1,
   R_WAIT    = 2,
   R_PRESENT = 3
} r_state, r_nstate;

// state register
always_ff @(posedge clk or posedge rst) begin
   if (rst)
      r_state <= R_IDLE;
   else
      r_state <= r_nstate;
end

// next state
always_comb begin
   r_nstate = r_state;
   case (r_state)
      R_IDLE:
      begin
         if (s_axil_if.arvalid)
            r_nstate = R_ISSUE;
         else
            r_nstate = R_IDLE;
      end

      R_ISSUE:
      begin
         if (m_axi_if.arready)
            r_nstate = R_WAIT;
         else
            r_nstate = R_ISSUE;
      end

      R_WAIT:
      begin
         if (m_axi_if.rvalid)
            r_nstate = R_PRESENT;
         else
            r_nstate = R_WAIT;
      end

      R_PRESENT:
      begin
         if (s_axil_if.rready && r_dvalid)
            r_nstate = R_IDLE;
         else
            r_nstate = R_PRESENT;
      end
   endcase
end

// data registers
always_ff @(posedge clk or posedge rst) begin
   if (rst) begin
      r_addr <= '0;
      r_prot <= '0;
   end else if (r_state == R_IDLE && s_axil_if.arvalid) begin
      r_addr <= s_axil_if.araddr;
      r_prot <= s_axil_if.arprot;
   end
end

always_ff @(posedge clk or posedge rst) begin
   if (rst) begin
      r_data  <= '0;
      r_resp  <= 2'b00;
      r_dvalid <= 1'b0;
   end else if (r_state == R_WAIT && m_axi_if.rvalid) begin
      r_data   <= m_axi_if.rdata;
      r_resp   <= m_axi_if.rresp;
      r_dvalid <= 1'b1;
   end else if (r_state == R_PRESENT && s_axil_if.rready && r_dvalid) begin
      r_dvalid <= 1'b0;
   end
end

// axi-lite slave interface assigns
assign s_axil_if.arready = (r_state == R_IDLE);
assign s_axil_if.rvalid  = r_dvalid;
assign s_axil_if.rdata   = r_data;
assign s_axil_if.rresp   = r_resp;

// axi master interface assigns
assign m_axi_if.araddr   = r_addr;
assign m_axi_if.arprot   = r_prot;
assign m_axi_if.arvalid  = (r_state == R_ISSUE);
assign m_axi_if.arlen    = 8'd0;
assign m_axi_if.arsize   = SIZE_VAL;
assign m_axi_if.arburst  = 2'b00;  // FIXED
assign m_axi_if.arcache  = 4'd0;
assign m_axi_if.arlock   = 1'b0;
assign m_axi_if.arqos    = 4'd0;
assign m_axi_if.arregion = 4'd0;
assign m_axi_if.arid     = {ID_WIDTH{1'b0}};

assign m_axi_if.rready   = (r_state == R_WAIT);

endmodule

`resetall
