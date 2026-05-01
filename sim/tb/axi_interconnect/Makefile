MODULE    = axi_interconnect_tb
TOP       = ./$(MODULE).sv
TEST_CPP  = ./$(MODULE).cpp

VERILATOR = verilator

RTL_DIR   = ../../../rtl
RTL_FILES = $(shell find $(RTL_DIR) -name "*.sv" -o -name "*.v")

BFM_DIR   = ../../../sim/bfm
CPP_DIRS  = $(BFM_DIR) $(BFM_DIR)/axi
CPP_INC   = $(foreach dir, $(CPP_DIRS), -I$(abspath $(dir)))

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

.stamp.verilate: $(TOP) $(TEST_CPP) FORCE
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
	  -Wno-SELRANGE -Wno-DECLFILENAME -Wno-UNSIGNED \
	  -Wno-ASCRANGE -Wno-CMPCONST
	@touch .stamp.verilate

.PHONY: lint
lint: $(TOP) $(RTL_FILES)
	$(VERILATOR) --lint-only $(TOP) $(RTL_FILES)

.PHONY: clean
clean:
	rm -rf .stamp.verilate ./obj_dir waveform.vcd
