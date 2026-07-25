// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxis_async_fifo_tb.h for the primary calling header

#include "Vaxis_async_fifo_tb__pch.h"

void Vaxis_async_fifo_tb_if_axis___nba_comb__TOP__axis_async_fifo_tb__DOT__s_axis_if__0(Vaxis_async_fifo_tb_if_axis* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vaxis_async_fifo_tb_if_axis___nba_comb__TOP__axis_async_fifo_tb__DOT__s_axis_if__0\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tready = (1U & (~ (IData)(vlSymsp->TOP.axis_async_fifo_tb__DOT__dut__DOT__dfifo_wr_full)));
}

void Vaxis_async_fifo_tb_if_axis___nba_comb__TOP__axis_async_fifo_tb__DOT__m_axis_if__0(Vaxis_async_fifo_tb_if_axis* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vaxis_async_fifo_tb_if_axis___nba_comb__TOP__axis_async_fifo_tb__DOT__m_axis_if__0\n"); );
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tvalid = (1U & (~ (IData)(vlSymsp->TOP.axis_async_fifo_tb__DOT__dut__DOT__dfifo_rd_empty)));
}

std::string VL_TO_STRING(const Vaxis_async_fifo_tb_if_axis* obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vaxis_async_fifo_tb_if_axis::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->vlNamep : "null");
}
