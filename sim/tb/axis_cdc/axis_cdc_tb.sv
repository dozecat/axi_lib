`timescale 1ns / 1ps

module axis_cdc_tb (
    input  wire               s_clk,
    input  wire               s_rst,
    input  wire               m_clk,
    input  wire               m_rst,

    input  wire  [63:0]       s_axis_tdata,
    input  wire  [7:0]        s_axis_tkeep,
    input  wire  [7:0]        s_axis_tstrb,
    input  wire  [7:0]        s_axis_tid,
    input  wire               s_axis_tdest,
    input  wire               s_axis_tuser,
    input  wire               s_axis_tlast,
    input  wire               s_axis_tvalid,
    output logic              s_axis_tready,

    output logic [63:0]       m_axis_tdata,
    output logic [7:0]        m_axis_tkeep,
    output logic [7:0]        m_axis_tstrb,
    output logic [7:0]        m_axis_tid,
    output logic              m_axis_tdest,
    output logic              m_axis_tuser,
    output logic              m_axis_tlast,
    output logic              m_axis_tvalid,
    input  wire               m_axis_tready
);

if_axis #(
    .DATA_WIDTH(64),
    .ID_WIDTH(8),
    .DEST_WIDTH(1),
    .USER_WIDTH(1)
) s_axis_if ();

if_axis #(
    .DATA_WIDTH(64),
    .ID_WIDTH(8),
    .DEST_WIDTH(1),
    .USER_WIDTH(1)
) m_axis_if ();

// s_axis_if is slave modport in DUT:
// DUT receives tdata/tvalid, drives tready
assign s_axis_if.tdata  = s_axis_tdata;
assign s_axis_if.tkeep  = s_axis_tkeep;
assign s_axis_if.tstrb  = s_axis_tstrb;
assign s_axis_if.tid    = s_axis_tid;
assign s_axis_if.tdest  = s_axis_tdest;
assign s_axis_if.tuser  = s_axis_tuser;
assign s_axis_if.tlast  = s_axis_tlast;
assign s_axis_if.tvalid = s_axis_tvalid;
assign s_axis_tready    = s_axis_if.tready;

// m_axis_if is master modport in DUT:
// DUT drives tdata/tvalid, receives tready
assign m_axis_tdata  = m_axis_if.tdata;
assign m_axis_tkeep  = m_axis_if.tkeep;
assign m_axis_tstrb  = m_axis_if.tstrb;
assign m_axis_tid    = m_axis_if.tid;
assign m_axis_tdest  = m_axis_if.tdest;
assign m_axis_tuser  = m_axis_if.tuser;
assign m_axis_tlast  = m_axis_if.tlast;
assign m_axis_tvalid = m_axis_if.tvalid;
assign m_axis_if.tready = m_axis_tready;

axis_cdc dut (
    .s_clk      ( s_clk    ),
    .s_rst      ( s_rst    ),
    .m_clk      ( m_clk    ),
    .m_rst      ( m_rst    ),
    .s_axis_if  ( s_axis_if ),
    .m_axis_if  ( m_axis_if )
);

endmodule
