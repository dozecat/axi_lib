###############################################################################
# axis_async_fifo_tb Makefile
#
# Usage:  make               — Basic direct mode  (FRAME_FIFO=0, ALWAYS=0)
#         make frame         — Frame FIFO mode     (FRAME_FIFO=1)
#         make always_recv   — Always receive       (ALWAYS_RECEIVE=1)
#         make frame-always_recv   — Frame + always receive
#         make FRAME_FIFO=1  — Same as "make frame" (variable syntax)
#
# Note: make --frame does NOT work — GNU Make intercepts --* as options.
#       Use "make frame" or "make FRAME_FIFO=1" instead.
#
# Other targets:
#         make test-all      — Run all parameter combinations
#         make waves         — Open GTKWave
#         make lint          — Verilator lint
#         make clean         — Remove build artifacts
#         make help          — Show this message
###############################################################################

MODULE    = axis_async_fifo_tb
TOP       = ./$(MODULE).sv
TEST_CPP  = ./$(MODULE).cpp

VERILATOR = verilator

RTL_DIR   = ../../../rtl
RTL_FILES = $(shell find $(RTL_DIR) -name "*.sv" -o -name "*.v")

BFM_DIR   = ../../../sim/bfm
CPP_DIRS  = $(BFM_DIR) $(BFM_DIR)/axis
CPP_INC   = $(foreach dir, $(CPP_DIRS), -I$(abspath $(dir)))

# ---- DUT parameters (overridable from command line / convenience targets) ----
FRAME_FIFO     ?= 0
ALWAYS_RECEIVE ?= 0

# ---- Build paths (unique per config) ----
OBJ_SUFFIX := _f$(FRAME_FIFO)a$(ALWAYS_RECEIVE)
OBJ_DIR   = obj_dir$(OBJ_SUFFIX)
STAMP     = .stamp.verilate$(OBJ_SUFFIX)
EXE       = $(OBJ_DIR)/V$(MODULE)
WAVEFORM  = waveform$(OBJ_SUFFIX).vcd

# ---- Verilator parameters ----
PARAMS = -GFRAME_FIFO=$(FRAME_FIFO) \
         -GALWAYS_RECEIVE=$(ALWAYS_RECEIVE)

# ---- Targets ----
.PHONY: all
all: run

.PHONY: run
run: $(WAVEFORM)

.PHONY: build
build: $(EXE)

.PHONY: verilate
verilate: $(STAMP)

$(WAVEFORM): $(EXE)
	@echo
	@echo "### SIMULATING ### (FRAME=$(FRAME_FIFO) ALWAYS=$(ALWAYS_RECEIVE))"
	@./$(EXE) $(WAVEFORM)

$(EXE): $(STAMP)
	@echo
	@echo "### BUILDING SIM ###"
	$(MAKE) -j -C $(OBJ_DIR) -f V$(MODULE).mk
	@touch $@

FORCE:

$(STAMP): $(TOP) $(TEST_CPP) FORCE
	@echo
	@echo "### VERILATING ### (FRAME=$(FRAME_FIFO) ALWAYS=$(ALWAYS_RECEIVE))"
	mkdir -p $(OBJ_DIR)
	$(VERILATOR) -Wall --trace --trace-depth 99 --no-trace-params \
	  --x-assign unique --x-initial unique \
	  --top-module $(MODULE) \
	  -cc $(TOP) --exe $(TEST_CPP) \
	  -Mdir $(OBJ_DIR) \
	  -CFLAGS "$(CPP_INC)" \
	  $(foreach f, $(RTL_FILES), $(f)) \
	  $(PARAMS) \
	  -public \
	  -Wno-PINCONNECTEMPTY -Wno-NULLPORT -Wno-PROCASSINIT \
	  -Wno-GENUNNAMED -Wno-IMPLICIT -Wno-PINNOTFOUND \
	  -Wno-PINMISSING -Wno-WIDTHEXPAND -Wno-WIDTHTRUNC \
	  -Wno-UNUSEDPARAM -Wno-SYNCASYNCNET -Wno-UNUSED \
	  -Wno-SELRANGE -Wno-DECLFILENAME -Wno-UNSIGNED \
	  -Wno-ASCRANGE -Wno-CMPCONST -Wno-MULTIDRIVEN \
	  -Wno-MULTITOP -Wno-UNOPTFLAT
	@touch $@

# ---- Convenience targets ----
# Each invokes a sub-make with the appropriate DUT parameters.
# GNU Make intercepts --* as options, so we use target names instead.

.PHONY: frame
frame:
	+$(MAKE) FRAME_FIFO=1

.PHONY: always_recv
always_recv:
	+$(MAKE) ALWAYS_RECEIVE=1

.PHONY: frame-always_recv
frame-always_recv:
	+$(MAKE) FRAME_FIFO=1 ALWAYS_RECEIVE=1

# ---- FRAME_FIFO comprehensive test ----
# A single simulation runs all scenarios (single-word, boundary GOOD/BAD,
# oversize, multi-frame, mixed GOOD+BAD+GOOD).
.PHONY: test-frame
test-frame:
	+$(MAKE) FRAME_FIFO=1

# ---- Test all ----
.PHONY: test-all
test-all:
	@echo "=== basic ===" &&     $(MAKE) && \
	echo "=== frame ===" &&      $(MAKE) frame && \
	echo "=== always_recv ===" && $(MAKE) always_recv && \
	echo "=== frame+always_recv ===" && $(MAKE) frame-always_recv

# ---- Lint ----
.PHONY: lint
lint: $(TOP) $(RTL_FILES)
	$(VERILATOR) --lint-only $(TOP) $(RTL_FILES) $(PARAMS) \
	  -Wno-PINCONNECTEMPTY -Wno-NULLPORT -Wno-PROCASSINIT \
	  -Wno-GENUNNAMED -Wno-IMPLICIT -Wno-PINNOTFOUND \
	  -Wno-PINMISSING -Wno-WIDTHEXPAND -Wno-WIDTHTRUNC \
	  -Wno-UNUSEDPARAM -Wno-SYNCASYNCNET -Wno-UNUSED \
	  -Wno-UNSIGNED -Wno-CMPCONST -Wno-MULTITOP

# ---- Waves ----
.PHONY: waves
waves: $(WAVEFORM)
	gtkwave $(WAVEFORM)

# ---- Help ----
.PHONY: help
help:
	@echo "Usage: make {frame|always_recv|test-all|lint|waves|clean|help}"
	@echo ""
	@echo "Convenience targets (set DUT parameters):"
	@echo "  make               Basic direct mode (default)"
	@echo "  make frame         Frame FIFO mode (FRAME_FIFO=1)"
	@echo "  make always_recv   Always receive (ALWAYS_RECEIVE=1)"
	@echo "  make frame-always_recv  Frame + always receive"
	@echo "  make test-frame    FRAME_FIFO comprehensive test (all scenarios)"
	@echo ""
	@echo "Other targets:"
	@echo "  make test-all      Run ALL tests (basic + frame + always_recv + test-frame)"
	@echo "  make waves         Open waveform in GTKWave"
	@echo "  make lint          Verilator lint"
	@echo "  make clean         Remove build artifacts"
	@echo ""
	@echo "Note: make --frame does not work because GNU Make intercepts"
	@echo "--* arguments as options. Use 'make frame' instead."

# ---- Clean ----
.PHONY: clean
clean:
	rm -rf .stamp.verilate* ./obj_dir* *.vcd
