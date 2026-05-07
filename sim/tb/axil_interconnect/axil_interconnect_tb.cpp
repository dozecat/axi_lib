/******************************************************************************
 * Copyright (C) 2025 dozecat. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axil_interconnect_tb.cpp
 * @brief       AXI4-Lite Interconnect Testbench (C++)
 * @see         https://github.com/dozecat/axi_lib
 *
 * @details     Verilator C++ TB for AXI4-Lite Interconnect.
 *              VIP: `axil_ptr.hpp`, `axil.hpp`
 *              (include dirs from `sim/bfm/axil`).
 *
 * Modification History:
 * Ver   Who  Date        Changes
 * ----  ---- ----------  -----------------------------------------------------
 * 1.0        2026/05/01  Initial release
 ******************************************************************************/

#include "Vaxil_interconnect_tb.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "axil_ptr.hpp"
#include "axil.hpp"

#define DATA_WIDTH 32
#define ADDR_WIDTH 16
#define SLV_NUM 2
#define MST_NUM 4

template <typename T>
static void connect_slv_port(axil_ptr<DATA_WIDTH, ADDR_WIDTH>& p, T* top, int idx) {
    #define MAP(n) \
        p.awaddr  = &(top->slv ## n ## _awaddr);  p.awprot  = &(top->slv ## n ## _awprot); \
        p.awready = &(top->slv ## n ## _awready); p.awvalid = &(top->slv ## n ## _awvalid); \
        p.bready  = &(top->slv ## n ## _bready);  p.bresp   = &(top->slv ## n ## _bresp); \
        p.bvalid  = &(top->slv ## n ## _bvalid); \
        p.wdata   = &(top->slv ## n ## _wdata);   p.wready  = &(top->slv ## n ## _wready); \
        p.wstrb   = &(top->slv ## n ## _wstrb);   p.wvalid  = &(top->slv ## n ## _wvalid); \
        p.araddr  = &(top->slv ## n ## _araddr);  p.arprot  = &(top->slv ## n ## _arprot); \
        p.arready = &(top->slv ## n ## _arready); p.arvalid = &(top->slv ## n ## _arvalid); \
        p.rdata   = &(top->slv ## n ## _rdata);   p.rready  = &(top->slv ## n ## _rready); \
        p.rresp   = &(top->slv ## n ## _rresp);   p.rvalid  = &(top->slv ## n ## _rvalid);
    switch (idx) {
        case 0: MAP(0); break;
        case 1: MAP(1); break;
    }
    #undef MAP
}

template <typename T>
static void connect_mst_port(axil_ptr<DATA_WIDTH, ADDR_WIDTH>& p, T* top, int idx) {
    #define MAP(n) \
        p.awaddr  = &(top->mst ## n ## _awaddr);  p.awprot  = &(top->mst ## n ## _awprot); \
        p.awready = &(top->mst ## n ## _awready); p.awvalid = &(top->mst ## n ## _awvalid); \
        p.bready  = &(top->mst ## n ## _bready);  p.bresp   = &(top->mst ## n ## _bresp); \
        p.bvalid  = &(top->mst ## n ## _bvalid); \
        p.wdata   = &(top->mst ## n ## _wdata);   p.wready  = &(top->mst ## n ## _wready); \
        p.wstrb   = &(top->mst ## n ## _wstrb);   p.wvalid  = &(top->mst ## n ## _wvalid); \
        p.araddr  = &(top->mst ## n ## _araddr);  p.arprot  = &(top->mst ## n ## _arprot); \
        p.arready = &(top->mst ## n ## _arready); p.arvalid = &(top->mst ## n ## _arvalid); \
        p.rdata   = &(top->mst ## n ## _rdata);   p.rready  = &(top->mst ## n ## _rready); \
        p.rresp   = &(top->mst ## n ## _rresp);   p.rvalid  = &(top->mst ## n ## _rvalid);
    switch (idx) {
        case 0: MAP(0); break;
        case 1: MAP(1); break;
        case 2: MAP(2); break;
        case 3: MAP(3); break;
    }
    #undef MAP
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vaxil_interconnect_tb* top = new Vaxil_interconnect_tb;
    VerilatedVcdC* tfp = new VerilatedVcdC;

    axil_ptr<DATA_WIDTH, ADDR_WIDTH> slv_ptr[SLV_NUM];
    axil_ptr<DATA_WIDTH, ADDR_WIDTH> mst_ptr[MST_NUM];

    for (int i = 0; i < SLV_NUM; i++) {
        connect_slv_port(slv_ptr[i], top, i);
    }
    for (int i = 0; i < MST_NUM; i++) {
        connect_mst_port(mst_ptr[i], top, i);
    }

    for (int i = 0; i < SLV_NUM; i++) {
        if (!slv_ptr[i].check()) {
            std::cerr << "[TB] slv_ptr[" << i << "] connection failed!" << std::endl;
            return -1;
        }
    }
    for (int i = 0; i < MST_NUM; i++) {
        if (!mst_ptr[i].check()) {
            std::cerr << "[TB] mst_ptr[" << i << "] connection failed!" << std::endl;
            return -1;
        }
    }

    axil_master<DATA_WIDTH, ADDR_WIDTH> mst_bfm[SLV_NUM] = {
        axil_master<DATA_WIDTH, ADDR_WIDTH>(slv_ptr[0]),
        axil_master<DATA_WIDTH, ADDR_WIDTH>(slv_ptr[1])
    };
    axil_slave<DATA_WIDTH, ADDR_WIDTH> slv_bfm[MST_NUM] = {
        axil_slave<DATA_WIDTH, ADDR_WIDTH>(mst_ptr[0]),
        axil_slave<DATA_WIDTH, ADDR_WIDTH>(mst_ptr[1]),
        axil_slave<DATA_WIDTH, ADDR_WIDTH>(mst_ptr[2]),
        axil_slave<DATA_WIDTH, ADDR_WIDTH>(mst_ptr[3])
    };

    top->trace(tfp, 100);
    tfp->open("waveform.vcd");

    top->clk = 0;
    top->rst = 1;

    uint64_t tick = 0;
    uint64_t cycle = 0;
    const uint64_t MAX_TICKS = 2000;
    int pass = 0, fail = 0;

    std::cout << "\n=== AXI4-Lite Interconnect Testbench (SLV_NUM=2, MST_NUM=4) ===\n" << std::endl;

    while (!Verilated::gotFinish() && tick < MAX_TICKS) {
        top->clk = !top->clk;
        tick++;

        if (tick == 5) {
            top->rst = 0;
        }

        if (top->clk) {
            for (int i = 0; i < SLV_NUM; i++) {
                mst_bfm[i].update_input();
            }
            for (int i = 0; i < MST_NUM; i++) {
                slv_bfm[i].update_input();
            }
        }

        top->eval();

        if (top->clk) {
            cycle++;

            // Phase 1: masters write to slaves
            if (cycle == 5) {
                std::cout << "[TEST] Master0->Slave0: write(0x0010, 0xA5A5A5A5)" << std::endl;
                mst_bfm[0].write(0x0010, 0xA5A5A5A5);
            }
            if (cycle == 6) {
                std::cout << "[TEST] Master1->Slave1: write(0x0110, 0x5A5A5A5A)" << std::endl;
                mst_bfm[1].write(0x0110, 0x5A5A5A5A);
            }

            // Phase 2: Read back
            if (cycle == 20) {
                std::cout << "[TEST] Read back" << std::endl;
                mst_bfm[0].read(0x0010);
                mst_bfm[1].read(0x0110);
            }

            // Phase 3: Simultaneous writes to different slaves
            if (cycle == 35) {
                std::cout << "[TEST] Both masters -> different slaves" << std::endl;
                mst_bfm[0].write(0x0020, 0x12345678);
                mst_bfm[1].write(0x0120, 0x87654321);
            }

            // Phase 4: Read back
            if (cycle == 50) {
                std::cout << "[TEST] Read back" << std::endl;
                mst_bfm[0].read(0x0020);
                mst_bfm[1].read(0x0120);
            }

            // Phase 5: Priority contention - both masters contend for Slave0
            // Master0(prio=1) has higher priority than Master1(prio=0)
            if (cycle == 65) {
                std::cout << "[TEST] Contention: 2 masters -> Slave0 (prio: M0>M1)" << std::endl;
                mst_bfm[0].write(0x0040, 0x11110000);
                mst_bfm[1].write(0x0040, 0x22220000);
            }

            // Phase 6: Verify contention
            if (cycle == 85) {
                std::cout << "[TEST] Contention read back" << std::endl;
                mst_bfm[0].read(0x0040);
                mst_bfm[1].read(0x0040);
            }

            // Phase 7: Unmapped access
            if (cycle == 100) {
                std::cout << "[TEST] Master0->unmapped: write(0x0400, expect DECERR)" << std::endl;
                mst_bfm[0].write(0x0400, 0xDEADBEEF);
            }

            // Read data verification
            for (int i = 0; i < SLV_NUM; i++) {
                uint64_t rdata;
                while (mst_bfm[i].get_read_data(rdata)) {
                    bool ok = false;
                    for (int m = 0; m < MST_NUM; m++) {
                        for (auto& kv : slv_bfm[m].mem) {
                            if (rdata == kv.second) { ok = true; break; }
                        }
                        if (ok) break;
                    }
                    std::cout << "[TB]   Master" << i << " rd: 0x"
                              << std::hex << rdata << std::dec;
                    if (ok) { std::cout << " PASS" << std::endl; pass++; }
                    else    { std::cout << " FAIL" << std::endl; fail++; }
                }
            }

            // Update BFM output signals
            for (int i = 0; i < SLV_NUM; i++) {
                mst_bfm[i].update_output();
            }
            for (int i = 0; i < MST_NUM; i++) {
                slv_bfm[i].update_output();
            }
        }

        top->eval();
        tfp->dump(tick);
    }

    tfp->close();
    delete tfp;
    delete top;

    std::cout << "\n=== Simulation Complete ===" << std::endl;
    std::cout << "  Cycles: " << cycle << std::endl;
    std::cout << "  Pass:   " << pass << std::endl;
    std::cout << "  Fail:   " << fail << std::endl;
    int result = (fail > 0) ? 1 : 0;
    std::cout << "  Result: " << (result ? "FAILED" : "PASSED") << std::endl;
    return result;
}
