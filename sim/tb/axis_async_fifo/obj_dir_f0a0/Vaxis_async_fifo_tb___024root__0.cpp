// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxis_async_fifo_tb.h for the primary calling header

#include "Vaxis_async_fifo_tb__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vaxis_async_fifo_tb___024root___eval_triggers__ico(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_triggers__ico\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
    vlSelfRef.__VicoFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vaxis_async_fifo_tb___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
}

bool Vaxis_async_fifo_tb___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___trigger_anySet__ico\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vaxis_async_fifo_tb___024root___ico_sequent__TOP__0(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___ico_sequent__TOP__0\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_en 
        = ((IData)(vlSymsp->TOP__axis_async_fifo_tb__DOT__s_axis_if.tready) 
           & (IData)(vlSelfRef.s_axis_tvalid));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_en 
        = ((IData)(vlSymsp->TOP__axis_async_fifo_tb__DOT__m_axis_if.tvalid) 
           & (IData)(vlSelfRef.m_axis_tready));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_data[0U] 
        = (IData)(vlSelfRef.s_axis_tdata);
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_data[1U] 
        = (IData)((vlSelfRef.s_axis_tdata >> 0x00000020U));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_data[2U] 
        = (0x0007ffffU & ((((IData)(vlSelfRef.s_axis_tuser) 
                            << 0x00000012U) | (((IData)(vlSelfRef.s_axis_tdest) 
                                                << 0x00000011U) 
                                               | ((IData)(vlSelfRef.s_axis_tid) 
                                                  << 9U))) 
                          | (((IData)(vlSelfRef.s_axis_tstrb) 
                              << 1U) | (IData)(vlSelfRef.s_axis_tlast))));
}

void Vaxis_async_fifo_tb___024root___eval_ico(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_ico\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vaxis_async_fifo_tb___024root___ico_sequent__TOP__0(vlSelf);
    }
}

bool Vaxis_async_fifo_tb___024root___eval_phase__ico(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_phase__ico\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vaxis_async_fifo_tb___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = Vaxis_async_fifo_tb___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vaxis_async_fifo_tb___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vaxis_async_fifo_tb___024root___eval_triggers__act(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_triggers__act\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    (((((IData)(vlSelfRef.m_rst) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__m_rst__0))) 
                                                       << 3U) 
                                                      | (((IData)(vlSelfRef.m_clk) 
                                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__m_clk__0))) 
                                                         << 2U)) 
                                                     | ((((IData)(vlSelfRef.s_rst) 
                                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__s_rst__0))) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.s_clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__s_clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__s_clk__0 = vlSelfRef.s_clk;
    vlSelfRef.__Vtrigprevexpr___TOP__s_rst__0 = vlSelfRef.s_rst;
    vlSelfRef.__Vtrigprevexpr___TOP__m_clk__0 = vlSelfRef.m_clk;
    vlSelfRef.__Vtrigprevexpr___TOP__m_rst__0 = vlSelfRef.m_rst;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vaxis_async_fifo_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vaxis_async_fifo_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vaxis_async_fifo_tb___024root___nba_sequent__TOP__0(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___nba_sequent__TOP__0\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__0__Vfuncout;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__0__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__0__gray;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__0__gray = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__4__Vfuncout;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__4__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__4__gray;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__4__gray = 0;
    // Body
    vlSelfRef.__VdlySet__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem__v0 = 0U;
    vlSelfRef.__VdlySet__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0 = 0U;
    if (((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_en) 
         & (~ (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_full)))) {
        vlSelfRef.__VdlyVal__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem__v0 
            = vlSelfRef.s_axis_tkeep;
        vlSelfRef.__VdlyDim0__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem__v0 
            = (0x0000000fU & (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr));
        vlSelfRef.__VdlySet__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem__v0 = 1U;
    }
    if (((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_en) 
         & (~ (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_full)))) {
        vlSelfRef.__VdlyVal__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0[0U] 
            = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_data[0U];
        vlSelfRef.__VdlyVal__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0[1U] 
            = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_data[1U];
        vlSelfRef.__VdlyVal__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0[2U] 
            = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_data[2U];
        vlSelfRef.__VdlyDim0__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0 
            = (0x0000000fU & (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr));
        vlSelfRef.__VdlySet__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0 = 1U;
    }
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray_wr 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray_ms;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray_wr 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray_ms;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__4__gray 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray_wr;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__4__gray;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp) 
                          ^ VL_SHIFTR_III(5,5,32, (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp), 1U)));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp) 
                          ^ VL_SHIFTR_III(5,5,32, (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp), 2U)));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp) 
                          ^ VL_SHIFTR_III(5,5,32, (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp), 4U)));
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__4__Vfuncout 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr_bin 
        = __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__4__Vfuncout;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray_ms 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__0__gray 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray_wr;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__0__gray;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp) 
                          ^ VL_SHIFTR_III(5,5,32, (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp), 1U)));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp) 
                          ^ VL_SHIFTR_III(5,5,32, (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp), 2U)));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp) 
                          ^ VL_SHIFTR_III(5,5,32, (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp), 4U)));
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__0__Vfuncout 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr_bin 
        = __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__0__Vfuncout;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray_ms 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray;
}

void Vaxis_async_fifo_tb___024root___nba_sequent__TOP__1(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___nba_sequent__TOP__1\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr;
    vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_overflow 
        = ((~ (IData)(vlSelfRef.s_rst)) & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_en) 
                                           & (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_full)));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_overflow 
        = ((~ (IData)(vlSelfRef.s_rst)) & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_en) 
                                           & (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_full)));
    vlSelfRef.s_aux_overflow = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_overflow;
    vlSelfRef.s_overflow = ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_overflow) 
                            | (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_overflow));
}

void Vaxis_async_fifo_tb___024root___nba_sequent__TOP__2(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___nba_sequent__TOP__2\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__3__Vfuncout;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__3__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__3__bin;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__3__bin = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__7__Vfuncout;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__7__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__7__bin;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__7__bin = 0;
    // Body
    vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr;
    vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_underflow 
        = ((~ (IData)(vlSelfRef.m_rst)) & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_en) 
                                           & (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_rd_empty)));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_underflow 
        = ((~ (IData)(vlSelfRef.m_rst)) & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_en) 
                                           & (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_empty)));
    if (vlSelfRef.m_rst) {
        vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr = 0U;
        vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray = 0U;
        vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr = 0U;
        vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray = 0U;
    } else {
        if (((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_en) 
             & (~ (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_rd_empty)))) {
            vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr 
                = (0x0000001fU & ((IData)(1U) + (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr)));
            __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__7__bin 
                = (0x0000001fU & ((IData)(1U) + (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr)));
            __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__7__Vfuncout 
                = (0x0000001fU & (VL_SHIFTR_III(5,5,32, (IData)(__Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__7__bin), 1U) 
                                  ^ (IData)(__Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__7__bin)));
            vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray 
                = __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__7__Vfuncout;
        }
        if (((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_en) 
             & (~ (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_empty)))) {
            vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr 
                = (0x0000001fU & ((IData)(1U) + (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr)));
            __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__3__bin 
                = (0x0000001fU & ((IData)(1U) + (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr)));
            __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__3__Vfuncout 
                = (0x0000001fU & (VL_SHIFTR_III(5,5,32, (IData)(__Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__3__bin), 1U) 
                                  ^ (IData)(__Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__3__bin)));
            vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray 
                = __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__3__Vfuncout;
        }
    }
    vlSelfRef.m_aux_underflow = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_underflow;
    vlSelfRef.m_underflow = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_underflow;
}

void Vaxis_async_fifo_tb___024root___nba_sequent__TOP__3(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___nba_sequent__TOP__3\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__1__Vfuncout;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__1__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__1__gray;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__1__gray = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__5__Vfuncout;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__5__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__5__gray;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__5__gray = 0;
    // Body
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_data 
        = (((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_en) 
            & (~ (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_rd_empty)))
            ? vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem
           [(0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr)))]
            : vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem
           [(0x0000000fU & (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr))]);
    if (((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_en) 
         & (~ (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_empty)))) {
        vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data[0U] 
            = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem
            [(0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr)))][0U];
        vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data[1U] 
            = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem
            [(0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr)))][1U];
        vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data[2U] 
            = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem
            [(0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr)))][2U];
    } else {
        vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data[0U] 
            = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem
            [(0x0000000fU & (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr))][0U];
        vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data[1U] 
            = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem
            [(0x0000000fU & (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr))][1U];
        vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data[2U] 
            = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem
            [(0x0000000fU & (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr))][2U];
    }
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray_rd 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray_ms;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray_rd 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray_ms;
    vlSelfRef.m_axis_tkeep = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_data;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tdata 
        = (((QData)((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data[1U])) 
            << 0x00000020U) | (QData)((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data[0U])));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tlast 
        = (1U & vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data[2U]);
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tstrb 
        = (0x000000ffU & (vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data[2U] 
                          >> 1U));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tid 
        = (0x000000ffU & (vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data[2U] 
                          >> 9U));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tdest 
        = (1U & (vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data[2U] 
                 >> 0x00000011U));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tuser 
        = (1U & (vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data[2U] 
                 >> 0x00000012U));
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__5__gray 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray_rd;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__5__gray;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp) 
                          ^ VL_SHIFTR_III(5,5,32, (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp), 1U)));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp) 
                          ^ VL_SHIFTR_III(5,5,32, (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp), 2U)));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp) 
                          ^ VL_SHIFTR_III(5,5,32, (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp), 4U)));
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__5__Vfuncout 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr_bin 
        = __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__5__Vfuncout;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray_ms 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__1__gray 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray_rd;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__1__gray;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp) 
                          ^ VL_SHIFTR_III(5,5,32, (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp), 1U)));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp) 
                          ^ VL_SHIFTR_III(5,5,32, (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp), 2U)));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp) 
                          ^ VL_SHIFTR_III(5,5,32, (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp), 4U)));
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__1__Vfuncout 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr_bin 
        = __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__1__Vfuncout;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray_ms 
        = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray;
    vlSelfRef.m_axis_tdata = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tdata;
    vlSelfRef.m_axis_tlast = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tlast;
    vlSelfRef.m_axis_tstrb = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tstrb;
    vlSelfRef.m_axis_tid = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tid;
    vlSelfRef.m_axis_tdest = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tdest;
    vlSelfRef.m_axis_tuser = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tuser;
}

void Vaxis_async_fifo_tb___024root___nba_sequent__TOP__4(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___nba_sequent__TOP__4\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.__VdlySet__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem__v0) {
        vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[vlSelfRef.__VdlyDim0__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem__v0] 
            = vlSelfRef.__VdlyVal__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem__v0;
    }
    if (vlSelfRef.__VdlySet__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0) {
        vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[vlSelfRef.__VdlyDim0__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0][0U] 
            = vlSelfRef.__VdlyVal__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0[0U];
        vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[vlSelfRef.__VdlyDim0__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0][1U] 
            = vlSelfRef.__VdlyVal__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0[1U];
        vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[vlSelfRef.__VdlyDim0__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0][2U] 
            = vlSelfRef.__VdlyVal__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0[2U];
    }
}

void Vaxis_async_fifo_tb___024root___nba_sequent__TOP__5(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___nba_sequent__TOP__5\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr 
        = vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr 
        = vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr;
}

void Vaxis_async_fifo_tb___024root___nba_sequent__TOP__6(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___nba_sequent__TOP__6\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__2__Vfuncout;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__2__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__2__bin;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__2__bin = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__6__Vfuncout;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__6__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__6__bin;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__6__bin = 0;
    // Body
    if (vlSelfRef.s_rst) {
        vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr = 0U;
        vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray = 0U;
        vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr = 0U;
        vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray = 0U;
    } else {
        if (((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_en) 
             & (~ (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_full)))) {
            vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr 
                = (0x0000001fU & ((IData)(1U) + (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr)));
            __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__6__bin 
                = (0x0000001fU & ((IData)(1U) + (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr)));
            __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__6__Vfuncout 
                = (0x0000001fU & (VL_SHIFTR_III(5,5,32, (IData)(__Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__6__bin), 1U) 
                                  ^ (IData)(__Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__6__bin)));
            vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray 
                = __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__bin2gray__6__Vfuncout;
        }
        if (((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_en) 
             & (~ (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_full)))) {
            vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr 
                = (0x0000001fU & ((IData)(1U) + (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr)));
            __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__2__bin 
                = (0x0000001fU & ((IData)(1U) + (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr)));
            __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__2__Vfuncout 
                = (0x0000001fU & (VL_SHIFTR_III(5,5,32, (IData)(__Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__2__bin), 1U) 
                                  ^ (IData)(__Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__2__bin)));
            vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray 
                = __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__bin2gray__2__Vfuncout;
        }
    }
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr 
        = vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr 
        = vlSelfRef.__Vdly__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr;
}

void Vaxis_async_fifo_tb___024root___nba_comb__TOP__0(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___nba_comb__TOP__0\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_rd_empty 
        = ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr) 
           == (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr_bin));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_level 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr_bin) 
                          - (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr)));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_level 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr_bin) 
                          - (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr)));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_empty 
        = ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr) 
           == (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr_bin));
    vlSelfRef.m_aux_level = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_level;
    vlSelfRef.m_level = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_level;
}

void Vaxis_async_fifo_tb___024root___nba_comb__TOP__1(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___nba_comb__TOP__1\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.m_axis_tvalid = vlSymsp->TOP__axis_async_fifo_tb__DOT__m_axis_if.tvalid;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_en 
        = ((IData)(vlSymsp->TOP__axis_async_fifo_tb__DOT__m_axis_if.tvalid) 
           & (IData)(vlSelfRef.m_axis_tready));
}

void Vaxis_async_fifo_tb___024root___nba_comb__TOP__2(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___nba_comb__TOP__2\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_full 
        = (((1U & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr) 
                   >> 4U)) != (1U & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr_bin) 
                                     >> 4U))) & ((0x0000000fU 
                                                  & (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr)) 
                                                 == 
                                                 (0x0000000fU 
                                                  & (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr_bin))));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_level 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr) 
                          - (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr_bin)));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_level 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr) 
                          - (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr_bin)));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_full 
        = (((1U & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr) 
                   >> 4U)) != (1U & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr_bin) 
                                     >> 4U))) & ((0x0000000fU 
                                                  & (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr)) 
                                                 == 
                                                 (0x0000000fU 
                                                  & (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr_bin))));
    vlSelfRef.s_aux_level = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_level;
    vlSelfRef.s_level = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_level;
}

void Vaxis_async_fifo_tb___024root___nba_comb__TOP__3(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___nba_comb__TOP__3\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.s_axis_tready = vlSymsp->TOP__axis_async_fifo_tb__DOT__s_axis_if.tready;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_en 
        = ((IData)(vlSymsp->TOP__axis_async_fifo_tb__DOT__s_axis_if.tready) 
           & (IData)(vlSelfRef.s_axis_tvalid));
}

void Vaxis_async_fifo_tb_if_axis___nba_comb__TOP__axis_async_fifo_tb__DOT__m_axis_if__0(Vaxis_async_fifo_tb_if_axis* vlSelf);
void Vaxis_async_fifo_tb_if_axis___nba_comb__TOP__axis_async_fifo_tb__DOT__s_axis_if__0(Vaxis_async_fifo_tb_if_axis* vlSelf);

void Vaxis_async_fifo_tb___024root___eval_nba(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_nba\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vaxis_async_fifo_tb___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vaxis_async_fifo_tb___024root___nba_sequent__TOP__1(vlSelf);
    }
    if ((0x000000000000000cULL & vlSelfRef.__VnbaTriggered
         [0U])) {
        Vaxis_async_fifo_tb___024root___nba_sequent__TOP__2(vlSelf);
    }
    if ((4ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vaxis_async_fifo_tb___024root___nba_sequent__TOP__3(vlSelf);
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vaxis_async_fifo_tb___024root___nba_sequent__TOP__4(vlSelf);
    }
    if ((0x000000000000000cULL & vlSelfRef.__VnbaTriggered
         [0U])) {
        Vaxis_async_fifo_tb___024root___nba_sequent__TOP__5(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vaxis_async_fifo_tb___024root___nba_sequent__TOP__6(vlSelf);
    }
    if ((0x000000000000000cULL & vlSelfRef.__VnbaTriggered
         [0U])) {
        Vaxis_async_fifo_tb___024root___nba_comb__TOP__0(vlSelf);
        Vaxis_async_fifo_tb_if_axis___nba_comb__TOP__axis_async_fifo_tb__DOT__m_axis_if__0((&vlSymsp->TOP__axis_async_fifo_tb__DOT__m_axis_if));
        Vaxis_async_fifo_tb___024root___nba_comb__TOP__1(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vaxis_async_fifo_tb___024root___nba_comb__TOP__2(vlSelf);
        Vaxis_async_fifo_tb_if_axis___nba_comb__TOP__axis_async_fifo_tb__DOT__s_axis_if__0((&vlSymsp->TOP__axis_async_fifo_tb__DOT__s_axis_if));
        Vaxis_async_fifo_tb___024root___nba_comb__TOP__3(vlSelf);
    }
}

void Vaxis_async_fifo_tb___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vaxis_async_fifo_tb___024root___eval_phase__act(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_phase__act\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vaxis_async_fifo_tb___024root___eval_triggers__act(vlSelf);
    Vaxis_async_fifo_tb___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vaxis_async_fifo_tb___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vaxis_async_fifo_tb___024root___eval_phase__nba(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_phase__nba\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vaxis_async_fifo_tb___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vaxis_async_fifo_tb___024root___eval_nba(vlSelf);
        Vaxis_async_fifo_tb___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vaxis_async_fifo_tb___024root___eval(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vaxis_async_fifo_tb___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("axis_async_fifo_tb.sv", 4, "", "Input combinational region did not converge after 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
    } while (Vaxis_async_fifo_tb___024root___eval_phase__ico(vlSelf));
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vaxis_async_fifo_tb___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("axis_async_fifo_tb.sv", 4, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vaxis_async_fifo_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("axis_async_fifo_tb.sv", 4, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vaxis_async_fifo_tb___024root___eval_phase__act(vlSelf));
    } while (Vaxis_async_fifo_tb___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vaxis_async_fifo_tb___024root___eval_debug_assertions(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_debug_assertions\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.s_clk & 0xfeU)))) {
        Verilated::overWidthError("s_clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.s_rst & 0xfeU)))) {
        Verilated::overWidthError("s_rst");
    }
    if (VL_UNLIKELY(((vlSelfRef.s_axis_tlast & 0xfeU)))) {
        Verilated::overWidthError("s_axis_tlast");
    }
    if (VL_UNLIKELY(((vlSelfRef.s_axis_tdest & 0xfeU)))) {
        Verilated::overWidthError("s_axis_tdest");
    }
    if (VL_UNLIKELY(((vlSelfRef.s_axis_tuser & 0xfeU)))) {
        Verilated::overWidthError("s_axis_tuser");
    }
    if (VL_UNLIKELY(((vlSelfRef.s_axis_tvalid & 0xfeU)))) {
        Verilated::overWidthError("s_axis_tvalid");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_clk & 0xfeU)))) {
        Verilated::overWidthError("m_clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_rst & 0xfeU)))) {
        Verilated::overWidthError("m_rst");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_axis_tready & 0xfeU)))) {
        Verilated::overWidthError("m_axis_tready");
    }
}
#endif  // VL_DEBUG
