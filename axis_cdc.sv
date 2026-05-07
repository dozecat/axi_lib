//*****************************************************************************
// Copyright (C) 2025 dozecat. All rights reserved.
// SPDX-License-Identifier: MIT
//
// File:        axis_cdc.sv
// Description: AXI Stream Clock Domain Crossing (wrapper)
// Repository:  https://github.com/dozecat/axi_lib.git
//
// Modification History:
// Ver   Who       Date        Changes
// ----  ----  ----------  ----------------------------------------------------
// 1.0         2025/12/25  Initial release
//*****************************************************************************

`timescale 1ns / 1ps
`default_nettype none

module axis_cdc #(
   parameter int DEPTH       = 4,
   parameter bit KEEP_ENABLE = 1,
   parameter bit ID_ENABLE   = 1,
   parameter bit DEST_ENABLE = 1,
   parameter bit USER_ENABLE = 1
)(
   input  wire               s_clk,
   input  wire               s_rst,
   input  wire               m_clk,
   input  wire               m_rst,

   if_axis.slave             s_axis_if,
   if_axis.master            m_axis_if
);

localparam DATA_WIDTH  = s_axis_if.DATA_WIDTH;
localparam DEST_WIDTH  = s_axis_if.DEST_WIDTH;
localparam ID_WIDTH    = s_axis_if.ID_WIDTH;
localparam USER_WIDTH  = s_axis_if.USER_WIDTH;
localparam KEEP_WIDTH  = DATA_WIDTH / 8;
localparam STRB_WIDTH  = DATA_WIDTH / 8;

localparam PACK_DEST   = DEST_ENABLE ? DEST_WIDTH : 0;
localparam PACK_KEEP   = KEEP_ENABLE ? KEEP_WIDTH : 0;
localparam PACK_STRB   = STRB_WIDTH;
localparam PACK_LAST   = 1;
localparam PACK_USER   = USER_ENABLE ? USER_WIDTH : 0;
localparam PACK_ID     = ID_ENABLE   ? ID_WIDTH   : 0;
localparam PACK_WIDTH  = DATA_WIDTH + PACK_DEST + PACK_KEEP + PACK_STRB
                        + PACK_LAST + PACK_USER + PACK_ID;

localparam OFF_DATA = 0;
localparam OFF_DEST = OFF_DATA + DATA_WIDTH;
localparam OFF_KEEP = OFF_DEST + PACK_DEST;
localparam OFF_STRB = OFF_KEEP + PACK_KEEP;
localparam OFF_LAST = OFF_STRB + PACK_STRB;
localparam OFF_USER = OFF_LAST + PACK_LAST;
localparam OFF_ID   = OFF_USER + PACK_USER;

localparam AW = $clog2(DEPTH);
localparam PW = AW + 1;

initial begin
   if (s_axis_if.DATA_WIDTH != m_axis_if.DATA_WIDTH)
      $fatal(1, "axis_cdc: DATA_WIDTH mismatch s=%0d m=%0d", s_axis_if.DATA_WIDTH, m_axis_if.DATA_WIDTH);
end

initial begin
   if (DEST_ENABLE && s_axis_if.DEST_WIDTH != m_axis_if.DEST_WIDTH)
      $fatal(1, "axis_cdc: DEST_WIDTH mismatch s=%0d m=%0d", s_axis_if.DEST_WIDTH, m_axis_if.DEST_WIDTH);
end

initial begin
   if (ID_ENABLE && s_axis_if.ID_WIDTH != m_axis_if.ID_WIDTH)
      $fatal(1, "axis_cdc: ID_WIDTH mismatch s=%0d m=%0d", s_axis_if.ID_WIDTH, m_axis_if.ID_WIDTH);
end

initial begin
   if (USER_ENABLE && s_axis_if.USER_WIDTH != m_axis_if.USER_WIDTH)
      $fatal(1, "axis_cdc: USER_WIDTH mismatch s=%0d m=%0d", s_axis_if.USER_WIDTH, m_axis_if.USER_WIDTH);
end

initial begin
   if (DEPTH < 2 || (DEPTH & (DEPTH - 1)) != 0)
      $fatal(1, "axis_cdc: DEPTH must be power of 2 and >= 2, got %0d", DEPTH);
end

function automatic logic [PW-1:0] bin2gray(input logic [PW-1:0] bin);
   bin2gray = bin ^ (bin >> 1);
endfunction

logic [PACK_WIDTH-1:0] mem [0:DEPTH-1];

logic [PW-1:0] wr_bin;
logic [PW-1:0] wr_gray;
logic [PW-1:0] rd_gray_sync_s[1:0];
wire [PW-1:0]  rd_gray_s = rd_gray_sync_s[1];
wire           full      = (wr_gray == {~rd_gray_s[PW-1:PW-2], rd_gray_s[PW-3:0]});

logic [PW-1:0] rd_bin;
logic [PW-1:0] rd_gray;
logic [PW-1:0] wr_gray_sync_m[1:0];
wire [PW-1:0]  wr_gray_m = wr_gray_sync_m[1];
wire           empty    = (rd_gray == wr_gray_m);

logic [PACK_WIDTH-1:0] s_packed;
always_comb begin
   s_packed = '0;
   s_packed[OFF_DATA +: DATA_WIDTH] = s_axis_if.tdata;
   if (DEST_ENABLE) s_packed[OFF_DEST +: DEST_WIDTH] = s_axis_if.tdest;
   if (KEEP_ENABLE) s_packed[OFF_KEEP +: KEEP_WIDTH] = s_axis_if.tkeep;
   s_packed[OFF_STRB +: STRB_WIDTH] = s_axis_if.tstrb;
   s_packed[OFF_LAST +: 1] = s_axis_if.tlast;
   if (USER_ENABLE) s_packed[OFF_USER +: USER_WIDTH] = s_axis_if.tuser;
   if (ID_ENABLE) s_packed[OFF_ID +: ID_WIDTH] = s_axis_if.tid;
end

wire [PACK_WIDTH-1:0] m_packed = mem[rd_bin[AW-1:0]];

assign s_axis_if.tready = !full;

always_ff @(posedge s_clk) begin
   if (s_rst) begin
      wr_bin  <= '0;
      wr_gray <= '0;
   end else if (s_axis_if.tvalid && !full) begin
      mem[wr_bin[AW-1:0]] <= s_packed;
      wr_bin  <= wr_bin + 1'd1;
      wr_gray <= bin2gray(wr_bin + 1'd1);
   end
end

always_ff @(posedge s_clk) begin
   if (s_rst) begin
      rd_gray_sync_s[0] <= '0;
      rd_gray_sync_s[1] <= '0;
   end else begin
      rd_gray_sync_s[0] <= rd_gray;
      rd_gray_sync_s[1] <= rd_gray_sync_s[0];
   end
end

always_ff @(posedge m_clk) begin
   if (m_rst) begin
      wr_gray_sync_m[0] <= '0;
      wr_gray_sync_m[1] <= '0;
   end else begin
      wr_gray_sync_m[0] <= wr_gray;
      wr_gray_sync_m[1] <= wr_gray_sync_m[0];
   end
end

always_ff @(posedge m_clk) begin
   if (m_rst) begin
      rd_bin  <= '0;
      rd_gray <= '0;
   end else if (!empty && m_axis_if.tready) begin
      rd_bin  <= rd_bin + 1'd1;
      rd_gray <= bin2gray(rd_bin + 1'd1);
   end
end

assign m_axis_if.tvalid = !empty;
assign m_axis_if.tdata  = m_packed[OFF_DATA +: DATA_WIDTH];
assign m_axis_if.tdest  = DEST_ENABLE ? m_packed[OFF_DEST +: DEST_WIDTH] : {DEST_WIDTH{1'b0}};
assign m_axis_if.tkeep  = KEEP_ENABLE ? m_packed[OFF_KEEP +: KEEP_WIDTH] : {KEEP_WIDTH{1'b1}};
assign m_axis_if.tstrb  = m_packed[OFF_STRB +: STRB_WIDTH];
assign m_axis_if.tlast  = m_packed[OFF_LAST +: 1];
assign m_axis_if.tuser  = USER_ENABLE ? m_packed[OFF_USER +: USER_WIDTH] : {USER_WIDTH{1'b0}};
assign m_axis_if.tid    = ID_ENABLE   ? m_packed[OFF_ID   +: ID_WIDTH  ] : {ID_WIDTH{1'b0}};

endmodule

`resetall
