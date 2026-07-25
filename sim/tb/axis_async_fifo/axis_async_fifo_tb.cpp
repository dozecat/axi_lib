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

static const int SIM_TIME   = 10000;
static const int DATA_BYTES = 8;

static int errors = 0;

// ---- port binding (replace BIND_AXIS macro) ----
static axis_master_ptr<64,8,1,1> bind_mst(Vaxis_async_fifo_tb* top) {
    axis_master_ptr<64,8,1,1> p;
    p.tdata=&top->s_axis_tdata; p.tkeep=&top->s_axis_tkeep;
    p.tstrb=&top->s_axis_tstrb; p.tid=&top->s_axis_tid;
    p.tdest=&top->s_axis_tdest; p.tuser=&top->s_axis_tuser;
    p.tlast=&top->s_axis_tlast; p.tvalid=&top->s_axis_tvalid;
    p.tready=&top->s_axis_tready;
    return p;
}

static axis_slave_ptr<64,8,1,1> bind_slv(Vaxis_async_fifo_tb* top) {
    axis_slave_ptr<64,8,1,1> p;
    p.tdata=&top->m_axis_tdata; p.tkeep=&top->m_axis_tkeep;
    p.tstrb=&top->m_axis_tstrb; p.tid=&top->m_axis_tid;
    p.tdest=&top->m_axis_tdest; p.tuser=&top->m_axis_tuser;
    p.tlast=&top->m_axis_tlast; p.tvalid=&top->m_axis_tvalid;
    p.tready=&top->m_axis_tready;
    return p;
}

// ---- reset: drive via Signal::next, not direct write ----
Task reset_proc(Signal<bool>* s_rst, Signal<bool>* m_rst, Signal<bool>* s_clk) {
    s_rst->next(1);
    m_rst->next(1);
    co_await clock_cycles(*s_clk, 3);
    s_rst->next(0);
    m_rst->next(0);
}

// ---- writer: send N words after reset ----
Task writer_proc(Vaxis_async_fifo_tb* top, Signal<bool>* s_clk,
                 axis_master<64,8,1,1>* mst, int nwords) {
    co_await clock_cycles(*s_clk, 5);
    co_await clock_cycles(*s_clk, 3);

    int total = nwords * DATA_BYTES;
    std::vector<uint8_t> bytes(total);
    for (int i = 0; i < total; i++)
        bytes[i] = i & 0xFF;

    printf("  writer: send %d words\n", nwords);
    mst->send(bytes, 0, 0, 0, false);
    co_await clock_cycles(*s_clk, 50);
}

// ---- reader: receive and verify N words ----
Task reader_proc(Vaxis_async_fifo_tb* top, Signal<bool>* m_clk,
                 axis_slave<64,8,1,1>* slv, int exp_words, int* rx_count) {
    co_await clock_cycles(*m_clk, 5);

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

    // Probe DUT parameters (need eval to settle combinational outputs)
    top->eval();
    int depth = top->tb_depth;
    int nwords = 14;

    Signal<bool> s_clk(&top->s_clk), m_clk(&top->m_clk);
    Signal<bool> s_rst(&top->s_rst), m_rst(&top->m_rst);

    axis_master<64,8,1,1> mst(bind_mst(top.get()));
    axis_slave<64,8,1,1>  slv(bind_slv(top.get()));
    mst.log.quiet = true; slv.log.quiet = true;

    Engine sim;

    sim.always(delay(5), [&] { s_clk.next(!s_clk.read()); });
    sim.always(delay(3), [&] { m_clk.next(!m_clk.read()); });

    sim.sample_cb(posedge(s_clk), [&] { mst.update_input(); });
    sim.sample_cb(posedge(m_clk), [&] { slv.update_input(); });
    sim.drive_cb(posedge(s_clk), [&] { mst.update_output(); });
    sim.drive_cb(posedge(m_clk), [&] { slv.update_output(); });

    sim.always(posedge(m_clk), [&] {
        slv.set_tready((std::rand() % 100) < 70);
    });

    int rx_count = 0;
    sim.task([&]() -> Task { return reset_proc(&s_rst, &m_rst, &s_clk); });
    sim.task([&]() -> Task { return writer_proc(top.get(), &s_clk, &mst, nwords); });
    sim.task([&]() -> Task { return reader_proc(top.get(), &m_clk, &slv, nwords, &rx_count); });

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
