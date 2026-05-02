//*****************************************************************************
// Copyright (C) 2025 dozecat. All rights reserved.
// SPDX-License-Identifier: MIT
// 
// File:        axil_interconnect_tb.sv
// Description: AXI4-Lite Interconnect Testbench Wrapper
// Repository:  https://github.com/dozecat/axi_lib.git
// 
// Modification History:
// Ver   Who       Date        Changes
// ----  ----  ----------  ----------------------------------------------------
// 1.0         2025/12/25  Initial release
//*****************************************************************************

`timescale 1ns / 1ps

module axil_interconnect_tb
#(
   parameter DATA_WIDTH          = 32,
   parameter ADDR_WIDTH          = 16,
   parameter STRB_WIDTH          = DATA_WIDTH / 8
)(
   input  wire                    clk,
   input  wire                    rst_n,

   // Slave port 0 (master BFM 0)
   input  wire                    slv0_awvalid,
   output logic                   slv0_awready,
   input  wire  [ADDR_WIDTH -1:0] slv0_awaddr,
   input  wire  [2          -1:0] slv0_awprot,
   input  wire                    slv0_wvalid,
   output logic                   slv0_wready,
   input  wire  [DATA_WIDTH -1:0] slv0_wdata,
   input  wire  [STRB_WIDTH -1:0] slv0_wstrb,
   output logic                   slv0_bvalid,
   input  wire                    slv0_bready,
   output logic [1:0] slv0_bresp,
   input  wire                    slv0_arvalid,
   output logic                   slv0_arready,
   input  wire  [ADDR_WIDTH -1:0] slv0_araddr,
   input  wire  [2          -1:0] slv0_arprot,
   output logic                   slv0_rvalid,
   input  wire                    slv0_rready,
   output logic [DATA_WIDTH -1:0] slv0_rdata,
   output logic [1:0] slv0_rresp,

   // Slave port 1 (master BFM 1)
   input  wire                    slv1_awvalid,
   output logic                   slv1_awready,
   input  wire  [ADDR_WIDTH -1:0] slv1_awaddr,
   input  wire  [2          -1:0] slv1_awprot,
   input  wire                    slv1_wvalid,
   output logic                   slv1_wready,
   input  wire  [DATA_WIDTH -1:0] slv1_wdata,
   input  wire  [STRB_WIDTH -1:0] slv1_wstrb,
   output logic                   slv1_bvalid,
   input  wire                    slv1_bready,
   output logic [1:0] slv1_bresp,
   input  wire                    slv1_arvalid,
   output logic                   slv1_arready,
   input  wire  [ADDR_WIDTH -1:0] slv1_araddr,
   input  wire  [2           -1:0] slv1_arprot,
   output logic                   slv1_rvalid,
   input  wire                    slv1_rready,
   output logic [DATA_WIDTH -1:0] slv1_rdata,
   output logic [1:0] slv1_rresp,

   // Slave port 2 (master BFM 2)
   input  wire                    slv2_awvalid,
   output logic                   slv2_awready,
   input  wire  [ADDR_WIDTH -1:0] slv2_awaddr,
   input  wire  [2          -1:0] slv2_awprot,
   input  wire                    slv2_wvalid,
   output logic                   slv2_wready,
   input  wire  [DATA_WIDTH -1:0] slv2_wdata,
   input  wire  [STRB_WIDTH -1:0] slv2_wstrb,
   output logic                   slv2_bvalid,
   input  wire                    slv2_bready,
   output logic [1:0] slv2_bresp,
   input  wire                    slv2_arvalid,
   output logic                   slv2_arready,
   input  wire  [ADDR_WIDTH -1:0] slv2_araddr,
   input  wire  [2          -1:0] slv2_arprot,
   output logic                   slv2_rvalid,
   input  wire                    slv2_rready,
   output logic [DATA_WIDTH -1:0] slv2_rdata,
   output logic [1:0] slv2_rresp,

   // Slave port 3 (master BFM 3)
   input  wire                    slv3_awvalid,
   output logic                   slv3_awready,
   input  wire  [ADDR_WIDTH -1:0] slv3_awaddr,
   input  wire  [2          -1:0] slv3_awprot,
   input  wire                    slv3_wvalid,
   output logic                   slv3_wready,
   input  wire  [DATA_WIDTH -1:0] slv3_wdata,
   input  wire  [STRB_WIDTH -1:0] slv3_wstrb,
   output logic                   slv3_bvalid,
   input  wire                    slv3_bready,
   output logic [1:0] slv3_bresp,
   input  wire                    slv3_arvalid,
   output logic                   slv3_arready,
   input  wire  [ADDR_WIDTH -1:0] slv3_araddr,
   input  wire  [2          -1:0] slv3_arprot,
   output logic                   slv3_rvalid,
   input  wire                    slv3_rready,
   output logic [DATA_WIDTH -1:0] slv3_rdata,
output logic [1:0] slv3_rresp,

   // Master port 0 (slave BFM 0)
   output logic                   mst0_awvalid,
   input  wire                    mst0_awready,
   output logic [ADDR_WIDTH -1:0] mst0_awaddr,
   output logic [2          -1:0] mst0_awprot,
   output logic                   mst0_wvalid,
   input  wire                    mst0_wready,
   output logic [DATA_WIDTH -1:0] mst0_wdata,
   output logic [STRB_WIDTH -1:0] mst0_wstrb,
   input  wire                    mst0_bvalid,
   output logic                   mst0_bready,
   input  wire  [1:0] mst0_bresp,
   output logic                   mst0_arvalid,
   input  wire                    mst0_arready,
   output logic [ADDR_WIDTH -1:0] mst0_araddr,
   output logic [2          -1:0] mst0_arprot,
   input  wire                    mst0_rvalid,
   output logic                   mst0_rready,
   input  wire  [DATA_WIDTH -1:0] mst0_rdata,
   input  wire  [1:0] mst0_rresp,

   // Master port 1 (slave BFM 1)
   output logic                   mst1_awvalid,
   input  wire                    mst1_awready,
   output logic [ADDR_WIDTH -1:0] mst1_awaddr,
   output logic [2          -1:0] mst1_awprot,
   output logic                   mst1_wvalid,
   input  wire                    mst1_wready,
   output logic [DATA_WIDTH -1:0] mst1_wdata,
   output logic [STRB_WIDTH -1:0] mst1_wstrb,
   input  wire                    mst1_bvalid,
   output logic                   mst1_bready,
   input  wire  [1:0] mst1_bresp,
   output logic                   mst1_arvalid,
   input  wire                    mst1_arready,
   output logic [ADDR_WIDTH -1:0] mst1_araddr,
   output logic [2          -1:0] mst1_arprot,
   input  wire                    mst1_rvalid,
   output logic                   mst1_rready,
   input  wire  [DATA_WIDTH -1:0] mst1_rdata,
   input  wire  [1:0] mst1_rresp,

   // Master port 2 (slave BFM 2)
   output logic                   mst2_awvalid,
   input  wire                    mst2_awready,
   output logic [ADDR_WIDTH -1:0] mst2_awaddr,
   output logic [2          -1:0] mst2_awprot,
   output logic                   mst2_wvalid,
   input  wire                    mst2_wready,
   output logic [DATA_WIDTH -1:0] mst2_wdata,
   output logic [STRB_WIDTH -1:0] mst2_wstrb,
   input  wire                    mst2_bvalid,
   output logic                   mst2_bready,
   input  wire  [1:0] mst2_bresp,
   output logic                   mst2_arvalid,
   input  wire                    mst2_arready,
   output logic [ADDR_WIDTH -1:0] mst2_araddr,
   output logic [2          -1:0] mst2_arprot,
   input  wire                    mst2_rvalid,
   output logic                   mst2_rready,
   input  wire  [DATA_WIDTH -1:0] mst2_rdata,
   input  wire  [1:0] mst2_rresp,

   // Master port 3 (slave BFM 3)
   output logic                   mst3_awvalid,
   input  wire                    mst3_awready,
   output logic [ADDR_WIDTH -1:0] mst3_awaddr,
   output logic [2          -1:0] mst3_awprot,
   output logic                   mst3_wvalid,
   input  wire                    mst3_wready,
   output logic [DATA_WIDTH -1:0] mst3_wdata,
   output logic [STRB_WIDTH -1:0] mst3_wstrb,
   input  wire                    mst3_bvalid,
   output logic                   mst3_bready,
   input  wire  [1:0] mst3_bresp,
   output logic                   mst3_arvalid,
   input  wire                    mst3_arready,
   output logic [ADDR_WIDTH -1:0] mst3_araddr,
   output logic [2          -1:0] mst3_arprot,
   input  wire                    mst3_rvalid,
   output logic                   mst3_rready,
   input  wire  [DATA_WIDTH -1:0] mst3_rdata,
   input  wire  [1:0] mst3_rresp
);

// Interface instances
if_axil #(.ADDR_WIDTH(ADDR_WIDTH),
          .DATA_WIDTH(DATA_WIDTH)) axil_slv_if [0:3] ();

if_axil #(.ADDR_WIDTH(ADDR_WIDTH),
         .DATA_WIDTH(DATA_WIDTH)) axil_mst_if [0:3] ();

// Slave port 0 -> axil_slv_if[0]
assign axil_slv_if[0].awvalid = slv0_awvalid;
assign axil_slv_if[0].awaddr  = slv0_awaddr;
assign axil_slv_if[0].awprot  = slv0_awprot;
assign axil_slv_if[0].wvalid  = slv0_wvalid;
assign axil_slv_if[0].wdata   = slv0_wdata;
assign axil_slv_if[0].wstrb   = slv0_wstrb;
assign axil_slv_if[0].bready  = slv0_bready;
assign axil_slv_if[0].arvalid = slv0_arvalid;
assign axil_slv_if[0].araddr  = slv0_araddr;
assign axil_slv_if[0].arprot  = slv0_arprot;
assign axil_slv_if[0].rready  = slv0_rready;
assign slv0_awready = axil_slv_if[0].awready;
assign slv0_wready  = axil_slv_if[0].wready;
assign slv0_bvalid  = axil_slv_if[0].bvalid;
assign slv0_bresp   = axil_slv_if[0].bresp;
assign slv0_arready = axil_slv_if[0].arready;
assign slv0_rvalid  = axil_slv_if[0].rvalid;
assign slv0_rdata   = axil_slv_if[0].rdata;
assign slv0_rresp   = axil_slv_if[0].rresp;

// Slave port 1 -> axil_slv_if[1]
assign axil_slv_if[1].awvalid = slv1_awvalid;
assign axil_slv_if[1].awaddr  = slv1_awaddr;
assign axil_slv_if[1].awprot  = slv1_awprot;
assign axil_slv_if[1].wvalid  = slv1_wvalid;
assign axil_slv_if[1].wdata   = slv1_wdata;
assign axil_slv_if[1].wstrb   = slv1_wstrb;
assign axil_slv_if[1].bready  = slv1_bready;
assign axil_slv_if[1].arvalid = slv1_arvalid;
assign axil_slv_if[1].araddr  = slv1_araddr;
assign axil_slv_if[1].arprot  = slv1_arprot;
assign axil_slv_if[1].rready  = slv1_rready;
assign slv1_awready = axil_slv_if[1].awready;
assign slv1_wready  = axil_slv_if[1].wready;
assign slv1_bvalid  = axil_slv_if[1].bvalid;
assign slv1_bresp   = axil_slv_if[1].bresp;
assign slv1_arready = axil_slv_if[1].arready;
assign slv1_rvalid  = axil_slv_if[1].rvalid;
assign slv1_rdata   = axil_slv_if[1].rdata;
assign slv1_rresp   = axil_slv_if[1].rresp;

// Slave port 2 -> axil_slv_if[2]
assign axil_slv_if[2].awvalid = slv2_awvalid;
assign axil_slv_if[2].awaddr  = slv2_awaddr;
assign axil_slv_if[2].awprot  = slv2_awprot;
assign axil_slv_if[2].wvalid  = slv2_wvalid;
assign axil_slv_if[2].wdata   = slv2_wdata;
assign axil_slv_if[2].wstrb   = slv2_wstrb;
assign axil_slv_if[2].bready  = slv2_bready;
assign axil_slv_if[2].arvalid = slv2_arvalid;
assign axil_slv_if[2].araddr  = slv2_araddr;
assign axil_slv_if[2].arprot  = slv2_arprot;
assign axil_slv_if[2].rready  = slv2_rready;
assign slv2_awready = axil_slv_if[2].awready;
assign slv2_wready  = axil_slv_if[2].wready;
assign slv2_bvalid  = axil_slv_if[2].bvalid;
assign slv2_bresp   = axil_slv_if[2].bresp;
assign slv2_arready = axil_slv_if[2].arready;
assign slv2_rvalid  = axil_slv_if[2].rvalid;
assign slv2_rdata   = axil_slv_if[2].rdata;
assign slv2_rresp   = axil_slv_if[2].rresp;

// Slave port 3 -> axil_slv_if[3]
assign axil_slv_if[3].awvalid = slv3_awvalid;
assign axil_slv_if[3].awaddr  = slv3_awaddr;
assign axil_slv_if[3].awprot  = slv3_awprot;
assign axil_slv_if[3].wvalid  = slv3_wvalid;
assign axil_slv_if[3].wdata   = slv3_wdata;
assign axil_slv_if[3].wstrb   = slv3_wstrb;
assign axil_slv_if[3].bready  = slv3_bready;
assign axil_slv_if[3].arvalid = slv3_arvalid;
assign axil_slv_if[3].araddr  = slv3_araddr;
assign axil_slv_if[3].arprot  = slv3_arprot;
assign axil_slv_if[3].rready  = slv3_rready;
assign slv3_awready = axil_slv_if[3].awready;
assign slv3_wready  = axil_slv_if[3].wready;
assign slv3_bvalid  = axil_slv_if[3].bvalid;
assign slv3_bresp   = axil_slv_if[3].bresp;
assign slv3_arready = axil_slv_if[3].arready;
assign slv3_rvalid  = axil_slv_if[3].rvalid;
assign slv3_rdata   = axil_slv_if[3].rdata;
assign slv3_rresp   = axil_slv_if[3].rresp;

// Master port 0 -> axil_mst_if[0]
assign mst0_awvalid = axil_mst_if[0].awvalid;
assign mst0_awaddr  = axil_mst_if[0].awaddr;
assign mst0_awprot  = axil_mst_if[0].awprot;
assign mst0_wvalid  = axil_mst_if[0].wvalid;
assign mst0_wdata   = axil_mst_if[0].wdata;
assign mst0_wstrb   = axil_mst_if[0].wstrb;
assign mst0_bready  = axil_mst_if[0].bready;
assign mst0_arvalid = axil_mst_if[0].arvalid;
assign mst0_araddr  = axil_mst_if[0].araddr;
assign mst0_arprot  = axil_mst_if[0].arprot;
assign mst0_rready  = axil_mst_if[0].rready;
assign axil_mst_if[0].awready = mst0_awready;
assign axil_mst_if[0].wready  = mst0_wready;
assign axil_mst_if[0].bvalid  = mst0_bvalid;
assign axil_mst_if[0].bresp   = mst0_bresp;
assign axil_mst_if[0].arready = mst0_arready;
assign axil_mst_if[0].rvalid  = mst0_rvalid;
assign axil_mst_if[0].rdata   = mst0_rdata;
assign axil_mst_if[0].rresp   = mst0_rresp;

// Master port 1 -> axil_mst_if[1]
assign mst1_awvalid = axil_mst_if[1].awvalid;
assign mst1_awaddr  = axil_mst_if[1].awaddr;
assign mst1_awprot  = axil_mst_if[1].awprot;
assign mst1_wvalid  = axil_mst_if[1].wvalid;
assign mst1_wdata   = axil_mst_if[1].wdata;
assign mst1_wstrb   = axil_mst_if[1].wstrb;
assign mst1_bready  = axil_mst_if[1].bready;
assign mst1_arvalid = axil_mst_if[1].arvalid;
assign mst1_araddr  = axil_mst_if[1].araddr;
assign mst1_arprot  = axil_mst_if[1].arprot;
assign mst1_rready  = axil_mst_if[1].rready;
assign axil_mst_if[1].awready = mst1_awready;
assign axil_mst_if[1].wready  = mst1_wready;
assign axil_mst_if[1].bvalid  = mst1_bvalid;
assign axil_mst_if[1].bresp   = mst1_bresp;
assign axil_mst_if[1].arready = mst1_arready;
assign axil_mst_if[1].rvalid  = mst1_rvalid;
assign axil_mst_if[1].rdata   = mst1_rdata;
assign axil_mst_if[1].rresp   = mst1_rresp;

// Master port 2 -> axil_mst_if[2]
assign mst2_awvalid = axil_mst_if[2].awvalid;
assign mst2_awaddr  = axil_mst_if[2].awaddr;
assign mst2_awprot  = axil_mst_if[2].awprot;
assign mst2_wvalid  = axil_mst_if[2].wvalid;
assign mst2_wdata   = axil_mst_if[2].wdata;
assign mst2_wstrb   = axil_mst_if[2].wstrb;
assign mst2_bready  = axil_mst_if[2].bready;
assign mst2_arvalid = axil_mst_if[2].arvalid;
assign mst2_araddr  = axil_mst_if[2].araddr;
assign mst2_arprot  = axil_mst_if[2].arprot;
assign mst2_rready  = axil_mst_if[2].rready;
assign axil_mst_if[2].awready = mst2_awready;
assign axil_mst_if[2].wready  = mst2_wready;
assign axil_mst_if[2].bvalid  = mst2_bvalid;
assign axil_mst_if[2].bresp   = mst2_bresp;
assign axil_mst_if[2].arready = mst2_arready;
assign axil_mst_if[2].rvalid  = mst2_rvalid;
assign axil_mst_if[2].rdata   = mst2_rdata;
assign axil_mst_if[2].rresp   = mst2_rresp;

// Master port 3 -> axil_mst_if[3]
assign mst3_awvalid = axil_mst_if[3].awvalid;
assign mst3_awaddr  = axil_mst_if[3].awaddr;
assign mst3_awprot  = axil_mst_if[3].awprot;
assign mst3_wvalid  = axil_mst_if[3].wvalid;
assign mst3_wdata   = axil_mst_if[3].wdata;
assign mst3_wstrb   = axil_mst_if[3].wstrb;
assign mst3_bready  = axil_mst_if[3].bready;
assign mst3_arvalid = axil_mst_if[3].arvalid;
assign mst3_araddr  = axil_mst_if[3].araddr;
assign mst3_arprot  = axil_mst_if[3].arprot;
assign mst3_rready  = axil_mst_if[3].rready;
assign axil_mst_if[3].awready = mst3_awready;
assign axil_mst_if[3].wready  = mst3_wready;
assign axil_mst_if[3].bvalid  = mst3_bvalid;
assign axil_mst_if[3].bresp   = mst3_bresp;
assign axil_mst_if[3].arready = mst3_arready;
assign axil_mst_if[3].rvalid  = mst3_rvalid;
assign axil_mst_if[3].rdata   = mst3_rdata;
assign axil_mst_if[3].rresp   = mst3_rresp;

// DUT instantiation with interface ports
axil_interconnect
#(
   .ADDR_WIDTH      ( ADDR_WIDTH ),
   .DATA_WIDTH      ( DATA_WIDTH ),
   .MST_NUM         ( 4 ),
   .SLV_NUM         ( 4 ),

   .MST_BUF_EN      ( 4'b1010 ),
   .MST_BUF_DEPTH   ( {16'd4, 16'd0, 16'd4, 16'd0} ),
   .MST_PRIORITY    ( {4'h0, 4'h1, 4'h2, 4'h1} ),
   .SLV_BUF_EN      ( 4'b0101 ),
   .SLV_BUF_DEPTH   ( {16'd0, 16'd4, 16'd0, 16'd4} ),

   .SLV_START_ADDR  ( {16'h0300, 16'h0200, 16'h0100, 16'h0000} ),
   .SLV_END_ADDR    ( {16'h03FF, 16'h02FF, 16'h01FF, 16'h00FF} ),
   .SLV_KEEP_BASE   ( 4'b1111 )
)
dut
(
   .aclk            ( clk ),
   .aresetn         ( rst_n ),

   .axil_slv_if     ( axil_slv_if ),
   .axil_mst_if     ( axil_mst_if )
);
                           
endmodule
