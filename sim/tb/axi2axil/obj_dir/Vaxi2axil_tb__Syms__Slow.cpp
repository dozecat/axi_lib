// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vaxi2axil_tb__pch.h"

Vaxi2axil_tb__Syms::Vaxi2axil_tb__Syms(VerilatedContext* contextp, const char* namep, Vaxi2axil_tb* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup top module instance
    , TOP{this, namep}
{
    // Check resources
    Verilated::stackCheck(346);
    // Setup sub module instances
    TOP__axi2axil_tb__DOT__axi_slv_if.ctor(this, "axi2axil_tb.axi_slv_if");
    TOP__axi2axil_tb__DOT__axil_mst_if.ctor(this, "axi2axil_tb.axil_mst_if");
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    TOP.__PVT__axi2axil_tb__DOT__axi_slv_if = &TOP__axi2axil_tb__DOT__axi_slv_if;
    TOP.__PVT__axi2axil_tb__DOT__axil_mst_if = &TOP__axi2axil_tb__DOT__axil_mst_if;
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    TOP__axi2axil_tb__DOT__axi_slv_if.__Vconfigure(true);
    TOP__axi2axil_tb__DOT__axil_mst_if.__Vconfigure(true);
    // Setup scopes
}

Vaxi2axil_tb__Syms::~Vaxi2axil_tb__Syms() {
    // Tear down scopes
    // Tear down sub module instances
    TOP__axi2axil_tb__DOT__axil_mst_if.dtor();
    TOP__axi2axil_tb__DOT__axi_slv_if.dtor();
}
