// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vaxil_test__pch.h"
#include "Vaxil_test.h"
#include "Vaxil_test___024root.h"

// FUNCTIONS
Vaxil_test__Syms::~Vaxil_test__Syms()
{
}

Vaxil_test__Syms::Vaxil_test__Syms(VerilatedContext* contextp, const char* namep, Vaxil_test* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(25);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
}
