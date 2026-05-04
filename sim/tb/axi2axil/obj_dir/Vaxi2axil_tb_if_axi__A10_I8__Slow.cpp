// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxi2axil_tb.h for the primary calling header

#include "Vaxi2axil_tb__pch.h"

// Parameter definitions for Vaxi2axil_tb_if_axi__A10_I8
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axi__A10_I8::ADDR_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axi__A10_I8::DATA_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axi__A10_I8::ID_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axi__A10_I8::STRB_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axi__A10_I8::BURST_TYPE_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axi__A10_I8::CACHE_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axi__A10_I8::LEN_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axi__A10_I8::LOCK_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axi__A10_I8::PROT_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axi__A10_I8::QOS_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axi__A10_I8::REGION_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axi__A10_I8::SIZE_WIDTH;
constexpr IData/*31:0*/ Vaxi2axil_tb_if_axi__A10_I8::RESP_WIDTH;


void Vaxi2axil_tb_if_axi__A10_I8___ctor_var_reset(Vaxi2axil_tb_if_axi__A10_I8* vlSelf);

void Vaxi2axil_tb_if_axi__A10_I8::ctor(Vaxi2axil_tb__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    Vaxi2axil_tb_if_axi__A10_I8___ctor_var_reset(this);
}

void Vaxi2axil_tb_if_axi__A10_I8::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void Vaxi2axil_tb_if_axi__A10_I8::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
