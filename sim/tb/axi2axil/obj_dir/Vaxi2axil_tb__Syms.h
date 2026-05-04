// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VAXI2AXIL_TB__SYMS_H_
#define VERILATED_VAXI2AXIL_TB__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vaxi2axil_tb.h"

// INCLUDE MODULE CLASSES
#include "Vaxi2axil_tb___024root.h"
#include "Vaxi2axil_tb_if_axi__A10_I8.h"
#include "Vaxi2axil_tb_if_axil__D40.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vaxi2axil_tb__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vaxi2axil_tb* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vaxi2axil_tb___024root         TOP;
    Vaxi2axil_tb_if_axi__A10_I8    TOP__axi2axil_tb__DOT__axi_slv_if;
    Vaxi2axil_tb_if_axil__D40      TOP__axi2axil_tb__DOT__axil_mst_if;

    // CONSTRUCTORS
    Vaxi2axil_tb__Syms(VerilatedContext* contextp, const char* namep, Vaxi2axil_tb* modelp);
    ~Vaxi2axil_tb__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
