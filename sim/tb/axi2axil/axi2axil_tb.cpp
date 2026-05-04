/******************************************************************************
 * Copyright (C) 2026 dozecat. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axi2axil_tb.cpp
 * @brief       AXI4-to-AXI4-Lite Bridge Testbench
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
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include "axi_ptr.hpp"
#include "axi.hpp"
#include "axil_ptr.hpp"
#include "axil.hpp"

#define DATA_WIDTH 64
#define ADDR_WIDTH 16
#define ID_WIDTH   8
#define STRB_WIDTH (DATA_WIDTH / 8)

static bool sim_err = false;

static void connect_axi_mst(axi_ptr<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH>& p, Vaxi2axil_tb* top) {
    p.awid     = &(top->m_awid);     p.awaddr   = &(top->m_awaddr);
    p.awlen    = &(top->m_awlen);    p.awsize   = &(top->m_awsize);
    p.awburst  = &(top->m_awburst);  p.awcache  = &(top->m_awcache);
    p.awlock   = &(top->m_awlock);   p.awprot   = &(top->m_awprot);
    p.awqos    = &(top->m_awqos);    p.awregion = &(top->m_awregion);
    p.awvalid  = &(top->m_awvalid);  p.awready  = &(top->m_awready);
    p.wdata    = &(top->m_wdata);    p.wstrb    = &(top->m_wstrb);
    p.wid      = &(top->m_wid);      p.wlast    = &(top->m_wlast);
    p.wvalid   = &(top->m_wvalid);   p.wready   = &(top->m_wready);
    p.bresp    = &(top->m_bresp);    p.bid      = &(top->m_bid);
    p.bvalid   = &(top->m_bvalid);   p.bready   = &(top->m_bready);
    p.arid     = &(top->m_arid);     p.araddr   = &(top->m_araddr);
    p.arlen    = &(top->m_arlen);    p.arsize   = &(top->m_arsize);
    p.arburst  = &(top->m_arburst);  p.arcache  = &(top->m_arcache);
    p.arlock   = &(top->m_arlock);   p.arprot   = &(top->m_arprot);
    p.arqos    = &(top->m_arqos);    p.arregion = &(top->m_arregion);
    p.arvalid  = &(top->m_arvalid);  p.arready  = &(top->m_arready);
    p.rdata    = &(top->m_rdata);    p.rresp    = &(top->m_rresp);
    p.rid      = &(top->m_rid);      p.rlast    = &(top->m_rlast);
    p.rvalid   = &(top->m_rvalid);   p.rready   = &(top->m_rready);
}

static void connect_axil_slv(axil_ptr<DATA_WIDTH, ADDR_WIDTH>& p, Vaxi2axil_tb* top) {
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

static void tick(Vaxi2axil_tb* top) {
    top->clk = 1;
    top->eval();
}

static void tick_half(Vaxi2axil_tb* top) {
    top->clk = !top->clk;
    top->eval();
}

static void run_cycles(Vaxi2axil_tb* top,
                        axi_master<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH>& mst,
                        axil_slave<DATA_WIDTH, ADDR_WIDTH>& slv,
                        int cycles) {
    for (int i = 0; i < cycles; i++) {
        if (!top->clk) { mst.update_input(); slv.update_input(); }
        tick_half(top);
        if (top->clk) { mst.update_output(); slv.update_output(); }
        tick_half(top);
    }
}

static bool run_read(Vaxi2axil_tb* top,
                      axi_master<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH>& mst,
                      axil_slave<DATA_WIDTH, ADDR_WIDTH>& slv,
                      std::vector<uint8_t>& rd_data,
                      int max_cycles) {
    for (int i = 0; i < max_cycles; i++) {
        if (!top->clk) { mst.update_input(); slv.update_input(); }
        tick_half(top);
        if (top->clk) { mst.update_output(); slv.update_output(); }
        tick_half(top);
        if (mst.get_read_data(rd_data)) return true;
    }
    return false;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    Vaxi2axil_tb* top = new Vaxi2axil_tb;
    VerilatedVcdC* trace = nullptr;

    if (getenv("TRACE")) {
        Verilated::traceEverOn(true);
        trace = new VerilatedVcdC;
        top->trace(trace, 99);
        trace->open("waveform.vcd");
    }

    axi_ptr<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH> axi_sig;
    connect_axi_mst(axi_sig, top);
    axi_master<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH> mst(axi_sig);

    axil_ptr<DATA_WIDTH, ADDR_WIDTH> axil_sig;
    connect_axil_slv(axil_sig, top);
    axil_slave<DATA_WIDTH, ADDR_WIDTH> slv(axil_sig);

    // Reset
    top->rst_n = 0;
    top->clk   = 0;
    top->eval();
    for (int i = 0; i < 10; i++) {
        tick_half(top);
        tick_half(top);
    }
    top->rst_n = 1;
    tick_half(top);
    tick_half(top);

    auto check = [&](const char* name, bool pass) {
        std::cout << "  [" << (pass ? "PASS" : "FAIL") << "] " << name << std::endl;
        if (!pass) sim_err = true;
    };

    int total = 0, pass = 0;

    // ─── Test 1: INCR write, len=0 (single beat) ───
    {
        std::cout << "\n[TEST] INCR write, len=0" << std::endl;
        uint64_t addr = 0x100;
        std::vector<uint8_t> data = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
        mst.write_incr(addr, data);
        run_cycles(top, mst, slv, 200);
        bool ok = (slv.mem[addr] == 0x8877665544332211ULL);
        check("single beat write", ok);
        total++; if (ok) pass++;
    }

    // ─── Test 2: INCR read, len=0 (single beat) ───
    {
        std::cout << "\n[TEST] INCR read, len=0" << std::endl;
        uint64_t addr = 0x200;
        slv.mem[addr] = 0xAABBCCDDEEFF0011ULL;
        mst.read_incr(addr, 8);
        std::vector<uint8_t> rd_data;
        run_read(top, mst, slv, rd_data, 200);
        bool ok = (rd_data.size() == 8 && rd_data[0] == 0x11 && rd_data[7] == 0xAA);
        check("single beat read", ok);
        total++; if (ok) pass++;
    }

    // ─── Test 3: INCR burst write, len=3 (4 beats) ───
    {
        std::cout << "\n[TEST] INCR burst write, len=3" << std::endl;
        uint64_t addr = 0x300;
        std::vector<uint8_t> data(32);
        for (int i = 0; i < 32; i++) data[i] = 0xA0 + i;
        mst.write_incr(addr, data);
        run_cycles(top, mst, slv, 500);
        // Check all 4 beats
        bool ok = true;
        for (int i = 0; i < 4; i++) {
            uint64_t beat_addr = addr + i * 8;
            uint64_t expected = 0;
            for (int b = 0; b < 8; b++) expected |= (uint64_t)(data[i*8+b]) << (b*8);
            ok &= (slv.mem[beat_addr] == expected);
        }
        check("burst write len=3", ok);
        total++; if (ok) pass++;
    }

    // ─── Test 4: INCR burst read, len=3 ───
    {
        std::cout << "\n[TEST] INCR burst read, len=3" << std::endl;
        uint64_t addr = 0x400;
        for (int i = 0; i < 4; i++) {
            uint64_t v = 0;
            for (int b = 0; b < 8; b++) v |= (uint64_t)(0x50 + i*8 + b) << (b*8);
            slv.mem[addr + i*8] = v;
        }
        mst.read_incr(addr, 32);
        std::vector<uint8_t> rd_data;
        run_read(top, mst, slv, rd_data, 500);
        bool ok = (rd_data.size() == 32);
        for (int i = 0; i < 32 && ok; i++) ok &= (rd_data[i] == (uint8_t)(0x50 + i));
        check("burst read len=3", ok);
        total++; if (ok) pass++;
    }

    // ─── Test 5: FIXED write, len=1 (2 beats to same addr) ───
    {
        std::cout << "\n[TEST] FIXED write, len=1" << std::endl;
        uint64_t addr = 0x500;
        std::vector<uint8_t> data(16); // 2 beats
        for (int i = 0; i < 16; i++) data[i] = 0x60 + i;
        mst.write_fixed(addr, data);
        run_cycles(top, mst, slv, 300);
        // FIXED: both beats go to same addr, last value wins
        uint64_t expected = 0;
        for (int b = 0; b < 8; b++) expected |= (uint64_t)(0x68 + b) << (b*8);
        bool ok = (slv.mem[addr] == expected);
        check("fixed write", ok);
        total++; if (ok) pass++;
    }

    // ─── Test 6: FIXED read, len=1 ───
    {
        std::cout << "\n[TEST] FIXED read, len=1" << std::endl;
        uint64_t addr = 0x600;
        slv.mem[addr] = 0xDEADBEEFCAFEBABEULL;
        mst.read_fixed(addr, 16);
        std::vector<uint8_t> rd_data;
        run_read(top, mst, slv, rd_data, 300);
        // FIXED read of same address twice returns same value
        bool ok = (rd_data.size() == 16);
        for (int i = 0; i < 8 && ok; i++) ok &= (rd_data[i] == rd_data[i+8]);
        check("fixed read", ok);
        total++; if (ok) pass++;
    }

    // ─── Test 7: WRAP write, len=3 ───
    {
        std::cout << "\n[TEST] WRAP write, len=3 (8-byte wrap)" << std::endl;
        // WRAP with len=3, DATA_WIDTH=64 wraps at 32-byte boundary
        uint64_t addr = 0x5C0;  // wraps within 0x5C0-0x5DF
        std::vector<uint8_t> data(32);
        for (int i = 0; i < 32; i++) data[i] = 0x70 + i;
        mst.write_wrap(addr, data);
        run_cycles(top, mst, slv, 500);
        bool ok = true;
        // WRAP writes: address progression = 0x5C0, 0x5C8, 0x5D0, 0x5D8
        uint64_t beat_addrs[4] = {0x5C0, 0x5C8, 0x5D0, 0x5D8};
        for (int i = 0; i < 4; i++) {
            uint64_t expected = 0;
            for (int b = 0; b < 8; b++) expected |= (uint64_t)(data[i*8+b]) << (b*8);
            ok &= (slv.mem[beat_addrs[i]] == expected);
        }
        check("wrap write", ok);
        total++; if (ok) pass++;
    }

    if (trace) trace->close();
    delete top;

    std::cout << "\n=== Simulation Complete ===" << std::endl;
    std::cout << "  Pass: " << pass << "  Fail: " << (total - pass) << "  Total: " << total << std::endl;
    std::cout << "  Result: " << (sim_err ? "FAILED" : "PASSED") << std::endl;
    return sim_err ? 1 : 0;
}
