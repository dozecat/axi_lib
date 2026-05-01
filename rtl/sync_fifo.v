//******************************************************************************
// sync_fifo.v
// SPDX-License-Identifier: MIT
//
// Single-clock synchronous FIFO with extended-MSB pointer full/empty
// detection.  Includes pipelined write (1-cycle latency) and read-after-write
// data forwarding to resolve write-then-read hazards on the same address.
//
// Parameter ranges:
//   WIDTH      > 0
//   DEPTH      power-of-2, >= 2
//   FWFT       "TRUE" for first-word fall-through, "FALSE" for registered read
//   RAM_STYLE  Xilinx:"block","distributed" | Altera:"M9K","M20K","MLAB","logic"
//
// https://github.com/dozecat/memory_lib
//******************************************************************************

`timescale 1 ns / 1 ps
`default_nettype none

module sync_fifo
#(
   parameter WIDTH            = 8,
   parameter DEPTH            = 16,
   parameter FWFT             = "FALSE",
   parameter RAM_STYLE        = "block"
)(
   input  wire                rst,
   input  wire                clk,

   input  wire                wr_en,
   input  wire [WIDTH-1:0]    wr_data,
   input  wire                rd_en,
   output wire [WIDTH-1:0]    rd_data,

   output wire                full,
   output wire                empty,
   output reg                 overflow,
   output reg                 underflow,

   output wire [LVLW-1:0]     level
);

// parameters and width constants
localparam AWID = $clog2(DEPTH);              // memory address width
localparam LVLW = $clog2(DEPTH + 1);          // level output width

localparam [AWID:0] PTR_ZERO = {(AWID+1){1'b0}};
localparam [AWID:0] PTR_ONE  = {{AWID{1'b0}}, 1'b1};

// pointer registers

reg [AWID:0] wptr;
reg [AWID:0] rptr;

// Full:  wptr MSB toggled (one lap ahead) and address bits match
// Empty: all bits equal
wire wfull_val = (wptr[AWID] != rptr[AWID]) &&
                  (wptr[AWID-1:0] == rptr[AWID-1:0]);
wire rempty_val = (wptr == rptr);

assign full  = wfull_val;
assign empty = rempty_val;
assign level = wptr - rptr;

// qualified enables

wire wren = wr_en & ~full;
wire rden = rd_en & ~empty;

// write pipeline registers

reg [AWID-1:0] waddr_q;
reg [WIDTH-1:0] wr_data_q;
reg wren_q;

// read data path
reg [WIDTH-1:0] rd_data_mem;
reg [WIDTH-1:0] rd_data_fwd;
reg take_new;

// memory
(* ram_style = RAM_STYLE, ramstyle = RAM_STYLE *)
reg [WIDTH-1:0] mem [0:(1<<AWID)-1];

// parameter validation
initial begin
   if ((DEPTH < 2) || ((DEPTH & (DEPTH - 1)) != 0)) begin
      $error("sync_fifo DEPTH must be power-of-2 and >= 2, got %0d", DEPTH);
      $finish;
   end
end

// write pointer
always @(posedge clk) begin
   if (rst)
      wptr <= PTR_ZERO;
   else if (wren)
      wptr <= wptr + PTR_ONE;
end

// read pointer
always @(posedge clk) begin
   if (rst)
      rptr <= PTR_ZERO;
   else if (rden)
      rptr <= rptr + PTR_ONE;
end

// registered flags
always @(posedge clk) begin
   if (rst) begin
      overflow  <= 1'b0;
      underflow <= 1'b0;
   end else begin
      overflow  <= wr_en & full;
      underflow <= rd_en & empty;
   end
end

// write pipeline
always @(posedge clk) begin
   if (rst) begin
      wren_q <= 1'b0;
      waddr_q <= {AWID{1'b0}};
      wr_data_q <= {WIDTH{1'b0}};
   end else begin
      wren_q <= 1'b0;
      if (wren) begin
         wr_data_q <= wr_data;
         waddr_q <= wptr[AWID-1:0];
      end
   end
end

always @(posedge clk) begin
   if (wren)
      mem[wptr[AWID-1:0]] <= wr_data;
end

// read-after-write forwarding
always @(posedge clk) begin
   if (rst) begin
      take_new <= 1'b0;
      rd_data_fwd <= {WIDTH{1'b0}};
   end else begin
      take_new <= ((rptr[AWID-1:0] == wptr[AWID-1:0]) && wren);
      if ((rptr[AWID-1:0] == wptr[AWID-1:0]) && wren)
         rd_data_fwd <= wr_data;
   end
end

// read data mux
generate
   if (FWFT == "TRUE") begin : fwft
      always @(*) begin
         rd_data_mem = mem[rptr[AWID-1:0]];
      end
   end else begin : registered
      always @(posedge clk) begin
         if (rst)
            rd_data_mem <= {WIDTH{1'b0}};
         else if (rden)
            rd_data_mem <= mem[rptr[AWID-1:0]];
      end
   end
endgenerate

assign rd_data = take_new ? rd_data_fwd : rd_data_mem;

endmodule

`resetall
