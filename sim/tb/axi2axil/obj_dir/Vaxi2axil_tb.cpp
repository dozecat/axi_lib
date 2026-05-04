// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vaxi2axil_tb__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vaxi2axil_tb::Vaxi2axil_tb(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vaxi2axil_tb__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst_n{vlSymsp->TOP.rst_n}
    , m_awid{vlSymsp->TOP.m_awid}
    , m_awlen{vlSymsp->TOP.m_awlen}
    , m_awsize{vlSymsp->TOP.m_awsize}
    , m_awburst{vlSymsp->TOP.m_awburst}
    , m_awcache{vlSymsp->TOP.m_awcache}
    , m_awlock{vlSymsp->TOP.m_awlock}
    , m_awprot{vlSymsp->TOP.m_awprot}
    , m_awqos{vlSymsp->TOP.m_awqos}
    , m_awregion{vlSymsp->TOP.m_awregion}
    , m_awvalid{vlSymsp->TOP.m_awvalid}
    , m_awready{vlSymsp->TOP.m_awready}
    , m_wstrb{vlSymsp->TOP.m_wstrb}
    , m_wid{vlSymsp->TOP.m_wid}
    , m_wlast{vlSymsp->TOP.m_wlast}
    , m_wvalid{vlSymsp->TOP.m_wvalid}
    , m_wready{vlSymsp->TOP.m_wready}
    , m_bresp{vlSymsp->TOP.m_bresp}
    , m_bid{vlSymsp->TOP.m_bid}
    , m_bvalid{vlSymsp->TOP.m_bvalid}
    , m_bready{vlSymsp->TOP.m_bready}
    , m_arid{vlSymsp->TOP.m_arid}
    , m_arlen{vlSymsp->TOP.m_arlen}
    , m_arsize{vlSymsp->TOP.m_arsize}
    , m_arburst{vlSymsp->TOP.m_arburst}
    , m_arcache{vlSymsp->TOP.m_arcache}
    , m_arlock{vlSymsp->TOP.m_arlock}
    , m_arprot{vlSymsp->TOP.m_arprot}
    , m_arqos{vlSymsp->TOP.m_arqos}
    , m_arregion{vlSymsp->TOP.m_arregion}
    , m_arvalid{vlSymsp->TOP.m_arvalid}
    , m_arready{vlSymsp->TOP.m_arready}
    , m_rresp{vlSymsp->TOP.m_rresp}
    , m_rid{vlSymsp->TOP.m_rid}
    , m_rlast{vlSymsp->TOP.m_rlast}
    , m_rvalid{vlSymsp->TOP.m_rvalid}
    , m_rready{vlSymsp->TOP.m_rready}
    , s_awvalid{vlSymsp->TOP.s_awvalid}
    , s_awready{vlSymsp->TOP.s_awready}
    , s_awprot{vlSymsp->TOP.s_awprot}
    , s_wvalid{vlSymsp->TOP.s_wvalid}
    , s_wready{vlSymsp->TOP.s_wready}
    , s_wstrb{vlSymsp->TOP.s_wstrb}
    , s_bvalid{vlSymsp->TOP.s_bvalid}
    , s_bready{vlSymsp->TOP.s_bready}
    , s_bresp{vlSymsp->TOP.s_bresp}
    , s_arvalid{vlSymsp->TOP.s_arvalid}
    , s_arready{vlSymsp->TOP.s_arready}
    , s_arprot{vlSymsp->TOP.s_arprot}
    , s_rvalid{vlSymsp->TOP.s_rvalid}
    , s_rready{vlSymsp->TOP.s_rready}
    , s_rresp{vlSymsp->TOP.s_rresp}
    , m_awaddr{vlSymsp->TOP.m_awaddr}
    , m_araddr{vlSymsp->TOP.m_araddr}
    , s_awaddr{vlSymsp->TOP.s_awaddr}
    , s_araddr{vlSymsp->TOP.s_araddr}
    , m_wdata{vlSymsp->TOP.m_wdata}
    , m_rdata{vlSymsp->TOP.m_rdata}
    , s_wdata{vlSymsp->TOP.s_wdata}
    , s_rdata{vlSymsp->TOP.s_rdata}
    , __PVT__axi2axil_tb__DOT__axi_slv_if{vlSymsp->TOP.__PVT__axi2axil_tb__DOT__axi_slv_if}
    , __PVT__axi2axil_tb__DOT__axil_mst_if{vlSymsp->TOP.__PVT__axi2axil_tb__DOT__axil_mst_if}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vaxi2axil_tb::Vaxi2axil_tb(const char* _vcname__)
    : Vaxi2axil_tb(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vaxi2axil_tb::~Vaxi2axil_tb() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vaxi2axil_tb___024root___eval_debug_assertions(Vaxi2axil_tb___024root* vlSelf);
#endif  // VL_DEBUG
void Vaxi2axil_tb___024root___eval_static(Vaxi2axil_tb___024root* vlSelf);
void Vaxi2axil_tb___024root___eval_initial(Vaxi2axil_tb___024root* vlSelf);
void Vaxi2axil_tb___024root___eval_settle(Vaxi2axil_tb___024root* vlSelf);
void Vaxi2axil_tb___024root___eval(Vaxi2axil_tb___024root* vlSelf);

void Vaxi2axil_tb::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vaxi2axil_tb::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vaxi2axil_tb___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vaxi2axil_tb___024root___eval_static(&(vlSymsp->TOP));
        Vaxi2axil_tb___024root___eval_initial(&(vlSymsp->TOP));
        Vaxi2axil_tb___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vaxi2axil_tb___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vaxi2axil_tb::eventsPending() { return false; }

uint64_t Vaxi2axil_tb::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vaxi2axil_tb::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vaxi2axil_tb___024root___eval_final(Vaxi2axil_tb___024root* vlSelf);

VL_ATTR_COLD void Vaxi2axil_tb::final() {
    Vaxi2axil_tb___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vaxi2axil_tb::hierName() const { return vlSymsp->name(); }
const char* Vaxi2axil_tb::modelName() const { return "Vaxi2axil_tb"; }
unsigned Vaxi2axil_tb::threads() const { return 1; }
void Vaxi2axil_tb::prepareClone() const { contextp()->prepareClone(); }
void Vaxi2axil_tb::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vaxi2axil_tb::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vaxi2axil_tb___024root__trace_decl_types(VerilatedVcd* tracep);

void Vaxi2axil_tb___024root__trace_init_top(Vaxi2axil_tb___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vaxi2axil_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaxi2axil_tb___024root*>(voidSelf);
    Vaxi2axil_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vaxi2axil_tb___024root__trace_decl_types(tracep);
    Vaxi2axil_tb___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vaxi2axil_tb___024root__trace_register(Vaxi2axil_tb___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vaxi2axil_tb::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vaxi2axil_tb::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vaxi2axil_tb___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
