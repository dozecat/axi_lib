//*****************************************************************************
// Copyright (C) 2025 dozecat. All rights reserved.
// SPDX-License-Identifier: MIT
//
// File:        axis_cdc.sv
// Description: AXI Stream Clock Domain Crossing
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
   parameter KEEP_ENABLE     = 1,
   parameter ID_ENABLE       = 1,
   parameter DEST_ENABLE     = 1,
   parameter USER_ENABLE     = 1
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

initial begin
   if (s_axis_if.DATA_WIDTH != m_axis_if.DATA_WIDTH)
      $error(1, "axis_cdc: DATA_WIDTH mismatch s=%0d m=%0d", s_axis_if.DATA_WIDTH, m_axis_if.DATA_WIDTH);
end

initial begin
   if (DEST_ENABLE && s_axis_if.DEST_WIDTH != m_axis_if.DEST_WIDTH)
      $error(1, "axis_cdc: DEST_WIDTH mismatch s=%0d m=%0d", s_axis_if.DEST_WIDTH, m_axis_if.DEST_WIDTH);
end

initial begin
   if (ID_ENABLE && s_axis_if.ID_WIDTH != m_axis_if.ID_WIDTH)
      $error(1, "axis_cdc: ID_WIDTH mismatch s=%0d m=%0d", s_axis_if.ID_WIDTH, m_axis_if.ID_WIDTH);
end

initial begin
   if (USER_ENABLE && s_axis_if.USER_WIDTH != m_axis_if.USER_WIDTH)
      $error(1, "axis_cdc: USER_WIDTH mismatch s=%0d m=%0d", s_axis_if.USER_WIDTH, m_axis_if.USER_WIDTH);
end

logic [PACK_WIDTH-1:0]        src_data;
logic                         req_toggle;

logic  ack_sync_r[2:0];
wire   ack_toggle_sync;

logic [PACK_WIDTH-1:0]        dst_data;
logic                         dst_valid;
logic                         ack_toggle;

logic  req_sync_r[1:0];
logic  req_sync_d1;
wire   req_event;

wire s_transfer = s_axis_if.tvalid & s_axis_if.tready;
assign s_axis_if.tready = (req_toggle == ack_toggle_sync);

always_ff @(posedge s_clk) begin
   if (s_rst) begin
      src_data   <= '0;
      req_toggle <= 1'b0;
   end else if (s_transfer) begin
      src_data[OFF_DATA +: DATA_WIDTH] <= s_axis_if.tdata;
      if (DEST_ENABLE) src_data[OFF_DEST +: DEST_WIDTH] <= s_axis_if.tdest;
      if (KEEP_ENABLE) src_data[OFF_KEEP +: KEEP_WIDTH] <= s_axis_if.tkeep;
      src_data[OFF_STRB +: STRB_WIDTH] <= s_axis_if.tstrb;
      src_data[OFF_LAST +: 1] <= s_axis_if.tlast;
      if (USER_ENABLE) src_data[OFF_USER +: USER_WIDTH] <= s_axis_if.tuser;
      if (ID_ENABLE)   src_data[OFF_ID   +: ID_WIDTH  ] <= s_axis_if.tid;
      req_toggle <= ~req_toggle;
   end
end

always_ff @(posedge s_clk) begin
   if (s_rst) begin
      ack_sync_r[0] <= 1'b0;
      ack_sync_r[1] <= 1'b0;
      ack_sync_r[2] <= 1'b0;
   end else begin
      ack_sync_r[0] <= ack_toggle;
      ack_sync_r[1] <= ack_sync_r[0];
      ack_sync_r[2] <= ack_sync_r[1];
   end
end
assign ack_toggle_sync = ack_sync_r[2];

always_ff @(posedge m_clk) begin
   if (m_rst) begin
      req_sync_r[0] <= 1'b0;
      req_sync_r[1] <= 1'b0;
   end else begin
      req_sync_r[0] <= req_toggle;
      req_sync_r[1] <= req_sync_r[0];
   end
end

always_ff @(posedge m_clk) begin
   if (m_rst)
      req_sync_d1 <= 1'b0;
   else
      req_sync_d1 <= req_sync_r[1];
end

assign req_event = req_sync_r[1] ^ req_sync_d1;

always_ff @(posedge m_clk) begin
   if (m_rst) begin
      dst_data   <= '0;
      dst_valid  <= 1'b0;
      ack_toggle <= 1'b0;
   end else if (req_event) begin
      dst_data   <= src_data;
      dst_valid  <= 1'b1;
      ack_toggle <= ~ack_toggle;
   end else if (m_axis_if.tready & dst_valid) begin
      dst_valid  <= 1'b0;
   end
end

assign m_axis_if.tvalid = dst_valid;
assign m_axis_if.tdata  = dst_data[OFF_DATA +: DATA_WIDTH];
assign m_axis_if.tdest  = DEST_ENABLE ? dst_data[OFF_DEST +: DEST_WIDTH] : {DEST_WIDTH{1'b0}};
assign m_axis_if.tkeep  = KEEP_ENABLE ? dst_data[OFF_KEEP +: KEEP_WIDTH] : {KEEP_WIDTH{1'b1}};
assign m_axis_if.tstrb  = dst_data[OFF_STRB +: STRB_WIDTH];
assign m_axis_if.tlast  = dst_data[OFF_LAST +: 1];
assign m_axis_if.tuser  = USER_ENABLE ? dst_data[OFF_USER +: USER_WIDTH] : {USER_WIDTH{1'b0}};
assign m_axis_if.tid    = ID_ENABLE   ? dst_data[OFF_ID   +: ID_WIDTH  ] : {ID_WIDTH{1'b0}};

endmodule

`resetall
