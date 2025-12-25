// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxil_test.h for the primary calling header

#include "Vaxil_test__pch.h"
#include "Vaxil_test___024root.h"

void Vaxil_test___024root___ico_sequent__TOP__0(Vaxil_test___024root* vlSelf);

void Vaxil_test___024root___eval_ico(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___eval_ico\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vaxil_test___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vaxil_test___024root___ico_sequent__TOP__0(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___ico_sequent__TOP__0\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.axil_test__DOT__clk = vlSelfRef.clk;
    vlSelfRef.axil_test__DOT__rst = vlSelfRef.rst;
    vlSelfRef.axil_test__DOT__s_axil_awaddr = vlSelfRef.s_axil_awaddr;
    vlSelfRef.axil_test__DOT__s_axil_awprot = vlSelfRef.s_axil_awprot;
    vlSelfRef.axil_test__DOT__s_axil_awvalid = vlSelfRef.s_axil_awvalid;
    vlSelfRef.axil_test__DOT__s_axil_wdata = vlSelfRef.s_axil_wdata;
    vlSelfRef.axil_test__DOT__s_axil_wstrb = vlSelfRef.s_axil_wstrb;
    vlSelfRef.axil_test__DOT__s_axil_wvalid = vlSelfRef.s_axil_wvalid;
    vlSelfRef.axil_test__DOT__s_axil_bready = vlSelfRef.s_axil_bready;
    vlSelfRef.axil_test__DOT__s_axil_araddr = vlSelfRef.s_axil_araddr;
    vlSelfRef.axil_test__DOT__s_axil_arprot = vlSelfRef.s_axil_arprot;
    vlSelfRef.axil_test__DOT__s_axil_arvalid = vlSelfRef.s_axil_arvalid;
    vlSelfRef.axil_test__DOT__s_axil_rready = vlSelfRef.s_axil_rready;
    vlSelfRef.axil_test__DOT__m_axil_awready = vlSelfRef.m_axil_awready;
    vlSelfRef.axil_test__DOT__m_axil_wready = vlSelfRef.m_axil_wready;
    vlSelfRef.axil_test__DOT__m_axil_bresp = vlSelfRef.m_axil_bresp;
    vlSelfRef.axil_test__DOT__m_axil_bvalid = vlSelfRef.m_axil_bvalid;
    vlSelfRef.axil_test__DOT__m_axil_arready = vlSelfRef.m_axil_arready;
    vlSelfRef.axil_test__DOT__m_axil_rdata = vlSelfRef.m_axil_rdata;
    vlSelfRef.axil_test__DOT__m_axil_rresp = vlSelfRef.m_axil_rresp;
    vlSelfRef.axil_test__DOT__m_axil_rvalid = vlSelfRef.m_axil_rvalid;
    vlSelfRef.m_axil_awaddr = vlSelfRef.s_axil_awaddr;
    vlSelfRef.m_axil_awprot = vlSelfRef.s_axil_awprot;
    vlSelfRef.m_axil_awvalid = vlSelfRef.s_axil_awvalid;
    vlSelfRef.s_axil_awready = vlSelfRef.m_axil_awready;
    vlSelfRef.m_axil_wdata = vlSelfRef.s_axil_wdata;
    vlSelfRef.m_axil_wstrb = vlSelfRef.s_axil_wstrb;
    vlSelfRef.m_axil_wvalid = vlSelfRef.s_axil_wvalid;
    vlSelfRef.s_axil_wready = vlSelfRef.m_axil_wready;
    vlSelfRef.s_axil_bresp = vlSelfRef.m_axil_bresp;
    vlSelfRef.s_axil_bvalid = vlSelfRef.m_axil_bvalid;
    vlSelfRef.m_axil_bready = vlSelfRef.s_axil_bready;
    vlSelfRef.m_axil_araddr = vlSelfRef.s_axil_araddr;
    vlSelfRef.m_axil_arprot = vlSelfRef.s_axil_arprot;
    vlSelfRef.m_axil_arvalid = vlSelfRef.s_axil_arvalid;
    vlSelfRef.s_axil_arready = vlSelfRef.m_axil_arready;
    vlSelfRef.s_axil_rdata = vlSelfRef.m_axil_rdata;
    vlSelfRef.s_axil_rresp = vlSelfRef.m_axil_rresp;
    vlSelfRef.s_axil_rvalid = vlSelfRef.m_axil_rvalid;
    vlSelfRef.m_axil_rready = vlSelfRef.s_axil_rready;
    vlSelfRef.axil_test__DOT__m_axil_awaddr = vlSelfRef.m_axil_awaddr;
    vlSelfRef.axil_test__DOT__m_axil_awprot = vlSelfRef.m_axil_awprot;
    vlSelfRef.axil_test__DOT__m_axil_awvalid = vlSelfRef.m_axil_awvalid;
    vlSelfRef.axil_test__DOT__s_axil_awready = vlSelfRef.s_axil_awready;
    vlSelfRef.axil_test__DOT__m_axil_wdata = vlSelfRef.m_axil_wdata;
    vlSelfRef.axil_test__DOT__m_axil_wstrb = vlSelfRef.m_axil_wstrb;
    vlSelfRef.axil_test__DOT__m_axil_wvalid = vlSelfRef.m_axil_wvalid;
    vlSelfRef.axil_test__DOT__s_axil_wready = vlSelfRef.s_axil_wready;
    vlSelfRef.axil_test__DOT__s_axil_bresp = vlSelfRef.s_axil_bresp;
    vlSelfRef.axil_test__DOT__s_axil_bvalid = vlSelfRef.s_axil_bvalid;
    vlSelfRef.axil_test__DOT__m_axil_bready = vlSelfRef.m_axil_bready;
    vlSelfRef.axil_test__DOT__m_axil_araddr = vlSelfRef.m_axil_araddr;
    vlSelfRef.axil_test__DOT__m_axil_arprot = vlSelfRef.m_axil_arprot;
    vlSelfRef.axil_test__DOT__m_axil_arvalid = vlSelfRef.m_axil_arvalid;
    vlSelfRef.axil_test__DOT__s_axil_arready = vlSelfRef.s_axil_arready;
    vlSelfRef.axil_test__DOT__s_axil_rdata = vlSelfRef.s_axil_rdata;
    vlSelfRef.axil_test__DOT__s_axil_rresp = vlSelfRef.s_axil_rresp;
    vlSelfRef.axil_test__DOT__s_axil_rvalid = vlSelfRef.s_axil_rvalid;
    vlSelfRef.axil_test__DOT__m_axil_rready = vlSelfRef.m_axil_rready;
}

void Vaxil_test___024root___eval_triggers__ico(Vaxil_test___024root* vlSelf);

bool Vaxil_test___024root___eval_phase__ico(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___eval_phase__ico\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vaxil_test___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vaxil_test___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vaxil_test___024root___eval_act(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___eval_act\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vaxil_test___024root___eval_nba(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___eval_nba\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vaxil_test___024root___eval_triggers__act(Vaxil_test___024root* vlSelf);

bool Vaxil_test___024root___eval_phase__act(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___eval_phase__act\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<0> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vaxil_test___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vaxil_test___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vaxil_test___024root___eval_phase__nba(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___eval_phase__nba\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vaxil_test___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxil_test___024root___dump_triggers__ico(Vaxil_test___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxil_test___024root___dump_triggers__nba(Vaxil_test___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxil_test___024root___dump_triggers__act(Vaxil_test___024root* vlSelf);
#endif  // VL_DEBUG

void Vaxil_test___024root___eval(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___eval\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY(((0x64U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vaxil_test___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("axil_test.sv", 17, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vaxil_test___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vaxil_test___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("axil_test.sv", 17, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vaxil_test___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("axil_test.sv", 17, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vaxil_test___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vaxil_test___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vaxil_test___024root___eval_debug_assertions(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___eval_debug_assertions\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY(((vlSelfRef.s_axil_awprot & 0xf8U)))) {
        Verilated::overWidthError("s_axil_awprot");}
    if (VL_UNLIKELY(((vlSelfRef.s_axil_awvalid & 0xfeU)))) {
        Verilated::overWidthError("s_axil_awvalid");}
    if (VL_UNLIKELY(((vlSelfRef.s_axil_wstrb & 0xf0U)))) {
        Verilated::overWidthError("s_axil_wstrb");}
    if (VL_UNLIKELY(((vlSelfRef.s_axil_wvalid & 0xfeU)))) {
        Verilated::overWidthError("s_axil_wvalid");}
    if (VL_UNLIKELY(((vlSelfRef.s_axil_bready & 0xfeU)))) {
        Verilated::overWidthError("s_axil_bready");}
    if (VL_UNLIKELY(((vlSelfRef.s_axil_arprot & 0xf8U)))) {
        Verilated::overWidthError("s_axil_arprot");}
    if (VL_UNLIKELY(((vlSelfRef.s_axil_arvalid & 0xfeU)))) {
        Verilated::overWidthError("s_axil_arvalid");}
    if (VL_UNLIKELY(((vlSelfRef.s_axil_rready & 0xfeU)))) {
        Verilated::overWidthError("s_axil_rready");}
    if (VL_UNLIKELY(((vlSelfRef.m_axil_awready & 0xfeU)))) {
        Verilated::overWidthError("m_axil_awready");}
    if (VL_UNLIKELY(((vlSelfRef.m_axil_wready & 0xfeU)))) {
        Verilated::overWidthError("m_axil_wready");}
    if (VL_UNLIKELY(((vlSelfRef.m_axil_bresp & 0xfcU)))) {
        Verilated::overWidthError("m_axil_bresp");}
    if (VL_UNLIKELY(((vlSelfRef.m_axil_bvalid & 0xfeU)))) {
        Verilated::overWidthError("m_axil_bvalid");}
    if (VL_UNLIKELY(((vlSelfRef.m_axil_arready & 0xfeU)))) {
        Verilated::overWidthError("m_axil_arready");}
    if (VL_UNLIKELY(((vlSelfRef.m_axil_rresp & 0xfcU)))) {
        Verilated::overWidthError("m_axil_rresp");}
    if (VL_UNLIKELY(((vlSelfRef.m_axil_rvalid & 0xfeU)))) {
        Verilated::overWidthError("m_axil_rvalid");}
}
#endif  // VL_DEBUG
