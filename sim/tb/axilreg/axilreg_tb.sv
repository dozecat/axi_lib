`timescale 1ns / 1ps

module axilreg_tb
#(
   parameter DATA_WIDTH    = 32,
   parameter ADDR_WIDTH    = 16,
   parameter STRB_WIDTH    = DATA_WIDTH / 8
)(
   input  wire                    clk,
   input  wire                    rst,

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

   input  wire [31:0]             reg_test1,
   output wire [31:0]             reg_test2
);

if_axil #(.ADDR_WIDTH(ADDR_WIDTH), .DATA_WIDTH(DATA_WIDTH)) s_axil_if ();

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

axil_register_file dut (
   .clk       ( clk       ),
   .rst       ( rst       ),
   .s_axil_if ( s_axil_if ),
   .reg_test1 ( reg_test1 ),
   .reg_test2 ( reg_test2 )
);

endmodule
