// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vaxil_test__Syms.h"


void Vaxil_test___024root__trace_chg_0_sub_0(Vaxil_test___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vaxil_test___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root__trace_chg_0\n"); );
    // Init
    Vaxil_test___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaxil_test___024root*>(voidSelf);
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vaxil_test___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vaxil_test___024root__trace_chg_0_sub_0(Vaxil_test___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root__trace_chg_0_sub_0\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    bufp->chgBit(oldp+0,(vlSelfRef.clk));
    bufp->chgBit(oldp+1,(vlSelfRef.rst));
    bufp->chgSData(oldp+2,(vlSelfRef.s_axil_awaddr),16);
    bufp->chgCData(oldp+3,(vlSelfRef.s_axil_awprot),3);
    bufp->chgBit(oldp+4,(vlSelfRef.s_axil_awvalid));
    bufp->chgBit(oldp+5,(vlSelfRef.s_axil_awready));
    bufp->chgIData(oldp+6,(vlSelfRef.s_axil_wdata),32);
    bufp->chgCData(oldp+7,(vlSelfRef.s_axil_wstrb),4);
    bufp->chgBit(oldp+8,(vlSelfRef.s_axil_wvalid));
    bufp->chgBit(oldp+9,(vlSelfRef.s_axil_wready));
    bufp->chgCData(oldp+10,(vlSelfRef.s_axil_bresp),2);
    bufp->chgBit(oldp+11,(vlSelfRef.s_axil_bvalid));
    bufp->chgBit(oldp+12,(vlSelfRef.s_axil_bready));
    bufp->chgSData(oldp+13,(vlSelfRef.s_axil_araddr),16);
    bufp->chgCData(oldp+14,(vlSelfRef.s_axil_arprot),3);
    bufp->chgBit(oldp+15,(vlSelfRef.s_axil_arvalid));
    bufp->chgBit(oldp+16,(vlSelfRef.s_axil_arready));
    bufp->chgIData(oldp+17,(vlSelfRef.s_axil_rdata),32);
    bufp->chgCData(oldp+18,(vlSelfRef.s_axil_rresp),2);
    bufp->chgBit(oldp+19,(vlSelfRef.s_axil_rvalid));
    bufp->chgBit(oldp+20,(vlSelfRef.s_axil_rready));
    bufp->chgSData(oldp+21,(vlSelfRef.m_axil_awaddr),16);
    bufp->chgCData(oldp+22,(vlSelfRef.m_axil_awprot),3);
    bufp->chgBit(oldp+23,(vlSelfRef.m_axil_awvalid));
    bufp->chgBit(oldp+24,(vlSelfRef.m_axil_awready));
    bufp->chgIData(oldp+25,(vlSelfRef.m_axil_wdata),32);
    bufp->chgCData(oldp+26,(vlSelfRef.m_axil_wstrb),4);
    bufp->chgBit(oldp+27,(vlSelfRef.m_axil_wvalid));
    bufp->chgBit(oldp+28,(vlSelfRef.m_axil_wready));
    bufp->chgCData(oldp+29,(vlSelfRef.m_axil_bresp),2);
    bufp->chgBit(oldp+30,(vlSelfRef.m_axil_bvalid));
    bufp->chgBit(oldp+31,(vlSelfRef.m_axil_bready));
    bufp->chgSData(oldp+32,(vlSelfRef.m_axil_araddr),16);
    bufp->chgCData(oldp+33,(vlSelfRef.m_axil_arprot),3);
    bufp->chgBit(oldp+34,(vlSelfRef.m_axil_arvalid));
    bufp->chgBit(oldp+35,(vlSelfRef.m_axil_arready));
    bufp->chgIData(oldp+36,(vlSelfRef.m_axil_rdata),32);
    bufp->chgCData(oldp+37,(vlSelfRef.m_axil_rresp),2);
    bufp->chgBit(oldp+38,(vlSelfRef.m_axil_rvalid));
    bufp->chgBit(oldp+39,(vlSelfRef.m_axil_rready));
    bufp->chgBit(oldp+40,(vlSelfRef.axil_test__DOT__clk));
    bufp->chgBit(oldp+41,(vlSelfRef.axil_test__DOT__rst));
    bufp->chgSData(oldp+42,(vlSelfRef.axil_test__DOT__s_axil_awaddr),16);
    bufp->chgCData(oldp+43,(vlSelfRef.axil_test__DOT__s_axil_awprot),3);
    bufp->chgBit(oldp+44,(vlSelfRef.axil_test__DOT__s_axil_awvalid));
    bufp->chgBit(oldp+45,(vlSelfRef.axil_test__DOT__s_axil_awready));
    bufp->chgIData(oldp+46,(vlSelfRef.axil_test__DOT__s_axil_wdata),32);
    bufp->chgCData(oldp+47,(vlSelfRef.axil_test__DOT__s_axil_wstrb),4);
    bufp->chgBit(oldp+48,(vlSelfRef.axil_test__DOT__s_axil_wvalid));
    bufp->chgBit(oldp+49,(vlSelfRef.axil_test__DOT__s_axil_wready));
    bufp->chgCData(oldp+50,(vlSelfRef.axil_test__DOT__s_axil_bresp),2);
    bufp->chgBit(oldp+51,(vlSelfRef.axil_test__DOT__s_axil_bvalid));
    bufp->chgBit(oldp+52,(vlSelfRef.axil_test__DOT__s_axil_bready));
    bufp->chgSData(oldp+53,(vlSelfRef.axil_test__DOT__s_axil_araddr),16);
    bufp->chgCData(oldp+54,(vlSelfRef.axil_test__DOT__s_axil_arprot),3);
    bufp->chgBit(oldp+55,(vlSelfRef.axil_test__DOT__s_axil_arvalid));
    bufp->chgBit(oldp+56,(vlSelfRef.axil_test__DOT__s_axil_arready));
    bufp->chgIData(oldp+57,(vlSelfRef.axil_test__DOT__s_axil_rdata),32);
    bufp->chgCData(oldp+58,(vlSelfRef.axil_test__DOT__s_axil_rresp),2);
    bufp->chgBit(oldp+59,(vlSelfRef.axil_test__DOT__s_axil_rvalid));
    bufp->chgBit(oldp+60,(vlSelfRef.axil_test__DOT__s_axil_rready));
    bufp->chgSData(oldp+61,(vlSelfRef.axil_test__DOT__m_axil_awaddr),16);
    bufp->chgCData(oldp+62,(vlSelfRef.axil_test__DOT__m_axil_awprot),3);
    bufp->chgBit(oldp+63,(vlSelfRef.axil_test__DOT__m_axil_awvalid));
    bufp->chgBit(oldp+64,(vlSelfRef.axil_test__DOT__m_axil_awready));
    bufp->chgIData(oldp+65,(vlSelfRef.axil_test__DOT__m_axil_wdata),32);
    bufp->chgCData(oldp+66,(vlSelfRef.axil_test__DOT__m_axil_wstrb),4);
    bufp->chgBit(oldp+67,(vlSelfRef.axil_test__DOT__m_axil_wvalid));
    bufp->chgBit(oldp+68,(vlSelfRef.axil_test__DOT__m_axil_wready));
    bufp->chgCData(oldp+69,(vlSelfRef.axil_test__DOT__m_axil_bresp),2);
    bufp->chgBit(oldp+70,(vlSelfRef.axil_test__DOT__m_axil_bvalid));
    bufp->chgBit(oldp+71,(vlSelfRef.axil_test__DOT__m_axil_bready));
    bufp->chgSData(oldp+72,(vlSelfRef.axil_test__DOT__m_axil_araddr),16);
    bufp->chgCData(oldp+73,(vlSelfRef.axil_test__DOT__m_axil_arprot),3);
    bufp->chgBit(oldp+74,(vlSelfRef.axil_test__DOT__m_axil_arvalid));
    bufp->chgBit(oldp+75,(vlSelfRef.axil_test__DOT__m_axil_arready));
    bufp->chgIData(oldp+76,(vlSelfRef.axil_test__DOT__m_axil_rdata),32);
    bufp->chgCData(oldp+77,(vlSelfRef.axil_test__DOT__m_axil_rresp),2);
    bufp->chgBit(oldp+78,(vlSelfRef.axil_test__DOT__m_axil_rvalid));
    bufp->chgBit(oldp+79,(vlSelfRef.axil_test__DOT__m_axil_rready));
}

void Vaxil_test___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root__trace_cleanup\n"); );
    // Init
    Vaxil_test___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaxil_test___024root*>(voidSelf);
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
