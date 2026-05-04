// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxi2axil_tb.h for the primary calling header

#include "Vaxi2axil_tb__pch.h"

VL_ATTR_COLD void Vaxi2axil_tb_if_axi__A10_I8___stl_sequent__TOP__axi2axil_tb__DOT__axi_slv_if__0(Vaxi2axil_tb_if_axi__A10_I8* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vaxi2axil_tb_if_axi__A10_I8___stl_sequent__TOP__axi2axil_tb__DOT__axi_slv_if__0\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.awready = (0U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_state));
    vlSelfRef.bvalid = (3U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_state));
    vlSelfRef.arready = (0U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__rd_state));
    vlSelfRef.wready = ((~ (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_wpend)) 
                        & (1U == (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_state)));
    vlSelfRef.bresp = ((IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_err)
                        ? 2U : (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__wr_resp));
    vlSelfRef.rlast = ((IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__rd_dvalid) 
                       & (IData)(vlSymsp->TOP.axi2axil_tb__DOT__dut__DOT__rd_last));
}

VL_ATTR_COLD void Vaxi2axil_tb_if_axi__A10_I8___ctor_var_reset(Vaxi2axil_tb_if_axi__A10_I8* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+          Vaxi2axil_tb_if_axi__A10_I8___ctor_var_reset\n"); );
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->araddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 17685200476622543275ull);
    vlSelf->arburst = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 17635634856046503333ull);
    vlSelf->arcache = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 5383566022461370443ull);
    vlSelf->arid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2554568685633023ull);
    vlSelf->arlen = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 2795619241893056918ull);
    vlSelf->arlock = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1028088570121261799ull);
    vlSelf->arprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 15011922206834421026ull);
    vlSelf->arqos = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 503377616339909361ull);
    vlSelf->arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2587622265565774708ull);
    vlSelf->arregion = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 7047348028896828731ull);
    vlSelf->arsize = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 548378465311237866ull);
    vlSelf->arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16774798297805906817ull);
    vlSelf->awaddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 10741232094138379896ull);
    vlSelf->awburst = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 2194945690521623954ull);
    vlSelf->awcache = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 12571631497265920282ull);
    vlSelf->awid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3795331727834872933ull);
    vlSelf->awlen = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 13823799410002427218ull);
    vlSelf->awlock = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4764929847244516576ull);
    vlSelf->awprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 4465653203409244048ull);
    vlSelf->awqos = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 6081282207813340951ull);
    vlSelf->awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9399710217136046492ull);
    vlSelf->awregion = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 3976432916626163437ull);
    vlSelf->awsize = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 14063175441069765856ull);
    vlSelf->awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14077405313628979207ull);
    vlSelf->bid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 3323000146968766057ull);
    vlSelf->bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16336171827316305440ull);
    vlSelf->bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3607396732575112162ull);
    vlSelf->bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14655036748745407948ull);
    vlSelf->rdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 10065165116613087284ull);
    vlSelf->rid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17711635114162165067ull);
    vlSelf->rlast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5670148758994432807ull);
    vlSelf->rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8930348232195030647ull);
    vlSelf->rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 810448354640171968ull);
    vlSelf->rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14125721737830190460ull);
    vlSelf->wdata = VL_SCOPED_RAND_RESET_Q(64, __VscopeHash, 12890271867161903902ull);
    vlSelf->wid = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 17912304310502850154ull);
    vlSelf->wlast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8447900327780902047ull);
    vlSelf->wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2694481459927628098ull);
    vlSelf->wstrb = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 15125268524300477597ull);
    vlSelf->wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13135585445238253745ull);
}
