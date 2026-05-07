/******************************************************************************
 * Copyright (C) 2025 dozecat. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axil_interconnect_tb.cpp
 * @brief       AXI4 Interconnect Testbench (C++)
 * @see         https://github.com/dozecat/axi_lib
 *
 * @details     Verilator C++ TB for AXI4 Interconnect.
 *              VIP: `axi_ptr.hpp`, `axi.hpp`
 *              (include dirs from `sim/bfm/axi`).
 *
 * Modification History:
 * Ver   Who  Date        Changes
 * ----  ---- ----------  -----------------------------------------------------
 * 1.0        2026/05/01  Initial release
 ******************************************************************************/

#include "Vaxi_interconnect_tb.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <cstdint>
#include <deque>
#include <iostream>
#include <vector>
#include "axi_ptr.hpp"
#include "axi.hpp"

#define DATA_WIDTH 64
#define ADDR_WIDTH 32
#define SLV_ID_WIDTH 8

constexpr int clog2(int n) { return (n <= 1) ? 0 : 1 + clog2((n + 1) / 2); }
static constexpr int MST_NUM = 4;
static constexpr int MST_ID_WIDTH = SLV_ID_WIDTH + clog2(MST_NUM);
static constexpr int SLV_NUM = 2;

template <typename T>
static void connect_slv(axi_ptr<DATA_WIDTH, ADDR_WIDTH, SLV_ID_WIDTH>& p, T* top, int idx) {
    p.awaddr   = &(top->slv_awaddr[idx]);
    p.awid     = &(top->slv_awid[idx]);
    p.awlen    = &(top->slv_awlen[idx]);
    p.awsize   = &(top->slv_awsize[idx]);
    p.awburst  = &(top->slv_awburst[idx]);
    p.awcache  = &(top->slv_awcache[idx]);
    p.awlock   = &(top->slv_awlock[idx]);
    p.awprot   = &(top->slv_awprot[idx]);
    p.awqos    = &(top->slv_awqos[idx]);
    p.awregion = &(top->slv_awregion[idx]);
    p.awready  = &(top->slv_awready[idx]);
    p.awvalid  = &(top->slv_awvalid[idx]);
    p.wdata    = &(top->slv_wdata[idx]);
    p.wstrb    = &(top->slv_wstrb[idx]);
    p.wid      = &(top->slv_wid[idx]);
    p.wlast    = &(top->slv_wlast[idx]);
    p.wready   = &(top->slv_wready[idx]);
    p.wvalid   = &(top->slv_wvalid[idx]);
    p.bready   = &(top->slv_bready[idx]);
    p.bresp    = &(top->slv_bresp[idx]);
    p.bid      = &(top->slv_bid[idx]);
    p.bvalid   = &(top->slv_bvalid[idx]);
    p.araddr   = &(top->slv_araddr[idx]);
    p.arid     = &(top->slv_arid[idx]);
    p.arlen    = &(top->slv_arlen[idx]);
    p.arsize   = &(top->slv_arsize[idx]);
    p.arburst  = &(top->slv_arburst[idx]);
    p.arcache  = &(top->slv_arcache[idx]);
    p.arlock   = &(top->slv_arlock[idx]);
    p.arprot   = &(top->slv_arprot[idx]);
    p.arqos    = &(top->slv_arqos[idx]);
    p.arregion = &(top->slv_arregion[idx]);
    p.arready  = &(top->slv_arready[idx]);
    p.arvalid  = &(top->slv_arvalid[idx]);
    p.rdata    = &(top->slv_rdata[idx]);
    p.rresp    = &(top->slv_rresp[idx]);
    p.rid      = &(top->slv_rid[idx]);
    p.rlast    = &(top->slv_rlast[idx]);
    p.rvalid   = &(top->slv_rvalid[idx]);
    p.rready   = &(top->slv_rready[idx]);
}

template <typename T>
static void connect_mst(axi_ptr<DATA_WIDTH, ADDR_WIDTH, MST_ID_WIDTH>& p, T* top, int idx) {
    p.awaddr   = &(top->mst_awaddr[idx]);
    p.awid     = &(top->mst_awid[idx]);
    p.awlen    = &(top->mst_awlen[idx]);
    p.awsize   = &(top->mst_awsize[idx]);
    p.awburst  = &(top->mst_awburst[idx]);
    p.awcache  = &(top->mst_awcache[idx]);
    p.awlock   = &(top->mst_awlock[idx]);
    p.awprot   = &(top->mst_awprot[idx]);
    p.awqos    = &(top->mst_awqos[idx]);
    p.awregion = &(top->mst_awregion[idx]);
    p.awready  = &(top->mst_awready[idx]);
    p.awvalid  = &(top->mst_awvalid[idx]);
    p.wdata    = &(top->mst_wdata[idx]);
    p.wstrb    = &(top->mst_wstrb[idx]);
    p.wid      = &(top->mst_wid[idx]);
    p.wlast    = &(top->mst_wlast[idx]);
    p.wready   = &(top->mst_wready[idx]);
    p.wvalid   = &(top->mst_wvalid[idx]);
    p.bready   = &(top->mst_bready[idx]);
    p.bresp    = &(top->mst_bresp[idx]);
    p.bid      = &(top->mst_bid[idx]);
    p.bvalid   = &(top->mst_bvalid[idx]);
    p.araddr   = &(top->mst_araddr[idx]);
    p.arid     = &(top->mst_arid[idx]);
    p.arlen    = &(top->mst_arlen[idx]);
    p.arsize   = &(top->mst_arsize[idx]);
    p.arburst  = &(top->mst_arburst[idx]);
    p.arcache  = &(top->mst_arcache[idx]);
    p.arlock   = &(top->mst_arlock[idx]);
    p.arprot   = &(top->mst_arprot[idx]);
    p.arqos    = &(top->mst_arqos[idx]);
    p.arregion = &(top->mst_arregion[idx]);
    p.arready  = &(top->mst_arready[idx]);
    p.arvalid  = &(top->mst_arvalid[idx]);
    p.rdata    = &(top->mst_rdata[idx]);
    p.rresp    = &(top->mst_rresp[idx]);
    p.rid      = &(top->mst_rid[idx]);
    p.rlast    = &(top->mst_rlast[idx]);
    p.rvalid   = &(top->mst_rvalid[idx]);
    p.rready   = &(top->mst_rready[idx]);
}

static std::vector<uint8_t> u64_le(uint64_t v) {
    std::vector<uint8_t> d(8);
    for (int i = 0; i < 8; i++)
        d[i] = (uint8_t)((v >> (8 * i)) & 0xff);
    return d;
}

static std::vector<uint8_t> bytes_inc(size_t n, uint8_t base) {
    std::vector<uint8_t> v(n);
    for (size_t i = 0; i < n; i++)
        v[i] = (uint8_t)(base + (uint8_t)i);
    return v;
}

static bool vec_eq(const std::vector<uint8_t>& a, const std::vector<uint8_t>& b) {
    if (a.size() != b.size())
        return false;
    for (size_t i = 0; i < a.size(); i++)
        if (a[i] != b[i])
            return false;
    return true;
}

static int slv_ix(uint64_t p) {
    if (p < 0x1000ull)
        return 0;
    if (p < 0x2000ull)
        return 1;
    if (p < 0x3000ull)
        return 2;
    return 3;
}

template <size_t IDW>
static void mem_eq(axi_slave<DATA_WIDTH, ADDR_WIDTH, IDW> (&slv)[MST_NUM], uint64_t addr,
    const std::vector<uint8_t>& exp, int& pass, int& fail) {
    bool ok = true;
    for (size_t i = 0; i < exp.size(); i++) {
        uint64_t p = addr + i;
        int si = slv_ix(p);
        auto it = slv[si].mem.find(p);
        uint8_t g = (it == slv[si].mem.end()) ? 0 : it->second;
        if (g != exp[i])
            ok = false;
    }
    if (ok)
        pass++;
    else
        fail++;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);
    Vaxi_interconnect_tb* top = new Vaxi_interconnect_tb;
    VerilatedVcdC* tfp = new VerilatedVcdC;

    axi_ptr<DATA_WIDTH, ADDR_WIDTH, SLV_ID_WIDTH> slv_p[SLV_NUM];
    axi_ptr<DATA_WIDTH, ADDR_WIDTH, MST_ID_WIDTH> mst_p[MST_NUM];
    for (int i = 0; i < SLV_NUM; i++) {
        connect_slv(slv_p[i], top, i);
    }
    for (int i = 0; i < MST_NUM; i++) {
        connect_mst(mst_p[i], top, i);
    }
    for (int i = 0; i < SLV_NUM; i++) {
        if (!slv_p[i].check())
            return 1;
    }
    for (int i = 0; i < MST_NUM; i++) {
        if (!mst_p[i].check())
            return 1;
    }

    axi_master<DATA_WIDTH, ADDR_WIDTH, SLV_ID_WIDTH> mst_bfm[] = {
        axi_master<DATA_WIDTH, ADDR_WIDTH, SLV_ID_WIDTH>(slv_p[0]),
        axi_master<DATA_WIDTH, ADDR_WIDTH, SLV_ID_WIDTH>(slv_p[1]),
    };
    axi_slave<DATA_WIDTH, ADDR_WIDTH, MST_ID_WIDTH> slv_bfm[] = {
        axi_slave<DATA_WIDTH, ADDR_WIDTH, MST_ID_WIDTH>(mst_p[0]),
        axi_slave<DATA_WIDTH, ADDR_WIDTH, MST_ID_WIDTH>(mst_p[1]),
        axi_slave<DATA_WIDTH, ADDR_WIDTH, MST_ID_WIDTH>(mst_p[2]),
        axi_slave<DATA_WIDTH, ADDR_WIDTH, MST_ID_WIDTH>(mst_p[3]),
    };

    top->trace(tfp, 99);
    tfp->open("waveform.vcd");
    top->clk = 0;
    top->rst = 1;
    for (int i = 0; i < SLV_NUM; i++) {
        mst_bfm[i].update_output();
    }
    for (int i = 0; i < MST_NUM; i++) {
        slv_bfm[i].update_output();
    }
    top->eval();

    uint64_t tick = 0, cycle = 0;
    int pass = 0, fail = 0;
    std::deque<std::vector<uint8_t>> rd_exp[SLV_NUM];
    const uint64_t MAX_TICK = 90000;

    auto push_exp = [&](int m, std::vector<uint8_t> e) { rd_exp[m].push_back(std::move(e)); };

    auto drain_reads = [&]() {
        for (int m = 0; m < SLV_NUM; m++) {
            std::vector<uint8_t> rd;
            while (mst_bfm[m].get_read_data(rd)) {
                if (rd_exp[m].empty()) {
                    fail++;
                    continue;
                }
                if (vec_eq(rd, rd_exp[m].front()))
                    pass++;
                else
                    fail++;
                rd_exp[m].pop_front();
            }
        }
    };

    while (!Verilated::gotFinish() && tick < MAX_TICK) {
        top->clk = !top->clk;
        tick++;
        if (tick == 5)
            top->rst = 0;

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
            if (cycle == 10) {
                for (int i = 0; i < SLV_NUM; i++) {
                    mst_bfm[i].write_incr(0x0010 + i * 0x1000, u64_le(0xA5A50000u + (unsigned)i));
                }
            }
            if (cycle == 280) {
                for (int i = 0; i < SLV_NUM; i++) {
                    mst_bfm[i].read_incr(0x0010 + i * 0x1000, DATA_WIDTH / 8);
                    push_exp(i, u64_le(0xA5A50000u + (unsigned)i));
                }
            }

            if (cycle == 600) {
                mst_bfm[0].write_incr(0x40, bytes_inc(32, 0x10));
            }
            if (cycle == 5000) {
                mem_eq(slv_bfm, 0x40, bytes_inc(32, 0x10), pass, fail);
            }
            if (cycle == 5100) {
                mst_bfm[0].read_incr(0x40, 32);
                push_exp(0, bytes_inc(32, 0x10));
            }

            if (cycle == 5400) {
                std::vector<uint8_t> wf(24);
                for (int b = 0; b < 3; b++) {
                    uint8_t x = (uint8_t)(0xA0 + b * 0x10);
                    for (int j = 0; j < 8; j++)
                        wf[b * 8 + j] = x;
                }
                mst_bfm[1].write_fixed(0x1180, wf);
            }
            if (cycle == 9800) {
                std::vector<uint8_t> eb(8, (uint8_t)0xC0);
                mem_eq(slv_bfm, 0x1180, eb, pass, fail);
            }
            if (cycle == 9900) {
                std::vector<uint8_t> ex24(24);
                for (int t = 0; t < 3; t++)
                    for (int j = 0; j < 8; j++)
                        ex24[t * 8 + j] = (uint8_t)0xC0;
                mst_bfm[1].read_fixed(0x1180, 24);
                push_exp(1, std::move(ex24));
            }

            if (cycle == 19800) {
                mst_bfm[0].write_incr(0x0050, bytes_inc(64, 0x5A));
            }
            if (cycle == 24200) {
                mem_eq(slv_bfm, 0x0050, bytes_inc(64, 0x5A), pass, fail);
            }
            if (cycle == 24300) {
                mst_bfm[0].read_incr(0x0050, 64);
                push_exp(0, bytes_inc(64, 0x5A));
            }

            if (cycle == 24600) {
                for (int i = 0; i < SLV_NUM; i++) {
                    mst_bfm[i].write_fixed(0x0100 + i * 0x1000, bytes_inc(8, (uint8_t)(0x51 + i)));
                }
            }
            if (cycle == 29000) {
                for (int i = 0; i < SLV_NUM; i++) {
                    mem_eq(slv_bfm, 0x0100 + i * 0x1000, bytes_inc(8, (uint8_t)(0x51 + i)), pass, fail);
                }
            }
            if (cycle == 29100) {
                for (int i = 0; i < SLV_NUM; i++) {
                    mst_bfm[i].read_fixed(0x0100 + i * 0x1000, 8);
                    push_exp(i, bytes_inc(8, (uint8_t)(0x51 + i)));
                }
            }

            drain_reads();

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

    drain_reads();
    for (int i = 0; i < SLV_NUM; i++) {
        if (!rd_exp[i].empty())
            fail += (int)rd_exp[i].size();
    }

    tfp->close();
    delete tfp;
    delete top;
    int rc = (fail > 0) ? 1 : 0;
    std::cout << "pass " << pass << " fail " << fail << (rc ? " FAIL\n" : " OK\n");
    return rc;
}
