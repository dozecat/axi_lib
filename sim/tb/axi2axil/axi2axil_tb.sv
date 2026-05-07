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
   input  wire                    rst,

   // AXI4 master port (to bridge slave side)
   input  wire [ID_WIDTH-1:0]     s_awid,
   input  wire [ADDR_WIDTH-1:0]   s_awaddr,
   input  wire [7:0]              s_awlen,
   input  wire [2:0]              s_awsize,
   input  wire [1:0]              s_awburst,
   input  wire [3:0]              s_awcache,
   input  wire                    s_awlock,
   input  wire [2:0]              s_awprot,
   input  wire [3:0]              s_awqos,
   input  wire [3:0]              s_awregion,
   input  wire                    s_awvalid,
   output logic                   s_awready,
   input  wire [DATA_WIDTH-1:0]   s_wdata,
   input  wire [STRB_WIDTH-1:0]   s_wstrb,
   input  wire [ID_WIDTH-1:0]     s_wid,
   input  wire                    s_wlast,
   input  wire                    s_wvalid,
   output logic                   s_wready,
   output logic [1:0]             s_bresp,
   output logic [ID_WIDTH-1:0]    s_bid,
   output logic                   s_bvalid,
   input  wire                    s_bready,
   input  wire [ID_WIDTH-1:0]     s_arid,
   input  wire [ADDR_WIDTH-1:0]   s_araddr,
   input  wire [7:0]              s_arlen,
   input  wire [2:0]              s_arsize,
   input  wire [1:0]              s_arburst,
   input  wire [3:0]              s_arcache,
   input  wire                    s_arlock,
   input  wire [2:0]              s_arprot,
   input  wire [3:0]              s_arqos,
   input  wire [3:0]              s_arregion,
   input  wire                    s_arvalid,
   output logic                   s_arready,
   output logic [DATA_WIDTH-1:0]  s_rdata,
   output logic [1:0]             s_rresp,
   output logic [ID_WIDTH-1:0]    s_rid,
   output logic                   s_rlast,
   output logic                   s_rvalid,
   input  wire                    s_rready,

   // AXI4-Lite slave port (to bridge master side)
   output logic                   m_awvalid,
   input  wire                    m_awready,
   output logic [ADDR_WIDTH-1:0]  m_awaddr,
   output logic [2:0]             m_awprot,
   output logic                   m_wvalid,
   input  wire                    m_wready,
   output logic [DATA_WIDTH-1:0]  m_wdata,
   output logic [STRB_WIDTH-1:0]  m_wstrb,
   input  wire                    m_bvalid,
   output logic                   m_bready,
   input  wire [1:0]              m_bresp,
   output logic                   m_arvalid,
   input  wire                    m_arready,
   output logic [ADDR_WIDTH-1:0]  m_araddr,
   output logic [2:0]             m_arprot,
   input  wire                    m_rvalid,
   output logic                   m_rready,
   input  wire [DATA_WIDTH-1:0]   m_rdata,
   input  wire [1:0]              m_rresp
);

// Interface instances
if_axi #(
   .ADDR_WIDTH ( ADDR_WIDTH ),
   .DATA_WIDTH ( DATA_WIDTH ),
   .ID_WIDTH   ( ID_WIDTH   )
) s_axi_if ();

if_axil #(
   .ADDR_WIDTH ( ADDR_WIDTH ),
   .DATA_WIDTH ( DATA_WIDTH )
) m_axil_if ();

// AXI4 master port → s_axi_if (bridge slave side)
assign s_axi_if.awid     = s_awid;
assign s_axi_if.awaddr   = s_awaddr;
assign s_axi_if.awlen    = s_awlen;
assign s_axi_if.awsize   = s_awsize;
assign s_axi_if.awburst  = s_awburst;
assign s_axi_if.awcache  = s_awcache;
assign s_axi_if.awlock   = s_awlock;
assign s_axi_if.awprot   = s_awprot;
assign s_axi_if.awqos    = s_awqos;
assign s_axi_if.awregion = s_awregion;
assign s_axi_if.awvalid  = s_awvalid;
assign s_axi_if.wdata    = s_wdata;
assign s_axi_if.wstrb    = s_wstrb;
assign s_axi_if.wid      = s_wid;
assign s_axi_if.wlast    = s_wlast;
assign s_axi_if.wvalid   = s_wvalid;
assign s_axi_if.bready   = s_bready;
assign s_axi_if.arid     = s_arid;
assign s_axi_if.araddr   = s_araddr;
assign s_axi_if.arlen    = s_arlen;
assign s_axi_if.arsize   = s_arsize;
assign s_axi_if.arburst  = s_arburst;
assign s_axi_if.arcache  = s_arcache;
assign s_axi_if.arlock   = s_arlock;
assign s_axi_if.arprot   = s_arprot;
assign s_axi_if.arqos    = s_arqos;
assign s_axi_if.arregion = s_arregion;
assign s_axi_if.arvalid  = s_arvalid;
assign s_axi_if.rready   = s_rready;
assign s_awready  = s_axi_if.awready;
assign s_wready   = s_axi_if.wready;
assign s_bresp    = s_axi_if.bresp;
assign s_bid      = s_axi_if.bid;
assign s_bvalid   = s_axi_if.bvalid;
assign s_arready  = s_axi_if.arready;
assign s_rdata    = s_axi_if.rdata;
assign s_rresp    = s_axi_if.rresp;
assign s_rid      = s_axi_if.rid;
assign s_rlast    = s_axi_if.rlast;
assign s_rvalid   = s_axi_if.rvalid;

// m_axil_if → AXI4-Lite slave port (bridge master side)
assign m_awaddr   = m_axil_if.awaddr;
assign m_awprot   = m_axil_if.awprot;
assign m_awvalid  = m_axil_if.awvalid;
assign m_wdata    = m_axil_if.wdata;
assign m_wstrb    = m_axil_if.wstrb;
assign m_wvalid   = m_axil_if.wvalid;
assign m_bready   = m_axil_if.bready;
assign m_araddr   = m_axil_if.araddr;
assign m_arprot   = m_axil_if.arprot;
assign m_arvalid  = m_axil_if.arvalid;
assign m_rready   = m_axil_if.rready;
assign m_axil_if.awready = m_awready;
assign m_axil_if.wready  = m_wready;
assign m_axil_if.bvalid  = m_bvalid;
assign m_axil_if.bresp   = m_bresp;
assign m_axil_if.arready = m_arready;
assign m_axil_if.rvalid  = m_rvalid;
assign m_axil_if.rdata   = m_rdata;
assign m_axil_if.rresp   = m_rresp;

// DUT
axi2axil dut (
   .clk         ( clk    ),
   .rst         ( rst    ),
   .s_axi_if    ( s_axi_if ),
   .m_axil_if   ( m_axil_if )
);

endmodule
