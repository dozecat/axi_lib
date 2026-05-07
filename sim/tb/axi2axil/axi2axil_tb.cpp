/******************************************************************************
 * Copyright (C) 2026 dozecat. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axi2axil_tb.cpp
 * @brief       AXI4-to-AXI4-Lite Bridge Testbench (C++)
 * @see         https://github.com/dozecat/axi_lib
 *
 * Modification History:
 * Ver   Who  Date        Changes
 * ----  ---- ----------  -----------------------------------------------------
 * 1.0        2026/05/04  Initial release
 ******************************************************************************/

#include "Vaxi2axil_tb.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <svdpi.h>
#include <iostream>
#include <vector>
#include "axi_ptr.hpp"
#include "axi.hpp"
#include "axil_ptr.hpp"
#include "axil.hpp"

#define DATA_WIDTH 64
#define ADDR_WIDTH 16
#define ID_WIDTH   8

/**
 * @brief Connect BFM pointers to Verilator model signals
 */
void bridge_connect(axi_ptr<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH>& axi_prt,
                    axil_ptr<DATA_WIDTH, ADDR_WIDTH>& axil_prt,
                    Vaxi2axil_tb* top) {
    // AXI Master (Input to DUT) - s_* signals
    axi_prt.awid     = &(top->s_awid);     axi_prt.awaddr   = &(top->s_awaddr);
    axi_prt.awlen    = &(top->s_awlen);    axi_prt.awsize   = &(top->s_awsize);
    axi_prt.awburst  = &(top->s_awburst);  axi_prt.awcache  = &(top->s_awcache);
    axi_prt.awlock   = &(top->s_awlock);   axi_prt.awprot   = &(top->s_awprot);
    axi_prt.awqos    = &(top->s_awqos);    axi_prt.awregion = &(top->s_awregion);
    axi_prt.awvalid  = &(top->s_awvalid);  axi_prt.awready  = &(top->s_awready);

    axi_prt.wdata    = &(top->s_wdata);    axi_prt.wstrb    = &(top->s_wstrb);
    axi_prt.wid      = &(top->s_wid);      axi_prt.wlast    = &(top->s_wlast);
    axi_prt.wvalid   = &(top->s_wvalid);   axi_prt.wready   = &(top->s_wready);

    axi_prt.bid      = &(top->s_bid);      axi_prt.bresp    = &(top->s_bresp);
    axi_prt.bvalid   = &(top->s_bvalid);   axi_prt.bready   = &(top->s_bready);

    axi_prt.arid     = &(top->s_arid);     axi_prt.araddr   = &(top->s_araddr);
    axi_prt.arlen    = &(top->s_arlen);    axi_prt.arsize   = &(top->s_arsize);
    axi_prt.arburst  = &(top->s_arburst);  axi_prt.arcache  = &(top->s_arcache);
    axi_prt.arlock   = &(top->s_arlock);   axi_prt.arprot   = &(top->s_arprot);
    axi_prt.arqos    = &(top->s_arqos);    axi_prt.arregion = &(top->s_arregion);
    axi_prt.arvalid  = &(top->s_arvalid);  axi_prt.arready  = &(top->s_arready);

    axi_prt.rdata    = &(top->s_rdata);    axi_prt.rresp    = &(top->s_rresp);
    axi_prt.rid      = &(top->s_rid);      axi_prt.rlast    = &(top->s_rlast);
    axi_prt.rvalid   = &(top->s_rvalid);   axi_prt.rready   = &(top->s_rready);

    // AXI4-Lite Slave (Output from DUT) - m_* signals
    axil_prt.awaddr  = &(top->m_awaddr);   axil_prt.awprot  = &(top->m_awprot);
    axil_prt.awready = &(top->m_awready);  axil_prt.awvalid = &(top->m_awvalid);
    axil_prt.bready  = &(top->m_bready);   axil_prt.bresp   = &(top->m_bresp);
    axil_prt.bvalid  = &(top->m_bvalid);
    axil_prt.wdata   = &(top->m_wdata);    axil_prt.wready  = &(top->m_wready);
    axil_prt.wstrb   = &(top->m_wstrb);    axil_prt.wvalid  = &(top->m_wvalid);
    axil_prt.araddr  = &(top->m_araddr);   axil_prt.arprot  = &(top->m_arprot);
    axil_prt.arready = &(top->m_arready);  axil_prt.arvalid = &(top->m_arvalid);
    axil_prt.rdata   = &(top->m_rdata);    axil_prt.rready  = &(top->m_rready);
    axil_prt.rresp   = &(top->m_rresp);    axil_prt.rvalid  = &(top->m_rvalid);
}

static bool check_result(const char* name, bool cond, int& pass, int& fail) {
    std::cout << "  [" << (cond ? "PASS" : "FAIL") << "] " << name << std::endl;
    if (cond) pass++; else fail++;
    return cond;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vaxi2axil_tb* top = new Vaxi2axil_tb;
    VerilatedVcdC* tfp = new VerilatedVcdC;

    axi_ptr<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH> axi_prt;
    axil_ptr<DATA_WIDTH, ADDR_WIDTH> axil_prt;

    bridge_connect(axi_prt, axil_prt, top);

    if (!axi_prt.check()) { std::cerr << "axi_prt connection failed!" << std::endl; return -1; }
    if (!axil_prt.check()) { std::cerr << "axil_prt connection failed!" << std::endl; return -1; }

    axi_master<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH> axi_mst(axi_prt);
    axil_slave<DATA_WIDTH, ADDR_WIDTH> axil_slv(axil_prt);

    top->trace(tfp, 100);
    tfp->open("waveform.vcd");

    // Reset
    top->clk   = 0;
    top->rst = 1;
    top->eval();
    for (int i = 0; i < 10; i++) { top->clk = !top->clk; top->eval(); }
    top->rst = 0;
    top->eval();

    int sim_time = 0;
    int cycle = 0;
    const int max_sim_time = 60000;
    int pass = 0, fail = 0;

    // Test phase tracking
    enum { PHASE_IDLE, PHASE_WR1, PHASE_RD1, PHASE_WRBURST, PHASE_RDBURST,
           PHASE_FIXWR, PHASE_FIXRD, PHASE_WRAP, PHASE_LARGEBURST, PHASE_LARGEREAD,
           PHASE_LARGERDWAIT, PHASE_MAXBURST, PHASE_MAXRD, PHASE_DONE, PHASE_DONE2 } phase = PHASE_IDLE;
    int phase_start = 0;

    std::vector<uint8_t> rd_data;

    while (!Verilated::gotFinish() && sim_time < max_sim_time) {
        sim_time++;
        top->clk = !top->clk;

        if (top->clk) {
            axi_mst.update_input();
            axil_slv.update_input();
        }

        top->eval();

        if (top->clk) {
            cycle++;

            // ==== Test 1: INCR write, len=0 ====
            if (cycle == 10) {
                std::cout << "\n[TEST] INCR write, len=0" << std::endl;
                std::vector<uint8_t> d = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
                axi_mst.write_incr(0x100, d);
                phase = PHASE_WR1;
                phase_start = cycle;
            }
            if (phase == PHASE_WR1 && cycle > phase_start + 150) {
                check_result("single beat write", axil_slv.mem[0x100] == 0x8877665544332211ULL, pass, fail);
                phase = PHASE_IDLE;
            }

            // ==== Test 2: INCR read, len=0 ====
            if (cycle == 200) {
                std::cout << "\n[TEST] INCR read, len=0" << std::endl;
                axil_slv.mem[0x200] = 0xAABBCCDDEEFF0011ULL;
                axi_mst.read_incr(0x200, 8);
                phase = PHASE_RD1;
            }
            if (phase == PHASE_RD1 && axi_mst.get_read_data(rd_data)) {
                bool ok = rd_data.size() == 8 && rd_data[0] == 0x11 && rd_data[7] == 0xAA;
                check_result("single beat read", ok, pass, fail);
                rd_data.clear();
                phase = PHASE_IDLE;
            }

            // ==== Test 3: INCR burst write, len=3 ====
            if (cycle == 400) {
                std::cout << "\n[TEST] INCR burst write, len=3" << std::endl;
                std::vector<uint8_t> d(32);
                for (int i = 0; i < 32; i++) d[i] = 0xA0 + i;
                axi_mst.write_incr(0x300, d);
                phase = PHASE_WRBURST;
                phase_start = cycle;
            }
            if (phase == PHASE_WRBURST && cycle > phase_start + 300) {
                bool ok = true;
                for (int i = 0; i < 4; i++) {
                    uint64_t v = 0;
                    for (int b = 0; b < 8; b++) v |= (uint64_t)(0xA0 + i*8 + b) << (b*8);
                    ok &= (axil_slv.mem[0x300 + i*8] == v);
                }
                check_result("burst write len=3", ok, pass, fail);
                phase = PHASE_IDLE;
            }

            // ==== Test 4: INCR burst read, len=3 ====
            if (cycle == 800) {
                std::cout << "\n[TEST] INCR burst read, len=3" << std::endl;
                for (int i = 0; i < 4; i++) {
                    uint64_t v = 0;
                    for (int b = 0; b < 8; b++) v |= (uint64_t)(0x50 + i*8 + b) << (b*8);
                    axil_slv.mem[0x400 + i*8] = v;
                }
                axi_mst.read_incr(0x400, 32);
                phase = PHASE_RDBURST;
            }
            if (phase == PHASE_RDBURST && axi_mst.get_read_data(rd_data)) {
                bool ok = rd_data.size() == 32;
                for (int i = 0; i < 32 && ok; i++) ok &= (rd_data[i] == (uint8_t)(0x50 + i));
                check_result("burst read len=3", ok, pass, fail);
                rd_data.clear();
                phase = PHASE_IDLE;
            }

            // ==== Test 5: FIXED write, len=1 ====
            if (cycle == 1100) {
                std::cout << "\n[TEST] FIXED write, len=1" << std::endl;
                std::vector<uint8_t> d(16);
                for (int i = 0; i < 16; i++) d[i] = 0x60 + i;
                axi_mst.write_fixed(0x500, d);
                phase = PHASE_FIXWR;
                phase_start = cycle;
            }
            if (phase == PHASE_FIXWR && cycle > phase_start + 200) {
                uint64_t exp = 0;
                for (int b = 0; b < 8; b++) exp |= (uint64_t)(0x68 + b) << (b*8);
                check_result("fixed write", axil_slv.mem[0x500] == exp, pass, fail);
                phase = PHASE_IDLE;
            }

            // ==== Test 6: FIXED read, len=1 ====
            if (cycle == 1400) {
                std::cout << "\n[TEST] FIXED read, len=1" << std::endl;
                axil_slv.mem[0x600] = 0xDEADBEEFCAFEBABEULL;
                axi_mst.read_fixed(0x600, 16);
                phase = PHASE_FIXRD;
            }
            if (phase == PHASE_FIXRD && axi_mst.get_read_data(rd_data)) {
                bool ok = rd_data.size() == 16;
                for (int i = 0; i < 8 && ok; i++) ok &= (rd_data[i] == rd_data[i+8]);
                check_result("fixed read", ok, pass, fail);
                rd_data.clear();
                phase = PHASE_IDLE;
            }

            // ==== Test 7: WRAP write, len=3 ====
            if (cycle == 1700) {
                std::cout << "\n[TEST] WRAP write, len=3" << std::endl;
                std::vector<uint8_t> d(32);
                for (int i = 0; i < 32; i++) d[i] = 0x70 + i;
                axi_mst.write_wrap(0x5C0, d);
                phase = PHASE_WRAP;
                phase_start = cycle;
            }
            if (phase == PHASE_WRAP && cycle > phase_start + 300) {
                bool ok = true;
                uint64_t baddr[4] = {0x5C0, 0x5C8, 0x5D0, 0x5D8};
                for (int i = 0; i < 4; i++) {
                    uint64_t v = 0;
                    for (int b = 0; b < 8; b++) v |= (uint64_t)(0x70 + i*8 + b) << (b*8);
                    ok &= (axil_slv.mem[baddr[i]] == v);
                }
                check_result("wrap write", ok, pass, fail);
                phase = PHASE_LARGEBURST;
                phase_start = cycle;
            }

            // ==== Test 8: INCR large burst write + read, len=15 (16 beats) ====
            if (phase == PHASE_LARGEBURST && cycle > phase_start + 100) {
                std::cout << "\n[TEST] INCR large burst, len=15 (16 beats)" << std::endl;
                std::vector<uint8_t> d(128);
                for (int i = 0; i < 128; i++) d[i] = i & 0xFF;
                axi_mst.write_incr(0x700, d);
                phase = PHASE_LARGEREAD;
                phase_start = cycle;
            }
            if (phase == PHASE_LARGEREAD && cycle > phase_start + 500) {
                // verify write
                bool ok = true;
                for (int i = 0; i < 16; i++) {
                    uint64_t v = 0;
                    for (int b = 0; b < 8; b++) v |= (uint64_t)((i*8+b) & 0xFF) << (b*8);
                    ok &= (axil_slv.mem[0x700 + i*8] == v);
                }
                check_result("large burst write", ok, pass, fail);

                // read back
                axi_mst.read_incr(0x700, 128);
                phase = PHASE_LARGERDWAIT;
            }
            if (phase == PHASE_LARGERDWAIT && axi_mst.get_read_data(rd_data)) {
                bool ok = rd_data.size() == 128;
                for (int i = 0; i < 128 && ok; i++) ok &= (rd_data[i] == (uint8_t)(i & 0xFF));
                check_result("large burst read", ok, pass, fail);
                rd_data.clear();
                phase = PHASE_MAXBURST;
                phase_start = cycle;
            }

            // ==== Test 9: INCR max burst write + read, len=255 (256 beats, 2KB) ====
            if (phase == PHASE_MAXBURST && cycle > phase_start + 100) {
                std::cout << "\n[TEST] INCR max burst, len=255 (256 beats, 2KB)" << std::endl;
                std::vector<uint8_t> d(2048);
                for (int i = 0; i < 2048; i++) d[i] = i & 0xFF;
                axi_mst.write_incr(0x0800, d);
                phase = PHASE_MAXRD;
                phase_start = cycle;
            }
            if (phase == PHASE_MAXRD && cycle > phase_start + 5000) {
                // verify write - spot check first, middle, last beats
                bool ok = true;
                for (int i = 0; i < 256; i += 16) {
                    uint64_t v = 0;
                    for (int b = 0; b < 8; b++) v |= (uint64_t)((i*8+b) & 0xFF) << (b*8);
                    ok &= (axil_slv.mem[0x0800 + i*8] == v);
                }
                check_result("max burst write spot check", ok, pass, fail);

                // read back
                axi_mst.read_incr(0x0800, 2048);
                phase = PHASE_DONE;
            }
            if (phase == PHASE_DONE && axi_mst.get_read_data(rd_data)) {
                bool ok = rd_data.size() == 2048;
                for (int i = 0; i < 2048 && ok; i += 64) {
                    int pos = i;
                    ok &= (rd_data[pos] == (uint8_t)(pos & 0xFF));
                }
                check_result("max burst read spot check", ok, pass, fail);
                rd_data.clear();
                phase = PHASE_DONE2;
                phase_start = cycle;
            }
            if (phase == PHASE_DONE2 && cycle > phase_start + 50) {
                break;
            }

            axi_mst.update_output();
            axil_slv.update_output();
        }

        top->eval();
        tfp->dump(sim_time);
    }

    tfp->close();
    delete tfp;
    delete top;

    std::cout << "\n=== Simulation Complete ===" << std::endl;
    std::cout << "  Pass: " << pass << "  Fail: " << fail << std::endl;
    std::cout << "  Result: " << (fail ? "FAILED" : "PASSED") << std::endl;
    return fail ? 1 : 0;
}
