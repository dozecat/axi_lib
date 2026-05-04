// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxi2axil_tb.h for the primary calling header

#include "Vaxi2axil_tb__pch.h"

// Parameter definitions for Vaxi2axil_tb___024root
constexpr IData/*31:0*/ Vaxi2axil_tb___024root::axi2axil_tb__DOT__DATA_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb___024root::axi2axil_tb__DOT__ADDR_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb___024root::axi2axil_tb__DOT__ID_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb___024root::axi2axil_tb__DOT__STRB_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb___024root::axi2axil_tb__DOT__dut__DOT__ADDR_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb___024root::axi2axil_tb__DOT__dut__DOT__DATA_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb___024root::axi2axil_tb__DOT__dut__DOT__ID_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb___024root::axi2axil_tb__DOT__dut__DOT__STRB_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb___024root::axi2axil_tb__DOT__dut__DOT__LEN_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb___024root::axi2axil_tb__DOT__dut__DOT__SIZE_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb___024root::axi2axil_tb__DOT__dut__DOT__PROT_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb___024root::axi2axil_tb__DOT__dut__DOT__RESP_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb___024root::axi2axil_tb__DOT__dut__DOT__BURST_WIDTH;


void Vaxi2axil_tb___024root___ctor_var_reset(Vaxi2axil_tb___024root* vlSelf);

Vaxi2axil_tb___024root::Vaxi2axil_tb___024root(Vaxi2axil_tb__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vaxi2axil_tb___024root___ctor_var_reset(this);
}

void Vaxi2axil_tb___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vaxi2axil_tb___024root::~Vaxi2axil_tb___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
