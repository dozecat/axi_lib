//*****************************************************************************
// Copyright (C) 2026 dozecat. All rights reserved.
// SPDX-License-Identifier: MIT
//
// File:        axil2reg_bridge.sv
// Description: AXI4-Lite to Register File Bridge
// Repository:  https://github.com/dozecat/axi_lib.git
//
// Converts AXI4-Lite single-beat transactions into a generic register file
// handshake interface. Supports word-aligned read/write with byte strobes.
// Write has priority for the shared register port.
//
// Modification History:
// Ver   Who       Date        Changes
// ----  ----  ----------  ----------------------------------------------------
// 1.0         2026/5/7    Initial release
//*****************************************************************************
`timescale 1ns / 1ps
`default_nettype none

module axil2reg_bridge (
   input  wire                    clk,
   input  wire                    rst,

   if_axil.slave                  s_axil_if,

   output wire [ADDR_WIDTH-1:0]   reg_addr,
   output wire [DATA_WIDTH-1:0]   reg_wr_data,
   output wire [STRB_WIDTH-1:0]   reg_wr_mask,
   input  wire [DATA_WIDTH-1:0]   reg_rd_data,
   output wire                    reg_wr_req,
   output wire                    reg_rd_req,
   input  wire                    reg_busy,
   input  wire                    reg_ack
);

localparam ADDR_WIDTH = s_axil_if.ADDR_WIDTH;
localparam DATA_WIDTH = s_axil_if.DATA_WIDTH;
localparam STRB_WIDTH = DATA_WIDTH / 8;

localparam RESP_WIDTH = 2;

initial begin
   if (DATA_WIDTH != 32 && DATA_WIDTH != 64)
      $error("axil2reg_bridge: DATA_WIDTH must be 32 or 64, got %0d", DATA_WIDTH);
end

//*****************************************************************************
// Shared register port mutex
//*****************************************************************************
wire reg_port_active;

assign reg_port_active = (w_state == W_ISSUE) || (r_state == R_ISSUE);

//*****************************************************************************
// Register interface drive (write has priority)
//*****************************************************************************
always_comb begin
   if (w_state == W_ISSUE)
      reg_wr_req = 1'b1;
   else
      reg_wr_req = 1'b0;
end

always_comb begin
   if (r_state == R_ISSUE)
      reg_rd_req = 1'b1;
   else
      reg_rd_req = 1'b0;
end

always_comb begin
   if (w_state == W_ISSUE)
      reg_addr = w_addr;
   else if (r_state == R_ISSUE)
      reg_addr = r_addr;
   else
      reg_addr = '0;
end

always_comb begin
   if (w_state == W_ISSUE)
      reg_wr_data = w_data;
   else
      reg_wr_data = '0;
end

always_comb begin
   if (w_state == W_ISSUE)
      reg_wr_mask = w_strb;
   else
      reg_wr_mask = '0;
end

//*****************************************************************************
// Write channel
//*****************************************************************************
reg  [ADDR_WIDTH       -1:0]  w_addr;
reg  [2:0]                    w_prot;
reg  [DATA_WIDTH       -1:0]  w_data;
reg  [STRB_WIDTH       -1:0]  w_strb;

enum logic [1:0] {
   W_IDLE  = 0,
   W_WAIT  = 1,
   W_ISSUE = 2,
   W_RESP  = 3
} w_state, w_nstate;

always_ff @(posedge clk or posedge rst) begin
   if (rst)
      w_state <= W_IDLE;
   else
      w_state <= w_nstate;
end

always_comb begin
   w_nstate = w_state;
   case (w_state)
      W_IDLE:
      begin
         if (s_axil_if.awvalid && !reg_port_active) begin
            if (s_axil_if.wvalid)
               w_nstate = W_ISSUE;
            else
               w_nstate = W_WAIT;
         end
      end

      W_WAIT:
      begin
         if (s_axil_if.wvalid && !reg_port_active)
            w_nstate = W_ISSUE;
      end

      W_ISSUE:
      begin
         if (reg_ack)
            w_nstate = W_RESP;
      end

      W_RESP:
      begin
         if (s_axil_if.bready)
            w_nstate = W_IDLE;
      end

      default: w_nstate = W_IDLE;
   endcase
end

always_ff @(posedge clk or posedge rst) begin
   if (rst) begin
      w_addr <= '0;
      w_prot <= '0;
   end else if (w_state == W_IDLE && s_axil_if.awvalid && !reg_port_active) begin
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

assign s_axil_if.awready = (w_state == W_IDLE) && !reg_port_active;
assign s_axil_if.wready  = (w_state == W_IDLE) ||
                           (w_state == W_WAIT && !reg_port_active);
assign s_axil_if.bvalid  = (w_state == W_RESP);
assign s_axil_if.bresp   = {RESP_WIDTH{1'b0}};

//*****************************************************************************
// Read channel
//*****************************************************************************
reg  [ADDR_WIDTH       -1:0]  r_addr;
reg  [2:0]                    r_prot;
reg  [DATA_WIDTH       -1:0]  r_data;

enum logic [1:0] {
   R_IDLE  = 0,
   R_ISSUE = 1,
   R_RESP  = 2
} r_state, r_nstate;

always_ff @(posedge clk or posedge rst) begin
   if (rst)
      r_state <= R_IDLE;
   else
      r_state <= r_nstate;
end

always_comb begin
   r_nstate = r_state;
   case (r_state)
      R_IDLE:
      begin
         if (s_axil_if.arvalid && !reg_port_active)
            r_nstate = R_ISSUE;
      end

      R_ISSUE:
      begin
         if (reg_ack)
            r_nstate = R_RESP;
      end

      R_RESP:
      begin
         if (s_axil_if.rready)
            r_nstate = R_IDLE;
      end

      default: r_nstate = R_IDLE;
   endcase
end

always_ff @(posedge clk or posedge rst) begin
   if (rst) begin
      r_addr <= '0;
      r_prot <= '0;
   end else if (r_state == R_IDLE && s_axil_if.arvalid && !reg_port_active) begin
      r_addr <= s_axil_if.araddr;
      r_prot <= s_axil_if.arprot;
   end
end

always_ff @(posedge clk or posedge rst) begin
   if (rst)
      r_data <= '0;
   else if (r_state == R_ISSUE && reg_ack)
      r_data <= reg_rd_data;
end

assign s_axil_if.arready = (r_state == R_IDLE) && !reg_port_active;
assign s_axil_if.rvalid  = (r_state == R_RESP);
assign s_axil_if.rdata   = r_data;
assign s_axil_if.rresp   = {RESP_WIDTH{1'b0}};

endmodule

`resetall
