// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaxis_async_fifo_tb.h for the primary calling header

#ifndef VERILATED_VAXIS_ASYNC_FIFO_TB___024ROOT_H_
#define VERILATED_VAXIS_ASYNC_FIFO_TB___024ROOT_H_  // guard

#include "verilated.h"
class Vaxis_async_fifo_tb_if_axis;


class Vaxis_async_fifo_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaxis_async_fifo_tb___024root final {
  public:
    // CELLS
    Vaxis_async_fifo_tb_if_axis* __PVT__axis_async_fifo_tb__DOT__s_axis_if;
    Vaxis_async_fifo_tb_if_axis* __PVT__axis_async_fifo_tb__DOT__m_axis_if;

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(s_clk,0,0);
        VL_IN8(s_rst,0,0);
        VL_IN8(m_clk,0,0);
        VL_IN8(m_rst,0,0);
        VL_IN8(s_axis_tkeep,7,0);
        VL_IN8(s_axis_tstrb,7,0);
        VL_IN8(s_axis_tlast,0,0);
        VL_IN8(s_axis_tid,7,0);
        VL_IN8(s_axis_tdest,0,0);
        VL_IN8(s_axis_tuser,0,0);
        VL_IN8(s_axis_tvalid,0,0);
        VL_OUT8(s_axis_tready,0,0);
        VL_OUT8(m_axis_tkeep,7,0);
        VL_OUT8(m_axis_tstrb,7,0);
        VL_OUT8(m_axis_tlast,0,0);
        VL_OUT8(m_axis_tid,7,0);
        VL_OUT8(m_axis_tdest,0,0);
        VL_OUT8(m_axis_tuser,0,0);
        VL_OUT8(m_axis_tvalid,0,0);
        VL_IN8(m_axis_tready,0,0);
        VL_OUT8(s_level,4,0);
        VL_OUT8(s_overflow,0,0);
        VL_OUT8(s_aux_level,4,0);
        VL_OUT8(s_aux_overflow,0,0);
        VL_OUT8(s_bad_frame,0,0);
        VL_OUT8(s_good_frame,0,0);
        VL_OUT8(m_level,4,0);
        VL_OUT8(m_underflow,0,0);
        VL_OUT8(m_aux_level,4,0);
        VL_OUT8(m_aux_underflow,0,0);
        VL_OUT8(m_bad_frame,0,0);
        VL_OUT8(m_good_frame,0,0);
        VL_OUT8(tb_frame_fifo,0,0);
        VL_OUT8(tb_always_recv,0,0);
        CData/*0:0*/ axis_async_fifo_tb__DOT__s_clk;
        CData/*0:0*/ axis_async_fifo_tb__DOT__s_rst;
        CData/*7:0*/ axis_async_fifo_tb__DOT__s_axis_tkeep;
        CData/*7:0*/ axis_async_fifo_tb__DOT__s_axis_tstrb;
        CData/*0:0*/ axis_async_fifo_tb__DOT__s_axis_tlast;
        CData/*7:0*/ axis_async_fifo_tb__DOT__s_axis_tid;
        CData/*0:0*/ axis_async_fifo_tb__DOT__s_axis_tdest;
        CData/*0:0*/ axis_async_fifo_tb__DOT__s_axis_tuser;
        CData/*0:0*/ axis_async_fifo_tb__DOT__s_axis_tvalid;
        CData/*0:0*/ axis_async_fifo_tb__DOT__s_axis_tready;
        CData/*0:0*/ axis_async_fifo_tb__DOT__m_clk;
        CData/*0:0*/ axis_async_fifo_tb__DOT__m_rst;
        CData/*7:0*/ axis_async_fifo_tb__DOT__m_axis_tkeep;
        CData/*7:0*/ axis_async_fifo_tb__DOT__m_axis_tstrb;
        CData/*0:0*/ axis_async_fifo_tb__DOT__m_axis_tlast;
        CData/*7:0*/ axis_async_fifo_tb__DOT__m_axis_tid;
        CData/*0:0*/ axis_async_fifo_tb__DOT__m_axis_tdest;
        CData/*0:0*/ axis_async_fifo_tb__DOT__m_axis_tuser;
        CData/*0:0*/ axis_async_fifo_tb__DOT__m_axis_tvalid;
        CData/*0:0*/ axis_async_fifo_tb__DOT__m_axis_tready;
        CData/*4:0*/ axis_async_fifo_tb__DOT__s_level;
        CData/*0:0*/ axis_async_fifo_tb__DOT__s_overflow;
        CData/*4:0*/ axis_async_fifo_tb__DOT__s_aux_level;
        CData/*0:0*/ axis_async_fifo_tb__DOT__s_aux_overflow;
        CData/*0:0*/ axis_async_fifo_tb__DOT__s_bad_frame;
        CData/*0:0*/ axis_async_fifo_tb__DOT__s_good_frame;
        CData/*4:0*/ axis_async_fifo_tb__DOT__m_level;
        CData/*0:0*/ axis_async_fifo_tb__DOT__m_underflow;
        CData/*4:0*/ axis_async_fifo_tb__DOT__m_aux_level;
        CData/*0:0*/ axis_async_fifo_tb__DOT__m_aux_underflow;
    };
    struct {
        CData/*0:0*/ axis_async_fifo_tb__DOT__m_bad_frame;
        CData/*0:0*/ axis_async_fifo_tb__DOT__m_good_frame;
        CData/*0:0*/ axis_async_fifo_tb__DOT__tb_frame_fifo;
        CData/*0:0*/ axis_async_fifo_tb__DOT__tb_always_recv;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__s_clk;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__s_rst;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__s_level;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__s_overflow;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__s_aux_level;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__s_aux_overflow;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__s_bad_frame;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__s_good_frame;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__m_clk;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__m_rst;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__m_level;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__m_underflow;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__m_aux_level;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__m_aux_underflow;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__m_bad_frame;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__m_good_frame;
        CData/*7:0*/ axis_async_fifo_tb__DOT__dut__DOT__afifo_tkeep;
        CData/*7:0*/ axis_async_fifo_tb__DOT__dut__DOT__afifo_tstrb;
        CData/*7:0*/ axis_async_fifo_tb__DOT__dut__DOT__afifo_tid;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__afifo_tdest;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__afifo_tuser;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__afifo_bad_frame;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__afifo_rd_empty;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__afifo_rd_en_fsm;
        CData/*7:0*/ axis_async_fifo_tb__DOT__dut__DOT__frame_tkeep;
        CData/*7:0*/ axis_async_fifo_tb__DOT__dut__DOT__frame_tstrb;
        CData/*7:0*/ axis_async_fifo_tb__DOT__dut__DOT__frame_tid;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__frame_tdest;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__frame_tuser;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__frame_is_bad;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_en;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_full;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_overflow;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_level;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_en;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_empty;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_underflow;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_level;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_tlast;
        CData/*7:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_tkeep;
        CData/*7:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_tstrb;
        CData/*7:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_tid;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_tdest;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_tuser;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_en;
        CData/*7:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_data;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_full;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_overflow;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_level;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_en;
        CData/*7:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_data;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_underflow;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_level;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_rst;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_rst;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_clk;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_en;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_full;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_overflow;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_level;
    };
    struct {
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_clk;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_en;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_empty;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_underflow;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_level;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray_ms;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray_rd;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray_ms;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray_wr;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr_bin;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr_bin;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wfull_val;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rempty_val;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wdiff;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rdiff;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_rst;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_rst;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_clk;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_en;
        CData/*7:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_data;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_full;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_overflow;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_level;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_clk;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_en;
        CData/*7:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_data;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_empty;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_underflow;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_level;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray_ms;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray_rd;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray_ms;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray_wr;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr_bin;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr_bin;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wfull_val;
        CData/*0:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rempty_val;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wdiff;
        CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rdiff;
        CData/*4:0*/ __Vdly__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr;
        CData/*4:0*/ __Vdly__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr;
        CData/*4:0*/ __Vdly__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr;
        CData/*4:0*/ __Vdly__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr;
        CData/*3:0*/ __VdlyDim0__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0;
        CData/*0:0*/ __VdlySet__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0;
        CData/*7:0*/ __VdlyVal__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem__v0;
        CData/*3:0*/ __VdlyDim0__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem__v0;
        CData/*0:0*/ __VdlySet__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem__v0;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__s_clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__s_rst__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__m_clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__m_rst__0;
    };
    struct {
        VL_OUT(tb_depth,31,0);
        VL_OUT(tb_data_width,31,0);
        IData/*31:0*/ axis_async_fifo_tb__DOT__tb_depth;
        IData/*31:0*/ axis_async_fifo_tb__DOT__tb_data_width;
        VlWide<3>/*82:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_data;
        VlWide<3>/*82:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data;
        VlWide<3>/*82:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_data;
        VlWide<3>/*82:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_data;
        IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__i;
        IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i;
        IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__i;
        IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i;
        VlWide<3>/*82:0*/ __VdlyVal__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0;
        IData/*31:0*/ __VactIterCount;
        VL_IN64(s_axis_tdata,63,0);
        VL_OUT64(m_axis_tdata,63,0);
        QData/*63:0*/ axis_async_fifo_tb__DOT__s_axis_tdata;
        QData/*63:0*/ axis_async_fifo_tb__DOT__m_axis_tdata;
        QData/*63:0*/ axis_async_fifo_tb__DOT__dut__DOT__dfifo_tdata;
        VlUnpacked<VlWide<3>/*82:0*/, 16> axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem;
        VlUnpacked<CData/*7:0*/, 16> axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    };

    // INTERNAL VARIABLES
    Vaxis_async_fifo_tb__Syms* vlSymsp;
    const char* vlNamep;

    // PARAMETERS
    static constexpr CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__AUX_ENABLE = 0x1fU;
    static constexpr CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__AUX_FIFO_USE = 0x10U;
    static constexpr CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__PTR_ZERO = 0U;
    static constexpr CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__PTR_ONE = 1U;
    static constexpr CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__PTR_ZERO = 0U;
    static constexpr CData/*4:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__PTR_ONE = 1U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__DATA_WIDTH = 0x00000040U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__ID_WIDTH = 8U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__DEST_WIDTH = 1U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__USER_WIDTH = 1U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__DEPTH = 0x00000010U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__FRAME_FIFO = 0U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__ALWAYS_RECEIVE = 0U;
    static constexpr VlWide<3>/*87:0*/ axis_async_fifo_tb__DOT__RAM_STYLE = VlWide<3>{{0x75746564, 0x74726962, 0x00646973}};
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__AUX_DEPTH = 0x00000010U;
    static constexpr VlWide<3>/*87:0*/ axis_async_fifo_tb__DOT__AUX_RAM_STYLE = VlWide<3>{{0x75746564, 0x74726962, 0x00646973}};
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__KEEP_WIDTH = 8U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__STRB_WIDTH = 8U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__FRAME_FIFO = 0U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__ALWAYS_RECEIVE = 0U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__DEPTH = 0x00000010U;
    static constexpr VlWide<3>/*87:0*/ axis_async_fifo_tb__DOT__dut__DOT__RAM_STYLE = VlWide<3>{{0x75746564, 0x74726962, 0x00646973}};
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__AUX_DEPTH = 0x00000010U;
    static constexpr VlWide<3>/*87:0*/ axis_async_fifo_tb__DOT__dut__DOT__AUX_RAM_STYLE = VlWide<3>{{0x75746564, 0x74726962, 0x00646973}};
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__DATA_WIDTH = 0x00000040U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__KEEP_WIDTH = 8U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__STRB_WIDTH = 8U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__ID_WIDTH = 8U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__DEST_WIDTH = 1U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__USER_WIDTH = 1U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__LVLW = 5U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__AUX_DEPTH_VAL = 0x00000010U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__AUX_LVLW = 5U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__D_TDATA_OFF = 0U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__D_TKEEP_OFF = 0x00000040U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__D_TLAST_OFF = 0x00000040U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__D_TSTRB_OFF = 0x00000041U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__D_TID_OFF = 0x00000049U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__D_TDEST_OFF = 0x00000051U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__D_TUSER_OFF = 0x00000052U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__DATA_FIFO_WIDTH = 0x00000053U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__A_TKEEP_OFF = 0U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__A_TSTRB_OFF = 8U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__A_TID_OFF = 8U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__A_TDEST_OFF = 8U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__A_TUSER_OFF = 8U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__A_BAD_OFF = 8U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__AUX_FIFO_RAW_WIDTH = 8U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__AUX_FIFO_WIDTH = 8U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__WIDTH = 0x00000053U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__DEPTH = 0x00000010U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__FWFT = 0x74727565U;
    static constexpr VlWide<3>/*87:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__RAM_STYLE = VlWide<3>{{0x75746564, 0x74726962, 0x00646973}};
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__AWID = 4U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__PTRW = 5U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__LVLW = 5U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__WIDTH = 8U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__DEPTH = 0x00000010U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__FWFT = 0x74727565U;
    static constexpr VlWide<3>/*87:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__RAM_STYLE = VlWide<3>{{0x75746564, 0x74726962, 0x00646973}};
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__AWID = 4U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__PTRW = 5U;
    static constexpr IData/*31:0*/ axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__LVLW = 5U;

    // CONSTRUCTORS
    Vaxis_async_fifo_tb___024root(Vaxis_async_fifo_tb__Syms* symsp, const char* namep);
    ~Vaxis_async_fifo_tb___024root();
    VL_UNCOPYABLE(Vaxis_async_fifo_tb___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
