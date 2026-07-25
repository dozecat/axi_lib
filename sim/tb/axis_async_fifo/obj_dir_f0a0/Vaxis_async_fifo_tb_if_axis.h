// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaxis_async_fifo_tb.h for the primary calling header

#ifndef VERILATED_VAXIS_ASYNC_FIFO_TB_IF_AXIS_H_
#define VERILATED_VAXIS_ASYNC_FIFO_TB_IF_AXIS_H_  // guard

#include "verilated.h"


class Vaxis_async_fifo_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaxis_async_fifo_tb_if_axis final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tdest;
    CData/*7:0*/ tkeep;
    CData/*7:0*/ tstrb;
    CData/*0:0*/ tlast;
    CData/*0:0*/ tready;
    CData/*0:0*/ tuser;
    CData/*7:0*/ tid;
    CData/*0:0*/ tvalid;
    QData/*63:0*/ tdata;

    // INTERNAL VARIABLES
    Vaxis_async_fifo_tb__Syms* vlSymsp;
    const char* vlNamep;

    // PARAMETERS
    static constexpr IData/*31:0*/ DATA_WIDTH = 0x00000040U;
    static constexpr IData/*31:0*/ DEST_WIDTH = 1U;
    static constexpr IData/*31:0*/ KEEP_WIDTH = 8U;
    static constexpr IData/*31:0*/ STRB_WIDTH = 8U;
    static constexpr IData/*31:0*/ ID_WIDTH = 8U;
    static constexpr IData/*31:0*/ USER_WIDTH = 1U;

    // CONSTRUCTORS
    Vaxis_async_fifo_tb_if_axis() = default;
    ~Vaxis_async_fifo_tb_if_axis() = default;
    void ctor(Vaxis_async_fifo_tb__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vaxis_async_fifo_tb_if_axis);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};

std::string VL_TO_STRING(const Vaxis_async_fifo_tb_if_axis* obj);

#endif  // guard
