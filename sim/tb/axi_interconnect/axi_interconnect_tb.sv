`timescale 1ns / 1ps

module axi_interconnect_tb
#(
   parameter DATA_WIDTH    = 64,
   parameter ADDR_WIDTH    = 32,
   parameter SLV_ID_WIDTH  = 8,
   parameter MST_ID_WIDTH  = SLV_ID_WIDTH + $clog2(MST_NUM),
   parameter STRB_WIDTH    = DATA_WIDTH / 8,
   parameter MST_NUM       = 4,
   parameter SLV_NUM       = 4
)(
   input  wire                    clk,
   input  wire                    rst_n,

   input  wire [ADDR_WIDTH-1:0]  slv_awaddr [SLV_NUM],
   input  wire [SLV_ID_WIDTH-1:0]    slv_awid   [SLV_NUM],
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
   input  wire [SLV_ID_WIDTH-1:0]    slv_wid    [SLV_NUM],
   input  wire                   slv_wlast  [SLV_NUM],
   input  wire                   slv_wvalid [SLV_NUM],
   output logic                  slv_wready [SLV_NUM],
   output logic [1:0]            slv_bresp  [SLV_NUM],
   output logic [SLV_ID_WIDTH-1:0]   slv_bid    [SLV_NUM],
   output logic                  slv_bvalid [SLV_NUM],
   input  wire                   slv_bready [SLV_NUM],
   input  wire [ADDR_WIDTH-1:0]  slv_araddr [SLV_NUM],
   input  wire [SLV_ID_WIDTH-1:0]    slv_arid   [SLV_NUM],
   input  wire [7:0]             slv_arlen  [SLV_NUM],
   input  wire [2:0]             slv_arsize [SLV_NUM],
   input  wire [1:0]             slv_arburst[MST_NUM],
   input  wire [3:0]             slv_arcache[SLV_NUM],
   input  wire                   slv_arlock [SLV_NUM],
   input  wire [2:0]             slv_arprot [SLV_NUM],
   input  wire [3:0]             slv_arqos  [SLV_NUM],
   input  wire [3:0]             slv_arregion[SLV_NUM],
   input  wire                   slv_arvalid[SLV_NUM],
   output logic                  slv_arready[SLV_NUM],
   output logic [DATA_WIDTH-1:0] slv_rdata  [SLV_NUM],
   output logic [1:0]            slv_rresp  [SLV_NUM],
   output logic [SLV_ID_WIDTH-1:0]   slv_rid    [SLV_NUM],
   output logic                  slv_rlast  [SLV_NUM],
   output logic                  slv_rvalid [SLV_NUM],
   input  wire                   slv_rready [SLV_NUM],

   output logic [ADDR_WIDTH-1:0] mst_awaddr [MST_NUM],
   output logic [MST_ID_WIDTH-1:0]   mst_awid   [MST_NUM],
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
   output logic [MST_ID_WIDTH-1:0]   mst_wid    [MST_NUM],
   output logic                  mst_wlast  [MST_NUM],
   output logic                  mst_wvalid [MST_NUM],
   input  wire                   mst_wready [MST_NUM],
   input  wire [1:0]             mst_bresp  [MST_NUM],
   input  wire [MST_ID_WIDTH-1:0]    mst_bid    [MST_NUM],
   input  wire                   mst_bvalid [MST_NUM],
   output logic                  mst_bready [MST_NUM],
   output logic [ADDR_WIDTH-1:0] mst_araddr [MST_NUM],
   output logic [MST_ID_WIDTH-1:0]   mst_arid   [MST_NUM],
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
   input  wire [MST_ID_WIDTH-1:0]    mst_rid    [MST_NUM],
   input  wire                   mst_rlast  [MST_NUM],
   input  wire                   mst_rvalid [MST_NUM],
   output logic                  mst_rready [MST_NUM]
);

localparam LEN_WIDTH = 8;
localparam RESP_WIDTH = 2;

if_axi #(.ADDR_WIDTH(ADDR_WIDTH), .DATA_WIDTH(DATA_WIDTH), .ID_WIDTH(SLV_ID_WIDTH))
   axi_slv_if [0:SLV_NUM-1] ();
if_axi #(.ADDR_WIDTH(ADDR_WIDTH), .DATA_WIDTH(DATA_WIDTH), .ID_WIDTH(MST_ID_WIDTH))
   axi_mst_if [0:MST_NUM-1] ();

generate
   for (genvar i = 0; i < SLV_NUM; i++) begin
      assign axi_slv_if[i].awaddr   = slv_awaddr[i];
      assign axi_slv_if[i].awid     = slv_awid[i];
      assign axi_slv_if[i].awlen    = slv_awlen[i];
      assign axi_slv_if[i].awsize   = slv_awsize[i];
      assign axi_slv_if[i].awburst  = slv_awburst[i];
      assign axi_slv_if[i].awcache  = slv_awcache[i];
      assign axi_slv_if[i].awlock   = slv_awlock[i];
      assign axi_slv_if[i].awprot   = slv_awprot[i];
      assign axi_slv_if[i].awqos    = slv_awqos[i];
      assign axi_slv_if[i].awregion = slv_awregion[i];
      assign axi_slv_if[i].awvalid  = slv_awvalid[i];
      assign slv_awready[i] = axi_slv_if[i].awready;
      assign axi_slv_if[i].wdata    = slv_wdata[i];
      assign axi_slv_if[i].wstrb    = slv_wstrb[i];
      assign axi_slv_if[i].wid      = slv_wid[i];
      assign axi_slv_if[i].wlast    = slv_wlast[i];
      assign axi_slv_if[i].wvalid   = slv_wvalid[i];
      assign slv_wready[i] = axi_slv_if[i].wready;
      assign axi_slv_if[i].bready   = slv_bready[i];
      assign slv_bresp[i]  = axi_slv_if[i].bresp;
      assign slv_bid[i]    = axi_slv_if[i].bid;
      assign slv_bvalid[i] = axi_slv_if[i].bvalid;
      assign axi_slv_if[i].araddr   = slv_araddr[i];
      assign axi_slv_if[i].arid     = slv_arid[i];
      assign axi_slv_if[i].arlen    = slv_arlen[i];
      assign axi_slv_if[i].arsize   = slv_arsize[i];
      assign axi_slv_if[i].arburst  = slv_arburst[i];
      assign axi_slv_if[i].arcache  = slv_arcache[i];
      assign axi_slv_if[i].arlock   = slv_arlock[i];
      assign axi_slv_if[i].arprot   = slv_arprot[i];
      assign axi_slv_if[i].arqos    = slv_arqos[i];
      assign axi_slv_if[i].arregion = slv_arregion[i];
      assign axi_slv_if[i].arvalid  = slv_arvalid[i];
      assign slv_arready[i] = axi_slv_if[i].arready;
      assign axi_slv_if[i].rready   = slv_rready[i];
      assign slv_rdata[i]  = axi_slv_if[i].rdata;
      assign slv_rresp[i]  = axi_slv_if[i].rresp;
      assign slv_rid[i]    = axi_slv_if[i].rid;
      assign slv_rlast[i]  = axi_slv_if[i].rlast;
      assign slv_rvalid[i] = axi_slv_if[i].rvalid;
   end
endgenerate

generate
   for (genvar i = 0; i < MST_NUM; i++) begin
      assign mst_awaddr[i]   = axi_mst_if[i].awaddr;
      assign mst_awid[i]     = axi_mst_if[i].awid;
      assign mst_awlen[i]    = axi_mst_if[i].awlen;
      assign mst_awsize[i]   = axi_mst_if[i].awsize;
      assign mst_awburst[i]  = axi_mst_if[i].awburst;
      assign mst_awcache[i]  = axi_mst_if[i].awcache;
      assign mst_awlock[i]   = axi_mst_if[i].awlock;
      assign mst_awprot[i]   = axi_mst_if[i].awprot;
      assign mst_awqos[i]    = axi_mst_if[i].awqos;
      assign mst_awregion[i] = axi_mst_if[i].awregion;
      assign mst_awvalid[i]  = axi_mst_if[i].awvalid;
      assign axi_mst_if[i].awready = mst_awready[i];
      assign mst_wdata[i]    = axi_mst_if[i].wdata;
      assign mst_wstrb[i]    = axi_mst_if[i].wstrb;
      assign mst_wid[i]      = axi_mst_if[i].wid;
      assign mst_wlast[i]    = axi_mst_if[i].wlast;
      assign mst_wvalid[i]   = axi_mst_if[i].wvalid;
      assign axi_mst_if[i].wready  = mst_wready[i];
      assign axi_mst_if[i].bresp   = mst_bresp[i];
      assign axi_mst_if[i].bid     = mst_bid[i];
      assign axi_mst_if[i].bvalid  = mst_bvalid[i];
      assign mst_bready[i]   = axi_mst_if[i].bready;
      assign mst_araddr[i]   = axi_mst_if[i].araddr;
      assign mst_arid[i]     = axi_mst_if[i].arid;
      assign mst_arlen[i]    = axi_mst_if[i].arlen;
      assign mst_arsize[i]   = axi_mst_if[i].arsize;
      assign mst_arburst[i]  = axi_mst_if[i].arburst;
      assign mst_arcache[i]  = axi_mst_if[i].arcache;
      assign mst_arlock[i]   = axi_mst_if[i].arlock;
      assign mst_arprot[i]   = axi_mst_if[i].arprot;
      assign mst_arqos[i]    = axi_mst_if[i].arqos;
      assign mst_arregion[i] = axi_mst_if[i].arregion;
      assign mst_arvalid[i]  = axi_mst_if[i].arvalid;
      assign axi_mst_if[i].arready = mst_arready[i];
      assign axi_mst_if[i].rdata   = mst_rdata[i];
      assign axi_mst_if[i].rresp   = mst_rresp[i];
      assign axi_mst_if[i].rid     = mst_rid[i];
      assign axi_mst_if[i].rlast   = mst_rlast[i];
      assign axi_mst_if[i].rvalid  = mst_rvalid[i];
      assign mst_rready[i]   = axi_mst_if[i].rready;
   end
endgenerate

axi_interconnect #(
   .ADDR_WIDTH     ( ADDR_WIDTH ),
   .DATA_WIDTH     ( DATA_WIDTH ),
   .SLV_ID_WIDTH   ( SLV_ID_WIDTH ),
   .MST_NUM        ( MST_NUM ),
   .SLV_NUM        ( SLV_NUM ),
   .MST_BUF_EN     ( 4'b1011 ),
   .MST_BUF_DEPTH  ( {16'd4, 16'd0, 16'd4, 16'd256} ),
   .MST_PRIORITY   ( {4'h0, 4'h1, 4'h2, 4'h1} ),
   .SLV_BUF_EN     ( 4'b0101 ),
   .SLV_BUF_DEPTH  ( {16'd0, 16'd4, 16'd0, 16'd4} ),
   .SLV_START_ADDR ( {32'h0000_3000, 32'h0000_2000, 32'h0000_1000, 32'h0000_0000} ),
   .SLV_END_ADDR   ( {32'h0000_3FFF, 32'h0000_2FFF, 32'h0000_1FFF, 32'h0000_0FFF} ),
   .SLV_KEEP_BASE  ( 4'b1111 )
) dut (
   .aclk           ( clk ),
   .aresetn        ( rst_n ),
   .axi_slv_if     ( axi_slv_if ),
   .axi_mst_if     ( axi_mst_if )
);

endmodule
