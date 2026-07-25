// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vaxis_async_fifo_tb__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vaxis_async_fifo_tb::Vaxis_async_fifo_tb(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vaxis_async_fifo_tb__Syms(contextp(), _vcname__, this)}
    , s_clk{vlSymsp->TOP.s_clk}
    , s_rst{vlSymsp->TOP.s_rst}
    , m_clk{vlSymsp->TOP.m_clk}
    , m_rst{vlSymsp->TOP.m_rst}
    , s_axis_tkeep{vlSymsp->TOP.s_axis_tkeep}
    , s_axis_tstrb{vlSymsp->TOP.s_axis_tstrb}
    , s_axis_tlast{vlSymsp->TOP.s_axis_tlast}
    , s_axis_tid{vlSymsp->TOP.s_axis_tid}
    , s_axis_tdest{vlSymsp->TOP.s_axis_tdest}
    , s_axis_tuser{vlSymsp->TOP.s_axis_tuser}
    , s_axis_tvalid{vlSymsp->TOP.s_axis_tvalid}
    , s_axis_tready{vlSymsp->TOP.s_axis_tready}
    , m_axis_tkeep{vlSymsp->TOP.m_axis_tkeep}
    , m_axis_tstrb{vlSymsp->TOP.m_axis_tstrb}
    , m_axis_tlast{vlSymsp->TOP.m_axis_tlast}
    , m_axis_tid{vlSymsp->TOP.m_axis_tid}
    , m_axis_tdest{vlSymsp->TOP.m_axis_tdest}
    , m_axis_tuser{vlSymsp->TOP.m_axis_tuser}
    , m_axis_tvalid{vlSymsp->TOP.m_axis_tvalid}
    , m_axis_tready{vlSymsp->TOP.m_axis_tready}
    , s_level{vlSymsp->TOP.s_level}
    , s_overflow{vlSymsp->TOP.s_overflow}
    , s_aux_level{vlSymsp->TOP.s_aux_level}
    , s_aux_overflow{vlSymsp->TOP.s_aux_overflow}
    , s_bad_frame{vlSymsp->TOP.s_bad_frame}
    , s_good_frame{vlSymsp->TOP.s_good_frame}
    , m_level{vlSymsp->TOP.m_level}
    , m_underflow{vlSymsp->TOP.m_underflow}
    , m_aux_level{vlSymsp->TOP.m_aux_level}
    , m_aux_underflow{vlSymsp->TOP.m_aux_underflow}
    , m_bad_frame{vlSymsp->TOP.m_bad_frame}
    , m_good_frame{vlSymsp->TOP.m_good_frame}
    , tb_frame_fifo{vlSymsp->TOP.tb_frame_fifo}
    , tb_always_recv{vlSymsp->TOP.tb_always_recv}
    , tb_depth{vlSymsp->TOP.tb_depth}
    , tb_data_width{vlSymsp->TOP.tb_data_width}
    , s_axis_tdata{vlSymsp->TOP.s_axis_tdata}
    , m_axis_tdata{vlSymsp->TOP.m_axis_tdata}
    , __PVT__axis_async_fifo_tb__DOT__s_axis_if{vlSymsp->TOP.__PVT__axis_async_fifo_tb__DOT__s_axis_if}
    , __PVT__axis_async_fifo_tb__DOT__m_axis_if{vlSymsp->TOP.__PVT__axis_async_fifo_tb__DOT__m_axis_if}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vaxis_async_fifo_tb::Vaxis_async_fifo_tb(const char* _vcname__)
    : Vaxis_async_fifo_tb(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vaxis_async_fifo_tb::~Vaxis_async_fifo_tb() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vaxis_async_fifo_tb___024root___eval_debug_assertions(Vaxis_async_fifo_tb___024root* vlSelf);
#endif  // VL_DEBUG
void Vaxis_async_fifo_tb___024root___eval_static(Vaxis_async_fifo_tb___024root* vlSelf);
void Vaxis_async_fifo_tb___024root___eval_initial(Vaxis_async_fifo_tb___024root* vlSelf);
void Vaxis_async_fifo_tb___024root___eval_settle(Vaxis_async_fifo_tb___024root* vlSelf);
void Vaxis_async_fifo_tb___024root___eval(Vaxis_async_fifo_tb___024root* vlSelf);

void Vaxis_async_fifo_tb::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vaxis_async_fifo_tb::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vaxis_async_fifo_tb___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vaxis_async_fifo_tb___024root___eval_static(&(vlSymsp->TOP));
        Vaxis_async_fifo_tb___024root___eval_initial(&(vlSymsp->TOP));
        Vaxis_async_fifo_tb___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vaxis_async_fifo_tb___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vaxis_async_fifo_tb::eventsPending() { return false; }

uint64_t Vaxis_async_fifo_tb::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vaxis_async_fifo_tb::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vaxis_async_fifo_tb___024root___eval_final(Vaxis_async_fifo_tb___024root* vlSelf);

VL_ATTR_COLD void Vaxis_async_fifo_tb::final() {
    Vaxis_async_fifo_tb___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vaxis_async_fifo_tb::hierName() const { return vlSymsp->name(); }
const char* Vaxis_async_fifo_tb::modelName() const { return "Vaxis_async_fifo_tb"; }
unsigned Vaxis_async_fifo_tb::threads() const { return 1; }
void Vaxis_async_fifo_tb::prepareClone() const { contextp()->prepareClone(); }
void Vaxis_async_fifo_tb::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vaxis_async_fifo_tb::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vaxis_async_fifo_tb___024root__trace_decl_types(VerilatedVcd* tracep);

void Vaxis_async_fifo_tb___024root__trace_init_top(Vaxis_async_fifo_tb___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vaxis_async_fifo_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaxis_async_fifo_tb___024root*>(voidSelf);
    Vaxis_async_fifo_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vaxis_async_fifo_tb___024root__trace_decl_types(tracep);
    Vaxis_async_fifo_tb___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vaxis_async_fifo_tb___024root__trace_register(Vaxis_async_fifo_tb___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vaxis_async_fifo_tb::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vaxis_async_fifo_tb::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vaxis_async_fifo_tb___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
