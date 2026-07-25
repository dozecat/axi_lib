// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxis_async_fifo_tb.h for the primary calling header

#include "Vaxis_async_fifo_tb__pch.h"

VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___eval_static(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_static\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__s_clk__0 = vlSelfRef.s_clk;
    vlSelfRef.__Vtrigprevexpr___TOP__s_rst__0 = vlSelfRef.s_rst;
    vlSelfRef.__Vtrigprevexpr___TOP__m_clk__0 = vlSelfRef.m_clk;
    vlSelfRef.__Vtrigprevexpr___TOP__m_rst__0 = vlSelfRef.m_rst;
}

VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___eval_initial__TOP(Vaxis_async_fifo_tb___024root* vlSelf);

VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___eval_initial(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_initial\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vaxis_async_fifo_tb___024root___eval_initial__TOP(vlSelf);
}

VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___eval_initial__TOP(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_initial__TOP\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__i = 1U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__i = 2U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__i = 4U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__i = 8U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__i = 1U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__i = 2U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__i = 4U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__i = 8U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__i = 1U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__i = 2U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__i = 4U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__i = 8U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__i = 1U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__i = 2U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__i = 4U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__i = 8U;
    vlSelfRef.tb_depth = 0x00000010U;
    vlSelfRef.tb_frame_fifo = 0U;
    vlSelfRef.tb_always_recv = 0U;
    vlSelfRef.tb_data_width = 0x00000040U;
    VL_WRITEF_NX("axis_async_fifo: DATA=64 KEEP=8/1 STRB=8/1 ID=8/1 DEST=1/1 USER=1/1\naxis_async_fifo: D_FIFO_WIDTH=83 A_FIFO_WIDTH=8 DEPTH=16 FRAME=0\n",0);
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tkeep = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_tstrb = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_tid = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_tdest = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_tuser = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_bad_frame = 0U;
    vlSelfRef.s_good_frame = 0U;
    vlSelfRef.s_bad_frame = 0U;
    vlSelfRef.m_good_frame = 0U;
    vlSelfRef.m_bad_frame = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0U][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0U][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0U][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 1U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[1U][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[1U][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[1U][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 2U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[2U][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[2U][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[2U][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 3U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[3U][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[3U][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[3U][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 4U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[4U][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[4U][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[4U][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 5U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[5U][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[5U][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[5U][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 6U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[6U][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[6U][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[6U][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 7U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[7U][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[7U][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[7U][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 8U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[8U][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[8U][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[8U][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 9U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[9U][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[9U][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[9U][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 0x0000000aU;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0aU][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0aU][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0aU][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 0x0000000bU;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0bU][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0bU][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0bU][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 0x0000000cU;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0cU][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0cU][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0cU][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 0x0000000dU;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0dU][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0dU][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0dU][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 0x0000000eU;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0eU][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0eU][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0eU][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 0x0000000fU;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0fU][0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0fU][1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[0x0fU][2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = 0x00000010U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[0U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 1U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[1U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 2U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[2U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 3U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[3U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 4U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[4U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 5U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[5U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 6U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[6U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 7U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[7U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 8U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[8U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 9U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[9U] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 0x0000000aU;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[0x0aU] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 0x0000000bU;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[0x0bU] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 0x0000000cU;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[0x0cU] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 0x0000000dU;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[0x0dU] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 0x0000000eU;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[0x0eU] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 0x0000000fU;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[0x0fU] = 0U;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = 0x00000010U;
}

VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___eval_final(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_final\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vaxis_async_fifo_tb___024root___eval_phase__stl(Vaxis_async_fifo_tb___024root* vlSelf);

VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___eval_settle(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_settle\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vaxis_async_fifo_tb___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("axis_async_fifo_tb.sv", 4, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (Vaxis_async_fifo_tb___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___eval_triggers__stl(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_triggers__stl\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vaxis_async_fifo_tb___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool Vaxis_async_fifo_tb___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vaxis_async_fifo_tb___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vaxis_async_fifo_tb___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___stl_sequent__TOP__0(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___stl_sequent__TOP__0\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__0__Vfuncout;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__0__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__0__gray;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__0__gray = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__1__Vfuncout;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__1__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__1__gray;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__1__gray = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__4__Vfuncout;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__4__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__4__gray;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__4__gray = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__5__Vfuncout;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__5__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__5__gray;
    __Vfunc_axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__5__gray = 0;
    // Body
    vlSelfRef.m_axis_tkeep = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_data;
    vlSelfRef.s_aux_overflow = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_overflow;
    vlSelfRef.m_underflow = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_underflow;
    vlSelfRef.m_aux_underflow = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_underflow;
    vlSelfRef.s_overflow = ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_overflow) 
                            | (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_overflow));
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
    vlSelfRef.m_axis_tdata = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tdata;
    vlSelfRef.m_axis_tlast = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tlast;
    vlSelfRef.m_axis_tstrb = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tstrb;
    vlSelfRef.m_axis_tid = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tid;
    vlSelfRef.m_axis_tdest = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tdest;
    vlSelfRef.m_axis_tuser = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_tuser;
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
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__afifo_rd_empty 
        = ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr) 
           == (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr_bin));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_level 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr_bin) 
                          - (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr)));
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
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_level 
        = (0x0000001fU & ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr_bin) 
                          - (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr)));
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_empty 
        = ((IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr) 
           == (IData)(vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr_bin));
    vlSelfRef.s_aux_level = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_level;
    vlSelfRef.m_aux_level = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_level;
    vlSelfRef.s_level = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_level;
    vlSelfRef.m_level = vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_level;
}

VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___stl_sequent__TOP__1(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___stl_sequent__TOP__1\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.s_axis_tready = vlSymsp->TOP__axis_async_fifo_tb__DOT__s_axis_if.tready;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_en 
        = ((IData)(vlSymsp->TOP__axis_async_fifo_tb__DOT__s_axis_if.tready) 
           & (IData)(vlSelfRef.s_axis_tvalid));
    vlSelfRef.m_axis_tvalid = vlSymsp->TOP__axis_async_fifo_tb__DOT__m_axis_if.tvalid;
    vlSelfRef.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_en 
        = ((IData)(vlSymsp->TOP__axis_async_fifo_tb__DOT__m_axis_if.tvalid) 
           & (IData)(vlSelfRef.m_axis_tready));
}

void Vaxis_async_fifo_tb_if_axis___nba_comb__TOP__axis_async_fifo_tb__DOT__s_axis_if__0(Vaxis_async_fifo_tb_if_axis* vlSelf);
void Vaxis_async_fifo_tb_if_axis___nba_comb__TOP__axis_async_fifo_tb__DOT__m_axis_if__0(Vaxis_async_fifo_tb_if_axis* vlSelf);

VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___eval_stl(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_stl\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vaxis_async_fifo_tb___024root___stl_sequent__TOP__0(vlSelf);
        Vaxis_async_fifo_tb_if_axis___nba_comb__TOP__axis_async_fifo_tb__DOT__s_axis_if__0((&vlSymsp->TOP__axis_async_fifo_tb__DOT__s_axis_if));
        Vaxis_async_fifo_tb_if_axis___nba_comb__TOP__axis_async_fifo_tb__DOT__m_axis_if__0((&vlSymsp->TOP__axis_async_fifo_tb__DOT__m_axis_if));
        Vaxis_async_fifo_tb___024root___stl_sequent__TOP__1(vlSelf);
    }
}

VL_ATTR_COLD bool Vaxis_async_fifo_tb___024root___eval_phase__stl(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___eval_phase__stl\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vaxis_async_fifo_tb___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = Vaxis_async_fifo_tb___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vaxis_async_fifo_tb___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vaxis_async_fifo_tb___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vaxis_async_fifo_tb___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vaxis_async_fifo_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vaxis_async_fifo_tb___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge s_clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(posedge s_rst)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @(posedge m_clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @(posedge m_rst)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vaxis_async_fifo_tb___024root___ctor_var_reset(Vaxis_async_fifo_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxis_async_fifo_tb___024root___ctor_var_reset\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->s_clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 987504882975007406ull);
    vlSelf->s_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11422721990674846214ull);
    vlSelf->s_axis_tdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 6413635470731068441ull);
    vlSelf->s_axis_tkeep = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6494536958632130591ull);
    vlSelf->s_axis_tstrb = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5372727792339366163ull);
    vlSelf->s_axis_tlast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 750346815483064505ull);
    vlSelf->s_axis_tid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3746330493245997045ull);
    vlSelf->s_axis_tdest = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14905977634003549670ull);
    vlSelf->s_axis_tuser = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8856106712201831047ull);
    vlSelf->s_axis_tvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7678217216116487763ull);
    vlSelf->s_axis_tready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12236809265553805965ull);
    vlSelf->m_clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13228922981617390314ull);
    vlSelf->m_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5206405339584845526ull);
    vlSelf->m_axis_tdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 8796747702141925029ull);
    vlSelf->m_axis_tkeep = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3915191572914464546ull);
    vlSelf->m_axis_tstrb = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 6311274944724556768ull);
    vlSelf->m_axis_tlast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3666489172703407315ull);
    vlSelf->m_axis_tid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11561059174860515233ull);
    vlSelf->m_axis_tdest = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17812931604494678829ull);
    vlSelf->m_axis_tuser = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4289079287625486832ull);
    vlSelf->m_axis_tvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11050073027672567459ull);
    vlSelf->m_axis_tready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5619517951140101778ull);
    vlSelf->s_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 11645528766674878957ull);
    vlSelf->s_overflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13072137030148786864ull);
    vlSelf->s_aux_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 4418353549529440532ull);
    vlSelf->s_aux_overflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10608504817731426223ull);
    vlSelf->s_bad_frame = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10418767911776594942ull);
    vlSelf->s_good_frame = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 191926137695663966ull);
    vlSelf->m_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 7455499520024098458ull);
    vlSelf->m_underflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3273650040439646619ull);
    vlSelf->m_aux_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 16501396953677123562ull);
    vlSelf->m_aux_underflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7585924089523290704ull);
    vlSelf->m_bad_frame = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11062633251524186564ull);
    vlSelf->m_good_frame = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9877976294731974252ull);
    vlSelf->tb_depth = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3431524116226799181ull);
    vlSelf->tb_frame_fifo = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2484578988980459492ull);
    vlSelf->tb_always_recv = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14266300072201127357ull);
    vlSelf->tb_data_width = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13801789718700935584ull);
    vlSelf->axis_async_fifo_tb__DOT__s_clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5330995558797031719ull);
    vlSelf->axis_async_fifo_tb__DOT__s_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1557752557431395955ull);
    vlSelf->axis_async_fifo_tb__DOT__s_axis_tdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 13579374965448264245ull);
    vlSelf->axis_async_fifo_tb__DOT__s_axis_tkeep = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5158267299888339800ull);
    vlSelf->axis_async_fifo_tb__DOT__s_axis_tstrb = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2728294280122449197ull);
    vlSelf->axis_async_fifo_tb__DOT__s_axis_tlast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5369375238000919936ull);
    vlSelf->axis_async_fifo_tb__DOT__s_axis_tid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8162040861339257003ull);
    vlSelf->axis_async_fifo_tb__DOT__s_axis_tdest = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 178128998929802640ull);
    vlSelf->axis_async_fifo_tb__DOT__s_axis_tuser = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11283798639845055916ull);
    vlSelf->axis_async_fifo_tb__DOT__s_axis_tvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8870554732539230930ull);
    vlSelf->axis_async_fifo_tb__DOT__s_axis_tready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3296722224544771748ull);
    vlSelf->axis_async_fifo_tb__DOT__m_clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 728247865967547436ull);
    vlSelf->axis_async_fifo_tb__DOT__m_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10256866259068987697ull);
    vlSelf->axis_async_fifo_tb__DOT__m_axis_tdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 17451536588167285132ull);
    vlSelf->axis_async_fifo_tb__DOT__m_axis_tkeep = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16693387069536982690ull);
    vlSelf->axis_async_fifo_tb__DOT__m_axis_tstrb = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 18395775122624252837ull);
    vlSelf->axis_async_fifo_tb__DOT__m_axis_tlast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5537993982462890417ull);
    vlSelf->axis_async_fifo_tb__DOT__m_axis_tid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14827199077681639958ull);
    vlSelf->axis_async_fifo_tb__DOT__m_axis_tdest = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4762451393017269906ull);
    vlSelf->axis_async_fifo_tb__DOT__m_axis_tuser = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15270900312748918733ull);
    vlSelf->axis_async_fifo_tb__DOT__m_axis_tvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11276777274009075123ull);
    vlSelf->axis_async_fifo_tb__DOT__m_axis_tready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11872944500354291807ull);
    vlSelf->axis_async_fifo_tb__DOT__s_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 11727905334397572734ull);
    vlSelf->axis_async_fifo_tb__DOT__s_overflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5802359124163754828ull);
    vlSelf->axis_async_fifo_tb__DOT__s_aux_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 2745784578403532329ull);
    vlSelf->axis_async_fifo_tb__DOT__s_aux_overflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4801309253578271115ull);
    vlSelf->axis_async_fifo_tb__DOT__s_bad_frame = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1948833779116181640ull);
    vlSelf->axis_async_fifo_tb__DOT__s_good_frame = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15568082473191281794ull);
    vlSelf->axis_async_fifo_tb__DOT__m_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 16442675231737729809ull);
    vlSelf->axis_async_fifo_tb__DOT__m_underflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14566944927926930953ull);
    vlSelf->axis_async_fifo_tb__DOT__m_aux_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 4806533613106406873ull);
    vlSelf->axis_async_fifo_tb__DOT__m_aux_underflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2532849228243768126ull);
    vlSelf->axis_async_fifo_tb__DOT__m_bad_frame = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16849077770616762248ull);
    vlSelf->axis_async_fifo_tb__DOT__m_good_frame = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12992507042731082664ull);
    vlSelf->axis_async_fifo_tb__DOT__tb_depth = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4773411164827784806ull);
    vlSelf->axis_async_fifo_tb__DOT__tb_frame_fifo = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15283191118207176607ull);
    vlSelf->axis_async_fifo_tb__DOT__tb_always_recv = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6887661135741176345ull);
    vlSelf->axis_async_fifo_tb__DOT__tb_data_width = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1380224993939308836ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__s_clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12224982522381410830ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__s_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13871977946481901301ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__s_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 16738438888659477902ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__s_overflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3741119156202384849ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__s_aux_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 12604468303813913225ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__s_aux_overflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17547183342321755544ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__s_bad_frame = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3920473116323220014ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__s_good_frame = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13845073154592792547ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__m_clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3408988607422422329ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__m_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2058315484248768913ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__m_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 17840499204305774095ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__m_underflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11370463542843915479ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__m_aux_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 11438439202196077373ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__m_aux_underflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7571231037844591185ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__m_bad_frame = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1223860827262941575ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__m_good_frame = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3540973532770059579ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__afifo_tkeep = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17079693009495379818ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__afifo_tstrb = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8708821943687180844ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__afifo_tid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14417860442926080211ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__afifo_tdest = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6543716194598193875ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__afifo_tuser = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7413330397393405197ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__afifo_bad_frame = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11622701916126008341ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__afifo_rd_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15111181164065808657ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__afifo_rd_en_fsm = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8498299429668007848ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__frame_tkeep = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 12454476665770361242ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__frame_tstrb = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7608261976035040514ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__frame_tid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 14825924368542017138ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__frame_tdest = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2024362970138943757ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__frame_tuser = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 22117355927752292ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__frame_is_bad = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11343517316294513162ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15586979857479178444ull);
    VL_SCOPED_RAND_RESET_W(83, vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_data, __VscopeHash, 17455605776492698550ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12841539305019305688ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_overflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12253346852238295958ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 934613355658977837ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15407148060597933100ull);
    VL_SCOPED_RAND_RESET_W(83, vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_data, __VscopeHash, 7999776759920827106ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3355591325223697819ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_underflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 811093689024815297ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 9617049878126135444ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_tdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 10447926682837322321ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_tlast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11576991413182611514ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_tkeep = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3467871047621111056ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_tstrb = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 10021757470266041032ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_tid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 1245182209283649094ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_tdest = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6399095501819968680ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__dfifo_tuser = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3563830606800873372ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8610470464722650555ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 8085983683040387209ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6008390372435263555ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_overflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15018261457709132382ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_wr_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 10419820060887132765ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4493639375804170141ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 11011507917377588439ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_underflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13396302278043423081ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__afifo_rd_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 1380911688440748360ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3202832083104527841ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11480996325223668978ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1824971289114879765ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2453755426635259390ull);
    VL_SCOPED_RAND_RESET_W(83, vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_data, __VscopeHash, 5015396174617241200ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9113076700687078686ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_overflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1025486629923246946ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 4413077522223228768ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10842644626097377447ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8994972030916781592ull);
    VL_SCOPED_RAND_RESET_W(83, vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_data, __VscopeHash, 17060858210368707652ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1719140584108570009ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_underflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2681555091451480343ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 4441638207418474873ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 339305700551866129ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__gray2bin__Vstatic__tmp = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 7541581002967898999ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 2003951731442081979ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 6390638015036609326ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray_ms = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 13913610405184526502ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_gray_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 8650195024330828445ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 14955732142225369765ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 9062189914277160512ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray_ms = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 10741247821148979332ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_gray_wr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 1930077343628569347ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr_bin = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 16419418923434697988ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr_bin = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 17621038616060912155ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wfull_val = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9635374585226269282ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rempty_val = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11169369047477817447ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wdiff = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 209583032508255887ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rdiff = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 4069151532005847558ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        VL_SCOPED_RAND_RESET_W(83, vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem[__Vi0], __VscopeHash, 2411575435843893623ull);
    }
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2437329802070935451ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14053322730539632649ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17751289362172448643ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8217810093168088085ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6000069989764914522ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2152680896257676099ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_full = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9111266288798770584ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_overflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12724670651362911755ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 3238095889994210580ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 286286805879358251ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_en = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15935313117187625954ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_data = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5149013421469572137ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6051799149017074196ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_underflow = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16308666635309374557ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_level = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 2299691366376435887ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 538018080997714667ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__gray2bin__Vstatic__tmp = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 17091235076829838061ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 16664643911088900750ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 16161151614559049120ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray_ms = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 1276236428503611984ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_gray_rd = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 246464449391244921ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 865741581041066011ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 5300209711431214857ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray_ms = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 4587261162200238916ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_gray_wr = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 4569319308724354480ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr_bin = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 6002079479281155759ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr_bin = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 15159448312931586272ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wfull_val = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11433438237108752053ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rempty_val = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14751531279645741706ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wdiff = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 11410704227149522695ull);
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rdiff = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 5947952384482309555ull);
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 12454128981766667986ull);
    }
    vlSelf->axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 927131309457656229ull);
    vlSelf->__Vdly__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__wr_ptr = 0;
    vlSelf->__Vdly__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__wr_ptr = 0;
    vlSelf->__Vdly__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__rd_ptr = 0;
    vlSelf->__Vdly__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__rd_ptr = 0;
    VL_ZERO_RESET_W(83, vlSelf->__VdlyVal__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0);
    vlSelf->__VdlyDim0__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0 = 0;
    vlSelf->__VdlySet__axis_async_fifo_tb__DOT__dut__DOT__data_fifo_inst__DOT__mem__v0 = 0;
    vlSelf->__VdlyVal__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem__v0 = 0;
    vlSelf->__VdlyDim0__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem__v0 = 0;
    vlSelf->__VdlySet__axis_async_fifo_tb__DOT__dut__DOT__gen_aux__DOT__aux_fifo_inst__DOT__mem__v0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__s_clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__s_rst__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__m_clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__m_rst__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
