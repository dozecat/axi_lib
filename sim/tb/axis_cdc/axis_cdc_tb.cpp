/******************************************************************************
 * Copyright (C) 2026 dozecat. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axis_cdc_tb.cpp
 * @brief       AXI4-Stream CDC Testbench (C++)
 * @see         https://github.com/dozecat/axi_lib
 ******************************************************************************/

#include "Vaxis_cdc_tb.h"
#include "verilated.h"
#if VM_TRACE
#include "verilated_vcd_c.h"
#endif
#include "clock_gen.hpp"
#include "axis.hpp"
#include <iostream>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <vector>

static const double        FREQ_S_MHZ   = 200.0;
static const double        FREQ_M_MHZ   = 325.0;
static const vluint64_t    TIME_STEP_PS = 10;
static const vluint64_t    MAX_TIME_PS  = 10000000;

static int errors = 0;

struct test_vector {
    std::string   name;
    std::vector<uint8_t> data;
};

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
#if VM_TRACE
    Verilated::traceEverOn(true);
#endif

    Vaxis_cdc_tb* top = new Vaxis_cdc_tb;
#if VM_TRACE
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("waveform.vcd");
#endif

    ClockGen<TIME_STEP_PS> s_clk_gen;
    ClockGen<TIME_STEP_PS> m_clk_gen;
    s_clk_gen.init(FREQ_S_MHZ, &top->s_clk);
    m_clk_gen.init(FREQ_M_MHZ, &top->m_clk);

    top->s_rst = 1;
    top->m_rst = 1;
    top->s_axis_tvalid = 0;
    top->s_axis_tdata  = 0;
    top->s_axis_tkeep  = 0;
    top->s_axis_tstrb  = 0;
    top->s_axis_tid    = 0;
    top->s_axis_tdest  = 0;
    top->s_axis_tuser  = 0;
    top->s_axis_tlast  = 0;
    top->m_axis_tready = 1;

    std::cout << "=== axis_cdc Test ===" << std::endl;
    std::cout << "FREQ_S=" << FREQ_S_MHZ << "MHz FREQ_M=" << FREQ_M_MHZ << "MHz" << std::endl;

    axis_master_ptr<64, 8, 1, 1> mst_ptr;
    axis_slave_ptr<64, 8, 1, 1> slv_ptr;

    mst_ptr.tdata  = &(top->s_axis_tdata);
    mst_ptr.tkeep  = &(top->s_axis_tkeep);
    mst_ptr.tstrb  = &(top->s_axis_tstrb);
    mst_ptr.tid    = &(top->s_axis_tid);
    mst_ptr.tdest  = &(top->s_axis_tdest);
    mst_ptr.tuser  = &(top->s_axis_tuser);
    mst_ptr.tlast  = &(top->s_axis_tlast);
    mst_ptr.tvalid = &(top->s_axis_tvalid);
    mst_ptr.tready = &(top->s_axis_tready);

    slv_ptr.tdata  = &(top->m_axis_tdata);
    slv_ptr.tkeep  = &(top->m_axis_tkeep);
    slv_ptr.tstrb  = &(top->m_axis_tstrb);
    slv_ptr.tid    = &(top->m_axis_tid);
    slv_ptr.tdest  = &(top->m_axis_tdest);
    slv_ptr.tuser  = &(top->m_axis_tuser);
    slv_ptr.tlast  = &(top->m_axis_tlast);
    slv_ptr.tvalid = &(top->m_axis_tvalid);
    slv_ptr.tready = &(top->m_axis_tready);

    if (!mst_ptr.check()) { std::cerr << "mst_ptr check failed" << std::endl; return -1; }
    if (!slv_ptr.check()) { std::cerr << "slv_ptr check failed" << std::endl; return -1; }

    axis_master<64, 8, 1, 1> axis_mst(mst_ptr);
    axis_slave<64, 8, 1, 1> axis_slv(slv_ptr);

    auto make_pattern = [](int n) {
        std::vector<uint8_t> v(n);
        for (int i = 0; i < n; i++) v[i] = i & 0xFF;
        return v;
    };

    std::vector<test_vector> tests = {
        { "1 byte"      , make_pattern(1)   },
        { "5 bytes"     , make_pattern(5)   },
        { "11 bytes"    , make_pattern(11)  },
        { "16 bytes"    , make_pattern(16)  },
        { "22 bytes"    , make_pattern(22)  },
        { "100 bytes"   , make_pattern(100) },
    };

    vluint64_t sim_time_ps = 0;

    enum { PHASE_RST, PHASE_IDLE, PHASE_SEND, PHASE_WAIT, PHASE_DONE } phase = PHASE_RST;
    int rst_cnt = 0;
    int test_idx = 0;
    bool send_queued = false;

    std::vector<uint8_t> rx_data;

    while (!Verilated::gotFinish() && sim_time_ps < MAX_TIME_PS) {
        bool s_pos = s_clk_gen.pedge(sim_time_ps);
        bool m_pos = m_clk_gen.pedge(sim_time_ps);

        if (s_pos) axis_mst.update_output();
        if (m_pos) axis_slv.update_output();

        top->eval();

        if (s_pos) axis_mst.update_input();
        if (m_pos) axis_slv.update_input();

        if (s_pos) {
            switch (phase) {
                case PHASE_RST:
                    rst_cnt++;
                    if (rst_cnt >= 20) {
                        top->s_rst = 0;
                        top->m_rst = 0;
                        phase = PHASE_IDLE;
                        std::cout << "\n[Phase: IDLE]\n";
                    }
                    break;
                case PHASE_SEND:
                    if (!send_queued && test_idx < (int)tests.size()) {
                        axis_mst.send(tests[test_idx].data);
                        send_queued = true;
                        std::cout << "  [" << test_idx << "] send \"" << tests[test_idx].name
                                  << "\" (" << tests[test_idx].data.size() << " bytes)\n";
                    }
                    break;
                default: break;
            }
        }

        if (m_pos) {
            switch (phase) {
                case PHASE_IDLE: {
                    static int idle_wait = 0;
                    idle_wait++;
                    if (idle_wait > 20) {
                        idle_wait = 0;
                        phase = PHASE_SEND;
                        send_queued = false;
                        std::cout << "\n[Phase: SEND]\n";
                    }
                    break;
                }
                case PHASE_WAIT: {
                    if (!axis_slv.empty()) {
                        ssize_t sz = axis_slv.recv(rx_data);
                        if (sz > 0) {
                            auto& tv = tests[test_idx - 1];
                            bool ok = ((size_t)sz == tv.data.size());
                            if (ok) {
                                for (size_t i = 0; i < (size_t)sz && i < tv.data.size(); i++) {
                                    if (rx_data[i] != tv.data[i]) { ok = false; break; }
                                }
                            }
                            if (ok) {
                                std::cout << "  PASS [\"" << tv.name << "\"] size=" << sz << "\n";
                            } else {
                                std::cout << "  FAIL [\"" << tv.name << "\"] size=" << sz << "\n";
                                errors++;
                            }
                            if (test_idx >= (int)tests.size()) {
                                phase = PHASE_DONE;
                            } else {
                                phase = PHASE_SEND;
                                send_queued = false;
                            }
                        }
                    }
                    break;
                }
                default: break;
            }
        }

        switch (phase) {
            case PHASE_SEND: {
                static vluint64_t t_start = 0;
                if (t_start == 0) t_start = sim_time_ps;
                if (send_queued) {
                    t_start = 0;
                    phase = PHASE_WAIT;
                    test_idx++;
                }
                break;
            }
            default: break;
        }

        if (sim_time_ps % 500000 == 0)
            std::cout << "  t=" << sim_time_ps << "ps ph=" << phase
                      << " idx=" << test_idx << " queued=" << send_queued
                      << " s_tv=" << (int)top->s_axis_tvalid
                      << " m_tv=" << (int)top->m_axis_tvalid
                      << " rx_q=" << axis_slv.rx_queue.size()
                      << std::endl;

#if VM_TRACE
        tfp->dump(sim_time_ps);
#endif
        sim_time_ps += TIME_STEP_PS;
        if (phase == PHASE_DONE) {
            static int done_delay = 0;
            done_delay++;
            if (done_delay > 2000) break;
        }
    }

    std::cout << "\n****************************************\n";
    if (errors == 0)
        std::cout << "ALL TESTS PASSED\n";
    else
        std::cout << "SOME TESTS FAILED (" << errors << " errors)\n";
    std::cout << "****************************************\n";

#if VM_TRACE
    tfp->close();
    delete tfp;
#endif
    delete top;
    return errors ? 1 : 0;
}
