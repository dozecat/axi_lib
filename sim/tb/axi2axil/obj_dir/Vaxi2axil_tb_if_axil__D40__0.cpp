// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxi2axil_tb.h for the primary calling header

#include "Vaxi2axil_tb__pch.h"

void Vaxi2axil_tb_if_axil__D40___nba_sequent__TOP__axi2axil_tb__DOT__axil_mst_if__0(Vaxi2axil_tb_if_axil__D40* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vaxi2axil_tb_if_axil__D40___nba_sequent__TOP__axi2axil_tb__DOT__axil_mst_if__0\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.arvalid = (1U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__rd_state));
    vlSelfRef.rready = (2U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__rd_state));
    vlSelfRef.bready = (2U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_state));
    vlSelfRef.awvalid = ((1U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_state)) 
                         & (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_wpend));
}

std::string VL_TO_STRING(const Vaxi2axil_tb_if_axil__D40* obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vaxi2axil_tb_if_axil__D40::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->vlNamep : "null");
}
