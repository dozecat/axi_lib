`timescale 1ns / 1ps

module axi_interconnect_tb
#(
   parameter DATA_WIDTH    = 64,
   parameter ADDR_WIDTH    = 32,
   parameter SLV_ID_WIDTH  = 8,
   parameter MST_ID_WIDTH  = SLV_ID_WIDTH + $clog2(MST_NUM),
   parameter STRB_WIDTH    = DATA_WIDTH / 8,
   parameter MST_NUM       = 4,
   parameter SLV_NUM       = 2
)(
   input  wire                    clk,
   input  wire                    rst,

   input  wire [ADDR_WIDTH-1:0]  slv_awaddr [SLV_NUM],
   input  wire [SLV_ID_WIDTH-1:0]slv_awid   [SLV_NUM],
   input  wire [7:0]             slv_awlen  [SLV_NUM],
   input  wire [2:0]             slv_awsize [SLV_NUM],
   input  wire [1:0]             slv_awburst[SLV_NUM],
   input  wire [3:0]             slv_awcache[SLV_NUM],
   input  wire                   slv_awlock [SLV_NUM],
   input  wire [2:0]             slv_awprot [SLV_NUM],
   input  wire [3:0]             slv_awqos  [SLV_NUM],
   input  wire [3:0]             slv_awregion[SLV_NUM],
   input  wire                   slv_awvalid[SLV_NUM],
   output logic                  slv_awready[SLV_NUM],
   input  wire [DATA_WIDTH-1:0]  slv_wdata  [SLV_NUM],
   input  wire [STRB_WIDTH-1:0]  slv_wstrb  [SLV_NUM],
   input  wire [SLV_ID_WIDTH-1:0]slv_wid    [SLV_NUM],
   input  wire                   slv_wlast  [SLV_NUM],
   input  wire                   slv_wvalid [SLV_NUM],
   output logic                  slv_wready [SLV_NUM],
   output logic [1:0]            slv_bresp  [SLV_NUM],
   output logic [SLV_ID_WIDTH-1:0]slv_bid   [SLV_NUM],
   output logic                  slv_bvalid [SLV_NUM],
   input  wire                   slv_bready [SLV_NUM],
   input  wire [ADDR_WIDTH-1:0]  slv_araddr [SLV_NUM],
   input  wire [SLV_ID_WIDTH-1:0] slv_arid  [SLV_NUM],
   input  wire [7:0]             slv_arlen  [SLV_NUM],
   input  wire [2:0]             slv_arsize [SLV_NUM],
   input  wire [1:0]             slv_arburst[SLV_NUM],
   input  wire [3:0]             slv_arcache[SLV_NUM],
   input  wire                   slv_arlock [SLV_NUM],
   input  wire [2:0]             slv_arprot [SLV_NUM],
   input  wire [3:0]             slv_arqos  [SLV_NUM],
   input  wire [3:0]             slv_arregion[SLV_NUM],
   input  wire                   slv_arvalid[SLV_NUM],
   output logic                  slv_arready[SLV_NUM],
   output logic [DATA_WIDTH-1:0] slv_rdata  [SLV_NUM],
   output logic [1:0]            slv_rresp  [SLV_NUM],
   output logic [SLV_ID_WIDTH-1:0] slv_rid  [SLV_NUM],
   output logic                  slv_rlast  [SLV_NUM],
   output logic                  slv_rvalid [SLV_NUM],
   input  wire                   slv_rready [SLV_NUM],

   output logic [ADDR_WIDTH-1:0] mst_awaddr [MST_NUM],
   output logic [MST_ID_WIDTH-1:0]mst_awid  [MST_NUM],
   output logic [7:0]            mst_awlen  [MST_NUM],
   output logic [2:0]            mst_awsize [MST_NUM],
   output logic [1:0]            mst_awburst[MST_NUM],
   output logic [3:0]            mst_awcache[MST_NUM],
   output logic                   mst_awlock[MST_NUM],
   output logic [2:0]            mst_awprot [MST_NUM],
   output logic [3:0]            mst_awqos  [MST_NUM],
   output logic [3:0]            mst_awregion[MST_NUM],
   output logic                  mst_awvalid[MST_NUM],
   input  wire                   mst_awready[MST_NUM],
   output logic [DATA_WIDTH-1:0] mst_wdata  [MST_NUM],
   output logic [STRB_WIDTH-1:0] mst_wstrb  [MST_NUM],
   output logic [MST_ID_WIDTH-1:0] mst_wid  [MST_NUM],
   output logic                  mst_wlast  [MST_NUM],
   output logic                  mst_wvalid [MST_NUM],
   input  wire                   mst_wready [MST_NUM],
   input  wire [1:0]             mst_bresp  [MST_NUM],
   input  wire [MST_ID_WIDTH-1:0] mst_bid   [MST_NUM],
   input  wire                   mst_bvalid [MST_NUM],
   output logic                  mst_bready [MST_NUM],
   output logic [ADDR_WIDTH-1:0] mst_araddr [MST_NUM],
   output logic [MST_ID_WIDTH-1:0] mst_arid [MST_NUM],
   output logic [7:0]            mst_arlen  [MST_NUM],
   output logic [2:0]            mst_arsize [MST_NUM],
   output logic [1:0]            mst_arburst[MST_NUM],
   output logic [3:0]            mst_arcache[MST_NUM],
   output logic                  mst_arlock [MST_NUM],
   output logic [2:0]            mst_arprot [MST_NUM],
   output logic [3:0]            mst_arqos  [MST_NUM],
   output logic [3:0]            mst_arregion[MST_NUM],
   output logic                  mst_arvalid[MST_NUM],
   input  wire                   mst_arready[MST_NUM],
   input  wire [DATA_WIDTH-1:0]  mst_rdata  [MST_NUM],
   input  wire [1:0]             mst_rresp  [MST_NUM],
   input  wire [MST_ID_WIDTH-1:0] mst_rid   [MST_NUM],
   input  wire                   mst_rlast  [MST_NUM],
   input  wire                   mst_rvalid [MST_NUM],
   output logic                  mst_rready [MST_NUM]
);

localparam LEN_WIDTH = 8;
localparam RESP_WIDTH = 2;

if_axi #(.ADDR_WIDTH(ADDR_WIDTH), .DATA_WIDTH(DATA_WIDTH), .ID_WIDTH(SLV_ID_WIDTH))
   s_axi_ifs [0:SLV_NUM-1] ();
if_axi #(.ADDR_WIDTH(ADDR_WIDTH), .DATA_WIDTH(DATA_WIDTH), .ID_WIDTH(MST_ID_WIDTH))
   m_axi_ifs [0:MST_NUM-1] ();

generate
   for (genvar i = 0; i < SLV_NUM; i++) begin
      assign s_axi_ifs[i].awaddr   = slv_awaddr[i];
      assign s_axi_ifs[i].awid     = slv_awid[i];
      assign s_axi_ifs[i].awlen    = slv_awlen[i];
      assign s_axi_ifs[i].awsize   = slv_awsize[i];
      assign s_axi_ifs[i].awburst  = slv_awburst[i];
      assign s_axi_ifs[i].awcache  = slv_awcache[i];
      assign s_axi_ifs[i].awlock   = slv_awlock[i];
      assign s_axi_ifs[i].awprot   = slv_awprot[i];
      assign s_axi_ifs[i].awqos    = slv_awqos[i];
      assign s_axi_ifs[i].awregion = slv_awregion[i];
      assign s_axi_ifs[i].awvalid  = slv_awvalid[i];
      assign slv_awready[i] = s_axi_ifs[i].awready;
      assign s_axi_ifs[i].wdata    = slv_wdata[i];
      assign s_axi_ifs[i].wstrb    = slv_wstrb[i];
      assign s_axi_ifs[i].wid      = slv_wid[i];
      assign s_axi_ifs[i].wlast    = slv_wlast[i];
      assign s_axi_ifs[i].wvalid   = slv_wvalid[i];
      assign slv_wready[i] = s_axi_ifs[i].wready;
      assign s_axi_ifs[i].bready   = slv_bready[i];
      assign slv_bresp[i]  = s_axi_ifs[i].bresp;
      assign slv_bid[i]    = s_axi_ifs[i].bid;
      assign slv_bvalid[i] = s_axi_ifs[i].bvalid;
      assign s_axi_ifs[i].araddr   = slv_araddr[i];
      assign s_axi_ifs[i].arid     = slv_arid[i];
      assign s_axi_ifs[i].arlen    = slv_arlen[i];
      assign s_axi_ifs[i].arsize   = slv_arsize[i];
      assign s_axi_ifs[i].arburst  = slv_arburst[i];
      assign s_axi_ifs[i].arcache  = slv_arcache[i];
      assign s_axi_ifs[i].arlock   = slv_arlock[i];
      assign s_axi_ifs[i].arprot   = slv_arprot[i];
      assign s_axi_ifs[i].arqos    = slv_arqos[i];
      assign s_axi_ifs[i].arregion = slv_arregion[i];
      assign s_axi_ifs[i].arvalid  = slv_arvalid[i];
      assign slv_arready[i] = s_axi_ifs[i].arready;
      assign s_axi_ifs[i].rready   = slv_rready[i];
      assign slv_rdata[i]  = s_axi_ifs[i].rdata;
      assign slv_rresp[i]  = s_axi_ifs[i].rresp;
      assign slv_rid[i]    = s_axi_ifs[i].rid;
      assign slv_rlast[i]  = s_axi_ifs[i].rlast;
      assign slv_rvalid[i] = s_axi_ifs[i].rvalid;
   end
endgenerate

generate
   for (genvar i = 0; i < MST_NUM; i++) begin
      assign mst_awaddr[i]   = m_axi_ifs[i].awaddr;
      assign mst_awid[i]     = m_axi_ifs[i].awid;
      assign mst_awlen[i]    = m_axi_ifs[i].awlen;
      assign mst_awsize[i]   = m_axi_ifs[i].awsize;
      assign mst_awburst[i]  = m_axi_ifs[i].awburst;
      assign mst_awcache[i]  = m_axi_ifs[i].awcache;
      assign mst_awlock[i]   = m_axi_ifs[i].awlock;
      assign mst_awprot[i]   = m_axi_ifs[i].awprot;
      assign mst_awqos[i]    = m_axi_ifs[i].awqos;
      assign mst_awregion[i] = m_axi_ifs[i].awregion;
      assign mst_awvalid[i]  = m_axi_ifs[i].awvalid;
      assign m_axi_ifs[i].awready = mst_awready[i];
      assign mst_wdata[i]    = m_axi_ifs[i].wdata;
      assign mst_wstrb[i]    = m_axi_ifs[i].wstrb;
      assign mst_wid[i]      = m_axi_ifs[i].wid;
      assign mst_wlast[i]    = m_axi_ifs[i].wlast;
      assign mst_wvalid[i]   = m_axi_ifs[i].wvalid;
      assign m_axi_ifs[i].wready  = mst_wready[i];
      assign m_axi_ifs[i].bresp   = mst_bresp[i];
      assign m_axi_ifs[i].bid     = mst_bid[i];
      assign m_axi_ifs[i].bvalid  = mst_bvalid[i];
      assign mst_bready[i]   = m_axi_ifs[i].bready;
      assign mst_araddr[i]   = m_axi_ifs[i].araddr;
      assign mst_arid[i]     = m_axi_ifs[i].arid;
      assign mst_arlen[i]    = m_axi_ifs[i].arlen;
      assign mst_arsize[i]   = m_axi_ifs[i].arsize;
      assign mst_arburst[i]  = m_axi_ifs[i].arburst;
      assign mst_arcache[i]  = m_axi_ifs[i].arcache;
      assign mst_arlock[i]   = m_axi_ifs[i].arlock;
      assign mst_arprot[i]   = m_axi_ifs[i].arprot;
      assign mst_arqos[i]    = m_axi_ifs[i].arqos;
      assign mst_arregion[i] = m_axi_ifs[i].arregion;
      assign mst_arvalid[i]  = m_axi_ifs[i].arvalid;
      assign m_axi_ifs[i].arready = mst_arready[i];
      assign m_axi_ifs[i].rdata   = mst_rdata[i];
      assign m_axi_ifs[i].rresp   = mst_rresp[i];
      assign m_axi_ifs[i].rid     = mst_rid[i];
      assign m_axi_ifs[i].rlast   = mst_rlast[i];
      assign m_axi_ifs[i].rvalid  = mst_rvalid[i];
      assign mst_rready[i]   = m_axi_ifs[i].rready;
   end
endgenerate

axi_interconnect #(
   .ADDR_WIDTH     ( ADDR_WIDTH ),
   .DATA_WIDTH     ( DATA_WIDTH ),
   .S_ID_WIDTH     ( SLV_ID_WIDTH ),
   .M_NUM          ( MST_NUM ),
   .S_NUM          ( SLV_NUM ),
   .S_BUF_EN       ( 2'b01 ),
   .S_BUF_DEPTH    ( {16'd4, 16'd256} ),
   .S_PRIORITY     ( {2'h3, 2'h1} ),
   .M_BUF_EN       ( 4'b0101 ),
   .M_BUF_DEPTH    ( {16'd0, 16'd4, 16'd0, 16'd4} ),
   .M_START_ADDR   ( {32'h0000_3000, 32'h0000_2000, 32'h0000_1000, 32'h0000_0000} ),
   .M_END_ADDR     ( {32'h0000_3FFF, 32'h0000_2FFF, 32'h0000_1FFF, 32'h0000_0FFF} ),
   .M_KEEP_BASE    ( 4'b1111 )
) dut (
   .clk            ( clk ),
   .rst            ( rst ),
   .s_axi_ifs      ( s_axi_ifs ),
   .m_axi_ifs      ( m_axi_ifs )
);

endmodule
