// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxil_test.h for the primary calling header

#include "Vaxil_test__pch.h"
#include "Vaxil_test__Syms.h"
#include "Vaxil_test___024root.h"

// Parameter definitions for Vaxil_test___024root
constexpr IData/*31:0*/ Vaxil_test___024root::axil_test__DOT__DATA_WIDTH;
constexpr IData/*31:0*/ Vaxil_test___024root::axil_test__DOT__ADDR_WIDTH;
constexpr IData/*31:0*/ Vaxil_test___024root::axil_test__DOT__STRB_WIDTH;


void Vaxil_test___024root___ctor_var_reset(Vaxil_test___024root* vlSelf);

Vaxil_test___024root::Vaxil_test___024root(Vaxil_test__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vaxil_test___024root___ctor_var_reset(this);
}

void Vaxil_test___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vaxil_test___024root::~Vaxil_test___024root() {
}
