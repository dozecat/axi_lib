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

static int errors = 0;

struct Shared {
    Signal<uint8_t>* s_clk, * m_clk;
    Vaxis_async_fifo_tb* top;
    axis_master<64,8,1,1>* mst;
    axis_slave<64,8,1,1>*  slv;
    int depth;
    std::vector<std::pair<int,int>> frames;
    int exp_words, exp_good, exp_bad;
    int good_count, bad_count;
    int total_sent_bytes;
    int rx_words, rx_frame_idx, exp_byte_idx;
};

Task writer_task(Shared* S) {
    co_await clock_cycles(*S->s_clk, 5);
    S->top->s_rst = 0;
    co_await clock_cycles(*S->s_clk, 3);

    for (size_t f = 0; f < S->frames.size(); f++) {
        int nw = S->frames[f].first;
        int total_bytes = nw * DATA_BYTES;
        std::vector<uint8_t> bytes(total_bytes);
        for (int i = 0; i < total_bytes; i++)
            bytes[i] = (S->total_sent_bytes + i) & 0xFF;
        printf("  frame %zu: %d words\n", f, nw);
        S->mst->send(bytes, 0, 0, S->frames[f].second, false);
        S->total_sent_bytes += total_bytes;
        if (f + 1 < S->frames.size())
            co_await clock_cycles(*S->s_clk, 25);
    }
    co_await clock_cycles(*S->s_clk, 50);
}

Task reader_task(Shared* S) {
    co_await clock_cycles(*S->m_clk, 5);
    S->top->m_rst = 0;

    while (S->rx_words < S->exp_words) {
        co_await posedge(*S->m_clk);
        std::vector<uint8_t> rx_buf;
        if (S->slv->recv(rx_buf) > 0) {
            while (S->rx_frame_idx < (int)S->frames.size()
                   && S->frames[S->rx_frame_idx].first > S->depth) {
                S->exp_byte_idx += S->frames[S->rx_frame_idx].first * DATA_BYTES;
                S->rx_frame_idx++;
            }
            int offset = 0;
            while (offset < (int)rx_buf.size() && S->rx_words < S->exp_words) {
                bool ok = true;
                for (int b = 0; b < DATA_BYTES; b++) {
                    uint8_t got = rx_buf[offset + b];
                    uint8_t exp = (S->exp_byte_idx + b) & 0xFF;
                    if (got != exp) {
                        if (ok) printf("  FAIL: rx[%d] byte[%d]=0x%02X exp=0x%02X\n",
                                       S->rx_words, b, got, exp);
                        ok = false; errors++;
                    }
                }
                if (ok) printf("  PASS: rx[%d]\n", S->rx_words);
                S->rx_words++;
                S->exp_byte_idx += DATA_BYTES;
                offset += DATA_BYTES;
            }
            S->rx_frame_idx++;
        }
    }
}

static axis_master_ptr<64,8,1,1> make_mst_port(Vaxis_async_fifo_tb* top) {
    axis_master_ptr<64,8,1,1> p;
    p.tdata=&top->s_axis_tdata; p.tkeep=&top->s_axis_tkeep;
    p.tstrb=&top->s_axis_tstrb; p.tid=&top->s_axis_tid;
    p.tdest=&top->s_axis_tdest; p.tuser=&top->s_axis_tuser;
    p.tlast=&top->s_axis_tlast; p.tvalid=&top->s_axis_tvalid;
    p.tready=&top->s_axis_tready;
    return p;
}

static axis_slave_ptr<64,8,1,1> make_slv_port(Vaxis_async_fifo_tb* top) {
    axis_slave_ptr<64,8,1,1> p;
    p.tdata=&top->m_axis_tdata; p.tkeep=&top->m_axis_tkeep;
    p.tstrb=&top->m_axis_tstrb; p.tid=&top->m_axis_tid;
    p.tdest=&top->m_axis_tdest; p.tuser=&top->m_axis_tuser;
    p.tlast=&top->m_axis_tlast; p.tvalid=&top->m_axis_tvalid;
    p.tready=&top->m_axis_tready;
    return p;
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
    bool frame_fifo = top->tb_frame_fifo;
    bool always_recv = top->tb_always_recv;

    Shared S;
    S.top = top.get(); S.depth = depth;
    S.exp_words = 0; S.exp_good = 0; S.exp_bad = 0;
    S.good_count = 0; S.bad_count = 0;
    S.total_sent_bytes = 0;
    S.rx_words = 0; S.rx_frame_idx = 0; S.exp_byte_idx = 0;

    if (frame_fifo) {
        int seq[] = {1, depth, depth+1, 28, 5, 8, 12, 5, depth+1, 8};
        for (int nw : seq) {
            bool bad = (nw > depth);
            S.frames.push_back({nw, bad ? 1 : 0});
            if (bad) S.exp_bad++; else { S.exp_good++; S.exp_words += nw; }
        }
    } else {
        S.frames.push_back({14, 0});
        S.exp_words = 14;
    }

    Signal<uint8_t> s_clk(&top->s_clk), m_clk(&top->m_clk);
    S.s_clk = &s_clk; S.m_clk = &m_clk;

    axis_master<64,8,1,1> mst(make_mst_port(top.get()));
    axis_slave<64,8,1,1>  slv(make_slv_port(top.get()));
    S.mst = &mst; S.slv = &slv;
    mst.log.quiet = true; slv.log.quiet = true;

    Engine sim;

    sim.always(delay(WR_HALF), [&] { s_clk.next(!s_clk.read()); });
    sim.always(delay(RD_HALF), [&] { m_clk.next(!m_clk.read()); });

    // update_input before eval, update_output after eval (SimCoop/vaxivip convention)
    // update_input before eval (pre_eval), update_output once per posedge
    sim.pre_eval([&] {
        if (s_clk.read()) mst.update_input();
        if (m_clk.read()) slv.update_input();
    });
    sim.always(posedge(s_clk), [&] { mst.update_output(); });
    sim.always(posedge(m_clk), [&] { slv.update_output(); });

    sim.always(posedge(s_clk), [&] {
        if (top->s_good_frame) S.good_count++;
        if (top->s_bad_frame)  S.bad_count++;
    });

    sim.task([&S]() -> Task { return writer_task(&S); });
    sim.task([&S]() -> Task { return reader_task(&S); });

    printf("=== axis_async_fifo TB (corosim) ===\n");
    printf("wr=200MHz rd=325MHz  sim_time=%d steps\n", SIM_TIME);
    printf("FRAME_FIFO=%d DEPTH=%d ALWAYS_RECEIVE=%d\n", frame_fifo, depth, always_recv);
    printf("frames=%zu  exp_words=%d  exp_good=%d  exp_bad=%d\n",
           S.frames.size(), S.exp_words, S.exp_good, S.exp_bad);

    sim.init(top.get(), [&](sim_time t) { tfp->dump(t); });
    sim.run(SIM_TIME);
    tfp->close();

    printf("=== Frame status ===\n");
    printf("  s_good_frame: %d (exp %d)  %s\n",
           S.good_count, S.exp_good,
           S.good_count == S.exp_good ? "PASS" : "FAIL");
    printf("  s_bad_frame:  %d (exp %d)  %s\n",
           S.bad_count, S.exp_bad,
           S.bad_count == S.exp_bad ? "PASS" : "FAIL");
    if (S.good_count != S.exp_good) errors++;
    if (S.bad_count != S.exp_bad) errors++;

    if (S.rx_words < S.exp_words) {
        printf("FAIL: only received %d of %d words\n", S.rx_words, S.exp_words);
        errors++;
    }
    printf("\n%s\n", errors == 0 ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
    return errors ? 1 : 0;
}
