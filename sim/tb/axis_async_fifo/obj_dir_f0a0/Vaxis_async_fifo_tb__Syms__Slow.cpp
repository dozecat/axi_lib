// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vaxis_async_fifo_tb__pch.h"

Vaxis_async_fifo_tb__Syms::Vaxis_async_fifo_tb__Syms(VerilatedContext* contextp, const char* namep, Vaxis_async_fifo_tb* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup top module instance
    , TOP{this, namep}
{
    // Check resources
    Verilated::stackCheck(298);
    // Setup sub module instances
    TOP__axis_async_fifo_tb__DOT__m_axis_if.ctor(this, "axis_async_fifo_tb.m_axis_if");
    TOP__axis_async_fifo_tb__DOT__s_axis_if.ctor(this, "axis_async_fifo_tb.s_axis_if");
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    TOP.__PVT__axis_async_fifo_tb__DOT__m_axis_if = &TOP__axis_async_fifo_tb__DOT__m_axis_if;
    TOP.__PVT__axis_async_fifo_tb__DOT__s_axis_if = &TOP__axis_async_fifo_tb__DOT__s_axis_if;
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    TOP__axis_async_fifo_tb__DOT__m_axis_if.__Vconfigure(true);
    TOP__axis_async_fifo_tb__DOT__s_axis_if.__Vconfigure(false);
    // Setup scopes
}

Vaxis_async_fifo_tb__Syms::~Vaxis_async_fifo_tb__Syms() {
    // Tear down scopes
    // Tear down sub module instances
    TOP__axis_async_fifo_tb__DOT__s_axis_if.dtor();
    TOP__axis_async_fifo_tb__DOT__m_axis_if.dtor();
}
