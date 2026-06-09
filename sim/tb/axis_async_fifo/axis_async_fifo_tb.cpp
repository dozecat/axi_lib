/******************************************************************************
 * Copyright (C) 2026 dozecat. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axis_async_fifo_tb.cpp
 * @brief       axis_async_fifo testbench — generic data transceiver
 *
 *              DUT parameters (FRAME_FIFO, DEPTH, etc.) are read from the
 *              Verilated top module at runtime.  Test sequences are generated
 *              programmatically — no compile-time -D defines needed.
 *
 * @see         https://github.com/dozecat/axi_lib
 ******************************************************************************/

#include "Vaxis_async_fifo_tb.h"
#include "sim_coop.hpp"
#include "axis.hpp"
#include <cstdio>
#include <cstdint>
#include <vector>
#include <cstring>

static const double FREQ_WR  = 200.0;
static const double FREQ_RD  = 325.0;
static const int    SIM_TIME = 10000000;
static const int    DATA_BYTES = 8;

static int word_nbytes(int) { return DATA_BYTES; }

struct Frame { int words; int user; };

static int errors = 0;

static axis_master_ptr<64,8,1,1> make_mst_port(Vaxis_async_fifo_tb* top) {
    axis_master_ptr<64,8,1,1> p;
    p.tdata  = &(top->s_axis_tdata);
    p.tkeep  = &(top->s_axis_tkeep);
    p.tstrb  = &(top->s_axis_tstrb);
    p.tid    = &(top->s_axis_tid);
    p.tdest  = &(top->s_axis_tdest);
    p.tuser  = &(top->s_axis_tuser);
    p.tlast  = &(top->s_axis_tlast);
    p.tvalid = &(top->s_axis_tvalid);
    p.tready = &(top->s_axis_tready);
    return p;
}

static axis_slave_ptr<64,8,1,1> make_slv_port(Vaxis_async_fifo_tb* top) {
    axis_slave_ptr<64,8,1,1> p;
    p.tdata  = &(top->m_axis_tdata);
    p.tkeep  = &(top->m_axis_tkeep);
    p.tstrb  = &(top->m_axis_tstrb);
    p.tid    = &(top->m_axis_tid);
    p.tdest  = &(top->m_axis_tdest);
    p.tuser  = &(top->m_axis_tuser);
    p.tlast  = &(top->m_axis_tlast);
    p.tvalid = &(top->m_axis_tvalid);
    p.tready = &(top->m_axis_tready);
    return p;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vaxis_async_fifo_tb* top = new Vaxis_async_fifo_tb;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    const char* vcd_file = (argc > 1) ? argv[1] : "waveform.vcd";
    tfp->open(vcd_file);

    top->s_rst = 1;
    top->m_rst = 1;
    top->eval();  // propagate combinatorial assignments (tb_* wires)

    // Read DUT parameters (exposed via wires in SV testbench)
    int  depth       = top->tb_depth;
    bool frame_fifo  = top->tb_frame_fifo;
    bool always_recv = top->tb_always_recv;

    // Build frame sequence programmatically
    std::vector<Frame> frames;
    int exp_words = 0, exp_good = 0, exp_bad = 0;

    if (frame_fifo) {
        // 7 scenarios in one run:
        //   1-good, depth-good(boundary), depth+1-bad(boundary), 28-bad(oversize),
        //   5-good, 8-good, 12-good (multi-frame),
        //   5-good, depth+1-bad, 8-good (mixed)
        int seq[] = {1, depth, depth+1, 28, 5, 8, 12, 5, depth+1, 8};
        for (int nw : seq) {
            bool bad = (nw > depth);
            frames.push_back({nw, bad ? 1 : 0});
            if (bad) exp_bad++; else { exp_good++; exp_words += nw; }
        }
    } else {
        frames.push_back({14, 0});
        exp_words = 14;
    }

    SimCoop<Vaxis_async_fifo_tb, 10> sim(top);
    sim.tfp = tfp;

    int wr_clk = sim.add_clock("wr", FREQ_WR, &top->s_clk);
    int rd_clk = sim.add_clock("rd", FREQ_RD, &top->m_clk);

    axis_master<64,8,1,1> mst(make_mst_port(top));
    axis_slave<64,8,1,1>  slv(make_slv_port(top));

    mst.log.quiet = false;
    slv.log.quiet = false;

    sim.add_sample_cb(wr_clk, [&](vluint64_t) { mst.update_input(); });
    sim.add_sample_cb(rd_clk, [&](vluint64_t) { slv.update_input(); });
    sim.add_drive_cb(wr_clk,  [&](vluint64_t) { mst.update_output(); });
    sim.add_drive_cb(rd_clk,  [&](vluint64_t) { slv.update_output(); });

    int good_count = 0, bad_count = 0;
    int total_sent = 0, total_sent_bytes = 0;
    bool wr_done = false, rd_done = false;

    // Monitor: count s_good_frame / s_bad_frame pulses on wr_clk
    sim.add_task("monitor", wr_clk, [&](PtCtx& ctx) {
        PT_BEGIN(ctx);
        while (true) {
            if (top->s_good_frame) good_count++;
            if (top->s_bad_frame)  bad_count++;
            PT_WAIT_CLK(ctx);
        }
        PT_END(ctx);
    });

    // Writer: send frames with deterministic byte pattern
    // Uses a frame-by-frame approach (not a for-loop) because Protothreads
    // cannot contain PT_WAIT inside C++ loop constructs.
    sim.add_task("writer", wr_clk, [&](PtCtx& ctx) {
        static int frame_idx = 0;
        int f, nw, us, total_bytes;
        std::vector<uint8_t> bytes;

        if (wr_done) { frame_idx = 0; return; }
        PT_BEGIN(ctx);

        // Reset sequence (first time only)
        if (frame_idx == 0) {
            printf("=== [wr] Reset ===\n");
            top->s_rst = 1;
            PT_WAIT_CYCLES(ctx, 10);
            top->s_rst = 0;
            PT_WAIT_CYCLES(ctx, 5);
            printf("=== [wr] Send %zu frames ===\n", frames.size());
        }

        if (frame_idx < (int)frames.size()) {
            f = frame_idx;
            nw = frames[f].words;
            us = frames[f].user;

            total_bytes = nw * DATA_BYTES;
            bytes.resize(total_bytes);
            for (int i = 0; i < total_bytes; i++)
                bytes[i] = (total_sent_bytes + i) & 0xFF;

            printf("  frame[%d]: %d words, user=%d\n", f, nw, us);
            mst.send(bytes, 0, 0, us, false);
            total_sent += nw;
            total_sent_bytes += total_bytes;
            frame_idx++;

            // Fixed frame gap to let FIFO drain
            if (frame_idx < (int)frames.size()) {
                PT_WAIT_CYCLES(ctx, 50);
            }
        } else {
            // All frames sent — wait for reader to finish
            PT_WAIT_CYCLES(ctx, 100);
            wr_done = true;
            frame_idx = 0;
        }

        PT_END(ctx);
    });

    // Reader: receive and verify data integrity
    int rx_words = 0, rx_frame_idx = 0;
    int exp_byte_idx = 0;  // tracks expected byte index (across all frames)
    std::vector<uint8_t> rx_buf;
    sim.add_task("reader", rd_clk, [&](PtCtx& ctx) {
        if (rd_done) return;
        PT_BEGIN(ctx);

        printf("=== [rd] Reset ===\n");
        top->m_rst = 1;
        PT_WAIT_CYCLES(ctx, 10);
        top->m_rst = 0;
        PT_WAIT_CYCLES(ctx, 5);

        printf("=== [rd] Receiving (%d words expected) ===\n", exp_words);
        while (rx_words < exp_words) {
            if (slv.recv(rx_buf) > 0) {
                // Advance past any bad frames so exp_byte_idx matches the
                // current good frame's position in the global sequence.
                while (rx_frame_idx < (int)frames.size()
                       && frames[rx_frame_idx].words > depth) {
                    exp_byte_idx += frames[rx_frame_idx].words * DATA_BYTES;
                    rx_frame_idx++;
                }
                int offset = 0;
                while (offset < (int)rx_buf.size() && rx_words < exp_words) {
                    int nb = word_nbytes(rx_words);
                    bool word_ok = true;
                    for (int b = 0; b < nb; b++) {
                        uint8_t got = rx_buf[offset + b];
                        uint8_t exp = (exp_byte_idx + b) & 0xFF;
                        if (got != exp) {
                            if (word_ok)
                                printf("  FAIL: rx[%d] byte[%d]=0x%02X exp=0x%02X\n",
                                       rx_words, b, got, exp);
                            word_ok = false;
                            errors++;
                        }
                    }
                    if (word_ok)
                        printf("  PASS: rx[%d]\n", rx_words);
                    rx_words++;
                    exp_byte_idx += nb;
                    offset += nb;
                }
                rx_frame_idx++;
            }
            PT_WAIT_CLK(ctx);
        }
        printf("=== [rd] Got %d words ===\n", exp_words);
        rd_done = true;
        PT_END(ctx);
    });

    // Checker: print FIFO status
    sim.add_task("checker", wr_clk, [&](PtCtx& ctx) {
        PT_BEGIN(ctx);
        PT_WAIT_CYCLES(ctx, 100);
        printf("  [chk] s_level=%d s_overflow=%d\n",
               (int)top->s_level, (int)top->s_overflow);
        PT_WAIT_CYCLES(ctx, 100);
        printf("  [chk] m_level=%d m_underflow=%d\n",
               (int)top->m_level, (int)top->m_underflow);
        PT_END(ctx);
    });

    // Ready control: random backpressure on m_axis
    sim.add_task("ready_ctrl", rd_clk, [&](PtCtx& ctx) {
        PT_BEGIN(ctx);
        while (true) {
            slv.set_tready((rand() % 100) < 70);  // 70% ready
            PT_WAIT_CLK(ctx);
        }
        PT_END(ctx);
    });

    printf("=== axis_async_fifo TB ===\n");
    printf("wr=%.0fMHz rd=%.0fMHz  sim_time=%dps\n", FREQ_WR, FREQ_RD, SIM_TIME);
    printf("FRAME_FIFO=%d DEPTH=%d ALWAYS_RECEIVE=%d\n",
           frame_fifo, depth, always_recv);
    printf("frames=%zu  exp_words=%d  exp_good=%d  exp_bad=%d\n",
           frames.size(), exp_words, exp_good, exp_bad);

    sim.run(SIM_TIME);

    // Check frame status pulses
    printf("=== Frame status ===\n");
    printf("  s_good_frame: %d (exp %d)  %s\n",
           good_count, exp_good,
           good_count == exp_good ? "PASS" : "FAIL");
    printf("  s_bad_frame:  %d (exp %d)  %s\n",
           bad_count, exp_bad,
           bad_count == exp_bad ? "PASS" : "FAIL");
    if (good_count != exp_good) errors++;
    if (bad_count != exp_bad) errors++;

    if (rx_words < exp_words) {
        printf("FAIL: only received %d of %d words\n", rx_words, exp_words);
        errors++;
    }

    printf("\n");
    if (errors == 0)
        printf("ALL TESTS PASSED\n");
    else
        printf("SOME TESTS FAILED (%d errors)\n", errors);

    tfp->close();
    delete top;
    return errors ? 1 : 0;
}
