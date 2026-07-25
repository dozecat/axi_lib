// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxis_async_fifo_tb.h for the primary calling header

#include "Vaxis_async_fifo_tb__pch.h"

// Parameter definitions for Vaxis_async_fifo_tb_if_axis
constexpr IData/*31:0*/ Vaxis_async_fifo_tb_if_axis::DATA_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb_if_axis::DEST_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb_if_axis::KEEP_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb_if_axis::STRB_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb_if_axis::ID_WIDTH;
constexpr IData/*31:0*/ Vaxis_async_fifo_tb_if_axis::USER_WIDTH;


void Vaxis_async_fifo_tb_if_axis___ctor_var_reset(Vaxis_async_fifo_tb_if_axis* vlSelf);

void Vaxis_async_fifo_tb_if_axis::ctor(Vaxis_async_fifo_tb__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vaxis_async_fifo_tb_if_axis___ctor_var_reset(this);
}

void Vaxis_async_fifo_tb_if_axis::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vaxis_async_fifo_tb_if_axis::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
