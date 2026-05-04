// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaxi2axil_tb.h for the primary calling header

#ifndef VERILATED_VAXI2AXIL_TB_IF_AXI__A10_I8_H_
#define VERILATED_VAXI2AXIL_TB_IF_AXI__A10_I8_H_  // guard

#include "verilated.h"


class Vaxi2axil_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaxi2axil_tb_if_axi__A10_I8 final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*1:0*/ arburst;
    CData/*3:0*/ arcache;
    CData/*7:0*/ arid;
    CData/*7:0*/ arlen;
    CData/*0:0*/ arlock;
    CData/*2:0*/ arprot;
    CData/*3:0*/ arqos;
    CData/*0:0*/ arready;
    CData/*3:0*/ arregion;
    CData/*2:0*/ arsize;
    CData/*0:0*/ arvalid;
    CData/*1:0*/ awburst;
    CData/*3:0*/ awcache;
    CData/*7:0*/ awid;
    CData/*7:0*/ awlen;
    CData/*0:0*/ awlock;
    CData/*2:0*/ awprot;
    CData/*3:0*/ awqos;
    CData/*0:0*/ awready;
    CData/*3:0*/ awregion;
    CData/*2:0*/ awsize;
    CData/*0:0*/ awvalid;
    CData/*7:0*/ bid;
    CData/*0:0*/ bready;
    CData/*1:0*/ bresp;
    CData/*0:0*/ bvalid;
    CData/*7:0*/ rid;
    CData/*0:0*/ rlast;
    CData/*0:0*/ rready;
    CData/*1:0*/ rresp;
    CData/*0:0*/ rvalid;
    CData/*7:0*/ wid;
    CData/*0:0*/ wlast;
    CData/*0:0*/ wready;
    CData/*7:0*/ wstrb;
    CData/*0:0*/ wvalid;
    SData/*15:0*/ araddr;
    SData/*15:0*/ awaddr;
    QData/*63:0*/ rdata;
    QData/*63:0*/ wdata;

    // INTERNAL VARIABLES
    Vaxi2axil_tb__Syms* vlSymsp;
    const char* vlNamep;

    // PARAMETERS
    static constexpr IData/*31:0*/ ADDR_WIDTH = 0x00000010U;
    static constexpr IData/*31:0*/ DATA_WIDTH = 0x00000040U;
    static constexpr IData/*31:0*/ ID_WIDTH = 8U;
    static constexpr IData/*31:0*/ STRB_WIDTH = 8U;
    static constexpr IData/*31:0*/ BURST_TYPE_WIDTH = 2U;
    static constexpr IData/*31:0*/ CACHE_WIDTH = 4U;
    static constexpr IData/*31:0*/ LEN_WIDTH = 8U;
    static constexpr IData/*31:0*/ LOCK_WIDTH = 1U;
    static constexpr IData/*31:0*/ PROT_WIDTH = 3U;
    static constexpr IData/*31:0*/ QOS_WIDTH = 4U;
    static constexpr IData/*31:0*/ REGION_WIDTH = 4U;
    static constexpr IData/*31:0*/ SIZE_WIDTH = 3U;
    static constexpr IData/*31:0*/ RESP_WIDTH = 2U;

    // CONSTRUCTORS
    Vaxi2axil_tb_if_axi__A10_I8() = default;
    ~Vaxi2axil_tb_if_axi__A10_I8() = default;
    void ctor(Vaxi2axil_tb__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(Vaxi2axil_tb_if_axi__A10_I8);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};

std::string VL_TO_STRING(const Vaxi2axil_tb_if_axi__A10_I8* obj);

#endif  // guard
