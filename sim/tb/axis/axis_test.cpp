/******************************************************************************
 * Copyright (C) 2025 WanderingKitsune. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axis_test.cpp
 * @brief       AXI4-Stream Testbench (C++)
 * @see         https://github.com/WanderingKitsune/axi_lib.git
 *
 * @details     This file contains the C++ testbench for verifying the
 *              AXI4-Stream interface using Verilator.
 *
 * Modification History:
 * Ver   Who  Date        Changes
 * ----  ---- ----------  -----------------------------------------------------
 * 1.0        2025/12/25  Initial release
 ******************************************************************************/

#include "Vaxis_test.h"
// #include "Vaxis_test__Dpi.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <svdpi.h>
#include <iostream>
#include "axis.hpp"

/**
 * @brief Connect BFM pointers to Verilator model signals
 * @param s_axis_ptr Slave interface pointer
 * @param m_axis_ptr Master interface pointer
 * @param top        Pointer to the Verilated top module
 */
void axis_connect(axis_ptr<256, 8, 1, 1>& s_axis_ptr, axis_ptr<256, 8, 1, 1>& m_axis_ptr, Vaxis_test* top) {
    s_axis_ptr.tdata  = &(top->s_tdata);
    s_axis_ptr.tkeep  = &(top->s_tkeep);
    s_axis_ptr.tdest  = &(top->s_tdest);
    s_axis_ptr.tstrb  = &(top->s_tstrb);
    s_axis_ptr.tid    = &(top->s_tid);
    s_axis_ptr.tuser  = &(top->s_tuser);
    s_axis_ptr.tlast  = &(top->s_tlast);
    s_axis_ptr.tvalid = &(top->s_tvalid);
    s_axis_ptr.tready = &(top->s_tready);

    m_axis_ptr.tdata  = &(top->m_tdata);
    m_axis_ptr.tkeep  = &(top->m_tkeep);
    m_axis_ptr.tdest  = &(top->m_tdest);
    m_axis_ptr.tstrb  = &(top->m_tstrb);
    m_axis_ptr.tid    = &(top->m_tid);
    m_axis_ptr.tuser  = &(top->m_tuser);
    m_axis_ptr.tlast  = &(top->m_tlast);
    m_axis_ptr.tvalid = &(top->m_tvalid);
    m_axis_ptr.tready = &(top->m_tready);
}

/**
 * @brief Main testbench function
 */
int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vaxis_test* top = new Vaxis_test;
    VerilatedVcdC* tfp = new VerilatedVcdC;

    axis_ptr<256, 8, 1, 1> axis_in_if;
    axis_ptr<256, 8, 1, 1> axis_out_if;

    axis_connect(axis_in_if, axis_out_if, top);
    if (!axis_in_if.check()) {
        std::cerr << "axis_in_if connection failed!" << std::endl;
        return -1;
    }
    if (!axis_out_if.check()) {
        std::cerr << "axis_out_if connection failed!" << std::endl;
        return -1;
    }

    axis_master<256> axis_mst(axis_in_if);
    axis_slave<256> axis_slv(axis_out_if);

    top->trace(tfp, 100);
    tfp->open("waveform.vcd");

    top->axis_clk = 0;
    top->axis_rst = 1;

    int sim_time = 0;
    const int max_sim_time = 100;

    while (!Verilated::gotFinish() && sim_time < max_sim_time) {
        sim_time++;
        top->axis_clk = !top->axis_clk;
        if (sim_time == 10) {
            top->axis_rst = 0;
        }
        if (top->axis_clk) {
            axis_mst.tick();
            axis_slv.tick();
        }
        if (sim_time == 20) {
            char data_num[100];
            for (int i = 0; i < 100; i++) {
                data_num[i] = i;
            }
            axis_mst.send(data_num, 77);
        }
        if (sim_time == 90) {
            char data_recv[100];
            std::cout << "Data at time 90: ";
            ssize_t recv_size = axis_slv.recv(100, data_recv);
            for (int i = 0; i < recv_size; i++) {
                std::cout << (int)data_recv[i] << " ";
            }
            std::cout << "Size: " << recv_size << std::endl;
        }
        top->eval();
        tfp->dump(sim_time);
    }

    tfp->close();
    delete tfp;
    delete top;

    std::cout << "Simulation finished at time " << sim_time << std::endl;
    return 0;
}
