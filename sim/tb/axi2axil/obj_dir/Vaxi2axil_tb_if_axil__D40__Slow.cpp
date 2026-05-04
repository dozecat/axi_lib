// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxi2axil_tb.h for the primary calling header

#include "Vaxi2axil_tb__pch.h"

// Parameter definitions for Vaxi2axil_tb_if_axil__D40
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axil__D40::ADDR_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axil__D40::DATA_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axil__D40::STRB_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axil__D40::PROT_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axil__D40::RESP_WIDTH;


void Vaxi2axil_tb_if_axil__D40___ctor_var_reset(Vaxi2axil_tb_if_axil__D40* vlSelf);

void Vaxi2axil_tb_if_axil__D40::ctor(Vaxi2axil_tb__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vaxi2axil_tb_if_axil__D40___ctor_var_reset(this);
}

void Vaxi2axil_tb_if_axil__D40::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vaxi2axil_tb_if_axil__D40::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
