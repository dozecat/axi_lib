// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vaxil_test__Syms.h"


VL_ATTR_COLD void Vaxil_test___024root__trace_init_sub__TOP__0(Vaxil_test___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root__trace_init_sub__TOP__0\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->pushPrefix("$rootio", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+1,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+2,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+3,0,"s_axil_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+4,0,"s_axil_awprot",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+5,0,"s_axil_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+6,0,"s_axil_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+7,0,"s_axil_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+8,0,"s_axil_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+9,0,"s_axil_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+10,0,"s_axil_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+11,0,"s_axil_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+12,0,"s_axil_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+13,0,"s_axil_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+14,0,"s_axil_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+15,0,"s_axil_arprot",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+16,0,"s_axil_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+17,0,"s_axil_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+18,0,"s_axil_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+19,0,"s_axil_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+20,0,"s_axil_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+21,0,"s_axil_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+22,0,"m_axil_awaddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+23,0,"m_axil_awprot",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+24,0,"m_axil_awvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+25,0,"m_axil_awready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+26,0,"m_axil_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+27,0,"m_axil_wstrb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+28,0,"m_axil_wvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+29,0,"m_axil_wready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+30,0,"m_axil_bresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+31,0,"m_axil_bvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+32,0,"m_axil_bready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+33,0,"m_axil_araddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+34,0,"m_axil_arprot",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+35,0,"m_axil_arvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+36,0,"m_axil_arready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+37,0,"m_axil_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+38,0,"m_axil_rresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+39,0,"m_axil_rvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+40,0,"m_axil_rready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("axil_test", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+41,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+42,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+43,0,"s_axil_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+44,0,"s_axil_awprot",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+45,0,"s_axil_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+46,0,"s_axil_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+47,0,"s_axil_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+48,0,"s_axil_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+49,0,"s_axil_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+50,0,"s_axil_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+51,0,"s_axil_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+52,0,"s_axil_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+53,0,"s_axil_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+54,0,"s_axil_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+55,0,"s_axil_arprot",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+56,0,"s_axil_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+57,0,"s_axil_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+58,0,"s_axil_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+59,0,"s_axil_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+60,0,"s_axil_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+61,0,"s_axil_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+62,0,"m_axil_awaddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+63,0,"m_axil_awprot",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+64,0,"m_axil_awvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+65,0,"m_axil_awready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+66,0,"m_axil_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+67,0,"m_axil_wstrb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+68,0,"m_axil_wvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+69,0,"m_axil_wready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+70,0,"m_axil_bresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+71,0,"m_axil_bvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+72,0,"m_axil_bready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+73,0,"m_axil_araddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+74,0,"m_axil_arprot",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+75,0,"m_axil_arvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+76,0,"m_axil_arready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+77,0,"m_axil_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+78,0,"m_axil_rresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+79,0,"m_axil_rvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+80,0,"m_axil_rready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vaxil_test___024root__trace_init_top(Vaxil_test___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root__trace_init_top\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vaxil_test___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vaxil_test___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vaxil_test___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vaxil_test___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vaxil_test___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vaxil_test___024root__trace_register(Vaxil_test___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root__trace_register\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vaxil_test___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&Vaxil_test___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&Vaxil_test___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&Vaxil_test___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vaxil_test___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root__trace_const_0\n"); );
    // Init
    Vaxil_test___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaxil_test___024root*>(voidSelf);
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
}

VL_ATTR_COLD void Vaxil_test___024root__trace_full_0_sub_0(Vaxil_test___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vaxil_test___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root__trace_full_0\n"); );
    // Init
    Vaxil_test___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaxil_test___024root*>(voidSelf);
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vaxil_test___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vaxil_test___024root__trace_full_0_sub_0(Vaxil_test___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root__trace_full_0_sub_0\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelfRef.clk));
    bufp->fullBit(oldp+2,(vlSelfRef.rst));
    bufp->fullSData(oldp+3,(vlSelfRef.s_axil_awaddr),16);
    bufp->fullCData(oldp+4,(vlSelfRef.s_axil_awprot),3);
    bufp->fullBit(oldp+5,(vlSelfRef.s_axil_awvalid));
    bufp->fullBit(oldp+6,(vlSelfRef.s_axil_awready));
    bufp->fullIData(oldp+7,(vlSelfRef.s_axil_wdata),32);
    bufp->fullCData(oldp+8,(vlSelfRef.s_axil_wstrb),4);
    bufp->fullBit(oldp+9,(vlSelfRef.s_axil_wvalid));
    bufp->fullBit(oldp+10,(vlSelfRef.s_axil_wready));
    bufp->fullCData(oldp+11,(vlSelfRef.s_axil_bresp),2);
    bufp->fullBit(oldp+12,(vlSelfRef.s_axil_bvalid));
    bufp->fullBit(oldp+13,(vlSelfRef.s_axil_bready));
    bufp->fullSData(oldp+14,(vlSelfRef.s_axil_araddr),16);
    bufp->fullCData(oldp+15,(vlSelfRef.s_axil_arprot),3);
    bufp->fullBit(oldp+16,(vlSelfRef.s_axil_arvalid));
    bufp->fullBit(oldp+17,(vlSelfRef.s_axil_arready));
    bufp->fullIData(oldp+18,(vlSelfRef.s_axil_rdata),32);
    bufp->fullCData(oldp+19,(vlSelfRef.s_axil_rresp),2);
    bufp->fullBit(oldp+20,(vlSelfRef.s_axil_rvalid));
    bufp->fullBit(oldp+21,(vlSelfRef.s_axil_rready));
    bufp->fullSData(oldp+22,(vlSelfRef.m_axil_awaddr),16);
    bufp->fullCData(oldp+23,(vlSelfRef.m_axil_awprot),3);
    bufp->fullBit(oldp+24,(vlSelfRef.m_axil_awvalid));
    bufp->fullBit(oldp+25,(vlSelfRef.m_axil_awready));
    bufp->fullIData(oldp+26,(vlSelfRef.m_axil_wdata),32);
    bufp->fullCData(oldp+27,(vlSelfRef.m_axil_wstrb),4);
    bufp->fullBit(oldp+28,(vlSelfRef.m_axil_wvalid));
    bufp->fullBit(oldp+29,(vlSelfRef.m_axil_wready));
    bufp->fullCData(oldp+30,(vlSelfRef.m_axil_bresp),2);
    bufp->fullBit(oldp+31,(vlSelfRef.m_axil_bvalid));
    bufp->fullBit(oldp+32,(vlSelfRef.m_axil_bready));
    bufp->fullSData(oldp+33,(vlSelfRef.m_axil_araddr),16);
    bufp->fullCData(oldp+34,(vlSelfRef.m_axil_arprot),3);
    bufp->fullBit(oldp+35,(vlSelfRef.m_axil_arvalid));
    bufp->fullBit(oldp+36,(vlSelfRef.m_axil_arready));
    bufp->fullIData(oldp+37,(vlSelfRef.m_axil_rdata),32);
    bufp->fullCData(oldp+38,(vlSelfRef.m_axil_rresp),2);
    bufp->fullBit(oldp+39,(vlSelfRef.m_axil_rvalid));
    bufp->fullBit(oldp+40,(vlSelfRef.m_axil_rready));
    bufp->fullBit(oldp+41,(vlSelfRef.axil_test__DOT__clk));
    bufp->fullBit(oldp+42,(vlSelfRef.axil_test__DOT__rst));
    bufp->fullSData(oldp+43,(vlSelfRef.axil_test__DOT__s_axil_awaddr),16);
    bufp->fullCData(oldp+44,(vlSelfRef.axil_test__DOT__s_axil_awprot),3);
    bufp->fullBit(oldp+45,(vlSelfRef.axil_test__DOT__s_axil_awvalid));
    bufp->fullBit(oldp+46,(vlSelfRef.axil_test__DOT__s_axil_awready));
    bufp->fullIData(oldp+47,(vlSelfRef.axil_test__DOT__s_axil_wdata),32);
    bufp->fullCData(oldp+48,(vlSelfRef.axil_test__DOT__s_axil_wstrb),4);
    bufp->fullBit(oldp+49,(vlSelfRef.axil_test__DOT__s_axil_wvalid));
    bufp->fullBit(oldp+50,(vlSelfRef.axil_test__DOT__s_axil_wready));
    bufp->fullCData(oldp+51,(vlSelfRef.axil_test__DOT__s_axil_bresp),2);
    bufp->fullBit(oldp+52,(vlSelfRef.axil_test__DOT__s_axil_bvalid));
    bufp->fullBit(oldp+53,(vlSelfRef.axil_test__DOT__s_axil_bready));
    bufp->fullSData(oldp+54,(vlSelfRef.axil_test__DOT__s_axil_araddr),16);
    bufp->fullCData(oldp+55,(vlSelfRef.axil_test__DOT__s_axil_arprot),3);
    bufp->fullBit(oldp+56,(vlSelfRef.axil_test__DOT__s_axil_arvalid));
    bufp->fullBit(oldp+57,(vlSelfRef.axil_test__DOT__s_axil_arready));
    bufp->fullIData(oldp+58,(vlSelfRef.axil_test__DOT__s_axil_rdata),32);
    bufp->fullCData(oldp+59,(vlSelfRef.axil_test__DOT__s_axil_rresp),2);
    bufp->fullBit(oldp+60,(vlSelfRef.axil_test__DOT__s_axil_rvalid));
    bufp->fullBit(oldp+61,(vlSelfRef.axil_test__DOT__s_axil_rready));
    bufp->fullSData(oldp+62,(vlSelfRef.axil_test__DOT__m_axil_awaddr),16);
    bufp->fullCData(oldp+63,(vlSelfRef.axil_test__DOT__m_axil_awprot),3);
    bufp->fullBit(oldp+64,(vlSelfRef.axil_test__DOT__m_axil_awvalid));
    bufp->fullBit(oldp+65,(vlSelfRef.axil_test__DOT__m_axil_awready));
    bufp->fullIData(oldp+66,(vlSelfRef.axil_test__DOT__m_axil_wdata),32);
    bufp->fullCData(oldp+67,(vlSelfRef.axil_test__DOT__m_axil_wstrb),4);
    bufp->fullBit(oldp+68,(vlSelfRef.axil_test__DOT__m_axil_wvalid));
    bufp->fullBit(oldp+69,(vlSelfRef.axil_test__DOT__m_axil_wready));
    bufp->fullCData(oldp+70,(vlSelfRef.axil_test__DOT__m_axil_bresp),2);
    bufp->fullBit(oldp+71,(vlSelfRef.axil_test__DOT__m_axil_bvalid));
    bufp->fullBit(oldp+72,(vlSelfRef.axil_test__DOT__m_axil_bready));
    bufp->fullSData(oldp+73,(vlSelfRef.axil_test__DOT__m_axil_araddr),16);
    bufp->fullCData(oldp+74,(vlSelfRef.axil_test__DOT__m_axil_arprot),3);
    bufp->fullBit(oldp+75,(vlSelfRef.axil_test__DOT__m_axil_arvalid));
    bufp->fullBit(oldp+76,(vlSelfRef.axil_test__DOT__m_axil_arready));
    bufp->fullIData(oldp+77,(vlSelfRef.axil_test__DOT__m_axil_rdata),32);
    bufp->fullCData(oldp+78,(vlSelfRef.axil_test__DOT__m_axil_rresp),2);
    bufp->fullBit(oldp+79,(vlSelfRef.axil_test__DOT__m_axil_rvalid));
    bufp->fullBit(oldp+80,(vlSelfRef.axil_test__DOT__m_axil_rready));
}
