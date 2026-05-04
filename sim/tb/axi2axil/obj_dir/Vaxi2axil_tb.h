// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary model header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VAXI2AXIL_TB_H_
#define VERILATED_VAXI2AXIL_TB_H_  // guard

#include "verilated.h"

class Vaxi2axil_tb__Syms;
class Vaxi2axil_tb___024root;
class VerilatedVcdC;
class Vaxi2axil_tb_if_axi__A10_I8;
class Vaxi2axil_tb_if_axil__D40;


// This class is the main interface to the Verilated model
class alignas(VL_CACHE_LINE_BYTES) Vaxi2axil_tb VL_NOT_FINAL : public VerilatedModel {
  private:
    // Symbol table holding complete model state (owned by this class)
    Vaxi2axil_tb__Syms* const vlSymsp;

  public:

    // CONSTEXPR CAPABILITIES
    // Verilated with --trace?
    static constexpr bool traceCapable = true;

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(&clk,0,0);
    VL_IN8(&rst_n,0,0);
    VL_IN8(&m_awid,7,0);
    VL_IN8(&m_awlen,7,0);
    VL_IN8(&m_awsize,2,0);
    VL_IN8(&m_awburst,1,0);
    VL_IN8(&m_awcache,3,0);
    VL_IN8(&m_awlock,0,0);
    VL_IN8(&m_awprot,2,0);
    VL_IN8(&m_awqos,3,0);
    VL_IN8(&m_awregion,3,0);
    VL_IN8(&m_awvalid,0,0);
    VL_OUT8(&m_awready,0,0);
    VL_IN8(&m_wstrb,7,0);
    VL_IN8(&m_wid,7,0);
    VL_IN8(&m_wlast,0,0);
    VL_IN8(&m_wvalid,0,0);
    VL_OUT8(&m_wready,0,0);
    VL_OUT8(&m_bresp,1,0);
    VL_OUT8(&m_bid,7,0);
    VL_OUT8(&m_bvalid,0,0);
    VL_IN8(&m_bready,0,0);
    VL_IN8(&m_arid,7,0);
    VL_IN8(&m_arlen,7,0);
    VL_IN8(&m_arsize,2,0);
    VL_IN8(&m_arburst,1,0);
    VL_IN8(&m_arcache,3,0);
    VL_IN8(&m_arlock,0,0);
    VL_IN8(&m_arprot,2,0);
    VL_IN8(&m_arqos,3,0);
    VL_IN8(&m_arregion,3,0);
    VL_IN8(&m_arvalid,0,0);
    VL_OUT8(&m_arready,0,0);
    VL_OUT8(&m_rresp,1,0);
    VL_OUT8(&m_rid,7,0);
    VL_OUT8(&m_rlast,0,0);
    VL_OUT8(&m_rvalid,0,0);
    VL_IN8(&m_rready,0,0);
    VL_OUT8(&s_awvalid,0,0);
    VL_IN8(&s_awready,0,0);
    VL_OUT8(&s_awprot,2,0);
    VL_OUT8(&s_wvalid,0,0);
    VL_IN8(&s_wready,0,0);
    VL_OUT8(&s_wstrb,7,0);
    VL_IN8(&s_bvalid,0,0);
    VL_OUT8(&s_bready,0,0);
    VL_IN8(&s_bresp,1,0);
    VL_OUT8(&s_arvalid,0,0);
    VL_IN8(&s_arready,0,0);
    VL_OUT8(&s_arprot,2,0);
    VL_IN8(&s_rvalid,0,0);
    VL_OUT8(&s_rready,0,0);
    VL_IN8(&s_rresp,1,0);
    VL_IN16(&m_awaddr,15,0);
    VL_IN16(&m_araddr,15,0);
    VL_OUT16(&s_awaddr,15,0);
    VL_OUT16(&s_araddr,15,0);
    VL_IN64(&m_wdata,63,0);
    VL_OUT64(&m_rdata,63,0);
    VL_OUT64(&s_wdata,63,0);
    VL_IN64(&s_rdata,63,0);

    // CELLS
    // Public to allow access to /* verilator public */ items.
    // Otherwise the application code can consider these internals.
    Vaxi2axil_tb_if_axi__A10_I8* const __PVT__axi2axil_tb__DOT__axi_slv_if;
    Vaxi2axil_tb_if_axil__D40* const __PVT__axi2axil_tb__DOT__axil_mst_if;

    // Root instance pointer to allow access to model internals,
    // including inlined /* verilator public_flat_* */ items.
    Vaxi2axil_tb___024root* const rootp;

    // CONSTRUCTORS
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    explicit Vaxi2axil_tb(VerilatedContext* contextp, const char* name = "TOP");
    explicit Vaxi2axil_tb(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    virtual ~Vaxi2axil_tb();
  private:
    VL_UNCOPYABLE(Vaxi2axil_tb);  ///< Copying not allowed

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
