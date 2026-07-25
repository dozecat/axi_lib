/******************************************************************************
 * Copyright (C) 2026 dozecat. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axis_async_fifo_tb.cpp
 * @brief       axis_async_fifo testbench using corosim
 * @see         https://github.com/dozecat/axi_lib
 ******************************************************************************/

#include "Vaxis_async_fifo_tb.h"
#include <verilated_vcd_c.h>
#include "corosim.hpp"
#include "axis.hpp"
#include <cstdio>

using namespace corosim;

static const int SIM_TIME   = 1000000;
static const int DATA_BYTES = 8;
static const int WR_HALF    = 250;
static const int RD_HALF    = 154;

// BIND_AXIS(p, prefix, top) fills axis_*_ptr<...> fields from a flat prefix
#define BIND_AXIS(p, prefix, top) \
    p.tdata=&top->prefix##_tdata; p.tkeep=&top->prefix##_tkeep; \
    p.tstrb=&top->prefix##_tstrb; p.tid=&top->prefix##_tid; \
    p.tdest=&top->prefix##_tdest; p.tuser=&top->prefix##_tuser; \
    p.tlast=&top->prefix##_tlast; p.tvalid=&top->prefix##_tvalid; \
    p.tready=&top->prefix##_tready

Task writer_proc(Vaxis_async_fifo_tb* top, Signal<bool>* s_clk,
                 axis_master<64,8,1,1>* mst, int nwords) {
    co_await clock_cycles(*s_clk, 5);
    top->s_rst = 0;
    co_await clock_cycles(*s_clk, 3);

    int total = nwords * DATA_BYTES;
    std::vector<uint8_t> bytes(total);
    for (int i = 0; i < total; i++)
        bytes[i] = i & 0xFF;

    printf("  writer: send %d words\n", nwords);
    mst->send(bytes, 0, 0, 0, false);
    co_await clock_cycles(*s_clk, 50);
}

static int errors = 0;

Task reader_proc(Vaxis_async_fifo_tb* top, Signal<bool>* m_clk,
                 axis_slave<64,8,1,1>* slv, int exp_words, int* rx_count) {
    co_await clock_cycles(*m_clk, 5);
    top->m_rst = 0;

    int rx = 0;
    while (rx < exp_words) {
        co_await posedge(*m_clk);
        std::vector<uint8_t> buf;
        if (slv->recv(buf) > 0) {
            for (int w = 0; w < (int)buf.size() / DATA_BYTES && rx < exp_words; w++) {
                bool ok = true;
                for (int b = 0; b < DATA_BYTES; b++) {
                    uint8_t got = buf[w * DATA_BYTES + b];
                    uint8_t exp = (rx * DATA_BYTES + b) & 0xFF;
                    if (got != exp) {
                        if (ok) printf("  FAIL: rx[%d] byte[%d]=0x%02X exp=0x%02X\n", rx, b, got, exp);
                        ok = false;
                    }
                }
                if (ok) printf("  PASS: rx[%d]\n", rx);
                rx++;
            }
        }
    }
    if (rx_count) *rx_count = rx;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    auto top  = std::make_unique<Vaxis_async_fifo_tb>();
    auto tfp  = std::make_unique<VerilatedVcdC>();
    top->trace(tfp.get(), 99);
    const char* vcd = (argc > 1) ? argv[1] : "waveform.vcd";
    tfp->open(vcd);

    top->s_rst = 1; top->m_rst = 1;
    top->eval();

    int depth = top->tb_depth;
    int nwords = 14;

    Signal<bool> s_clk(&top->s_clk), m_clk(&top->m_clk);

    axis_master_ptr<64,8,1,1> mp;
    BIND_AXIS(mp, s_axis, top);
    axis_master<64,8,1,1> mst(mp);
    mst.log.quiet = true;

    axis_slave_ptr<64,8,1,1> sp;
    BIND_AXIS(sp, m_axis, top);
    axis_slave<64,8,1,1> slv(sp);
    slv.log.quiet = true;

    Engine sim;

    sim.always(delay(WR_HALF), [&] { s_clk.next(!s_clk.read()); });
    sim.always(delay(RD_HALF), [&] { m_clk.next(!m_clk.read()); });

    sim.sample_cb(posedge(s_clk), [&] { mst.update_input(); });
    sim.sample_cb(posedge(m_clk), [&] { slv.update_input(); });
    sim.drive_cb(posedge(s_clk), [&] { mst.update_output(); });
    sim.drive_cb(posedge(m_clk), [&] { slv.update_output(); });

    sim.always(posedge(m_clk), [&] {
        slv.set_tready((std::rand() % 100) < 70);
    });

    int rx_count = 0;
    sim.task([&]() -> Task {
        return writer_proc(top.get(), &s_clk, &mst, nwords);
    });
    sim.task([&]() -> Task {
        return reader_proc(top.get(), &m_clk, &slv, nwords, &rx_count);
    });

    printf("=== axis_async_fifo TB (corosim) ===\n");
    printf("DEPTH=%d words=%d\n", depth, nwords);

    sim.init(top.get(), [&](sim_time t) { tfp->dump(t); });
    sim.run(SIM_TIME);
    tfp->close();

    printf("  received %d of %d words\n", rx_count, nwords);
    if (rx_count < nwords) errors++;

    int ok = (errors == 0);
    printf("\n%s\n", ok ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
    return ok ? 0 : 1;
}
