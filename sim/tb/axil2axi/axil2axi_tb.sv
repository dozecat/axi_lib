`timescale 1ns / 1ps

module axil2axi_tb
#(
   parameter DATA_WIDTH    = 64,
   parameter ADDR_WIDTH    = 16,
   parameter ID_WIDTH      = 1,
   parameter STRB_WIDTH    = DATA_WIDTH / 8
)(
   input  wire                    clk,
   input  wire                    rst_n,

   // AXI4-Lite master port (to bridge slave side)
   input  wire                    m_awvalid,
   output logic                   m_awready,
   input  wire  [ADDR_WIDTH-1:0]  m_awaddr,
   input  wire  [2:0]             m_awprot,
   input  wire                    m_wvalid,
   output logic                   m_wready,
   input  wire  [DATA_WIDTH-1:0]  m_wdata,
   input  wire  [STRB_WIDTH-1:0]  m_wstrb,
   output logic                   m_bvalid,
   input  wire                    m_bready,
   output logic [1:0]             m_bresp,
   input  wire                    m_arvalid,
   output logic                   m_arready,
   input  wire  [ADDR_WIDTH-1:0]  m_araddr,
   input  wire  [2:0]             m_arprot,
   output logic                   m_rvalid,
   input  wire                    m_rready,
   output logic [DATA_WIDTH-1:0]  m_rdata,
   output logic [1:0]             m_rresp,

   // AXI4 slave port (to bridge master side)
   output logic                   s_awvalid,
   input  wire                    s_awready,
   output logic [ADDR_WIDTH-1:0]  s_awaddr,
   output logic [1:0]             s_awburst,
   output logic [3:0]             s_awcache,
   output logic [ID_WIDTH-1:0]    s_awid,
   output logic [7:0]             s_awlen,
   output logic                   s_awlock,
   output logic [2:0]             s_awprot,
   output logic [3:0]             s_awqos,
   output logic [3:0]             s_awregion,
   output logic [2:0]             s_awsize,
   output logic                   s_wvalid,
   input  wire                    s_wready,
   output logic [DATA_WIDTH-1:0]  s_wdata,
   output logic [ID_WIDTH-1:0]    s_wid,
   output logic                   s_wlast,
   output logic [STRB_WIDTH-1:0]  s_wstrb,
   input  wire                    s_bvalid,
   output logic                   s_bready,
   input  wire  [1:0]             s_bresp,
   input  wire  [ID_WIDTH-1:0]    s_bid,
   output logic                   s_arvalid,
   input  wire                    s_arready,
   output logic [ADDR_WIDTH-1:0]  s_araddr,
   output logic [1:0]             s_arburst,
   output logic [3:0]             s_arcache,
   output logic [ID_WIDTH-1:0]    s_arid,
   output logic [7:0]             s_arlen,
   output logic                   s_arlock,
   output logic [2:0]             s_arprot,
   output logic [3:0]             s_arqos,
   output logic [3:0]             s_arregion,
   output logic [2:0]             s_arsize,
   input  wire                    s_rvalid,
   output logic                   s_rready,
   input  wire  [DATA_WIDTH-1:0]  s_rdata,
   input  wire  [1:0]             s_rresp,
   input  wire  [ID_WIDTH-1:0]    s_rid,
   input  wire                    s_rlast
);

if_axil #(.ADDR_WIDTH(ADDR_WIDTH), .DATA_WIDTH(DATA_WIDTH)) axil_slv_if ();
if_axi  #(.ADDR_WIDTH(ADDR_WIDTH), .DATA_WIDTH(DATA_WIDTH), .ID_WIDTH(ID_WIDTH)) axi_mst_if ();

// AXI4-Lite master → axil_slv_if
assign axil_slv_if.awaddr  = m_awaddr;
assign axil_slv_if.awprot  = m_awprot;
assign axil_slv_if.awvalid = m_awvalid;
assign axil_slv_if.wdata   = m_wdata;
assign axil_slv_if.wstrb   = m_wstrb;
assign axil_slv_if.wvalid  = m_wvalid;
assign axil_slv_if.araddr  = m_araddr;
assign axil_slv_if.arprot  = m_arprot;
assign axil_slv_if.arvalid = m_arvalid;
assign axil_slv_if.bready  = m_bready;
assign axil_slv_if.rready  = m_rready;
assign m_awready = axil_slv_if.awready;
assign m_wready  = axil_slv_if.wready;
assign m_bvalid  = axil_slv_if.bvalid;
assign m_bresp   = axil_slv_if.bresp;
assign m_arready = axil_slv_if.arready;
assign m_rvalid  = axil_slv_if.rvalid;
assign m_rdata   = axil_slv_if.rdata;
assign m_rresp   = axil_slv_if.rresp;

// axi_mst_if → AXI4 slave port
assign s_awaddr    = axi_mst_if.awaddr;
assign s_awburst   = axi_mst_if.awburst;
assign s_awcache   = axi_mst_if.awcache;
assign s_awid      = axi_mst_if.awid;
assign s_awlen     = axi_mst_if.awlen;
assign s_awlock    = axi_mst_if.awlock;
assign s_awprot    = axi_mst_if.awprot;
assign s_awqos     = axi_mst_if.awqos;
assign s_awregion  = axi_mst_if.awregion;
assign s_awsize    = axi_mst_if.awsize;
assign s_awvalid   = axi_mst_if.awvalid;
assign s_wdata     = axi_mst_if.wdata;
assign s_wid       = axi_mst_if.wid;
assign s_wlast     = axi_mst_if.wlast;
assign s_wstrb     = axi_mst_if.wstrb;
assign s_wvalid    = axi_mst_if.wvalid;
assign s_bready    = axi_mst_if.bready;
assign s_araddr    = axi_mst_if.araddr;
assign s_arburst   = axi_mst_if.arburst;
assign s_arcache   = axi_mst_if.arcache;
assign s_arid      = axi_mst_if.arid;
assign s_arlen     = axi_mst_if.arlen;
assign s_arlock    = axi_mst_if.arlock;
assign s_arprot    = axi_mst_if.arprot;
assign s_arqos     = axi_mst_if.arqos;
assign s_arregion  = axi_mst_if.arregion;
assign s_arsize    = axi_mst_if.arsize;
assign s_arvalid   = axi_mst_if.arvalid;
assign s_rready    = axi_mst_if.rready;
assign axi_mst_if.awready = s_awready;
assign axi_mst_if.wready  = s_wready;
assign axi_mst_if.bvalid  = s_bvalid;
assign axi_mst_if.bresp   = s_bresp;
assign axi_mst_if.bid     = s_bid;
assign axi_mst_if.arready = s_arready;
assign axi_mst_if.rvalid  = s_rvalid;
assign axi_mst_if.rdata   = s_rdata;
assign axi_mst_if.rresp   = s_rresp;
assign axi_mst_if.rid     = s_rid;
assign axi_mst_if.rlast   = s_rlast;

axil2axi dut (
   .aclk        ( clk    ),
   .aresetn     ( rst_n  ),
   .axil_slv_if ( axil_slv_if ),
   .axi_mst_if  ( axi_mst_if )
);

endmodule
