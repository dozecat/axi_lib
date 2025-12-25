// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vaxil_test__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vaxil_test::Vaxil_test(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vaxil_test__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , s_axil_awprot{vlSymsp->TOP.s_axil_awprot}
    , s_axil_awvalid{vlSymsp->TOP.s_axil_awvalid}
    , s_axil_awready{vlSymsp->TOP.s_axil_awready}
    , s_axil_wstrb{vlSymsp->TOP.s_axil_wstrb}
    , s_axil_wvalid{vlSymsp->TOP.s_axil_wvalid}
    , s_axil_wready{vlSymsp->TOP.s_axil_wready}
    , s_axil_bresp{vlSymsp->TOP.s_axil_bresp}
    , s_axil_bvalid{vlSymsp->TOP.s_axil_bvalid}
    , s_axil_bready{vlSymsp->TOP.s_axil_bready}
    , s_axil_arprot{vlSymsp->TOP.s_axil_arprot}
    , s_axil_arvalid{vlSymsp->TOP.s_axil_arvalid}
    , s_axil_arready{vlSymsp->TOP.s_axil_arready}
    , s_axil_rresp{vlSymsp->TOP.s_axil_rresp}
    , s_axil_rvalid{vlSymsp->TOP.s_axil_rvalid}
    , s_axil_rready{vlSymsp->TOP.s_axil_rready}
    , m_axil_awprot{vlSymsp->TOP.m_axil_awprot}
    , m_axil_awvalid{vlSymsp->TOP.m_axil_awvalid}
    , m_axil_awready{vlSymsp->TOP.m_axil_awready}
    , m_axil_wstrb{vlSymsp->TOP.m_axil_wstrb}
    , m_axil_wvalid{vlSymsp->TOP.m_axil_wvalid}
    , m_axil_wready{vlSymsp->TOP.m_axil_wready}
    , m_axil_bresp{vlSymsp->TOP.m_axil_bresp}
    , m_axil_bvalid{vlSymsp->TOP.m_axil_bvalid}
    , m_axil_bready{vlSymsp->TOP.m_axil_bready}
    , m_axil_arprot{vlSymsp->TOP.m_axil_arprot}
    , m_axil_arvalid{vlSymsp->TOP.m_axil_arvalid}
    , m_axil_arready{vlSymsp->TOP.m_axil_arready}
    , m_axil_rresp{vlSymsp->TOP.m_axil_rresp}
    , m_axil_rvalid{vlSymsp->TOP.m_axil_rvalid}
    , m_axil_rready{vlSymsp->TOP.m_axil_rready}
    , s_axil_awaddr{vlSymsp->TOP.s_axil_awaddr}
    , s_axil_araddr{vlSymsp->TOP.s_axil_araddr}
    , m_axil_awaddr{vlSymsp->TOP.m_axil_awaddr}
    , m_axil_araddr{vlSymsp->TOP.m_axil_araddr}
    , s_axil_wdata{vlSymsp->TOP.s_axil_wdata}
    , s_axil_rdata{vlSymsp->TOP.s_axil_rdata}
    , m_axil_wdata{vlSymsp->TOP.m_axil_wdata}
    , m_axil_rdata{vlSymsp->TOP.m_axil_rdata}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vaxil_test::Vaxil_test(const char* _vcname__)
    : Vaxil_test(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vaxil_test::~Vaxil_test() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vaxil_test___024root___eval_debug_assertions(Vaxil_test___024root* vlSelf);
#endif  // VL_DEBUG
void Vaxil_test___024root___eval_static(Vaxil_test___024root* vlSelf);
void Vaxil_test___024root___eval_initial(Vaxil_test___024root* vlSelf);
void Vaxil_test___024root___eval_settle(Vaxil_test___024root* vlSelf);
void Vaxil_test___024root___eval(Vaxil_test___024root* vlSelf);

void Vaxil_test::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vaxil_test::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vaxil_test___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vaxil_test___024root___eval_static(&(vlSymsp->TOP));
        Vaxil_test___024root___eval_initial(&(vlSymsp->TOP));
        Vaxil_test___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vaxil_test___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vaxil_test::eventsPending() { return false; }

uint64_t Vaxil_test::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vaxil_test::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vaxil_test___024root___eval_final(Vaxil_test___024root* vlSelf);

VL_ATTR_COLD void Vaxil_test::final() {
    Vaxil_test___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vaxil_test::hierName() const { return vlSymsp->name(); }
const char* Vaxil_test::modelName() const { return "Vaxil_test"; }
unsigned Vaxil_test::threads() const { return 1; }
void Vaxil_test::prepareClone() const { contextp()->prepareClone(); }
void Vaxil_test::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vaxil_test::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vaxil_test___024root__trace_decl_types(VerilatedVcd* tracep);

void Vaxil_test___024root__trace_init_top(Vaxil_test___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vaxil_test___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaxil_test___024root*>(voidSelf);
    Vaxil_test__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vaxil_test___024root__trace_decl_types(tracep);
    Vaxil_test___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vaxil_test___024root__trace_register(Vaxil_test___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vaxil_test::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vaxil_test::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vaxil_test___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
