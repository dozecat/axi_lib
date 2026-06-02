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
   input  logic                     clk,
   input  logic                     rst,

   if_axil.slave                    s_axil_if,

   output logic [7:0]               reg_test0,
   input  logic [31:0]              reg_test1,
   output logic [31:0]              reg_test2,
   output logic [15:0]              reg_test3
);

//*****************************************************************************
// localparam
//*****************************************************************************
localparam ADDR_WIDTH = s_axil_if.ADDR_WIDTH;
localparam DATA_WIDTH = s_axil_if.DATA_WIDTH;
localparam STRB_WIDTH = DATA_WIDTH / 8;

//*****************************************************************************
// Bridge instance
//*****************************************************************************
logic [ADDR_WIDTH       -1:0]    reg_addr;
logic [DATA_WIDTH       -1:0]    reg_wr_data;
logic [STRB_WIDTH       -1:0]    reg_wr_mask;
logic [DATA_WIDTH       -1:0]    reg_rd_data;
logic                            reg_wr_req;
logic                            reg_rd_req;
logic                            reg_busy;
logic                            reg_ack;

axil2reg_bridge bridge_inst
(
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

//*****************************************************************************
// Register decode — direct handshake with axil2reg_bridge
//*****************************************************************************
// Write decode
always @(posedge clk or posedge rst) begin
   if (rst) begin
      reg_test0 <= 8'h0;
      reg_test2 <= 32'h0;
      reg_test3 <= 16'h1;
   end else if (reg_wr_req) begin
      unique case (reg_addr)
         'h00: reg_test0 <= reg_wr_data[7:0];
         'h08: reg_test2 <= reg_wr_data;
         'h0c: reg_test3 <= reg_wr_data[15:0];
         default: ;
      endcase
   end
end

// Read decode
always @(posedge clk or posedge rst) begin
   if (rst)
      reg_rd_data <= '0;
   else if (reg_rd_req)
      unique case (reg_addr)
         'h00: reg_rd_data <= {24'h0, reg_test0};
         'h04: reg_rd_data <= reg_test1;
         'h08: reg_rd_data <= reg_test2;
         'h0c: reg_rd_data <= {16'h0, reg_test3};
         default: reg_rd_data <= 32'hdeadbeef;
      endcase
end

endmodule

`resetall
