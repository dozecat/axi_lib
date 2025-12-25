// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaxil_test.h for the primary calling header

#ifndef VERILATED_VAXIL_TEST___024ROOT_H_
#define VERILATED_VAXIL_TEST___024ROOT_H_  // guard

#include "verilated.h"


class Vaxil_test__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaxil_test___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(rst,0,0);
        VL_IN8(s_axil_awprot,2,0);
        VL_IN8(s_axil_awvalid,0,0);
        VL_OUT8(s_axil_awready,0,0);
        VL_IN8(s_axil_wstrb,3,0);
        VL_IN8(s_axil_wvalid,0,0);
        VL_OUT8(s_axil_wready,0,0);
        VL_OUT8(s_axil_bresp,1,0);
        VL_OUT8(s_axil_bvalid,0,0);
        VL_IN8(s_axil_bready,0,0);
        VL_IN8(s_axil_arprot,2,0);
        VL_IN8(s_axil_arvalid,0,0);
        VL_OUT8(s_axil_arready,0,0);
        VL_OUT8(s_axil_rresp,1,0);
        VL_OUT8(s_axil_rvalid,0,0);
        VL_IN8(s_axil_rready,0,0);
        VL_OUT8(m_axil_awprot,2,0);
        VL_OUT8(m_axil_awvalid,0,0);
        VL_IN8(m_axil_awready,0,0);
        VL_OUT8(m_axil_wstrb,3,0);
        VL_OUT8(m_axil_wvalid,0,0);
        VL_IN8(m_axil_wready,0,0);
        VL_IN8(m_axil_bresp,1,0);
        VL_IN8(m_axil_bvalid,0,0);
        VL_OUT8(m_axil_bready,0,0);
        VL_OUT8(m_axil_arprot,2,0);
        VL_OUT8(m_axil_arvalid,0,0);
        VL_IN8(m_axil_arready,0,0);
        VL_IN8(m_axil_rresp,1,0);
        VL_IN8(m_axil_rvalid,0,0);
        VL_OUT8(m_axil_rready,0,0);
        CData/*0:0*/ axil_test__DOT__clk;
        CData/*0:0*/ axil_test__DOT__rst;
        CData/*2:0*/ axil_test__DOT__s_axil_awprot;
        CData/*0:0*/ axil_test__DOT__s_axil_awvalid;
        CData/*0:0*/ axil_test__DOT__s_axil_awready;
        CData/*3:0*/ axil_test__DOT__s_axil_wstrb;
        CData/*0:0*/ axil_test__DOT__s_axil_wvalid;
        CData/*0:0*/ axil_test__DOT__s_axil_wready;
        CData/*1:0*/ axil_test__DOT__s_axil_bresp;
        CData/*0:0*/ axil_test__DOT__s_axil_bvalid;
        CData/*0:0*/ axil_test__DOT__s_axil_bready;
        CData/*2:0*/ axil_test__DOT__s_axil_arprot;
        CData/*0:0*/ axil_test__DOT__s_axil_arvalid;
        CData/*0:0*/ axil_test__DOT__s_axil_arready;
        CData/*1:0*/ axil_test__DOT__s_axil_rresp;
        CData/*0:0*/ axil_test__DOT__s_axil_rvalid;
        CData/*0:0*/ axil_test__DOT__s_axil_rready;
        CData/*2:0*/ axil_test__DOT__m_axil_awprot;
        CData/*0:0*/ axil_test__DOT__m_axil_awvalid;
        CData/*0:0*/ axil_test__DOT__m_axil_awready;
        CData/*3:0*/ axil_test__DOT__m_axil_wstrb;
        CData/*0:0*/ axil_test__DOT__m_axil_wvalid;
        CData/*0:0*/ axil_test__DOT__m_axil_wready;
        CData/*1:0*/ axil_test__DOT__m_axil_bresp;
        CData/*0:0*/ axil_test__DOT__m_axil_bvalid;
        CData/*0:0*/ axil_test__DOT__m_axil_bready;
        CData/*2:0*/ axil_test__DOT__m_axil_arprot;
        CData/*0:0*/ axil_test__DOT__m_axil_arvalid;
        CData/*0:0*/ axil_test__DOT__m_axil_arready;
        CData/*1:0*/ axil_test__DOT__m_axil_rresp;
        CData/*0:0*/ axil_test__DOT__m_axil_rvalid;
        CData/*0:0*/ axil_test__DOT__m_axil_rready;
    };
    struct {
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __VactContinue;
        VL_IN16(s_axil_awaddr,15,0);
        VL_IN16(s_axil_araddr,15,0);
        VL_OUT16(m_axil_awaddr,15,0);
        VL_OUT16(m_axil_araddr,15,0);
        SData/*15:0*/ axil_test__DOT__s_axil_awaddr;
        SData/*15:0*/ axil_test__DOT__s_axil_araddr;
        SData/*15:0*/ axil_test__DOT__m_axil_awaddr;
        SData/*15:0*/ axil_test__DOT__m_axil_araddr;
        VL_IN(s_axil_wdata,31,0);
        VL_OUT(s_axil_rdata,31,0);
        VL_OUT(m_axil_wdata,31,0);
        VL_IN(m_axil_rdata,31,0);
        IData/*31:0*/ axil_test__DOT__s_axil_wdata;
        IData/*31:0*/ axil_test__DOT__s_axil_rdata;
        IData/*31:0*/ axil_test__DOT__m_axil_wdata;
        IData/*31:0*/ axil_test__DOT__m_axil_rdata;
        IData/*31:0*/ __VactIterCount;
    };
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<0> __VactTriggered;
    VlTriggerVec<0> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vaxil_test__Syms* const vlSymsp;

    // PARAMETERS
    static constexpr IData/*31:0*/ axil_test__DOT__DATA_WIDTH = 0x00000020U;
    static constexpr IData/*31:0*/ axil_test__DOT__ADDR_WIDTH = 0x00000010U;
    static constexpr IData/*31:0*/ axil_test__DOT__STRB_WIDTH = 4U;

    // CONSTRUCTORS
    Vaxil_test___024root(Vaxil_test__Syms* symsp, const char* v__name);
    ~Vaxil_test___024root();
    VL_UNCOPYABLE(Vaxil_test___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
