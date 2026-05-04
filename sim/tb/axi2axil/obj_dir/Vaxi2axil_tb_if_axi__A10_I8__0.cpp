// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxi2axil_tb.h for the primary calling header

#include "Vaxi2axil_tb__pch.h"

void Vaxi2axil_tb_if_axi__A10_I8___nba_sequent__TOP__axi2axil_tb__DOT__axi_slv_if__0(Vaxi2axil_tb_if_axi__A10_I8* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vaxi2axil_tb_if_axi__A10_I8___nba_sequent__TOP__axi2axil_tb__DOT__axi_slv_if__0\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.bresp = ((IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_err)
                        ? 2U : (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_resp));
    vlSelfRef.rlast = ((IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__rd_dvalid) 
                       & (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__rd_last));
    vlSelfRef.arready = (0U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__rd_state));
    vlSelfRef.awready = (0U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_state));
    vlSelfRef.bvalid = (3U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_state));
    vlSelfRef.wready = ((~ (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_wpend)) 
                        & (1U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_state)));
}

std::string VL_TO_STRING(const Vaxi2axil_tb_if_axi__A10_I8* obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vaxi2axil_tb_if_axi__A10_I8::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->vlNamep : "null");
}
