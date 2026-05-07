/******************************************************************************
 * Copyright (C) 2026 dozecat. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axil2axi_tb.cpp
 * @brief       AXI4-Lite-to-AXI4 Bridge Testbench (C++)
 * @see         https://github.com/dozecat/axi_lib
 *
 * Modification History:
 * Ver   Who  Date        Changes
 * ----  ---- ----------  -----------------------------------------------------
 * 1.0        2026/05/04  Initial release
 ******************************************************************************/

#include "Vaxil2axi_tb.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <svdpi.h>
#include <iostream>
#include "axil_ptr.hpp"
#include "axil.hpp"
#include "axi_ptr.hpp"
#include "axi.hpp"

#define DATA_WIDTH 64
#define ADDR_WIDTH 16
#define ID_WIDTH   1

void bridge_connect(axil_ptr<DATA_WIDTH, ADDR_WIDTH>& axil_prt,
                    axi_ptr<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH>& axi_prt,
                    Vaxil2axi_tb* top) {
    axil_prt.awaddr  = &(top->s_awaddr);   axil_prt.awprot  = &(top->s_awprot);
    axil_prt.awready = &(top->s_awready);  axil_prt.awvalid = &(top->s_awvalid);
    axil_prt.bready  = &(top->s_bready);   axil_prt.bresp   = &(top->s_bresp);
    axil_prt.bvalid  = &(top->s_bvalid);
    axil_prt.wdata   = &(top->s_wdata);    axil_prt.wready  = &(top->s_wready);
    axil_prt.wstrb   = &(top->s_wstrb);    axil_prt.wvalid  = &(top->s_wvalid);
    axil_prt.araddr  = &(top->s_araddr);   axil_prt.arprot  = &(top->s_arprot);
    axil_prt.arready = &(top->s_arready);  axil_prt.arvalid = &(top->s_arvalid);
    axil_prt.rdata   = &(top->s_rdata);    axil_prt.rready  = &(top->s_rready);
    axil_prt.rresp   = &(top->s_rresp);    axil_prt.rvalid  = &(top->s_rvalid);

    axi_prt.awaddr   = &(top->m_awaddr);   axi_prt.awburst  = &(top->m_awburst);
    axi_prt.awcache  = &(top->m_awcache);  axi_prt.awid     = &(top->m_awid);
    axi_prt.awlen    = &(top->m_awlen);    axi_prt.awlock   = &(top->m_awlock);
    axi_prt.awprot   = &(top->m_awprot);   axi_prt.awqos    = &(top->m_awqos);
    axi_prt.awregion = &(top->m_awregion); axi_prt.awsize   = &(top->m_awsize);
    axi_prt.awvalid  = &(top->m_awvalid);  axi_prt.awready  = &(top->m_awready);
    axi_prt.wdata    = &(top->m_wdata);    axi_prt.wid      = &(top->m_wid);
    axi_prt.wlast    = &(top->m_wlast);    axi_prt.wready   = &(top->m_wready);
    axi_prt.wstrb    = &(top->m_wstrb);    axi_prt.wvalid   = &(top->m_wvalid);
    axi_prt.bid      = &(top->m_bid);      axi_prt.bready   = &(top->m_bready);
    axi_prt.bresp    = &(top->m_bresp);    axi_prt.bvalid   = &(top->m_bvalid);
    axi_prt.araddr   = &(top->m_araddr);   axi_prt.arburst  = &(top->m_arburst);
    axi_prt.arcache  = &(top->m_arcache);  axi_prt.arid     = &(top->m_arid);
    axi_prt.arlen    = &(top->m_arlen);    axi_prt.arlock   = &(top->m_arlock);
    axi_prt.arprot   = &(top->m_arprot);   axi_prt.arqos    = &(top->m_arqos);
    axi_prt.arregion = &(top->m_arregion); axi_prt.arsize   = &(top->m_arsize);
    axi_prt.arvalid  = &(top->m_arvalid);  axi_prt.arready  = &(top->m_arready);
    axi_prt.rdata    = &(top->m_rdata);    axi_prt.rid      = &(top->m_rid);
    axi_prt.rlast    = &(top->m_rlast);    axi_prt.rready   = &(top->m_rready);
    axi_prt.rresp    = &(top->m_rresp);    axi_prt.rvalid   = &(top->m_rvalid);
}

static bool check(const char* name, bool cond, int& pass, int& fail) {
    std::cout << "  [" << (cond ? "PASS" : "FAIL") << "] " << name << std::endl;
    if (cond) pass++; else fail++;
    return cond;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vaxil2axi_tb* top = new Vaxil2axi_tb;
    VerilatedVcdC* tfp = new VerilatedVcdC;

    axil_ptr<DATA_WIDTH, ADDR_WIDTH> axil_prt;
    axi_ptr<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH> axi_prt;

    bridge_connect(axil_prt, axi_prt, top);
    if (!axil_prt.check()) { std::cerr << "axil_prt connection failed!" << std::endl; return -1; }
    if (!axi_prt.check()) { std::cerr << "axi_prt connection failed!" << std::endl; return -1; }

    axil_master<DATA_WIDTH, ADDR_WIDTH> axil_mst(axil_prt);
    axi_slave<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH> axi_slv(axi_prt);

    top->trace(tfp, 100);
    tfp->open("waveform.vcd");

    top->clk   = 0;
    top->rst = 1;
    top->eval();
    for (int i = 0; i < 10; i++) { top->clk = !top->clk; top->eval(); }
    top->rst = 0;
    top->eval();

    int sim_time = 0, cycle = 0, pass = 0, fail = 0;
    enum { PHASE_IDLE, PHASE_WR, PHASE_RD, PHASE_DONE } phase = PHASE_IDLE;
    int phase_start = 0;
    uint64_t rd_val = 0;
    bool test_write_ok = false;

    while (!Verilated::gotFinish() && sim_time < 5000) {
        sim_time++;
        top->clk = !top->clk;

        if (top->clk) { axil_mst.update_input(); axi_slv.update_input(); }
        top->eval();

        if (top->clk) {
            cycle++;

            // Test 1: write
            if (cycle == 10) {
                std::cout << "\n[TEST] axil2axi write" << std::endl;
                axil_mst.write(0x100, 0x8877665544332211ULL);
                phase = PHASE_WR;
                phase_start = cycle;
            }

            // Wait, then read back
            if (phase == PHASE_WR && cycle > phase_start + 200) {
                std::cout << "\n[TEST] axil2axi read" << std::endl;
                axil_mst.read(0x100);
                phase = PHASE_RD;
            }

            // Check read result
            if (phase == PHASE_RD && axil_mst.get_read_data(rd_val)) {
                bool ok = (rd_val == 0x8877665544332211ULL);
                check("write+read back", ok, pass, fail);
                phase = PHASE_DONE;
                phase_start = cycle;
            }

            if (phase == PHASE_DONE && cycle > phase_start + 50) break;

            axil_mst.update_output();
            axi_slv.update_output();
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
