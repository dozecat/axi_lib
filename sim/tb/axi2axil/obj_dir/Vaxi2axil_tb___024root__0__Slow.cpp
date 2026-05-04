// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxi2axil_tb.h for the primary calling header

#include "Vaxi2axil_tb__pch.h"

VL_ATTR_COLD void Vaxi2axil_tb___024root___eval_static(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval_static\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
}

VL_ATTR_COLD void Vaxi2axil_tb___024root___eval_initial(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval_initial\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vaxi2axil_tb___024root___eval_final(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval_final\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxi2axil_tb___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vaxi2axil_tb___024root___eval_phase__stl(Vaxi2axil_tb___024root* vlSelf);

VL_ATTR_COLD void Vaxi2axil_tb___024root___eval_settle(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval_settle\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vaxi2axil_tb___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("axi2axil_tb.sv", 16, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vaxi2axil_tb___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vaxi2axil_tb___024root___eval_triggers__stl(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval_triggers__stl\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vaxi2axil_tb___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vaxi2axil_tb___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxi2axil_tb___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vaxi2axil_tb___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vaxi2axil_tb___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___trigger_anySet__stl\n"); );
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

extern const VlUnpacked<CData/*1:0*/, 512> Vaxi2axil_tb__ConstPool__TABLE_h70a9bd5b_0;
extern const VlUnpacked<CData/*1:0*/, 512> Vaxi2axil_tb__ConstPool__TABLE_hc2665c4e_0;

VL_ATTR_COLD void Vaxi2axil_tb___024root___stl_sequent__TOP__0(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___stl_sequent__TOP__0\n"); );
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
    // Body
    vlSelfRef.m_bid = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_id;
    vlSelfRef.m_rdata = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_rdata_q;
    vlSelfRef.m_rresp = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_rresp_q;
    vlSelfRef.m_rid = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_id;
    vlSelfRef.m_rvalid = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_dvalid;
    vlSelfRef.s_awprot = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_prot;
    vlSelfRef.s_wdata = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wdata_q;
    vlSelfRef.s_wstrb = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wstrb_q;
    vlSelfRef.s_arprot = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_prot;
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
    vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_last = 
        ((IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_beat) 
         >= (IData)(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_len));
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
    vlSelfRef.s_awaddr = vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_beat_addr;
    vlSelfRef.s_araddr = vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_beat_addr;
}

VL_ATTR_COLD void Vaxi2axil_tb___024root___stl_sequent__TOP__1(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___stl_sequent__TOP__1\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.m_awready = vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.awready;
    vlSelfRef.m_bvalid = vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.bvalid;
    vlSelfRef.m_arready = vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.arready;
    vlSelfRef.m_wready = vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.wready;
    vlSelfRef.m_bresp = vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.bresp;
    vlSelfRef.m_rlast = vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.rlast;
    vlSelfRef.s_bready = vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if.bready;
    vlSelfRef.s_arvalid = vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if.arvalid;
    vlSelfRef.s_rready = vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if.rready;
    vlSelfRef.s_awvalid = vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if.awvalid;
    vlSelfRef.s_wvalid = vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if.awvalid;
}

VL_ATTR_COLD void Vaxi2axil_tb_if_axi__A10_I8___stl_sequent__TOP__axi2axil_tb__DOT__axi_slv_if__0(Vaxi2axil_tb_if_axi__A10_I8* vlSelf);
VL_ATTR_COLD void Vaxi2axil_tb_if_axil__D40___stl_sequent__TOP__axi2axil_tb__DOT__axil_mst_if__0(Vaxi2axil_tb_if_axil__D40* vlSelf);

VL_ATTR_COLD void Vaxi2axil_tb___024root___eval_stl(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval_stl\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vaxi2axil_tb___024root___stl_sequent__TOP__0(vlSelf);
        Vaxi2axil_tb_if_axi__A10_I8___stl_sequent__TOP__axi2axil_tb__DOT__axi_slv_if__0((&vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if));
        Vaxi2axil_tb_if_axil__D40___stl_sequent__TOP__axi2axil_tb__DOT__axil_mst_if__0((&vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if));
        Vaxi2axil_tb___024root___stl_sequent__TOP__1(vlSelf);
    }
}

VL_ATTR_COLD bool Vaxi2axil_tb___024root___eval_phase__stl(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___eval_phase__stl\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vaxi2axil_tb___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vaxi2axil_tb___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vaxi2axil_tb___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vaxi2axil_tb___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxi2axil_tb___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vaxi2axil_tb___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vaxi2axil_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxi2axil_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vaxi2axil_tb___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vaxi2axil_tb___024root___ctor_var_reset(Vaxi2axil_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root___ctor_var_reset\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1638864771569018232ull);
    vlSelf->m_awid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16394950902815574590ull);
    vlSelf->m_awaddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 3169234031117663542ull);
    vlSelf->m_awlen = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 13394423541176324255ull);
    vlSelf->m_awsize = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 13160256126570148354ull);
    vlSelf->m_awburst = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10312526296998696398ull);
    vlSelf->m_awcache = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 2693276432124214361ull);
    vlSelf->m_awlock = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2307138178591418983ull);
    vlSelf->m_awprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 12265871149664643295ull);
    vlSelf->m_awqos = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 4366988113743344168ull);
    vlSelf->m_awregion = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 284295280768860601ull);
    vlSelf->m_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6959745953305777653ull);
    vlSelf->m_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4259156306466528033ull);
    vlSelf->m_wdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 15494961946000700504ull);
    vlSelf->m_wstrb = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16102823512841672097ull);
    vlSelf->m_wid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6963002225322899985ull);
    vlSelf->m_wlast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2600293730191863169ull);
    vlSelf->m_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14788020737313657040ull);
    vlSelf->m_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1728470165562692237ull);
    vlSelf->m_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13089959803563711611ull);
    vlSelf->m_bid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9987844304016030498ull);
    vlSelf->m_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8973761176877109757ull);
    vlSelf->m_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 866843429093315018ull);
    vlSelf->m_arid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5380731426131582360ull);
    vlSelf->m_araddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 2374049049873106714ull);
    vlSelf->m_arlen = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 9351101179588457779ull);
    vlSelf->m_arsize = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 267850028161621430ull);
    vlSelf->m_arburst = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 7641253239825668471ull);
    vlSelf->m_arcache = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 12071739831360063651ull);
    vlSelf->m_arlock = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3971082766457045435ull);
    vlSelf->m_arprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 261648877812645399ull);
    vlSelf->m_arqos = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 4518539605400792833ull);
    vlSelf->m_arregion = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 11161665052597162745ull);
    vlSelf->m_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14018080948827659885ull);
    vlSelf->m_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11734703036927835001ull);
    vlSelf->m_rdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 14308343192490993725ull);
    vlSelf->m_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 6332025148105678889ull);
    vlSelf->m_rid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15430107651537149892ull);
    vlSelf->m_rlast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7267810819620092262ull);
    vlSelf->m_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3102679248430181142ull);
    vlSelf->m_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1313307773326899870ull);
    vlSelf->s_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15943857874525107354ull);
    vlSelf->s_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4918823101085808447ull);
    vlSelf->s_awaddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 779103011958781805ull);
    vlSelf->s_awprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 15150428810498139838ull);
    vlSelf->s_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14002152698677192039ull);
    vlSelf->s_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13515512478695746316ull);
    vlSelf->s_wdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13325040402057955508ull);
    vlSelf->s_wstrb = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5022708899488754323ull);
    vlSelf->s_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15281852200509557954ull);
    vlSelf->s_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 679853055183660306ull);
    vlSelf->s_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16525949292227129891ull);
    vlSelf->s_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6951755687480165749ull);
    vlSelf->s_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9121568763004205844ull);
    vlSelf->s_araddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 6950598773701058237ull);
    vlSelf->s_arprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 17367931703268741372ull);
    vlSelf->s_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6837359908538963129ull);
    vlSelf->s_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18293703372854712141ull);
    vlSelf->s_rdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 2301979449509909042ull);
    vlSelf->s_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 18109029074036420517ull);
    vlSelf->axi2axil_tb__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14263863421475411352ull);
    vlSelf->axi2axil_tb__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8318215413747581531ull);
    vlSelf->axi2axil_tb__DOT__m_awid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11190210599633210648ull);
    vlSelf->axi2axil_tb__DOT__m_awaddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1468717210937762084ull);
    vlSelf->axi2axil_tb__DOT__m_awlen = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2742032280495581454ull);
    vlSelf->axi2axil_tb__DOT__m_awsize = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 15438249262842036608ull);
    vlSelf->axi2axil_tb__DOT__m_awburst = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 4663537138581672368ull);
    vlSelf->axi2axil_tb__DOT__m_awcache = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 3418061762825510279ull);
    vlSelf->axi2axil_tb__DOT__m_awlock = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9355053847721860662ull);
    vlSelf->axi2axil_tb__DOT__m_awprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 5680475334203232614ull);
    vlSelf->axi2axil_tb__DOT__m_awqos = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 13623766306488137199ull);
    vlSelf->axi2axil_tb__DOT__m_awregion = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 5330982349048664635ull);
    vlSelf->axi2axil_tb__DOT__m_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8893412159523348360ull);
    vlSelf->axi2axil_tb__DOT__m_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5624521346565614434ull);
    vlSelf->axi2axil_tb__DOT__m_wdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 15946406780211813477ull);
    vlSelf->axi2axil_tb__DOT__m_wstrb = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3357497777168430730ull);
    vlSelf->axi2axil_tb__DOT__m_wid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5860571072077010261ull);
    vlSelf->axi2axil_tb__DOT__m_wlast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11823436297907441326ull);
    vlSelf->axi2axil_tb__DOT__m_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4847964018588929642ull);
    vlSelf->axi2axil_tb__DOT__m_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2814465654252987135ull);
    vlSelf->axi2axil_tb__DOT__m_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14765524990750740317ull);
    vlSelf->axi2axil_tb__DOT__m_bid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2434621022031853897ull);
    vlSelf->axi2axil_tb__DOT__m_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8693271049909842284ull);
    vlSelf->axi2axil_tb__DOT__m_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9572465724684456645ull);
    vlSelf->axi2axil_tb__DOT__m_arid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 4429611757445937670ull);
    vlSelf->axi2axil_tb__DOT__m_araddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4733456862167716046ull);
    vlSelf->axi2axil_tb__DOT__m_arlen = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15719946660617050091ull);
    vlSelf->axi2axil_tb__DOT__m_arsize = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 14889656348429134579ull);
    vlSelf->axi2axil_tb__DOT__m_arburst = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5705409063676598554ull);
    vlSelf->axi2axil_tb__DOT__m_arcache = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 408387818354084566ull);
    vlSelf->axi2axil_tb__DOT__m_arlock = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11288092860877635934ull);
    vlSelf->axi2axil_tb__DOT__m_arprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10821625607754038004ull);
    vlSelf->axi2axil_tb__DOT__m_arqos = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 17602393443644207309ull);
    vlSelf->axi2axil_tb__DOT__m_arregion = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 1735857236985716667ull);
    vlSelf->axi2axil_tb__DOT__m_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15623981790365197851ull);
    vlSelf->axi2axil_tb__DOT__m_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7184714084431990014ull);
    vlSelf->axi2axil_tb__DOT__m_rdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 3640155937261314823ull);
    vlSelf->axi2axil_tb__DOT__m_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9867034804073567686ull);
    vlSelf->axi2axil_tb__DOT__m_rid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14723215137179947449ull);
    vlSelf->axi2axil_tb__DOT__m_rlast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14960428333469705410ull);
    vlSelf->axi2axil_tb__DOT__m_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9549307141930462490ull);
    vlSelf->axi2axil_tb__DOT__m_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18371288845456211395ull);
    vlSelf->axi2axil_tb__DOT__s_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4229265279780732757ull);
    vlSelf->axi2axil_tb__DOT__s_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14576869251210843314ull);
    vlSelf->axi2axil_tb__DOT__s_awaddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 9049158731693089254ull);
    vlSelf->axi2axil_tb__DOT__s_awprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11556545419078113857ull);
    vlSelf->axi2axil_tb__DOT__s_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13988283135376096502ull);
    vlSelf->axi2axil_tb__DOT__s_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14081822258916501770ull);
    vlSelf->axi2axil_tb__DOT__s_wdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 15388176750022920618ull);
    vlSelf->axi2axil_tb__DOT__s_wstrb = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1860482591069466883ull);
    vlSelf->axi2axil_tb__DOT__s_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11511586867031007207ull);
    vlSelf->axi2axil_tb__DOT__s_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11095037054830886970ull);
    vlSelf->axi2axil_tb__DOT__s_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11547575186993630697ull);
    vlSelf->axi2axil_tb__DOT__s_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 39051770628773420ull);
    vlSelf->axi2axil_tb__DOT__s_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15410675715448797865ull);
    vlSelf->axi2axil_tb__DOT__s_araddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 13069545831236756694ull);
    vlSelf->axi2axil_tb__DOT__s_arprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 8020218260625616086ull);
    vlSelf->axi2axil_tb__DOT__s_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10918792961790572330ull);
    vlSelf->axi2axil_tb__DOT__s_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17178141711974400623ull);
    vlSelf->axi2axil_tb__DOT__s_rdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 5051985838993463814ull);
    vlSelf->axi2axil_tb__DOT__s_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5025083735195913760ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__aclk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5140728223517203429ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__aresetn = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13776497098033181457ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 4482924300074869744ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_nstate = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14661294892993330269ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_addr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7293138290429935455ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_len = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6696140060686652117ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_size = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 4486222716696787806ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_burst = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12561078982158609139ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_id = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10481022446585365667ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_prot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 5550390744140198550ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_beat = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16355901980873221580ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_resp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 505561414067889233ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_err = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17904776816140714783ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_wdata_q = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 7314182308575251389ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_wstrb_q = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5288497305376861472ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_wlast_q = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1169877453685348372ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_wpend = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 633682860215119729ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__wr_beat_addr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7392631035163612013ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__rd_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3387106455570307767ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__rd_nstate = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 16328825837651459878ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__rd_addr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 4025197132839006124ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__rd_len = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8595691430054446604ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__rd_size = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 11838378227183883249ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__rd_burst = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10321238562232357878ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__rd_id = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14014084051254518907ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__rd_prot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 6716854955033396162ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__rd_beat = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17618418913603051022ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__rd_rdata_q = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 9260911231527764096ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__rd_rresp_q = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 18389188836382661927ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__rd_dvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16835534124001395440ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__rd_beat_addr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 2024802730561657363ull);
    vlSelf->axi2axil_tb__DOT__dut__DOT__rd_last = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1111357665064206640ull);
    vlSelf->__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__Vfuncout = 0;
    vlSelf->__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__wrap_bytes = 0;
    vlSelf->__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__Vfuncout = 0;
    vlSelf->__Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__wrap_bytes = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
