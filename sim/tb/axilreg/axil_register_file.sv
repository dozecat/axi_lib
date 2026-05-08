//*****************************************************************************
// Copyright (C) 2026 dozecat. All rights reserved.
// SPDX-License-Identifier: MIT
//
// File:        axil_register_file.sv
// Description: AXI4-Lite to Register File Bridge with Register Decode
// Repository:  https://github.com/dozecat/axi_lib.git
//
// Modification History:
// Ver   Who       Date        Changes
// ----  ----  ----------  ----------------------------------------------------
// 1.0         2026/5/7    Initial release
// 1.1         2026/5/8    Simplify: remove redundant bus protocol layer
//*****************************************************************************
`timescale 1ns / 1ps
`default_nettype none

module axil_register_file (
   input  wire                    clk,
   input  wire                    rst,

   if_axil.slave                  s_axil_if,

   input  wire [31:0]             reg_test1,
   output reg [31:0]              reg_test2
);

localparam ADDR_WIDTH = s_axil_if.ADDR_WIDTH;
localparam DATA_WIDTH = s_axil_if.DATA_WIDTH;
localparam STRB_WIDTH = DATA_WIDTH / 8;

localparam REG_TEST1_OFFSET = 3'b000;
localparam REG_TEST2_OFFSET = 3'b001;

// Address bit offset for word-aligned access
localparam ADDR_LSB = $clog2(DATA_WIDTH / 8);

//*****************************************************************************
// Bridge instance
//*****************************************************************************
wire [ADDR_WIDTH-1:0] reg_addr;
wire [DATA_WIDTH-1:0] reg_wr_data;
wire [STRB_WIDTH-1:0] reg_wr_mask;
logic [DATA_WIDTH-1:0] reg_rd_data;
wire                   reg_wr_req;
wire                   reg_rd_req;
logic                  reg_busy;
logic                  reg_ack;

axil2reg_bridge bridge_inst (
   .clk         ( clk          ),
   .rst         ( rst          ),
   .s_axil_if   ( s_axil_if    ),
   .reg_addr    ( reg_addr     ),
   .reg_wr_data ( reg_wr_data  ),
   .reg_wr_mask ( reg_wr_mask  ),
   .reg_rd_data ( reg_rd_data  ),
   .reg_wr_req  ( reg_wr_req   ),
   .reg_rd_req  ( reg_rd_req   ),
   .reg_busy    ( reg_busy     ),
   .reg_ack     ( reg_ack      )
);

//*****************************************************************************
// Register decode — direct handshake with axil2reg_bridge
//*****************************************************************************

// Write decode
always @(posedge clk or posedge rst) begin
   if (rst)
      reg_test2 <= '0;
   else if (reg_wr_req)
      unique case (reg_addr[ADDR_LSB +: 3])
         REG_TEST2_OFFSET: reg_test2 <= reg_wr_data;
         default: ;
      endcase
end

// Read decode
always @(posedge clk or posedge rst) begin
   if (rst)
      reg_rd_data <= '0;
   else if (reg_rd_req)
      unique case (reg_addr[ADDR_LSB +: 3])
         REG_TEST1_OFFSET: reg_rd_data <= reg_test1;
         REG_TEST2_OFFSET: reg_rd_data <= reg_test2;
         default:         reg_rd_data <= 32'hDEADBEEF;
      endcase
end

// Ack 1 cycle after request (pipeline latency)
reg reg_wr_req_d1;
reg reg_rd_req_d1;

always @(posedge clk or posedge rst) begin
   if (rst) begin
      reg_wr_req_d1 <= '0;
      reg_rd_req_d1 <= '0;
   end else begin
      reg_wr_req_d1 <= reg_wr_req;
      reg_rd_req_d1 <= reg_rd_req;
   end
end

assign reg_ack  = reg_wr_req_d1 || reg_rd_req_d1;
assign reg_busy = 1'b0;

endmodule

`resetall
