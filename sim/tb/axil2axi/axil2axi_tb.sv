`timescale 1ns / 1ps

module axil2axi_tb
#(
   parameter DATA_WIDTH    = 64,
   parameter ADDR_WIDTH    = 16,
   parameter ID_WIDTH      = 1,
   parameter STRB_WIDTH    = DATA_WIDTH / 8
)(
   input  wire                    clk,
   input  wire                    rst,

   // AXI4-Lite master port (to bridge slave side)
   input  wire                    s_awvalid,
   output logic                   s_awready,
   input  wire  [ADDR_WIDTH-1:0]  s_awaddr,
   input  wire  [2:0]             s_awprot,
   input  wire                    s_wvalid,
   output logic                   s_wready,
   input  wire  [DATA_WIDTH-1:0]  s_wdata,
   input  wire  [STRB_WIDTH-1:0]  s_wstrb,
   output logic                   s_bvalid,
   input  wire                    s_bready,
   output logic [1:0]             s_bresp,
   input  wire                    s_arvalid,
   output logic                   s_arready,
   input  wire  [ADDR_WIDTH-1:0]  s_araddr,
   input  wire  [2:0]             s_arprot,
   output logic                   s_rvalid,
   input  wire                    s_rready,
   output logic [DATA_WIDTH-1:0]  s_rdata,
   output logic [1:0]             s_rresp,

   // AXI4 slave port (to bridge master side)
   output logic                   m_awvalid,
   input  wire                    m_awready,
   output logic [ADDR_WIDTH-1:0]  m_awaddr,
   output logic [1:0]             m_awburst,
   output logic [3:0]             m_awcache,
   output logic [ID_WIDTH-1:0]    m_awid,
   output logic [7:0]             m_awlen,
   output logic                   m_awlock,
   output logic [2:0]             m_awprot,
   output logic [3:0]             m_awqos,
   output logic [3:0]             m_awregion,
   output logic [2:0]             m_awsize,
   output logic                   m_wvalid,
   input  wire                    m_wready,
   output logic [DATA_WIDTH-1:0]  m_wdata,
   output logic [ID_WIDTH-1:0]    m_wid,
   output logic                   m_wlast,
   output logic [STRB_WIDTH-1:0]  m_wstrb,
   input  wire                    m_bvalid,
   output logic                   m_bready,
   input  wire  [1:0]             m_bresp,
   input  wire  [ID_WIDTH-1:0]    m_bid,
   output logic                   m_arvalid,
   input  wire                    m_arready,
   output logic [ADDR_WIDTH-1:0]  m_araddr,
   output logic [1:0]             m_arburst,
   output logic [3:0]             m_arcache,
   output logic [ID_WIDTH-1:0]    m_arid,
   output logic [7:0]             m_arlen,
   output logic                   m_arlock,
   output logic [2:0]             m_arprot,
   output logic [3:0]             m_arqos,
   output logic [3:0]             m_arregion,
   output logic [2:0]             m_arsize,
   input  wire                    m_rvalid,
   output logic                   m_rready,
   input  wire  [DATA_WIDTH-1:0]  m_rdata,
   input  wire  [1:0]             m_rresp,
   input  wire  [ID_WIDTH-1:0]    m_rid,
   input  wire                    m_rlast
);

if_axil #(.ADDR_WIDTH(ADDR_WIDTH), .DATA_WIDTH(DATA_WIDTH)) s_axil_if ();
if_axi  #(.ADDR_WIDTH(ADDR_WIDTH), .DATA_WIDTH(DATA_WIDTH), .ID_WIDTH(ID_WIDTH)) m_axi_if ();

// AXI4-Lite master → s_axil_if
assign s_axil_if.awaddr  = s_awaddr;
assign s_axil_if.awprot  = s_awprot;
assign s_axil_if.awvalid = s_awvalid;
assign s_axil_if.wdata   = s_wdata;
assign s_axil_if.wstrb   = s_wstrb;
assign s_axil_if.wvalid  = s_wvalid;
assign s_axil_if.araddr  = s_araddr;
assign s_axil_if.arprot  = s_arprot;
assign s_axil_if.arvalid = s_arvalid;
assign s_axil_if.bready  = s_bready;
assign s_axil_if.rready  = s_rready;
assign s_awready = s_axil_if.awready;
assign s_wready  = s_axil_if.wready;
assign s_bvalid  = s_axil_if.bvalid;
assign s_bresp   = s_axil_if.bresp;
assign s_arready = s_axil_if.arready;
assign s_rvalid  = s_axil_if.rvalid;
assign s_rdata   = s_axil_if.rdata;
assign s_rresp   = s_axil_if.rresp;

// m_axi_if → AXI4 slave port
assign m_awaddr    = m_axi_if.awaddr;
assign m_awburst   = m_axi_if.awburst;
assign m_awcache   = m_axi_if.awcache;
assign m_awid      = m_axi_if.awid;
assign m_awlen     = m_axi_if.awlen;
assign m_awlock    = m_axi_if.awlock;
assign m_awprot    = m_axi_if.awprot;
assign m_awqos     = m_axi_if.awqos;
assign m_awregion  = m_axi_if.awregion;
assign m_awsize    = m_axi_if.awsize;
assign m_awvalid   = m_axi_if.awvalid;
assign m_wdata     = m_axi_if.wdata;
assign m_wid       = m_axi_if.wid;
assign m_wlast     = m_axi_if.wlast;
assign m_wstrb     = m_axi_if.wstrb;
assign m_wvalid    = m_axi_if.wvalid;
assign m_bready    = m_axi_if.bready;
assign m_araddr    = m_axi_if.araddr;
assign m_arburst   = m_axi_if.arburst;
assign m_arcache   = m_axi_if.arcache;
assign m_arid      = m_axi_if.arid;
assign m_arlen     = m_axi_if.arlen;
assign m_arlock    = m_axi_if.arlock;
assign m_arprot    = m_axi_if.arprot;
assign m_arqos     = m_axi_if.arqos;
assign m_arregion  = m_axi_if.arregion;
assign m_arsize    = m_axi_if.arsize;
assign m_arvalid   = m_axi_if.arvalid;
assign m_rready    = m_axi_if.rready;
assign m_axi_if.awready = m_awready;
assign m_axi_if.wready  = m_wready;
assign m_axi_if.bvalid  = m_bvalid;
assign m_axi_if.bresp   = m_bresp;
assign m_axi_if.bid     = m_bid;
assign m_axi_if.arready = m_arready;
assign m_axi_if.rvalid  = m_rvalid;
assign m_axi_if.rdata   = m_rdata;
assign m_axi_if.rresp   = m_rresp;
assign m_axi_if.rid     = m_rid;
assign m_axi_if.rlast   = m_rlast;

axil2axi dut (
   .clk         ( clk    ),
   .rst         ( rst    ),
   .s_axil_if   ( s_axil_if ),
   .m_axi_if    ( m_axi_if )
);

endmodule
