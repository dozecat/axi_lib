// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary model header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VAXIS_ASYNC_FIFO_TB_H_
#define VERILATED_VAXIS_ASYNC_FIFO_TB_H_  // guard

#include "verilated.h"

class Vaxis_async_fifo_tb__Syms;
class Vaxis_async_fifo_tb___024root;
class VerilatedVcdC;
class Vaxis_async_fifo_tb_if_axis;


// This class is the main interface to the Verilated model
class alignas(VL_CACHE_LINE_BYTES) Vaxis_async_fifo_tb VL_NOT_FINAL : public VerilatedModel {
  private:
    // Symbol table holding complete model state (owned by this class)
    Vaxis_async_fifo_tb__Syms* const vlSymsp;

  public:

    // CONSTEXPR CAPABILITIES
    // Verilated with --trace?
    static constexpr bool traceCapable = true;

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(&s_clk,0,0);
    VL_IN8(&s_rst,0,0);
    VL_IN8(&m_clk,0,0);
    VL_IN8(&m_rst,0,0);
    VL_IN8(&s_axis_tkeep,7,0);
    VL_IN8(&s_axis_tstrb,7,0);
    VL_IN8(&s_axis_tlast,0,0);
    VL_IN8(&s_axis_tid,7,0);
    VL_IN8(&s_axis_tdest,0,0);
    VL_IN8(&s_axis_tuser,0,0);
    VL_IN8(&s_axis_tvalid,0,0);
    VL_OUT8(&s_axis_tready,0,0);
    VL_OUT8(&m_axis_tkeep,7,0);
    VL_OUT8(&m_axis_tstrb,7,0);
    VL_OUT8(&m_axis_tlast,0,0);
    VL_OUT8(&m_axis_tid,7,0);
    VL_OUT8(&m_axis_tdest,0,0);
    VL_OUT8(&m_axis_tuser,0,0);
    VL_OUT8(&m_axis_tvalid,0,0);
    VL_IN8(&m_axis_tready,0,0);
    VL_OUT8(&s_level,4,0);
    VL_OUT8(&s_overflow,0,0);
    VL_OUT8(&s_aux_level,4,0);
    VL_OUT8(&s_aux_overflow,0,0);
    VL_OUT8(&s_bad_frame,0,0);
    VL_OUT8(&s_good_frame,0,0);
    VL_OUT8(&m_level,4,0);
    VL_OUT8(&m_underflow,0,0);
    VL_OUT8(&m_aux_level,4,0);
    VL_OUT8(&m_aux_underflow,0,0);
    VL_OUT8(&m_bad_frame,0,0);
    VL_OUT8(&m_good_frame,0,0);
    VL_OUT8(&tb_frame_fifo,0,0);
    VL_OUT8(&tb_always_recv,0,0);
    VL_OUT(&tb_depth,31,0);
    VL_OUT(&tb_data_width,31,0);
    VL_IN64(&s_axis_tdata,63,0);
    VL_OUT64(&m_axis_tdata,63,0);

    // CELLS
    // Public to allow access to /* verilator public */ items.
    // Otherwise the application code can consider these internals.
    Vaxis_async_fifo_tb_if_axis* const __PVT__axis_async_fifo_tb__DOT__s_axis_if;
    Vaxis_async_fifo_tb_if_axis* const __PVT__axis_async_fifo_tb__DOT__m_axis_if;

    // Root instance pointer to allow access to model internals,
    // including inlined /* verilator public_flat_* */ items.
    Vaxis_async_fifo_tb___024root* const rootp;

    // CONSTRUCTORS
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    explicit Vaxis_async_fifo_tb(VerilatedContext* contextp, const char* name = "TOP");
    explicit Vaxis_async_fifo_tb(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    virtual ~Vaxis_async_fifo_tb();
  private:
    VL_UNCOPYABLE(Vaxis_async_fifo_tb);  ///< Copying not allowed

  public:
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    /// Are there scheduled events to handle?
    bool eventsPending();
    /// Returns time at next time slot. Aborts if !eventsPending()
    uint64_t nextTimeSlot();
    /// Trace signals in the model; called by application code
    void trace(VerilatedTraceBaseC* tfp, int levels, int options = 0) { contextp()->trace(tfp, levels, options); }
    /// Retrieve name of this model instance (as passed to constructor).
    const char* name() const;

    // Abstract methods from VerilatedModel
    const char* hierName() const override final;
    const char* modelName() const override final;
    unsigned threads() const override final;
    /// Prepare for cloning the model at the process level (e.g. fork in Linux)
    /// Release necessary resources. Called before cloning.
    void prepareClone() const;
    /// Re-init after cloning the model at the process level (e.g. fork in Linux)
    /// Re-allocate necessary resources. Called after cloning.
    void atClone() const;
    std::unique_ptr<VerilatedTraceConfig> traceConfig() const override final;
  private:
    // Internal functions - trace registration
    void traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options);
};

#endif  // guard
