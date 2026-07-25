// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VAXIS_ASYNC_FIFO_TB__SYMS_H_
#define VERILATED_VAXIS_ASYNC_FIFO_TB__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vaxis_async_fifo_tb.h"

// INCLUDE MODULE CLASSES
#include "Vaxis_async_fifo_tb___024root.h"
#include "Vaxis_async_fifo_tb_if_axis.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vaxis_async_fifo_tb__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vaxis_async_fifo_tb* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vaxis_async_fifo_tb___024root  TOP;
    Vaxis_async_fifo_tb_if_axis    TOP__axis_async_fifo_tb__DOT__m_axis_if;
    Vaxis_async_fifo_tb_if_axis    TOP__axis_async_fifo_tb__DOT__s_axis_if;

    // CONSTRUCTORS
    Vaxis_async_fifo_tb__Syms(VerilatedContext* contextp, const char* namep, Vaxis_async_fifo_tb* modelp);
    ~Vaxis_async_fifo_tb__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
