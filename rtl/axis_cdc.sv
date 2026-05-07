`timescale 1ns / 1ps
`default_nettype none

module axis_cdc #(
   parameter DATA_WIDTH  = 64,
   parameter DEST_WIDTH  = 1,
   parameter ID_WIDTH    = 8,
   parameter USER_WIDTH  = 1,
   parameter FIFO_DEPTH  = 16,
   parameter RAM_STYLE   = "distributed"
)(
   input  wire s_aclk,
   input  wire s_aresetn,
   input  wire m_aclk,
   input  wire m_aresetn,
   if_axis.slave  s_axis,
   if_axis.master m_axis
);

localparam KEEP_WIDTH = DATA_WIDTH / 8;
localparam STRB_WIDTH = DATA_WIDTH / 8;
localparam PACK_WIDTH = DATA_WIDTH + DEST_WIDTH + KEEP_WIDTH + STRB_WIDTH
                        + 1 + USER_WIDTH + ID_WIDTH;

logic [PACK_WIDTH-1:0] fifo_wr_data;
logic [PACK_WIDTH-1:0] fifo_rd_data;
logic                  fifo_full;
logic                  fifo_empty;
logic                  fifo_wr_en;
logic                  fifo_rd_en;

assign fifo_wr_data = {
   s_axis.tdata,
   s_axis.tdest,
   s_axis.tkeep,
   s_axis.tstrb,
   s_axis.tlast,
   s_axis.tuser,
   s_axis.tid
};

assign fifo_wr_en = s_axis.tvalid & ~fifo_full;
assign s_axis.tready = ~fifo_full;

assign fifo_rd_en = m_axis.tvalid & m_axis.tready;
assign m_axis.tvalid = ~fifo_empty;

assign {
   m_axis.tdata,
   m_axis.tdest,
   m_axis.tkeep,
   m_axis.tstrb,
   m_axis.tlast,
   m_axis.tuser,
   m_axis.tid
} = fifo_rd_data;

async_fifo #(
   .WIDTH     (PACK_WIDTH),
   .DEPTH     (FIFO_DEPTH),
   .RAM_STYLE (RAM_STYLE)
) u_fifo (
   .wclk    (s_aclk),
   .wrst    (~s_aresetn),
   .rclk    (m_aclk),
   .rrst    (~m_aresetn),
   .wr_en   (fifo_wr_en),
   .wr_data (fifo_wr_data),
   .full    (fifo_full),
   .rd_en   (fifo_rd_en),
   .rd_data (fifo_rd_data),
   .empty   (fifo_empty)
);

endmodule

`resetall
