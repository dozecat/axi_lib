// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxi2axil_tb.h for the primary calling header

#include "Vaxi2axil_tb__pch.h"

VL_ATTR_COLD void Vaxi2axil_tb_if_axil__D40___stl_sequent__TOP__axi2axil_tb__DOT__axil_mst_if__0(Vaxi2axil_tb_if_axil__D40* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vaxi2axil_tb_if_axil__D40___stl_sequent__TOP__axi2axil_tb__DOT__axil_mst_if__0\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.bready = (2U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_state));
    vlSelfRef.arvalid = (1U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__rd_state));
    vlSelfRef.rready = (2U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__rd_state));
    vlSelfRef.awvalid = ((1U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_state)) 
                         & (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_wpend));
}

VL_ATTR_COLD void Vaxi2axil_tb_if_axil__D40___ctor_var_reset(Vaxi2axil_tb_if_axil__D40* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vaxi2axil_tb_if_axil__D40___ctor_var_reset\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->awaddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 10741232094138379896ull);
    vlSelf->awprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 4465653203409244048ull);
    vlSelf->awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9399710217136046492ull);
    vlSelf->awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14077405313628979207ull);
    vlSelf->bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16336171827316305440ull);
    vlSelf->bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3607396732575112162ull);
    vlSelf->bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14655036748745407948ull);
    vlSelf->wdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 12890271867161903902ull);
    vlSelf->wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2694481459927628098ull);
    vlSelf->wstrb = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15125268524300477597ull);
    vlSelf->wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13135585445238253745ull);
    vlSelf->araddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 17685200476622543275ull);
    vlSelf->arprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 15011922206834421026ull);
    vlSelf->arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2587622265565774708ull);
    vlSelf->arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16774798297805906817ull);
    vlSelf->rdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 10065165116613087284ull);
    vlSelf->rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8930348232195030647ull);
    vlSelf->rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 810448354640171968ull);
    vlSelf->rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14125721737830190460ull);
}
