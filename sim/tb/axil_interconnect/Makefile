# Module name configuration
MODULE    = axil_interconnect_tb
TOP       = ./$(MODULE).sv
TEST_CPP  = ./$(MODULE).cpp

VERILATOR = verilator

# RTL source files (DUT)
RTL_DIR   = ../../../rtl
RTL_FILES = $(shell find $(RTL_DIR) -name "*.sv" -o -name "*.v")

ROOT_DIR   = $(abspath ../../..)
DEPS_DIR   = $(ROOT_DIR)/.deps
VAXIVIP_DIR = $(DEPS_DIR)/sim/vaxivip

CPP_DIRS  = $(VAXIVIP_DIR) $(VAXIVIP_DIR)/axil
CPP_INC   = $(foreach dir, $(CPP_DIRS), -I$(abspath $(dir)))

# Local SV files
SVLOG_FILES = $(shell find . -name "*.sv" -o -name "*.v") $(RTL_FILES)

.PHONY: sim
sim: waveform.vcd

.PHONY: verilate
verilate: .stamp.verilate

.PHONY: build
build: .stamp.verilate ./obj_dir/V$(MODULE)

.PHONY: waves
waves: waveform.vcd
	@echo
	@echo "### WAVES ###"
	gtkwave waveform.vcd

waveform.vcd: ./obj_dir/V$(MODULE)
	@echo
	@echo "### SIMULATING ###"
	@./obj_dir/V$(MODULE)

./obj_dir/V$(MODULE): .stamp.verilate
	@echo
	@echo "### BUILDING SIM ###"
	$(MAKE) -C obj_dir -f V$(MODULE).mk V$(MODULE)

FORCE:

$(DEPS_DIR)/.stamp.prepare:
	@echo "Error: dependencies not found. Run: python3 $(ROOT_DIR)/script/get_deps.py --init"
	@false

.stamp.verilate: $(TOP) $(TEST_CPP) $(DEPS_DIR)/.stamp.prepare FORCE
	@echo
	@echo "### VERILATING ###"
	$(VERILATOR) -Wall --trace --no-trace-params \
	  --x-assign unique --x-initial unique \
	  --top-module $(MODULE) \
	  -cc $(TOP) --exe $(TEST_CPP) \
	  -CFLAGS "$(CPP_INC)" \
	  $(foreach f, $(RTL_FILES), $(f)) \
	  -public \
	  -Wno-PINCONNECTEMPTY -Wno-NULLPORT -Wno-PROCASSINIT \
	  -Wno-GENUNNAMED -Wno-IMPLICIT -Wno-PINNOTFOUND \
	  -Wno-PINMISSING -Wno-WIDTHEXPAND -Wno-WIDTHTRUNC \
	  -Wno-UNUSEDPARAM -Wno-SYNCASYNCNET -Wno-UNUSED \
	  -Wno-SELRANGE -Wno-DECLFILENAME -Wno-UNSIGNED
	@touch .stamp.verilate

.PHONY: lint
lint: $(TOP) $(RTL_FILES)
	$(VERILATOR) --lint-only $(TOP) $(RTL_FILES)

.PHONY: clean
clean:
	rm -rf .stamp.verilate ./obj_dir waveform.vcd
