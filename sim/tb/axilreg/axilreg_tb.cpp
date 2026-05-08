/******************************************************************************
 * Copyright (C) 2026 dozecat. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axilreg_tb.cpp
 * @brief       AXI4-Lite Register File Testbench (C++)
 * @see         https://github.com/dozecat/axi_lib
 *
 * Modification History:
 * Ver   Who  Date        Changes
 * ----  ---- ----------  -----------------------------------------------------
 * 1.0        2026/05/07  Initial release
 ******************************************************************************/

#include "Vaxilreg_tb.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <svdpi.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "axil_ptr.hpp"
#include "axil.hpp"

#define DATA_WIDTH 32
#define ADDR_WIDTH 16

#define REG_TEST1_ADDR 0x00
#define REG_TEST2_ADDR 0x04

static void connect_axil(axil_ptr<DATA_WIDTH, ADDR_WIDTH>& p, Vaxilreg_tb* top) {
    p.awaddr  = &(top->s_awaddr);   p.awprot  = &(top->s_awprot);
    p.awready = &(top->s_awready);  p.awvalid = &(top->s_awvalid);
    p.bready  = &(top->s_bready);   p.bresp   = &(top->s_bresp);
    p.bvalid  = &(top->s_bvalid);
    p.wdata   = &(top->s_wdata);    p.wready  = &(top->s_wready);
    p.wstrb   = &(top->s_wstrb);    p.wvalid  = &(top->s_wvalid);
    p.araddr  = &(top->s_araddr);   p.arprot  = &(top->s_arprot);
    p.arready = &(top->s_arready);  p.arvalid = &(top->s_arvalid);
    p.rdata   = &(top->s_rdata);    p.rready  = &(top->s_rready);
    p.rresp   = &(top->s_rresp);    p.rvalid  = &(top->s_rvalid);
}

static bool check(const char* name, bool cond, int& pass, int& fail) {
    std::cout << "  [" << (cond ? "PASS" : "FAIL") << "] " << name << std::endl;
    if (cond) pass++; else fail++;
    return cond;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vaxilreg_tb* top = new Vaxilreg_tb;
    VerilatedVcdC* tfp = new VerilatedVcdC;

    axil_ptr<DATA_WIDTH, ADDR_WIDTH> axil_prt;
    connect_axil(axil_prt, top);
    if (!axil_prt.check()) { std::cerr << "axil_prt connection failed!" << std::endl; return -1; }

    axil_master<DATA_WIDTH, ADDR_WIDTH> axil_mst(axil_prt);

    top->trace(tfp, 100);
    tfp->open("waveform.vcd");

    top->clk = 0;
    top->rst = 1;
    top->eval();
    for (int i = 0; i < 10; i++) { top->clk = !top->clk; top->eval(); }
    top->rst = 0;
    top->eval();

    uint64_t rd_val = 0;
    int sim_time = 0, cycle = 0, pass = 0, fail = 0;
    bool test_ok = false;

    enum {
        PHASE_INIT, PHASE_T1_WR, PHASE_T1_RD, PHASE_T2_SET,
        PHASE_T2_RD, PHASE_T3_MULTI, PHASE_T3_CHK, PHASE_DONE
    } phase = PHASE_INIT;
    int phase_start = 0, multi_cnt = 0;

    const uint32_t test_val_a = 0xDEADBEEF;
    const uint32_t test_val_b = 0x12345678;
    const uint32_t test_val_c = 0xA5A5A5A5;

    std::cout << "\n=== AXI4-Lite Register File Testbench ===" << std::endl;

    while (!Verilated::gotFinish() && sim_time < 10000) {
        sim_time++;
        top->clk = !top->clk;

        if (top->clk) { axil_mst.update_input(); }
        top->eval();

        if (top->clk) {
            cycle++;

            switch (phase) {

            // Test 1: write reg_test2 via AXI-Lite, verify via port and readback
            case PHASE_INIT:
                if (cycle == 10) {
                    std::cout << "\n[TEST 1] Write reg_test2 via AXI-Lite" << std::endl;
                    std::cout << "  Write 0x04 = 0x" << std::hex << test_val_a << std::dec << std::endl;
                    axil_mst.write(REG_TEST2_ADDR, test_val_a);
                    phase = PHASE_T1_WR;
                    phase_start = cycle;
                }
                break;

            case PHASE_T1_WR:
                if (cycle > phase_start + 80) {
                    test_ok = (top->reg_test2 == test_val_a);
                    check("reg_test2 port reflects AXI-Lite write", test_ok, pass, fail);
                    std::cout << "  Read back 0x04 via AXI-Lite" << std::endl;
                    axil_mst.read(REG_TEST2_ADDR);
                    phase = PHASE_T1_RD;
                }
                break;

            case PHASE_T1_RD:
                if (axil_mst.get_read_data(rd_val)) {
                    test_ok = (rd_val == test_val_a);
                    check("reg_test2 AXI-Lite readback", test_ok, pass, fail);

                    std::cout << "\n[TEST 2] Read reg_test1 via AXI-Lite" << std::endl;
                    top->reg_test1 = test_val_b;
                    std::cout << "  Set reg_test1 = 0x" << std::hex << test_val_b << std::dec << std::endl;
                    std::cout << "  Read 0x00 via AXI-Lite" << std::endl;
                    axil_mst.read(REG_TEST1_ADDR);
                    phase = PHASE_T2_SET;
                }
                break;

            // Test 2: set reg_test1 via port, read via AXI-Lite
            case PHASE_T2_SET:
                if (axil_mst.get_read_data(rd_val)) {
                    test_ok = (rd_val == test_val_b);
                    check("reg_test1 AXI-Lite readback matches port", test_ok, pass, fail);

                    std::cout << "\n[TEST 3] Multiple writes" << std::endl;
                    axil_mst.write(REG_TEST2_ADDR, test_val_c);
                    phase = PHASE_T3_MULTI;
                    phase_start = cycle;
                    multi_cnt = 0;
                }
                break;

            // Test 3: Multiple writes to reg_test2, verify via port
            case PHASE_T3_MULTI:
                if (cycle > phase_start + 80) {
                    test_ok = (top->reg_test2 == test_val_c);
                    check("reg_test2 = 0xA5A5A5A5 after write", test_ok, pass, fail);

                    axil_mst.write(REG_TEST2_ADDR, 0x11112222);
                    multi_cnt = 1;
                    phase_start = cycle;
                    phase = PHASE_T3_CHK;
                }
                break;

            case PHASE_T3_CHK:
                if (multi_cnt == 1 && cycle > phase_start + 80) {
                    test_ok = (top->reg_test2 == 0x11112222);
                    check("reg_test2 = 0x11112222 after second write", test_ok, pass, fail);

                    axil_mst.read(REG_TEST2_ADDR);
                    multi_cnt = 2;
                }
                if (multi_cnt == 2 && axil_mst.get_read_data(rd_val)) {
                    test_ok = (rd_val == 0x11112222);
                    check("reg_test2 AXI-Lite readback after second write", test_ok, pass, fail);
                    phase = PHASE_DONE;
                    phase_start = cycle;
                }
                break;

            case PHASE_DONE:
                if (cycle > phase_start + 50) goto done;
                break;
            }

            axil_mst.update_output();
        }

        top->eval();
        tfp->dump(sim_time);
    }

done:
    tfp->close();
    delete tfp;
    delete top;

    std::cout << "\n=== Simulation Complete ===" << std::endl;
    std::cout << "  Pass: " << pass << "  Fail: " << fail << std::endl;
    std::cout << "  Result: " << (fail ? "FAILED" : "PASSED") << std::endl;
    return fail ? 1 : 0;
}
