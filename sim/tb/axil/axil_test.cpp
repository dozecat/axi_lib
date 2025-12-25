/******************************************************************************
 * Copyright (C) 2025 WanderingKitsune. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axil_test.cpp
 * @brief       AXI4-Lite Testbench (C++)
 * @see         https://github.com/WanderingKitsune/axi_lib.git
 *
 * @details     This file contains the C++ testbench for verifying the
 *              AXI4-Lite interface using Verilator.
 *
 * Modification History:
 * Ver   Who  Date        Changes
 * ----  ---- ----------  -----------------------------------------------------
 * 1.0        2025/12/25  Initial release
 ******************************************************************************/

#include "Vaxil_test.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <svdpi.h>
#include <iostream>
#include "axil.hpp"

/**
 * @brief Connect BFM pointers to Verilator model signals
 * @param s_axil_ptr Slave interface pointer
 * @param m_axil_ptr Master interface pointer
 * @param top        Pointer to the Verilated top module
 */
void axil_connect(axil_ptr<32, 16>& s_axil_ptr, axil_ptr<32, 16>& m_axil_ptr, Vaxil_test* top) {
    s_axil_ptr.awaddr   = &(top->s_axil_awaddr);
    s_axil_ptr.awprot   = &(top->s_axil_awprot);
    s_axil_ptr.awready  = &(top->s_axil_awready);
    s_axil_ptr.awvalid  = &(top->s_axil_awvalid);
    s_axil_ptr.bready   = &(top->s_axil_bready);
    s_axil_ptr.bresp    = &(top->s_axil_bresp);
    s_axil_ptr.bvalid   = &(top->s_axil_bvalid);
    s_axil_ptr.wdata    = &(top->s_axil_wdata);
    s_axil_ptr.wready   = &(top->s_axil_wready);
    s_axil_ptr.wstrb    = &(top->s_axil_wstrb);
    s_axil_ptr.wvalid   = &(top->s_axil_wvalid);
    s_axil_ptr.araddr   = &(top->s_axil_araddr);
    s_axil_ptr.arprot   = &(top->s_axil_arprot);
    s_axil_ptr.arready  = &(top->s_axil_arready);
    s_axil_ptr.arvalid  = &(top->s_axil_arvalid);
    s_axil_ptr.rdata    = &(top->s_axil_rdata);
    s_axil_ptr.rready   = &(top->s_axil_rready);
    s_axil_ptr.rresp    = &(top->s_axil_rresp);
    s_axil_ptr.rvalid   = &(top->s_axil_rvalid);

    m_axil_ptr.awaddr   = &(top->m_axil_awaddr);
    m_axil_ptr.awprot   = &(top->m_axil_awprot);
    m_axil_ptr.awready  = &(top->m_axil_awready);
    m_axil_ptr.awvalid  = &(top->m_axil_awvalid);
    m_axil_ptr.bready   = &(top->m_axil_bready);
    m_axil_ptr.bresp    = &(top->m_axil_bresp);
    m_axil_ptr.bvalid   = &(top->m_axil_bvalid);
    m_axil_ptr.wdata    = &(top->m_axil_wdata);
    m_axil_ptr.wready   = &(top->m_axil_wready);
    m_axil_ptr.wstrb    = &(top->m_axil_wstrb);
    m_axil_ptr.wvalid   = &(top->m_axil_wvalid);
    m_axil_ptr.araddr   = &(top->m_axil_araddr);
    m_axil_ptr.arprot   = &(top->m_axil_arprot);
    m_axil_ptr.arready  = &(top->m_axil_arready);
    m_axil_ptr.arvalid  = &(top->m_axil_arvalid);
    m_axil_ptr.rdata    = &(top->m_axil_rdata);
    m_axil_ptr.rready   = &(top->m_axil_rready);
    m_axil_ptr.rresp    = &(top->m_axil_rresp);
    m_axil_ptr.rvalid   = &(top->m_axil_rvalid);
}

/**
 * @brief Main testbench function
 */
int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vaxil_test* top = new Vaxil_test;
    VerilatedVcdC* tfp = new VerilatedVcdC;

    axil_ptr<32, 16> axil_in_if;
    axil_ptr<32, 16> axil_out_if;

    axil_connect(axil_in_if, axil_out_if, top);
    if (!axil_in_if.check()) {
        std::cerr << "axil_in_if connection failed!" << std::endl;
        return -1;
    }
    if (!axil_out_if.check()) {
        std::cerr << "axil_out_if connection failed!" << std::endl;
        return -1;
    }

    axil_master<32, 16> axil_mst(axil_in_if);
    axil_slave<32, 16> axil_slv(axil_out_if);

    top->trace(tfp, 100);
    tfp->open("waveform.vcd");

    top->clk = 0;
    top->rst = 1;

    int sim_time = 0;
    const int max_sim_time = 500;

    while (!Verilated::gotFinish() && sim_time < max_sim_time) {
        sim_time++;
        top->clk = !top->clk;
        if (sim_time == 10) {
            top->rst = 0;
        }
        if (top->clk) {
            axil_mst.tick();
            axil_slv.tick();
            uint32_t rdata;
            if (axil_mst.get_read_data(rdata)) {
                std::cout << "[TEST] Got read data: 0x" << std::hex << rdata << std::endl;
            }
        }
        if (sim_time == 20) {
            axil_mst.write(0x100, 0xABCD1234);
            axil_mst.write(0x200, 0x12121212);
            axil_mst.write(0x300, 0x10000000);
        }
        if (sim_time == 90) {
            axil_mst.read(0x100);
            axil_mst.read(0x200);
            axil_mst.read(0x300);
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
