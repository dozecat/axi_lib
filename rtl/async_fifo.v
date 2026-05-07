`timescale 1 ns / 1 ps
`default_nettype none

module async_fifo #(
   parameter WIDTH  = 8,
   parameter DEPTH  = 16,
   parameter RAM_STYLE = "distributed"
)(
   input  wire                wclk,
   input  wire                wrst,
   input  wire                rclk,
   input  wire                rrst,

   input  wire                wr_en,
   input  wire [WIDTH-1:0]    wr_data,
   output wire                full,

   input  wire                rd_en,
   output wire [WIDTH-1:0]    rd_data,
   output wire                empty
);

localparam AW = $clog2(DEPTH);

function automatic [AW:0] bin2gray;
   input [AW:0] bin;
   bin2gray = bin ^ (bin >> 1);
endfunction

reg [AW:0] wptr_bin;
reg [AW:0] rptr_bin;
reg [AW:0] wptr_gray;
reg [AW:0] rptr_gray;

reg [AW:0] wq1_rptr_gray;
reg [AW:0] wq2_rptr_gray;
reg [AW:0] rq1_wptr_gray;
reg [AW:0] rq2_wptr_gray;

(* ram_style = RAM_STYLE, ramstyle = RAM_STYLE *)
reg [WIDTH-1:0] mem [0:DEPTH-1];

wire winc = wr_en & ~full;
wire rinc = rd_en & ~empty;

wire [AW:0] wptr_bin_next = wptr_bin + winc;
wire [AW:0] wptr_gray_next = bin2gray(wptr_bin_next);

generate
   if (AW >= 2) begin : g_full_wide
      assign full = (wptr_gray_next == {~wq2_rptr_gray[AW], ~wq2_rptr_gray[AW-1],
                                         wq2_rptr_gray[AW-2:0]});
   end else begin : g_full_aw1
      assign full = (wptr_gray_next == {~wq2_rptr_gray[1], ~wq2_rptr_gray[0]});
   end
endgenerate

assign empty = (rptr_gray == rq2_wptr_gray);

wire [AW-1:0] waddr = wptr_bin[AW-1:0];
wire [AW-1:0] raddr = rptr_bin[AW-1:0];

assign rd_data = mem[raddr];

always @(posedge wclk) begin
   if (wrst)
      wptr_bin <= {(AW+1){1'b0}};
   else if (winc)
      wptr_bin <= wptr_bin_next;
end

always @(posedge wclk) begin
   if (wrst)
      wptr_gray <= {(AW+1){1'b0}};
   else if (winc)
      wptr_gray <= wptr_gray_next;
end

always @(posedge rclk) begin
   if (rrst) begin
      rptr_bin  <= {(AW+1){1'b0}};
      rptr_gray <= {(AW+1){1'b0}};
   end else if (rinc) begin
      rptr_bin  <= rptr_bin + 1'b1;
      rptr_gray <= bin2gray(rptr_bin + 1'b1);
   end
end

always @(posedge wclk) begin
   if (wrst) begin
      wq1_rptr_gray <= {(AW+1){1'b0}};
      wq2_rptr_gray <= {(AW+1){1'b0}};
   end else begin
      wq1_rptr_gray <= rptr_gray;
      wq2_rptr_gray <= wq1_rptr_gray;
   end
end

always @(posedge rclk) begin
   if (rrst) begin
      rq1_wptr_gray <= {(AW+1){1'b0}};
      rq2_wptr_gray <= {(AW+1){1'b0}};
   end else begin
      rq1_wptr_gray <= wptr_gray;
      rq2_wptr_gray <= rq1_wptr_gray;
   end
end

always @(posedge wclk) begin
   if (winc)
      mem[waddr] <= wr_data;
end

initial begin
   if (DEPTH < 2 || (DEPTH & (DEPTH - 1)) != 0) begin
      $error("async_fifo DEPTH must be power-of-2 and >= 2, got %0d", DEPTH);
      $finish;
   end
end

endmodule

`resetall
