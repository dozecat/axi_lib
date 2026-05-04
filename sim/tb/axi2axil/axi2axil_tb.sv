//*****************************************************************************
// Copyright (C) 2026 dozecat. All rights reserved.
// SPDX-License-Identifier: MIT
//
// File:        axi2axil_tb.sv
// Description: AXI4-to-AXI4-Lite Bridge Testbench Wrapper
// Repository:  https://github.com/dozecat/axi_lib.git
//
// Modification History:
// Ver   Who       Date        Changes
// ----  ----  ----------  ----------------------------------------------------
// 1.0         2026/5/4    Initial release
//*****************************************************************************
`timescale 1ns / 1ps

module axi2axil_tb
#(
   parameter DATA_WIDTH    = 64,
   parameter ADDR_WIDTH    = 16,
   parameter ID_WIDTH      = 8,
   parameter STRB_WIDTH    = DATA_WIDTH / 8
)(
   input  wire                    clk,
   input  wire                    rst_n,

   // AXI4 master port (to bridge slave side)
   input  wire [ID_WIDTH-1:0]     m_awid,
   input  wire [ADDR_WIDTH-1:0]   m_awaddr,
   input  wire [7:0]              m_awlen,
   input  wire [2:0]              m_awsize,
   input  wire [1:0]              m_awburst,
   input  wire [3:0]              m_awcache,
   input  wire                    m_awlock,
   input  wire [2:0]              m_awprot,
   input  wire [3:0]              m_awqos,
   input  wire [3:0]              m_awregion,
   input  wire                    m_awvalid,
   output logic                   m_awready,
   input  wire [DATA_WIDTH-1:0]   m_wdata,
   input  wire [STRB_WIDTH-1:0]   m_wstrb,
   input  wire [ID_WIDTH-1:0]     m_wid,
   input  wire                    m_wlast,
   input  wire                    m_wvalid,
   output logic                   m_wready,
   output logic [1:0]             m_bresp,
   output logic [ID_WIDTH-1:0]    m_bid,
   output logic                   m_bvalid,
   input  wire                    m_bready,
   input  wire [ID_WIDTH-1:0]     m_arid,
   input  wire [ADDR_WIDTH-1:0]   m_araddr,
   input  wire [7:0]              m_arlen,
   input  wire [2:0]              m_arsize,
   input  wire [1:0]              m_arburst,
   input  wire [3:0]              m_arcache,
   input  wire                    m_arlock,
   input  wire [2:0]              m_arprot,
   input  wire [3:0]              m_arqos,
   input  wire [3:0]              m_arregion,
   input  wire                    m_arvalid,
   output logic                   m_arready,
   output logic [DATA_WIDTH-1:0]  m_rdata,
   output logic [1:0]             m_rresp,
   output logic [ID_WIDTH-1:0]    m_rid,
   output logic                   m_rlast,
   output logic                   m_rvalid,
   input  wire                    m_rready,

   // AXI4-Lite slave port (to bridge master side)
   output logic                   s_awvalid,
   input  wire                    s_awready,
   output logic [ADDR_WIDTH-1:0]  s_awaddr,
   output logic [2:0]             s_awprot,
   output logic                   s_wvalid,
   input  wire                    s_wready,
   output logic [DATA_WIDTH-1:0]  s_wdata,
   output logic [STRB_WIDTH-1:0]  s_wstrb,
   input  wire                    s_bvalid,
   output logic                   s_bready,
   input  wire [1:0]              s_bresp,
   output logic                   s_arvalid,
   input  wire                    s_arready,
   output logic [ADDR_WIDTH-1:0]  s_araddr,
   output logic [2:0]             s_arprot,
   input  wire                    s_rvalid,
   output logic                   s_rready,
   input  wire [DATA_WIDTH-1:0]   s_rdata,
   input  wire [1:0]              s_rresp
);

// Interface instances
if_axi #(
   .ADDR_WIDTH ( ADDR_WIDTH ),
   .DATA_WIDTH ( DATA_WIDTH ),
   .ID_WIDTH   ( ID_WIDTH   )
) axi_slv_if ();

if_axil #(
   .ADDR_WIDTH ( ADDR_WIDTH ),
   .DATA_WIDTH ( DATA_WIDTH )
) axil_mst_if ();

// AXI4 master port → axi_slv_if (bridge slave side)
assign axi_slv_if.awid     = m_awid;
assign axi_slv_if.awaddr   = m_awaddr;
assign axi_slv_if.awlen    = m_awlen;
assign axi_slv_if.awsize   = m_awsize;
assign axi_slv_if.awburst  = m_awburst;
assign axi_slv_if.awcache  = m_awcache;
assign axi_slv_if.awlock   = m_awlock;
assign axi_slv_if.awprot   = m_awprot;
assign axi_slv_if.awqos    = m_awqos;
assign axi_slv_if.awregion = m_awregion;
assign axi_slv_if.awvalid  = m_awvalid;
assign axi_slv_if.wdata    = m_wdata;
assign axi_slv_if.wstrb    = m_wstrb;
assign axi_slv_if.wid      = m_wid;
assign axi_slv_if.wlast    = m_wlast;
assign axi_slv_if.wvalid   = m_wvalid;
assign axi_slv_if.bready   = m_bready;
assign axi_slv_if.arid     = m_arid;
assign axi_slv_if.araddr   = m_araddr;
assign axi_slv_if.arlen    = m_arlen;
assign axi_slv_if.arsize   = m_arsize;
assign axi_slv_if.arburst  = m_arburst;
assign axi_slv_if.arcache  = m_arcache;
assign axi_slv_if.arlock   = m_arlock;
assign axi_slv_if.arprot   = m_arprot;
assign axi_slv_if.arqos    = m_arqos;
assign axi_slv_if.arregion = m_arregion;
assign axi_slv_if.arvalid  = m_arvalid;
assign axi_slv_if.rready   = m_rready;
assign m_awready  = axi_slv_if.awready;
assign m_wready   = axi_slv_if.wready;
assign m_bresp    = axi_slv_if.bresp;
assign m_bid      = axi_slv_if.bid;
assign m_bvalid   = axi_slv_if.bvalid;
assign m_arready  = axi_slv_if.arready;
assign m_rdata    = axi_slv_if.rdata;
assign m_rresp    = axi_slv_if.rresp;
assign m_rid      = axi_slv_if.rid;
assign m_rlast    = axi_slv_if.rlast;
assign m_rvalid   = axi_slv_if.rvalid;

// axil_mst_if → AXI4-Lite slave port (bridge master side)
assign s_awaddr   = axil_mst_if.awaddr;
assign s_awprot   = axil_mst_if.awprot;
assign s_awvalid  = axil_mst_if.awvalid;
assign s_wdata    = axil_mst_if.wdata;
assign s_wstrb    = axil_mst_if.wstrb;
assign s_wvalid   = axil_mst_if.wvalid;
assign s_bready   = axil_mst_if.bready;
assign s_araddr   = axil_mst_if.araddr;
assign s_arprot   = axil_mst_if.arprot;
assign s_arvalid  = axil_mst_if.arvalid;
assign s_rready   = axil_mst_if.rready;
assign axil_mst_if.awready = s_awready;
assign axil_mst_if.wready  = s_wready;
assign axil_mst_if.bvalid  = s_bvalid;
assign axil_mst_if.bresp   = s_bresp;
assign axil_mst_if.arready = s_arready;
assign axil_mst_if.rvalid  = s_rvalid;
assign axil_mst_if.rdata   = s_rdata;
assign axil_mst_if.rresp   = s_rresp;

// DUT
axi2axil dut (
   .aclk        ( clk    ),
   .aresetn     ( rst_n  ),
   .axi_slv_if  ( axi_slv_if  ),
   .axil_mst_if ( axil_mst_if )
);

endmodule
