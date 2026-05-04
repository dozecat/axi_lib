// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vaxi2axil_tb__Syms.h"


void Vaxi2axil_tb___024root__trace_chg_0_sub_0(Vaxi2axil_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vaxi2axil_tb___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root__trace_chg_0\n"); );
    // Body
    Vaxi2axil_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaxi2axil_tb___024root*>(voidSelf);
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vaxi2axil_tb___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vaxi2axil_tb___024root__trace_chg_0_sub_0(Vaxi2axil_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root__trace_chg_0_sub_0\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    bufp->chgBit(oldp+0,(vlSelfRef.clk));
    bufp->chgBit(oldp+1,(vlSelfRef.rst_n));
    bufp->chgCData(oldp+2,(vlSelfRef.m_awid),8);
    bufp->chgSData(oldp+3,(vlSelfRef.m_awaddr),16);
    bufp->chgCData(oldp+4,(vlSelfRef.m_awlen),8);
    bufp->chgCData(oldp+5,(vlSelfRef.m_awsize),3);
    bufp->chgCData(oldp+6,(vlSelfRef.m_awburst),2);
    bufp->chgCData(oldp+7,(vlSelfRef.m_awcache),4);
    bufp->chgBit(oldp+8,(vlSelfRef.m_awlock));
    bufp->chgCData(oldp+9,(vlSelfRef.m_awprot),3);
    bufp->chgCData(oldp+10,(vlSelfRef.m_awqos),4);
    bufp->chgCData(oldp+11,(vlSelfRef.m_awregion),4);
    bufp->chgBit(oldp+12,(vlSelfRef.m_awvalid));
    bufp->chgBit(oldp+13,(vlSelfRef.m_awready));
    bufp->chgQData(oldp+14,(vlSelfRef.m_wdata),64);
    bufp->chgCData(oldp+16,(vlSelfRef.m_wstrb),8);
    bufp->chgCData(oldp+17,(vlSelfRef.m_wid),8);
    bufp->chgBit(oldp+18,(vlSelfRef.m_wlast));
    bufp->chgBit(oldp+19,(vlSelfRef.m_wvalid));
    bufp->chgBit(oldp+20,(vlSelfRef.m_wready));
    bufp->chgCData(oldp+21,(vlSelfRef.m_bresp),2);
    bufp->chgCData(oldp+22,(vlSelfRef.m_bid),8);
    bufp->chgBit(oldp+23,(vlSelfRef.m_bvalid));
    bufp->chgBit(oldp+24,(vlSelfRef.m_bready));
    bufp->chgCData(oldp+25,(vlSelfRef.m_arid),8);
    bufp->chgSData(oldp+26,(vlSelfRef.m_araddr),16);
    bufp->chgCData(oldp+27,(vlSelfRef.m_arlen),8);
    bufp->chgCData(oldp+28,(vlSelfRef.m_arsize),3);
    bufp->chgCData(oldp+29,(vlSelfRef.m_arburst),2);
    bufp->chgCData(oldp+30,(vlSelfRef.m_arcache),4);
    bufp->chgBit(oldp+31,(vlSelfRef.m_arlock));
    bufp->chgCData(oldp+32,(vlSelfRef.m_arprot),3);
    bufp->chgCData(oldp+33,(vlSelfRef.m_arqos),4);
    bufp->chgCData(oldp+34,(vlSelfRef.m_arregion),4);
    bufp->chgBit(oldp+35,(vlSelfRef.m_arvalid));
    bufp->chgBit(oldp+36,(vlSelfRef.m_arready));
    bufp->chgQData(oldp+37,(vlSelfRef.m_rdata),64);
    bufp->chgCData(oldp+39,(vlSelfRef.m_rresp),2);
    bufp->chgCData(oldp+40,(vlSelfRef.m_rid),8);
    bufp->chgBit(oldp+41,(vlSelfRef.m_rlast));
    bufp->chgBit(oldp+42,(vlSelfRef.m_rvalid));
    bufp->chgBit(oldp+43,(vlSelfRef.m_rready));
    bufp->chgBit(oldp+44,(vlSelfRef.s_awvalid));
    bufp->chgBit(oldp+45,(vlSelfRef.s_awready));
    bufp->chgSData(oldp+46,(vlSelfRef.s_awaddr),16);
    bufp->chgCData(oldp+47,(vlSelfRef.s_awprot),3);
    bufp->chgBit(oldp+48,(vlSelfRef.s_wvalid));
    bufp->chgBit(oldp+49,(vlSelfRef.s_wready));
    bufp->chgQData(oldp+50,(vlSelfRef.s_wdata),64);
    bufp->chgCData(oldp+52,(vlSelfRef.s_wstrb),8);
    bufp->chgBit(oldp+53,(vlSelfRef.s_bvalid));
    bufp->chgBit(oldp+54,(vlSelfRef.s_bready));
    bufp->chgCData(oldp+55,(vlSelfRef.s_bresp),2);
    bufp->chgBit(oldp+56,(vlSelfRef.s_arvalid));
    bufp->chgBit(oldp+57,(vlSelfRef.s_arready));
    bufp->chgSData(oldp+58,(vlSelfRef.s_araddr),16);
    bufp->chgCData(oldp+59,(vlSelfRef.s_arprot),3);
    bufp->chgBit(oldp+60,(vlSelfRef.s_rvalid));
    bufp->chgBit(oldp+61,(vlSelfRef.s_rready));
    bufp->chgQData(oldp+62,(vlSelfRef.s_rdata),64);
    bufp->chgCData(oldp+64,(vlSelfRef.s_rresp),2);
    bufp->chgCData(oldp+65,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_state),2);
    bufp->chgCData(oldp+66,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_nstate),2);
    bufp->chgSData(oldp+67,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_addr),16);
    bufp->chgCData(oldp+68,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_len),8);
    bufp->chgCData(oldp+69,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_size),3);
    bufp->chgCData(oldp+70,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_burst),2);
    bufp->chgCData(oldp+71,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_id),8);
    bufp->chgCData(oldp+72,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_prot),3);
    bufp->chgCData(oldp+73,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_beat),8);
    bufp->chgCData(oldp+74,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_resp),2);
    bufp->chgBit(oldp+75,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_err));
    bufp->chgQData(oldp+76,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wdata_q),64);
    bufp->chgCData(oldp+78,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wstrb_q),8);
    bufp->chgBit(oldp+79,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wlast_q));
    bufp->chgBit(oldp+80,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_wpend));
    bufp->chgSData(oldp+81,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__wr_beat_addr),16);
    bufp->chgCData(oldp+82,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_state),2);
    bufp->chgCData(oldp+83,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_nstate),2);
    bufp->chgSData(oldp+84,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_addr),16);
    bufp->chgCData(oldp+85,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_len),8);
    bufp->chgCData(oldp+86,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_size),3);
    bufp->chgCData(oldp+87,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_burst),2);
    bufp->chgCData(oldp+88,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_id),8);
    bufp->chgCData(oldp+89,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_prot),3);
    bufp->chgCData(oldp+90,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_beat),8);
    bufp->chgQData(oldp+91,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_rdata_q),64);
    bufp->chgCData(oldp+93,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_rresp_q),2);
    bufp->chgBit(oldp+94,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_dvalid));
    bufp->chgSData(oldp+95,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_beat_addr),16);
    bufp->chgBit(oldp+96,(vlSelfRef.axi2axil_tb__DOT__dut__DOT__rd_last));
    bufp->chgBit(oldp+97,(vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.arready));
    bufp->chgBit(oldp+98,(vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.awready));
    bufp->chgCData(oldp+99,(vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.bresp),2);
    bufp->chgBit(oldp+100,(vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.bvalid));
    bufp->chgBit(oldp+101,(vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.rlast));
    bufp->chgBit(oldp+102,(vlSymsp->TOP__axi2axil_tb__DOT__axi_slv_if.wready));
    bufp->chgBit(oldp+103,(vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if.awvalid));
    bufp->chgBit(oldp+104,(vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if.bready));
    bufp->chgBit(oldp+105,(vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if.arvalid));
    bufp->chgBit(oldp+106,(vlSymsp->TOP__axi2axil_tb__DOT__axil_mst_if.rready));
}

void Vaxi2axil_tb___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxi2axil_tb___024root__trace_cleanup\n"); );
    // Locals
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    Vaxi2axil_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaxi2axil_tb___024root*>(voidSelf);
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
