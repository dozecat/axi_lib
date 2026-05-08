MODULE    = axilreg_tb
TOP       = ./$(MODULE).sv
TEST_CPP  = ./$(MODULE).cpp
TB_SV     = ./axil_register_file.sv

VERILATOR = verilator

RTL_DIR   = ../../../rtl
RTL_FILES = $(shell find $(RTL_DIR) -name "*.sv" -o -name "*.v")

BFM_DIR   = ../../../sim/bfm
CPP_DIRS  = $(BFM_DIR) $(BFM_DIR)/axil
CPP_INC   = $(foreach dir, $(CPP_DIRS), -I$(abspath $(dir)))

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

.stamp.verilate: $(TOP) $(TEST_CPP) $(TB_SV) FORCE
	@echo
	@echo "### VERILATING ###"
	$(VERILATOR) -Wall --trace --no-trace-params \
	  --x-assign unique --x-initial unique \
	  --top-module $(MODULE) \
	  -cc $(TOP) $(TB_SV) --exe $(TEST_CPP) \
	  -CFLAGS "$(CPP_INC)" \
	  $(foreach f, $(RTL_FILES), $(f)) \
	  -public \
	  -Wno-PINCONNECTEMPTY -Wno-NULLPORT -Wno-PROCASSINIT \
	  -Wno-GENUNNAMED -Wno-IMPLICIT -Wno-PINNOTFOUND \
	  -Wno-PINMISSING -Wno-WIDTHEXPAND -Wno-WIDTHTRUNC \
	  -Wno-UNUSEDPARAM -Wno-SYNCASYNCNET -Wno-UNUSED \
	  -Wno-SELRANGE -Wno-DECLFILENAME -Wno-UNSIGNED \
	  -Wno-ASCRANGE -Wno-CMPCONST \
	  -Wno-CASEINCOMPLETE
	@touch .stamp.verilate

.PHONY: lint
lint: $(TOP) $(TB_SV) $(RTL_FILES)
	$(VERILATOR) --lint-only --top-module $(MODULE) $(TOP) $(TB_SV) $(RTL_FILES) -Wno-WIDTHEXPAND -Wno-CASEINCOMPLETE

.PHONY: clean
clean:
	rm -rf .stamp.verilate ./obj_dir waveform.vcd
