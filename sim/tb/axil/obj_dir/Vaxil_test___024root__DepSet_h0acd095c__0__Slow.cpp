// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaxil_test.h for the primary calling header

#include "Vaxil_test__pch.h"
#include "Vaxil_test___024root.h"

VL_ATTR_COLD void Vaxil_test___024root___eval_static(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___eval_static\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vaxil_test___024root___eval_initial(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___eval_initial\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vaxil_test___024root___eval_final(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___eval_final\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxil_test___024root___dump_triggers__stl(Vaxil_test___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vaxil_test___024root___eval_phase__stl(Vaxil_test___024root* vlSelf);

VL_ATTR_COLD void Vaxil_test___024root___eval_settle(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___eval_settle\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY(((0x64U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vaxil_test___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("axil_test.sv", 17, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vaxil_test___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxil_test___024root___dump_triggers__stl(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___dump_triggers__stl\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

void Vaxil_test___024root___ico_sequent__TOP__0(Vaxil_test___024root* vlSelf);

VL_ATTR_COLD void Vaxil_test___024root___eval_stl(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___eval_stl\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vaxil_test___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vaxil_test___024root___eval_triggers__stl(Vaxil_test___024root* vlSelf);

VL_ATTR_COLD bool Vaxil_test___024root___eval_phase__stl(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___eval_phase__stl\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vaxil_test___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vaxil_test___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxil_test___024root___dump_triggers__ico(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___dump_triggers__ico\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxil_test___024root___dump_triggers__act(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___dump_triggers__act\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaxil_test___024root___dump_triggers__nba(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___dump_triggers__nba\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vaxil_test___024root___ctor_var_reset(Vaxil_test___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaxil_test___024root___ctor_var_reset\n"); );
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->s_axil_awaddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 13848725219975908421ull);
    vlSelf->s_axil_awprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 12586643765258326842ull);
    vlSelf->s_axil_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5565460829454824723ull);
    vlSelf->s_axil_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16902639615143046160ull);
    vlSelf->s_axil_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1103157403480817957ull);
    vlSelf->s_axil_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 10019753739795228426ull);
    vlSelf->s_axil_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7856252330729444323ull);
    vlSelf->s_axil_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10617832712156855404ull);
    vlSelf->s_axil_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 4619599597122007664ull);
    vlSelf->s_axil_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15275381318758420228ull);
    vlSelf->s_axil_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 341218635761165985ull);
    vlSelf->s_axil_araddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14530572992589720136ull);
    vlSelf->s_axil_arprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 654750358719645750ull);
    vlSelf->s_axil_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14086364826711030938ull);
    vlSelf->s_axil_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3912437489807458257ull);
    vlSelf->s_axil_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5485178797053085655ull);
    vlSelf->s_axil_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 7204267391845473835ull);
    vlSelf->s_axil_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13034476536657300307ull);
    vlSelf->s_axil_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14687157439859267212ull);
    vlSelf->m_axil_awaddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 15768832821461394746ull);
    vlSelf->m_axil_awprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 15399529573511315256ull);
    vlSelf->m_axil_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8430627827263741264ull);
    vlSelf->m_axil_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4280802658202100904ull);
    vlSelf->m_axil_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17762191872756659979ull);
    vlSelf->m_axil_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 1664089752958632314ull);
    vlSelf->m_axil_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6708607417609230471ull);
    vlSelf->m_axil_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5714596453847712469ull);
    vlSelf->m_axil_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 3534485943927033350ull);
    vlSelf->m_axil_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12671347613219417516ull);
    vlSelf->m_axil_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5049936059991651696ull);
    vlSelf->m_axil_araddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 9121807861907387591ull);
    vlSelf->m_axil_arprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 12275326428732292631ull);
    vlSelf->m_axil_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1861743073447131793ull);
    vlSelf->m_axil_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6652997721851075177ull);
    vlSelf->m_axil_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1298481953808388169ull);
    vlSelf->m_axil_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 1619600104025692561ull);
    vlSelf->m_axil_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17932991328843106914ull);
    vlSelf->m_axil_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13045881202544420739ull);
    vlSelf->axil_test__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3535428741104036207ull);
    vlSelf->axil_test__DOT__rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11112172502776866563ull);
    vlSelf->axil_test__DOT__s_axil_awaddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 17614540420397062387ull);
    vlSelf->axil_test__DOT__s_axil_awprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10945659524813163425ull);
    vlSelf->axil_test__DOT__s_axil_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1987132796508039802ull);
    vlSelf->axil_test__DOT__s_axil_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2999541668916743357ull);
    vlSelf->axil_test__DOT__s_axil_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2416110573165339765ull);
    vlSelf->axil_test__DOT__s_axil_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 9758707083499615343ull);
    vlSelf->axil_test__DOT__s_axil_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13162906831768496454ull);
    vlSelf->axil_test__DOT__s_axil_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17045432069438066164ull);
    vlSelf->axil_test__DOT__s_axil_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 15790890553723484149ull);
    vlSelf->axil_test__DOT__s_axil_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2799625341154596949ull);
    vlSelf->axil_test__DOT__s_axil_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14047193002462693093ull);
    vlSelf->axil_test__DOT__s_axil_araddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 11937455326755279821ull);
    vlSelf->axil_test__DOT__s_axil_arprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 10972022323533036664ull);
    vlSelf->axil_test__DOT__s_axil_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 928322701710560319ull);
    vlSelf->axil_test__DOT__s_axil_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8369696617359890410ull);
    vlSelf->axil_test__DOT__s_axil_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9808559298272570568ull);
    vlSelf->axil_test__DOT__s_axil_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10587738580243137844ull);
    vlSelf->axil_test__DOT__s_axil_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11505585354543356680ull);
    vlSelf->axil_test__DOT__s_axil_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9711202516112785414ull);
    vlSelf->axil_test__DOT__m_axil_awaddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 2729491948563246594ull);
    vlSelf->axil_test__DOT__m_axil_awprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 4127956723191610779ull);
    vlSelf->axil_test__DOT__m_axil_awvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4102939161091726933ull);
    vlSelf->axil_test__DOT__m_axil_awready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4739829509993752920ull);
    vlSelf->axil_test__DOT__m_axil_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13554169768056214853ull);
    vlSelf->axil_test__DOT__m_axil_wstrb = VL_SCOPED_RAND_RESET_I(4, __VscopeHash, 12969743634932291080ull);
    vlSelf->axil_test__DOT__m_axil_wvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1660233096126319120ull);
    vlSelf->axil_test__DOT__m_axil_wready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13742145945008212651ull);
    vlSelf->axil_test__DOT__m_axil_bresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 10413451824293579303ull);
    vlSelf->axil_test__DOT__m_axil_bvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15675905928820450742ull);
    vlSelf->axil_test__DOT__m_axil_bready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2771634494781346439ull);
    vlSelf->axil_test__DOT__m_axil_araddr = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 5506990612080878887ull);
    vlSelf->axil_test__DOT__m_axil_arprot = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 12115386773590293575ull);
    vlSelf->axil_test__DOT__m_axil_arvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16465291820536458676ull);
    vlSelf->axil_test__DOT__m_axil_arready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16352032166544202399ull);
    vlSelf->axil_test__DOT__m_axil_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7238927022699766961ull);
    vlSelf->axil_test__DOT__m_axil_rresp = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 912635133420462322ull);
    vlSelf->axil_test__DOT__m_axil_rvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10961970910551920830ull);
    vlSelf->axil_test__DOT__m_axil_rready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16553742232390812153ull);
}
