// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxi2axil_tb.h for the primary calling header

#include "Vaxi2axil_tb__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxi2axil_tb___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vaxi2axil_tb___024root___eval_triggers__ico(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval_triggers__ico\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
    vlSelfRef.__VicoFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vaxi2axil_tb___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
}

bool Vaxi2axil_tb___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___trigger_anySet__ico\n"); );
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

extern const VlUnpacked<CData/*1:0*/, 512> Vaxi2axil_tb__ConstPool__TABLE_hc2665c4e_0;
extern const VlUnpacked<CData/*1:0*/, 512> Vaxi2axil_tb__ConstPool__TABLE_h70a9bd5b_0;

void Vaxi2axil_tb___024root___ico_sequent__TOP__0(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___ico_sequent__TOP__0\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    SData/*8:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    SData/*8:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    // Body
    __Vtableidx2 = ((((IData)(vlSelfRef.m_arvalid) 
                      << 8U) | (((IData)(vlSelfRef.s_arready) 
                                 << 7U) | (((IData)(vlSelfRef.s_rvalid) 
                                            << 6U) 
                                           | (((IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_last)
                                                ? 0U
                                                : 1U) 
                                              << 4U)))) 
                    | (((IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_dvalid) 
                        << 3U) | (((IData)(vlSelfRef.m_rready) 
                                   << 2U) | (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_state))));
    vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_nstate 
        = Vaxi2axil_tb__ConstPool__TABLE_hc2665c4e_0
        [__Vtableidx2];
    __Vtableidx1 = ((((((IData)(vlSelfRef.m_awvalid) 
                        << 4U) | (((IData)(vlSelfRef.s_wready) 
                                   << 3U) | ((IData)(vlSelfRef.s_awready) 
                                             << 2U))) 
                      | (((IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wpend) 
                          << 1U) | (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wlast_q))) 
                     << 4U) | (((IData)(vlSelfRef.s_bvalid) 
                                << 3U) | (((IData)(vlSelfRef.m_bready) 
                                           << 2U) | (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_state))));
    vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_nstate 
        = Vaxi2axil_tb__ConstPool__TABLE_h70a9bd5b_0
        [__Vtableidx1];
}

void Vaxi2axil_tb___024root___eval_ico(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval_ico\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vaxi2axil_tb___024root___ico_sequent__TOP__0(vlSelf);
    }
}

bool Vaxi2axil_tb___024root___eval_phase__ico(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval_phase__ico\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vaxi2axil_tb___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = Vaxi2axil_tb___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vaxi2axil_tb___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxi2axil_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void Vaxi2axil_tb___024root___eval_triggers__act(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval_triggers__act\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((((~ (IData)(vlSelfRef.rst_n)) 
                                                       & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0)) 
                                                      << 1U) 
                                                     | ((IData)(vlSelfRef.clk) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vaxi2axil_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool Vaxi2axil_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___trigger_anySet__act\n"); );
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

void Vaxi2axil_tb___024root___nba_sequent__TOP__0(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___nba_sequent__TOP__0\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    SData/*15:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__base;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__base = 0;
    CData/*7:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__len;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__len = 0;
    CData/*2:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__size;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__size = 0;
    CData/*1:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__burst;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__burst = 0;
    CData/*7:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__beat;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__beat = 0;
    SData/*15:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__offset;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__offset = 0;
    SData/*15:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__base;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__base = 0;
    CData/*7:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__len;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__len = 0;
    CData/*2:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__size;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__size = 0;
    CData/*1:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__burst;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__burst = 0;
    CData/*7:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__beat;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__beat = 0;
    SData/*15:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__offset;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__offset = 0;
    SData/*8:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    SData/*8:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    CData/*7:0*/ __Vdly__axi2axil_tb__DOT__dut__DOT__wr_beat;
    __Vdly__axi2axil_tb__DOT__dut__DOT__wr_beat = 0;
    CData/*0:0*/ __Vdly__axi2axil_tb__DOT__dut__DOT__wr_wpend;
    __Vdly__axi2axil_tb__DOT__dut__DOT__wr_wpend = 0;
    CData/*7:0*/ __Vdly__axi2axil_tb__DOT__dut__DOT__rd_beat;
    __Vdly__axi2axil_tb__DOT__dut__DOT__rd_beat = 0;
    CData/*0:0*/ __Vdly__axi2axil_tb__DOT__dut__DOT__rd_dvalid;
    __Vdly__axi2axil_tb__DOT__dut__DOT__rd_dvalid = 0;
    // Body
    __Vdly__axi2axil_tb__DOT__dut__DOT__wr_wpend = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wpend;
    __Vdly__axi2axil_tb__DOT__dut__DOT__rd_dvalid = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_dvalid;
    __Vdly__axi2axil_tb__DOT__dut__DOT__rd_beat = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_beat;
    __Vdly__axi2axil_tb__DOT__dut__DOT__wr_beat = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_beat;
    if (vlSelfRef.rst_n) {
        if (((0U == (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_state)) 
             & (IData)(vlSelfRef.m_arvalid))) {
            __Vdly__axi2axil_tb__DOT__dut__DOT__rd_beat = 0U;
            __Vdly__axi2axil_tb__DOT__dut__DOT__rd_dvalid = 0U;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_id 
                = vlSelfRef.m_arid;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_prot 
                = vlSelfRef.m_arprot;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_addr 
                = vlSelfRef.m_araddr;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_size 
                = vlSelfRef.m_arsize;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_burst 
                = vlSelfRef.m_arburst;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_len 
                = vlSelfRef.m_arlen;
        }
        if (((2U == (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_state)) 
             & (IData)(vlSelfRef.s_rvalid))) {
            __Vdly__axi2axil_tb__DOT__dut__DOT__rd_dvalid = 1U;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_rdata_q 
                = vlSelfRef.s_rdata;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_rresp_q 
                = vlSelfRef.s_rresp;
        }
        if ((((3U == (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_state)) 
              & (IData)(vlSelfRef.m_rready)) & (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_dvalid))) {
            if ((1U & (~ (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_last)))) {
                __Vdly__axi2axil_tb__DOT__dut__DOT__rd_beat 
                    = (0x000000ffU & ((IData)(1U) + (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_beat)));
            }
            __Vdly__axi2axil_tb__DOT__dut__DOT__rd_dvalid = 0U;
        }
        if (((0U == (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_state)) 
             & (IData)(vlSelfRef.m_awvalid))) {
            __Vdly__axi2axil_tb__DOT__dut__DOT__wr_beat = 0U;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_id 
                = vlSelfRef.m_awid;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_prot 
                = vlSelfRef.m_awprot;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_err = 0U;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_resp = 0U;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_addr 
                = vlSelfRef.m_awaddr;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_size 
                = vlSelfRef.m_awsize;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_burst 
                = vlSelfRef.m_awburst;
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_len 
                = vlSelfRef.m_awlen;
            __Vdly__axi2axil_tb__DOT__dut__DOT__wr_wpend = 0U;
        }
        if (((2U == (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_state)) 
             & (IData)(vlSelfRef.s_bvalid))) {
            if ((1U & (~ (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wlast_q)))) {
                __Vdly__axi2axil_tb__DOT__dut__DOT__wr_beat 
                    = (0x000000ffU & ((IData)(1U) + (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_beat)));
            }
            if ((0U != (IData)(vlSelfRef.s_bresp))) {
                vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_err = 1U;
            }
            vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_resp 
                = vlSelfRef.s_bresp;
        }
        if ((1U == (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_state))) {
            if (((~ (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wpend)) 
                 & (IData)(vlSelfRef.m_wvalid))) {
                vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wdata_q 
                    = vlSelfRef.m_wdata;
                vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wstrb_q 
                    = vlSelfRef.m_wstrb;
                vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wlast_q 
                    = vlSelfRef.m_wlast;
                __Vdly__axi2axil_tb__DOT__dut__DOT__wr_wpend = 1U;
            } else if ((((IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wpend) 
                         & (IData)(vlSelfRef.s_awready)) 
                        & (IData)(vlSelfRef.s_wready))) {
                __Vdly__axi2axil_tb__DOT__dut__DOT__wr_wpend = 0U;
            }
        }
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_state 
            = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_nstate;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_state 
            = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_nstate;
    } else {
        __Vdly__axi2axil_tb__DOT__dut__DOT__rd_beat = 0U;
        __Vdly__axi2axil_tb__DOT__dut__DOT__rd_dvalid = 0U;
        __Vdly__axi2axil_tb__DOT__dut__DOT__wr_beat = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_rdata_q = 0ULL;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_rresp_q = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_id = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_prot = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_addr = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_size = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_burst = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_id = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_prot = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_err = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_resp = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_len = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_addr = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_size = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_burst = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_len = 0U;
        __Vdly__axi2axil_tb__DOT__dut__DOT__wr_wpend = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wdata_q = 0ULL;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wstrb_q = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wlast_q = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_state = 0U;
        vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_state = 0U;
    }
    vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_dvalid 
        = __Vdly__axi2axil_tb__DOT__dut__DOT__rd_dvalid;
    vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_beat = __Vdly__axi2axil_tb__DOT__dut__DOT__rd_beat;
    vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_beat = __Vdly__axi2axil_tb__DOT__dut__DOT__wr_beat;
    vlSelfRef.m_rvalid = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_dvalid;
    vlSelfRef.m_rdata = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_rdata_q;
    vlSelfRef.m_rresp = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_rresp_q;
    vlSelfRef.m_rid = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_id;
    vlSelfRef.s_arprot = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_prot;
    vlSelfRef.m_bid = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_id;
    vlSelfRef.s_awprot = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_prot;
    vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_last = 
        ((IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_beat) 
         >= (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_len));
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__beat 
        = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_beat;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__burst 
        = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_burst;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__size 
        = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_size;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__len 
        = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_len;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__base 
        = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_addr;
    vlSelf->__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__wrap_bytes = 0;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__offset 
        = (0x0000ffffU & ((IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__beat) 
                          << (IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__size)));
    if ((1U == (IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__burst))) {
        vlSelfRef.__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__Vfuncout 
            = (0x0000ffffU & ((IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__base) 
                              + (IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__offset)));
    } else if ((2U == (IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__burst))) {
        vlSelfRef.__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__wrap_bytes 
            = (0x0000ffffU & (((IData)(1U) + (IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__len)) 
                              << (IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__size)));
        vlSelfRef.__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__Vfuncout 
            = (0x0000ffffU & (((IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__base) 
                               & (~ ((IData)(vlSelfRef.__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__wrap_bytes) 
                                     - (IData)(1U)))) 
                              | (((IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__base) 
                                  + (IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__offset)) 
                                 & ((IData)(vlSelfRef.__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__wrap_bytes) 
                                    - (IData)(1U)))));
    } else {
        vlSelfRef.__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__Vfuncout 
            = __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__base;
    }
    vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_beat_addr 
        = vlSelfRef.__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__Vfuncout;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__beat 
        = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_beat;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__burst 
        = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_burst;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__size 
        = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_size;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__len 
        = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_len;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__base 
        = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_addr;
    vlSelf->__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__wrap_bytes = 0;
    __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__offset 
        = (0x0000ffffU & ((IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__beat) 
                          << (IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__size)));
    if ((1U == (IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__burst))) {
        vlSelfRef.__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__Vfuncout 
            = (0x0000ffffU & ((IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__base) 
                              + (IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__offset)));
    } else if ((2U == (IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__burst))) {
        vlSelfRef.__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__wrap_bytes 
            = (0x0000ffffU & (((IData)(1U) + (IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__len)) 
                              << (IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__size)));
        vlSelfRef.__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__Vfuncout 
            = (0x0000ffffU & (((IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__base) 
                               & (~ ((IData)(vlSelfRef.__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__wrap_bytes) 
                                     - (IData)(1U)))) 
                              | (((IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__base) 
                                  + (IData)(__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__offset)) 
                                 & ((IData)(vlSelfRef.__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__wrap_bytes) 
                                    - (IData)(1U)))));
    } else {
        vlSelfRef.__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__Vfuncout 
            = __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__base;
    }
    vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_beat_addr 
        = vlSelfRef.__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__Vfuncout;
    vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wpend 
        = __Vdly__axi2axil_tb__DOT__dut__DOT__wr_wpend;
    vlSelfRef.s_araddr = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_beat_addr;
    vlSelfRef.s_awaddr = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_beat_addr;
    vlSelfRef.s_wdata = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wdata_q;
    vlSelfRef.s_wstrb = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wstrb_q;
    __Vtableidx2 = ((((IData)(vlSelfRef.m_arvalid) 
                      << 8U) | (((IData)(vlSelfRef.s_arready) 
                                 << 7U) | (((IData)(vlSelfRef.s_rvalid) 
                                            << 6U) 
                                           | (((IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_last)
                                                ? 0U
                                                : 1U) 
                                              << 4U)))) 
                    | (((IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_dvalid) 
                        << 3U) | (((IData)(vlSelfRef.m_rready) 
                                   << 2U) | (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_state))));
    vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_nstate 
        = Vaxi2axil_tb__ConstPool__TABLE_hc2665c4e_0
        [__Vtableidx2];
    __Vtableidx1 = ((((((IData)(vlSelfRef.m_awvalid) 
                        << 4U) | (((IData)(vlSelfRef.s_wready) 
                                   << 3U) | ((IData)(vlSelfRef.s_awready) 
                                             << 2U))) 
                      | (((IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wpend) 
                          << 1U) | (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wlast_q))) 
                     << 4U) | (((IData)(vlSelfRef.s_bvalid) 
                                << 3U) | (((IData)(vlSelfRef.m_bready) 
                                           << 2U) | (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_state))));
    vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_nstate 
        = Vaxi2axil_tb__ConstPool__TABLE_h70a9bd5b_0
        [__Vtableidx1];
}

void Vaxi2axil_tb___024root___nba_sequent__TOP__1(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___nba_sequent__TOP__1\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.m_bresp = vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.bresp;
    vlSelfRef.m_rlast = vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.rlast;
    vlSelfRef.m_arready = vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.arready;
    vlSelfRef.m_awready = vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.awready;
    vlSelfRef.m_bvalid = vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.bvalid;
    vlSelfRef.m_wready = vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.wready;
    vlSelfRef.s_arvalid = vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if.arvalid;
    vlSelfRef.s_rready = vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if.rready;
    vlSelfRef.s_bready = vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if.bready;
    vlSelfRef.s_awvalid = vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if.awvalid;
    vlSelfRef.s_wvalid = vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if.awvalid;
}

void Vaxi2axil_tb_if_axi__A10_I8___nba_sequent__TOP__axi2axil_tb__DOT__axi_slv_if__0(Vaxi2axil_tb_if_axi__A10_I8* vlSelf);
void Vaxi2axil_tb_if_axil__D40___nba_sequent__TOP__axi2axil_tb__DOT__axil_mst_if__0(Vaxi2axil_tb_if_axil__D40* vlSelf);

void Vaxi2axil_tb___024root___eval_nba(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval_nba\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vaxi2axil_tb___024root___nba_sequent__TOP__0(vlSelf);
        Vaxi2axil_tb_if_axi__A10_I8___nba_sequent__TOP__axi2axil_tb__DOT__axi_slv_if__0((&vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if));
        Vaxi2axil_tb_if_axil__D40___nba_sequent__TOP__axi2axil_tb__DOT__axil_mst_if__0((&vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if));
        Vaxi2axil_tb___024root___nba_sequent__TOP__1(vlSelf);
    }
}

void Vaxi2axil_tb___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vaxi2axil_tb___024root___eval_phase__act(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval_phase__act\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vaxi2axil_tb___024root___eval_triggers__act(vlSelf);
    Vaxi2axil_tb___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vaxi2axil_tb___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vaxi2axil_tb___024root___eval_phase__nba(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval_phase__nba\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vaxi2axil_tb___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vaxi2axil_tb___024root___eval_nba(vlSelf);
        Vaxi2axil_tb___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vaxi2axil_tb___024root___eval(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
            Vaxi2axil_tb___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("axi2axil_tb.sv", 16, "", "Input combinational region did not converge after 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
    } while (Vaxi2axil_tb___024root___eval_phase__ico(vlSelf));
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vaxi2axil_tb___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("axi2axil_tb.sv", 16, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vaxi2axil_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("axi2axil_tb.sv", 16, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (Vaxi2axil_tb___024root___eval_phase__act(vlSelf));
    } while (Vaxi2axil_tb___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void Vaxi2axil_tb___024root___eval_debug_assertions(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval_debug_assertions\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst_n & 0xfeU)))) {
        Verilated::overWidthError("rst_n");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_awsize & 0xf8U)))) {
        Verilated::overWidthError("m_awsize");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_awburst & 0xfcU)))) {
        Verilated::overWidthError("m_awburst");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_awcache & 0xf0U)))) {
        Verilated::overWidthError("m_awcache");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_awlock & 0xfeU)))) {
        Verilated::overWidthError("m_awlock");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_awprot & 0xf8U)))) {
        Verilated::overWidthError("m_awprot");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_awqos & 0xf0U)))) {
        Verilated::overWidthError("m_awqos");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_awregion & 0xf0U)))) {
        Verilated::overWidthError("m_awregion");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_awvalid & 0xfeU)))) {
        Verilated::overWidthError("m_awvalid");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_wlast & 0xfeU)))) {
        Verilated::overWidthError("m_wlast");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_wvalid & 0xfeU)))) {
        Verilated::overWidthError("m_wvalid");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_bready & 0xfeU)))) {
        Verilated::overWidthError("m_bready");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_arsize & 0xf8U)))) {
        Verilated::overWidthError("m_arsize");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_arburst & 0xfcU)))) {
        Verilated::overWidthError("m_arburst");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_arcache & 0xf0U)))) {
        Verilated::overWidthError("m_arcache");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_arlock & 0xfeU)))) {
        Verilated::overWidthError("m_arlock");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_arprot & 0xf8U)))) {
        Verilated::overWidthError("m_arprot");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_arqos & 0xf0U)))) {
        Verilated::overWidthError("m_arqos");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_arregion & 0xf0U)))) {
        Verilated::overWidthError("m_arregion");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_arvalid & 0xfeU)))) {
        Verilated::overWidthError("m_arvalid");
    }
    if (VL_UNLIKELY(((vlSelfRef.m_rready & 0xfeU)))) {
        Verilated::overWidthError("m_rready");
    }
    if (VL_UNLIKELY(((vlSelfRef.s_awready & 0xfeU)))) {
        Verilated::overWidthError("s_awready");
    }
    if (VL_UNLIKELY(((vlSelfRef.s_wready & 0xfeU)))) {
        Verilated::overWidthError("s_wready");
    }
    if (VL_UNLIKELY(((vlSelfRef.s_bvalid & 0xfeU)))) {
        Verilated::overWidthError("s_bvalid");
    }
    if (VL_UNLIKELY(((vlSelfRef.s_bresp & 0xfcU)))) {
        Verilated::overWidthError("s_bresp");
    }
    if (VL_UNLIKELY(((vlSelfRef.s_arready & 0xfeU)))) {
        Verilated::overWidthError("s_arready");
    }
    if (VL_UNLIKELY(((vlSelfRef.s_rvalid & 0xfeU)))) {
        Verilated::overWidthError("s_rvalid");
    }
    if (VL_UNLIKELY(((vlSelfRef.s_rresp & 0xfcU)))) {
        Verilated::overWidthError("s_rresp");
    }
}
#endif  // VL_DEBUG
