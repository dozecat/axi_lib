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
   input  wire                    rst,

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
   output logic [1:0]             slv0_bresp,
   input  wire                    slv0_arvalid,
   output logic                   slv0_arready,
   input  wire  [ADDR_WIDTH -1:0] slv0_araddr,
   input  wire  [2          -1:0] slv0_arprot,
   output logic                   slv0_rvalid,
   input  wire                    slv0_rready,
   output logic [DATA_WIDTH -1:0] slv0_rdata,
   output logic [1:0]             slv0_rresp,

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
   output logic [1:0]             slv1_bresp,
   input  wire                    slv1_arvalid,
   output logic                   slv1_arready,
   input  wire  [ADDR_WIDTH -1:0] slv1_araddr,
   input  wire  [2          -1:0] slv1_arprot,
   output logic                   slv1_rvalid,
   input  wire                    slv1_rready,
   output logic [DATA_WIDTH -1:0] slv1_rdata,
   output logic [1:0]             slv1_rresp,

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
   input  wire  [1:0]             mst0_bresp,
   output logic                   mst0_arvalid,
   input  wire                    mst0_arready,
   output logic [ADDR_WIDTH -1:0] mst0_araddr,
   output logic [2          -1:0] mst0_arprot,
   input  wire                    mst0_rvalid,
   output logic                   mst0_rready,
   input  wire  [DATA_WIDTH -1:0] mst0_rdata,
   input  wire  [1:0]             mst0_rresp,

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
   input  wire  [1:0]             mst1_bresp,
   output logic                   mst1_arvalid,
   input  wire                    mst1_arready,
   output logic [ADDR_WIDTH -1:0] mst1_araddr,
   output logic [2          -1:0] mst1_arprot,
   input  wire                    mst1_rvalid,
   output logic                   mst1_rready,
   input  wire  [DATA_WIDTH -1:0] mst1_rdata,
   input  wire  [1:0]             mst1_rresp,

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
   input  wire  [1:0]             mst2_bresp,
   output logic                   mst2_arvalid,
   input  wire                    mst2_arready,
   output logic [ADDR_WIDTH -1:0] mst2_araddr,
   output logic [2          -1:0] mst2_arprot,
   input  wire                    mst2_rvalid,
   output logic                   mst2_rready,
   input  wire  [DATA_WIDTH -1:0] mst2_rdata,
   input  wire  [1:0]             mst2_rresp,

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
   input  wire  [1:0]             mst3_bresp,
   output logic                   mst3_arvalid,
   input  wire                    mst3_arready,
   output logic [ADDR_WIDTH -1:0] mst3_araddr,
   output logic [2          -1:0] mst3_arprot,
   input  wire                    mst3_rvalid,
   output logic                   mst3_rready,
   input  wire  [DATA_WIDTH -1:0] mst3_rdata,
   input  wire  [1:0]             mst3_rresp
);

// Interface instances
if_axil #(.ADDR_WIDTH(ADDR_WIDTH),
          .DATA_WIDTH(DATA_WIDTH)) s_axil_ifs [0:1] ();

if_axil #(.ADDR_WIDTH(ADDR_WIDTH),
         .DATA_WIDTH(DATA_WIDTH)) m_axil_ifs [0:3] ();

// Slave port 0 -> s_axil_ifs[0]
assign s_axil_ifs[0].awvalid = slv0_awvalid;
assign s_axil_ifs[0].awaddr  = slv0_awaddr;
assign s_axil_ifs[0].awprot  = slv0_awprot;
assign s_axil_ifs[0].wvalid  = slv0_wvalid;
assign s_axil_ifs[0].wdata   = slv0_wdata;
assign s_axil_ifs[0].wstrb   = slv0_wstrb;
assign s_axil_ifs[0].bready  = slv0_bready;
assign s_axil_ifs[0].arvalid = slv0_arvalid;
assign s_axil_ifs[0].araddr  = slv0_araddr;
assign s_axil_ifs[0].arprot  = slv0_arprot;
assign s_axil_ifs[0].rready  = slv0_rready;
assign slv0_awready = s_axil_ifs[0].awready;
assign slv0_wready  = s_axil_ifs[0].wready;
assign slv0_bvalid  = s_axil_ifs[0].bvalid;
assign slv0_bresp   = s_axil_ifs[0].bresp;
assign slv0_arready = s_axil_ifs[0].arready;
assign slv0_rvalid  = s_axil_ifs[0].rvalid;
assign slv0_rdata   = s_axil_ifs[0].rdata;
assign slv0_rresp   = s_axil_ifs[0].rresp;

// Slave port 1 -> s_axil_ifs[1]
assign s_axil_ifs[1].awvalid = slv1_awvalid;
assign s_axil_ifs[1].awaddr  = slv1_awaddr;
assign s_axil_ifs[1].awprot  = slv1_awprot;
assign s_axil_ifs[1].wvalid  = slv1_wvalid;
assign s_axil_ifs[1].wdata   = slv1_wdata;
assign s_axil_ifs[1].wstrb   = slv1_wstrb;
assign s_axil_ifs[1].bready  = slv1_bready;
assign s_axil_ifs[1].arvalid = slv1_arvalid;
assign s_axil_ifs[1].araddr  = slv1_araddr;
assign s_axil_ifs[1].arprot  = slv1_arprot;
assign s_axil_ifs[1].rready  = slv1_rready;
assign slv1_awready = s_axil_ifs[1].awready;
assign slv1_wready  = s_axil_ifs[1].wready;
assign slv1_bvalid  = s_axil_ifs[1].bvalid;
assign slv1_bresp   = s_axil_ifs[1].bresp;
assign slv1_arready = s_axil_ifs[1].arready;
assign slv1_rvalid  = s_axil_ifs[1].rvalid;
assign slv1_rdata   = s_axil_ifs[1].rdata;
assign slv1_rresp   = s_axil_ifs[1].rresp;

// Master port 0 -> m_axil_ifs[0]
assign mst0_awvalid = m_axil_ifs[0].awvalid;
assign mst0_awaddr  = m_axil_ifs[0].awaddr;
assign mst0_awprot  = m_axil_ifs[0].awprot;
assign mst0_wvalid  = m_axil_ifs[0].wvalid;
assign mst0_wdata   = m_axil_ifs[0].wdata;
assign mst0_wstrb   = m_axil_ifs[0].wstrb;
assign mst0_bready  = m_axil_ifs[0].bready;
assign mst0_arvalid = m_axil_ifs[0].arvalid;
assign mst0_araddr  = m_axil_ifs[0].araddr;
assign mst0_arprot  = m_axil_ifs[0].arprot;
assign mst0_rready  = m_axil_ifs[0].rready;
assign m_axil_ifs[0].awready = mst0_awready;
assign m_axil_ifs[0].wready  = mst0_wready;
assign m_axil_ifs[0].bvalid  = mst0_bvalid;
assign m_axil_ifs[0].bresp   = mst0_bresp;
assign m_axil_ifs[0].arready = mst0_arready;
assign m_axil_ifs[0].rvalid  = mst0_rvalid;
assign m_axil_ifs[0].rdata   = mst0_rdata;
assign m_axil_ifs[0].rresp   = mst0_rresp;

// Master port 1 -> m_axil_ifs[1]
assign mst1_awvalid = m_axil_ifs[1].awvalid;
assign mst1_awaddr  = m_axil_ifs[1].awaddr;
assign mst1_awprot  = m_axil_ifs[1].awprot;
assign mst1_wvalid  = m_axil_ifs[1].wvalid;
assign mst1_wdata   = m_axil_ifs[1].wdata;
assign mst1_wstrb   = m_axil_ifs[1].wstrb;
assign mst1_bready  = m_axil_ifs[1].bready;
assign mst1_arvalid = m_axil_ifs[1].arvalid;
assign mst1_araddr  = m_axil_ifs[1].araddr;
assign mst1_arprot  = m_axil_ifs[1].arprot;
assign mst1_rready  = m_axil_ifs[1].rready;
assign m_axil_ifs[1].awready = mst1_awready;
assign m_axil_ifs[1].wready  = mst1_wready;
assign m_axil_ifs[1].bvalid  = mst1_bvalid;
assign m_axil_ifs[1].bresp   = mst1_bresp;
assign m_axil_ifs[1].arready = mst1_arready;
assign m_axil_ifs[1].rvalid  = mst1_rvalid;
assign m_axil_ifs[1].rdata   = mst1_rdata;
assign m_axil_ifs[1].rresp   = mst1_rresp;

// Master port 2 -> m_axil_ifs[2]
assign mst2_awvalid = m_axil_ifs[2].awvalid;
assign mst2_awaddr  = m_axil_ifs[2].awaddr;
assign mst2_awprot  = m_axil_ifs[2].awprot;
assign mst2_wvalid  = m_axil_ifs[2].wvalid;
assign mst2_wdata   = m_axil_ifs[2].wdata;
assign mst2_wstrb   = m_axil_ifs[2].wstrb;
assign mst2_bready  = m_axil_ifs[2].bready;
assign mst2_arvalid = m_axil_ifs[2].arvalid;
assign mst2_araddr  = m_axil_ifs[2].araddr;
assign mst2_arprot  = m_axil_ifs[2].arprot;
assign mst2_rready  = m_axil_ifs[2].rready;
assign m_axil_ifs[2].awready = mst2_awready;
assign m_axil_ifs[2].wready  = mst2_wready;
assign m_axil_ifs[2].bvalid  = mst2_bvalid;
assign m_axil_ifs[2].bresp   = mst2_bresp;
assign m_axil_ifs[2].arready = mst2_arready;
assign m_axil_ifs[2].rvalid  = mst2_rvalid;
assign m_axil_ifs[2].rdata   = mst2_rdata;
assign m_axil_ifs[2].rresp   = mst2_rresp;

// Master port 3 -> m_axil_ifs[3]
assign mst3_awvalid = m_axil_ifs[3].awvalid;
assign mst3_awaddr  = m_axil_ifs[3].awaddr;
assign mst3_awprot  = m_axil_ifs[3].awprot;
assign mst3_wvalid  = m_axil_ifs[3].wvalid;
assign mst3_wdata   = m_axil_ifs[3].wdata;
assign mst3_wstrb   = m_axil_ifs[3].wstrb;
assign mst3_bready  = m_axil_ifs[3].bready;
assign mst3_arvalid = m_axil_ifs[3].arvalid;
assign mst3_araddr  = m_axil_ifs[3].araddr;
assign mst3_arprot  = m_axil_ifs[3].arprot;
assign mst3_rready  = m_axil_ifs[3].rready;
assign m_axil_ifs[3].awready = mst3_awready;
assign m_axil_ifs[3].wready  = mst3_wready;
assign m_axil_ifs[3].bvalid  = mst3_bvalid;
assign m_axil_ifs[3].bresp   = mst3_bresp;
assign m_axil_ifs[3].arready = mst3_arready;
assign m_axil_ifs[3].rvalid  = mst3_rvalid;
assign m_axil_ifs[3].rdata   = mst3_rdata;
assign m_axil_ifs[3].rresp   = mst3_rresp;

// DUT instantiation with interface ports
axil_interconnect
#(
   .S_NUM           ( 2 ),
   .M_NUM           ( 4 ),
   .ADDR_WIDTH      ( ADDR_WIDTH ),
   .DATA_WIDTH      ( DATA_WIDTH ),
   .S_SKID_EN       ( 2'b01 ),
   .S_PRIORITY      ( {2'h0, 2'h1} ),
   .M_SKID_EN       ( 4'b1010 ),
   .M_START_ADDR    ( {16'h0300, 16'h0200, 16'h0100, 16'h0000} ),
   .M_END_ADDR      ( {16'h03FF, 16'h02FF, 16'h01FF, 16'h00FF} ),
   .M_KEEP_BASE     ( 4'b1111 )
)
dut
(
   .clk             ( clk ),
   .rst             ( rst ),

   .s_axil_ifs      ( s_axil_ifs ),
   .m_axil_ifs      ( m_axil_ifs )
);

endmodule
