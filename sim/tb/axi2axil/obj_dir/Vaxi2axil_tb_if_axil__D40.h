// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaxi2axil_tb.h for the primary calling header

#ifndef VERILATED_VAXI2AXIL_TB_IF_AXIL__D40_H_
#define VERILATED_VAXI2AXIL_TB_IF_AXIL__D40_H_  // guard

#include "verilated.h"


class Vaxi2axil_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaxi2axil_tb_if_axil__D40 final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*2:0*/ awprot;
    CData/*0:0*/ awready;
    CData/*0:0*/ awvalid;
    CData/*0:0*/ bready;
    CData/*1:0*/ bresp;
    CData/*0:0*/ bvalid;
    CData/*0:0*/ wready;
    CData/*7:0*/ wstrb;
    CData/*0:0*/ wvalid;
    CData/*2:0*/ arprot;
    CData/*0:0*/ arready;
    CData/*0:0*/ arvalid;
    CData/*0:0*/ rready;
    CData/*1:0*/ rresp;
    CData/*0:0*/ rvalid;
    SData/*15:0*/ awaddr;
    SData/*15:0*/ araddr;
    QData/*63:0*/ wdata;
    QData/*63:0*/ rdata;

    // INTERNAL VARIABLES
    Vaxi2axil_tb__Syms* vlSymsp;
    const char* vlNamep;

    // PARAMETERS
    static constexpr IData/*31:0*/ ADDR_WIDTH = 0x00000010U;
    static constexpr IData/*31:0*/ DATA_WIDTH = 0x00000040U;
    static constexpr IData/*31:0*/ STRB_WIDTH = 8U;
    static constexpr IData/*31:0*/ PROT_WIDTH = 3U;
    static constexpr IData/*31:0*/ RESP_WIDTH = 2U;

    // CONSTRUCTORS
    Vaxi2axil_tb_if_axil__D40() = default;
    ~Vaxi2axil_tb_if_axil__D40() = default;
    void ctor(Vaxi2axil_tb__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vaxi2axil_tb_if_axil__D40);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};

std::string VL_TO_STRING(const Vaxi2axil_tb_if_axil__D40* obj);

#endif  // guard
