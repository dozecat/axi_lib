// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaxi2axil_tb.h for the primary calling header

#ifndef VERILATED_VAXI2AXIL_TB___024ROOT_H_
#define VERILATED_VAXI2AXIL_TB___024ROOT_H_  // guard

#include "verilated.h"
class Vaxi2axil_tb_if_axi__A10_I8;
class Vaxi2axil_tb_if_axil__D40;


class Vaxi2axil_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaxi2axil_tb___024root final {
  public:
    // CELLS
    Vaxi2axil_tb_if_axi__A10_I8* __PVT__axi2axil_tb__DOT__axi_slv_if;
    Vaxi2axil_tb_if_axil__D40* __PVT__axi2axil_tb__DOT__axil_mst_if;

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(rst_n,0,0);
        VL_IN8(m_awid,7,0);
        VL_IN8(m_awlen,7,0);
        VL_IN8(m_awsize,2,0);
        VL_IN8(m_awburst,1,0);
        VL_IN8(m_awcache,3,0);
        VL_IN8(m_awlock,0,0);
        VL_IN8(m_awprot,2,0);
        VL_IN8(m_awqos,3,0);
        VL_IN8(m_awregion,3,0);
        VL_IN8(m_awvalid,0,0);
        VL_OUT8(m_awready,0,0);
        VL_IN8(m_wstrb,7,0);
        VL_IN8(m_wid,7,0);
        VL_IN8(m_wlast,0,0);
        VL_IN8(m_wvalid,0,0);
        VL_OUT8(m_wready,0,0);
        VL_OUT8(m_bresp,1,0);
        VL_OUT8(m_bid,7,0);
        VL_OUT8(m_bvalid,0,0);
        VL_IN8(m_bready,0,0);
        VL_IN8(m_arid,7,0);
        VL_IN8(m_arlen,7,0);
        VL_IN8(m_arsize,2,0);
        VL_IN8(m_arburst,1,0);
        VL_IN8(m_arcache,3,0);
        VL_IN8(m_arlock,0,0);
        VL_IN8(m_arprot,2,0);
        VL_IN8(m_arqos,3,0);
        VL_IN8(m_arregion,3,0);
        VL_IN8(m_arvalid,0,0);
        VL_OUT8(m_arready,0,0);
        VL_OUT8(m_rresp,1,0);
        VL_OUT8(m_rid,7,0);
        VL_OUT8(m_rlast,0,0);
        VL_OUT8(m_rvalid,0,0);
        VL_IN8(m_rready,0,0);
        VL_OUT8(s_awvalid,0,0);
        VL_IN8(s_awready,0,0);
        VL_OUT8(s_awprot,2,0);
        VL_OUT8(s_wvalid,0,0);
        VL_IN8(s_wready,0,0);
        VL_OUT8(s_wstrb,7,0);
        VL_IN8(s_bvalid,0,0);
        VL_OUT8(s_bready,0,0);
        VL_IN8(s_bresp,1,0);
        VL_OUT8(s_arvalid,0,0);
        VL_IN8(s_arready,0,0);
        VL_OUT8(s_arprot,2,0);
        VL_IN8(s_rvalid,0,0);
        VL_OUT8(s_rready,0,0);
        VL_IN8(s_rresp,1,0);
        CData/*0:0*/ axi2axil_tb__DOT__clk;
        CData/*0:0*/ axi2axil_tb__DOT__rst_n;
        CData/*7:0*/ axi2axil_tb__DOT__m_awid;
        CData/*7:0*/ axi2axil_tb__DOT__m_awlen;
        CData/*2:0*/ axi2axil_tb__DOT__m_awsize;
        CData/*1:0*/ axi2axil_tb__DOT__m_awburst;
        CData/*3:0*/ axi2axil_tb__DOT__m_awcache;
        CData/*0:0*/ axi2axil_tb__DOT__m_awlock;
        CData/*2:0*/ axi2axil_tb__DOT__m_awprot;
        CData/*3:0*/ axi2axil_tb__DOT__m_awqos;
        CData/*3:0*/ axi2axil_tb__DOT__m_awregion;
    };
    struct {
        CData/*0:0*/ axi2axil_tb__DOT__m_awvalid;
        CData/*0:0*/ axi2axil_tb__DOT__m_awready;
        CData/*7:0*/ axi2axil_tb__DOT__m_wstrb;
        CData/*7:0*/ axi2axil_tb__DOT__m_wid;
        CData/*0:0*/ axi2axil_tb__DOT__m_wlast;
        CData/*0:0*/ axi2axil_tb__DOT__m_wvalid;
        CData/*0:0*/ axi2axil_tb__DOT__m_wready;
        CData/*1:0*/ axi2axil_tb__DOT__m_bresp;
        CData/*7:0*/ axi2axil_tb__DOT__m_bid;
        CData/*0:0*/ axi2axil_tb__DOT__m_bvalid;
        CData/*0:0*/ axi2axil_tb__DOT__m_bready;
        CData/*7:0*/ axi2axil_tb__DOT__m_arid;
        CData/*7:0*/ axi2axil_tb__DOT__m_arlen;
        CData/*2:0*/ axi2axil_tb__DOT__m_arsize;
        CData/*1:0*/ axi2axil_tb__DOT__m_arburst;
        CData/*3:0*/ axi2axil_tb__DOT__m_arcache;
        CData/*0:0*/ axi2axil_tb__DOT__m_arlock;
        CData/*2:0*/ axi2axil_tb__DOT__m_arprot;
        CData/*3:0*/ axi2axil_tb__DOT__m_arqos;
        CData/*3:0*/ axi2axil_tb__DOT__m_arregion;
        CData/*0:0*/ axi2axil_tb__DOT__m_arvalid;
        CData/*0:0*/ axi2axil_tb__DOT__m_arready;
        CData/*1:0*/ axi2axil_tb__DOT__m_rresp;
        CData/*7:0*/ axi2axil_tb__DOT__m_rid;
        CData/*0:0*/ axi2axil_tb__DOT__m_rlast;
        CData/*0:0*/ axi2axil_tb__DOT__m_rvalid;
        CData/*0:0*/ axi2axil_tb__DOT__m_rready;
        CData/*0:0*/ axi2axil_tb__DOT__s_awvalid;
        CData/*0:0*/ axi2axil_tb__DOT__s_awready;
        CData/*2:0*/ axi2axil_tb__DOT__s_awprot;
        CData/*0:0*/ axi2axil_tb__DOT__s_wvalid;
        CData/*0:0*/ axi2axil_tb__DOT__s_wready;
        CData/*7:0*/ axi2axil_tb__DOT__s_wstrb;
        CData/*0:0*/ axi2axil_tb__DOT__s_bvalid;
        CData/*0:0*/ axi2axil_tb__DOT__s_bready;
        CData/*1:0*/ axi2axil_tb__DOT__s_bresp;
        CData/*0:0*/ axi2axil_tb__DOT__s_arvalid;
        CData/*0:0*/ axi2axil_tb__DOT__s_arready;
        CData/*2:0*/ axi2axil_tb__DOT__s_arprot;
        CData/*0:0*/ axi2axil_tb__DOT__s_rvalid;
        CData/*0:0*/ axi2axil_tb__DOT__s_rready;
        CData/*1:0*/ axi2axil_tb__DOT__s_rresp;
        CData/*0:0*/ axi2axil_tb__DOT__dut__DOT__aclk;
        CData/*0:0*/ axi2axil_tb__DOT__dut__DOT__aresetn;
        CData/*1:0*/ axi2axil_tb__DOT__dut__DOT__wr_state;
        CData/*1:0*/ axi2axil_tb__DOT__dut__DOT__wr_nstate;
        CData/*7:0*/ axi2axil_tb__DOT__dut__DOT__wr_len;
        CData/*2:0*/ axi2axil_tb__DOT__dut__DOT__wr_size;
        CData/*1:0*/ axi2axil_tb__DOT__dut__DOT__wr_burst;
        CData/*7:0*/ axi2axil_tb__DOT__dut__DOT__wr_id;
        CData/*2:0*/ axi2axil_tb__DOT__dut__DOT__wr_prot;
        CData/*7:0*/ axi2axil_tb__DOT__dut__DOT__wr_beat;
        CData/*1:0*/ axi2axil_tb__DOT__dut__DOT__wr_resp;
        CData/*0:0*/ axi2axil_tb__DOT__dut__DOT__wr_err;
        CData/*7:0*/ axi2axil_tb__DOT__dut__DOT__wr_wstrb_q;
        CData/*0:0*/ axi2axil_tb__DOT__dut__DOT__wr_wlast_q;
        CData/*0:0*/ axi2axil_tb__DOT__dut__DOT__wr_wpend;
        CData/*1:0*/ axi2axil_tb__DOT__dut__DOT__rd_state;
        CData/*1:0*/ axi2axil_tb__DOT__dut__DOT__rd_nstate;
        CData/*7:0*/ axi2axil_tb__DOT__dut__DOT__rd_len;
        CData/*2:0*/ axi2axil_tb__DOT__dut__DOT__rd_size;
        CData/*1:0*/ axi2axil_tb__DOT__dut__DOT__rd_burst;
        CData/*7:0*/ axi2axil_tb__DOT__dut__DOT__rd_id;
        CData/*2:0*/ axi2axil_tb__DOT__dut__DOT__rd_prot;
    };
    struct {
        CData/*7:0*/ axi2axil_tb__DOT__dut__DOT__rd_beat;
        CData/*1:0*/ axi2axil_tb__DOT__dut__DOT__rd_rresp_q;
        CData/*0:0*/ axi2axil_tb__DOT__dut__DOT__rd_dvalid;
        CData/*0:0*/ axi2axil_tb__DOT__dut__DOT__rd_last;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__rst_n__0;
        VL_IN16(m_awaddr,15,0);
        VL_IN16(m_araddr,15,0);
        VL_OUT16(s_awaddr,15,0);
        VL_OUT16(s_araddr,15,0);
        SData/*15:0*/ axi2axil_tb__DOT__m_awaddr;
        SData/*15:0*/ axi2axil_tb__DOT__m_araddr;
        SData/*15:0*/ axi2axil_tb__DOT__s_awaddr;
        SData/*15:0*/ axi2axil_tb__DOT__s_araddr;
        SData/*15:0*/ axi2axil_tb__DOT__dut__DOT__wr_addr;
        SData/*15:0*/ axi2axil_tb__DOT__dut__DOT__wr_beat_addr;
        SData/*15:0*/ axi2axil_tb__DOT__dut__DOT__rd_addr;
        SData/*15:0*/ axi2axil_tb__DOT__dut__DOT__rd_beat_addr;
        SData/*15:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__Vfuncout;
        SData/*15:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__0__wrap_bytes;
        SData/*15:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__Vfuncout;
        SData/*15:0*/ __Vfunc_axi2axil_tb__DOT__dut__DOT__calc_beat_addr__1__wrap_bytes;
        IData/*31:0*/ __VactIterCount;
        VL_IN64(m_wdata,63,0);
        VL_OUT64(m_rdata,63,0);
        VL_OUT64(s_wdata,63,0);
        VL_IN64(s_rdata,63,0);
        QData/*63:0*/ axi2axil_tb__DOT__m_wdata;
        QData/*63:0*/ axi2axil_tb__DOT__m_rdata;
        QData/*63:0*/ axi2axil_tb__DOT__s_wdata;
        QData/*63:0*/ axi2axil_tb__DOT__s_rdata;
        QData/*63:0*/ axi2axil_tb__DOT__dut__DOT__wr_wdata_q;
        QData/*63:0*/ axi2axil_tb__DOT__dut__DOT__rd_rdata_q;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    };

    // INTERNAL VARIABLES
    Vaxi2axil_tb__Syms* vlSymsp;
    const char* vlNamep;

    // PARAMETERS
    static constexpr IData/*31:0*/ axi2axil_tb__DOT__DATA_WIDTH = 0x00000040U;
    static constexpr IData/*31:0*/ axi2axil_tb__DOT__ADDR_WIDTH = 0x00000010U;
    static constexpr IData/*31:0*/ axi2axil_tb__DOT__ID_WIDTH = 8U;
    static constexpr IData/*31:0*/ axi2axil_tb__DOT__STRB_WIDTH = 8U;
    static constexpr IData/*31:0*/ axi2axil_tb__DOT__dut__DOT__ADDR_WIDTH = 0x00000010U;
    static constexpr IData/*31:0*/ axi2axil_tb__DOT__dut__DOT__DATA_WIDTH = 0x00000040U;
    static constexpr IData/*31:0*/ axi2axil_tb__DOT__dut__DOT__ID_WIDTH = 8U;
    static constexpr IData/*31:0*/ axi2axil_tb__DOT__dut__DOT__STRB_WIDTH = 8U;
    static constexpr IData/*31:0*/ axi2axil_tb__DOT__dut__DOT__LEN_WIDTH = 8U;
    static constexpr IData/*31:0*/ axi2axil_tb__DOT__dut__DOT__SIZE_WIDTH = 3U;
    static constexpr IData/*31:0*/ axi2axil_tb__DOT__dut__DOT__PROT_WIDTH = 3U;
    static constexpr IData/*31:0*/ axi2axil_tb__DOT__dut__DOT__RESP_WIDTH = 2U;
    static constexpr IData/*31:0*/ axi2axil_tb__DOT__dut__DOT__BURST_WIDTH = 2U;

    // CONSTRUCTORS
    Vaxi2axil_tb___024root(Vaxi2axil_tb__Syms* symsp, const char* namep);
    ~Vaxi2axil_tb___024root();
    VL_UNCOPYABLE(Vaxi2axil_tb___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
