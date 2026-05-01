# AGENTS.md — axi_lib

## Build & Run

```bash
# Run AXI interconnect testbench (full pipeline: verilate + build + sim)
cd sim/tb/axi_interconnect && make sim

# Run AXI4-Lite interconnect testbench
cd sim/tb/axil_interconnect && make sim

# Lint RTL only
cd sim/tb/axi_interconnect && make lint

# Open waveform
make waves           # requires gtkwave

# Clean artifacts (.stamp.verilate, obj_dir/, waveform.vcd)
make clean
```

Make targets per testbench: `verilate` → `build` → `sim` → `waves`.

## Architecture

```
rtl/              # SystemVerilog: interface defs + interconnects + primitives
  if_axi.sv        - AXI4 interface (modport master/slave)
  if_axil.sv       - AXI4-Lite interface
  if_axis.sv       - AXI4-Stream interface
  axi_interconnect.sv, axil_interconnect.sv  - crossbar interconnects
  arbiter.sv, sync_fifo.v, async_fifo.v, skid_buffer.v, axil_sc_fifo.sv

sim/bfm/           # Header-only C++ BFMs (no .cpp, no library build)
  axi/{axi.hpp, axi_ptr.hpp, axi_master.hpp, axi_slave.hpp, axi_common.hpp}
  axil/{axil.hpp, axil_ptr.hpp, axil_master.hpp, axil_slave.hpp}
  axis/{axis.hpp, axis_prt.hpp, axis_master.hpp, axis_slave.hpp}
  log.hpp, sig.hpp

sim/tb/            # Verilator testbenches
  axi_interconnect/    - 4-master, 4-slave AXI crossbar TB
  axil_interconnect/   - AXI4-Lite crossbar TB
```

**Important:** README is stale — there are no `sim/tb/axi/`, `sim/tb/axil/`, or `sim/tb/axis/` dirs.

## BFM Template Parameters

| BFM | Template args | Pointer struct |
|-----|--------------|----------------|
| `axi_master/slave` | `<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH>` | `axi_ptr<D, A, I>` |
| `axil_master/slave` | `<DATA_WIDTH, ADDR_WIDTH>` | `axil_ptr<D, A>` |
| `axis_master/slave` | `<DATA_WIDTH>` | `axis_prt<D>` |

## BFM Simulation Loop Pattern (C++ testbench)

```cpp
// negedge: sample inputs from DUT
if (!clk) { bfm.update_input(); }

// posedge: drive outputs to DUT
if (clk) { bfm.update_output(); }
```

Testbench always runs to max tick unless `Verilated::gotFinish()` (not typically set). See `sim/tb/axi_interconnect/axi_interconnect_tb.cpp` for the full pattern: call `update_input` on negedge, `update_output` on posedge, `top->eval()` after each clock toggle.

BFM ops: `write_incr`, `read_incr`, `write_fixed`, `read_fixed`, `write_wrap`, `read_wrap` — all take `(addr, data, id)`.

Signal pointers must be connected via the `*_ptr` struct and pass `check()` before use.

## Makefile Quirks

- RTL sources discovered by `find $(RTL_DIR) -name "*.sv" -o -name "*.v"` — add files there and they're picked up automatically.
- C++ includes added via `-I` for BFM directory + protocol subdirectory.
- Verilator warnings suppressed: `PINCONNECTEMPTY NULLPORT PROCASSINIT GENUNNAMED IMPLICIT PINNOTFOUND PINMISSING WIDTHEXPAND WIDTHTRUNC UNUSEDPARAM SYNCASYNCNET UNUSED SELRANGE DECLFILENAME UNSIGNED ASCRANGE CMPCONST`.
- Uses `--x-assign unique --x-initial unique`, `--trace --no-trace-params`, `-public`.
- `sig.hpp` provides `sig_t(msb, lsb)` macro mapping bit width to `CData`/`SData`/`IData`/`QData`/`VlWide`.

## No CI, no formatter, no package manager

This is a pure RTL + C++ header-only library. No npm, no pre-commit, no CI workflows. Git history is 7 commits.
