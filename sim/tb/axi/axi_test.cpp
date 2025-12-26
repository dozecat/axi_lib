/******************************************************************************
 * Copyright (C) 2025 WanderingKitsune. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axi_test.cpp
 * @brief       AXI4 Testbench (C++)
 * @see         https://github.com/WanderingKitsune/axi_lib.git
 *
 * @details     This file contains the C++ testbench for verifying the
 *              AXI4 interface using Verilator.
 *
 * Modification History:
 * Ver   Who  Date        Changes
 * ----  ---- ----------  -----------------------------------------------------
 * 1.0        2025/12/26  Initial release
 ******************************************************************************/

#include "Vaxi_test.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <svdpi.h>
#include <iostream>
#include "axi.hpp"

/**
 * @brief Connect BFM pointers to Verilator model signals
 * @param s_axi_ptr Slave interface pointer
 * @param m_axi_ptr Master interface pointer
 * @param top       Pointer to the Verilated top module
 */
void axi_connect(axi_ptr<256, 40, 16>& s_axi_ptr, axi_ptr<256, 40, 16>& m_axi_ptr, Vaxi_test* top) {
    // Slave Interface (Input to DUT)
    s_axi_ptr.awaddr   = &(top->s_axi_awaddr);
    s_axi_ptr.awburst  = &(top->s_axi_awburst);
    s_axi_ptr.awcache  = &(top->s_axi_awcache);
    s_axi_ptr.awid     = &(top->s_axi_awid);
    s_axi_ptr.awlen    = &(top->s_axi_awlen);
    s_axi_ptr.awlock   = &(top->s_axi_awlock);
    s_axi_ptr.awprot   = &(top->s_axi_awprot);
    s_axi_ptr.awqos    = &(top->s_axi_awqos);
    s_axi_ptr.awready  = &(top->s_axi_awready);
    s_axi_ptr.awregion = &(top->s_axi_awregion);
    s_axi_ptr.awsize   = &(top->s_axi_awsize);
    s_axi_ptr.awvalid  = &(top->s_axi_awvalid);

    s_axi_ptr.wdata    = &(top->s_axi_wdata);
    s_axi_ptr.wid      = &(top->s_axi_wid);
    s_axi_ptr.wlast    = &(top->s_axi_wlast);
    s_axi_ptr.wready   = &(top->s_axi_wready);
    s_axi_ptr.wstrb    = &(top->s_axi_wstrb);
    s_axi_ptr.wvalid   = &(top->s_axi_wvalid);

    s_axi_ptr.bid      = &(top->s_axi_bid);
    s_axi_ptr.bready   = &(top->s_axi_bready);
    s_axi_ptr.bresp    = &(top->s_axi_bresp);
    s_axi_ptr.bvalid   = &(top->s_axi_bvalid);

    s_axi_ptr.araddr   = &(top->s_axi_araddr);
    s_axi_ptr.arburst  = &(top->s_axi_arburst);
    s_axi_ptr.arcache  = &(top->s_axi_arcache);
    s_axi_ptr.arid     = &(top->s_axi_arid);
    s_axi_ptr.arlen    = &(top->s_axi_arlen);
    s_axi_ptr.arlock   = &(top->s_axi_arlock);
    s_axi_ptr.arprot   = &(top->s_axi_arprot);
    s_axi_ptr.arqos    = &(top->s_axi_arqos);
    s_axi_ptr.arready  = &(top->s_axi_arready);
    s_axi_ptr.arregion = &(top->s_axi_arregion);
    s_axi_ptr.arsize   = &(top->s_axi_arsize);
    s_axi_ptr.arvalid  = &(top->s_axi_arvalid);

    s_axi_ptr.rdata    = &(top->s_axi_rdata);
    s_axi_ptr.rid      = &(top->s_axi_rid);
    s_axi_ptr.rlast    = &(top->s_axi_rlast);
    s_axi_ptr.rready   = &(top->s_axi_rready);
    s_axi_ptr.rresp    = &(top->s_axi_rresp);
    s_axi_ptr.rvalid   = &(top->s_axi_rvalid);

    // Master Interface (Output from DUT)
    m_axi_ptr.awaddr   = &(top->m_axi_awaddr);
    m_axi_ptr.awburst  = &(top->m_axi_awburst);
    m_axi_ptr.awcache  = &(top->m_axi_awcache);
    m_axi_ptr.awid     = &(top->m_axi_awid);
    m_axi_ptr.awlen    = &(top->m_axi_awlen);
    m_axi_ptr.awlock   = &(top->m_axi_awlock);
    m_axi_ptr.awprot   = &(top->m_axi_awprot);
    m_axi_ptr.awqos    = &(top->m_axi_awqos);
    m_axi_ptr.awready  = &(top->m_axi_awready);
    m_axi_ptr.awregion = &(top->m_axi_awregion);
    m_axi_ptr.awsize   = &(top->m_axi_awsize);
    m_axi_ptr.awvalid  = &(top->m_axi_awvalid);

    m_axi_ptr.wdata    = &(top->m_axi_wdata);
    m_axi_ptr.wid      = &(top->m_axi_wid);
    m_axi_ptr.wlast    = &(top->m_axi_wlast);
    m_axi_ptr.wready   = &(top->m_axi_wready);
    m_axi_ptr.wstrb    = &(top->m_axi_wstrb);
    m_axi_ptr.wvalid   = &(top->m_axi_wvalid);

    m_axi_ptr.bid      = &(top->m_axi_bid);
    m_axi_ptr.bready   = &(top->m_axi_bready);
    m_axi_ptr.bresp    = &(top->m_axi_bresp);
    m_axi_ptr.bvalid   = &(top->m_axi_bvalid);

    m_axi_ptr.araddr   = &(top->m_axi_araddr);
    m_axi_ptr.arburst  = &(top->m_axi_arburst);
    m_axi_ptr.arcache  = &(top->m_axi_arcache);
    m_axi_ptr.arid     = &(top->m_axi_arid);
    m_axi_ptr.arlen    = &(top->m_axi_arlen);
    m_axi_ptr.arlock   = &(top->m_axi_arlock);
    m_axi_ptr.arprot   = &(top->m_axi_arprot);
    m_axi_ptr.arqos    = &(top->m_axi_arqos);
    m_axi_ptr.arready  = &(top->m_axi_arready);
    m_axi_ptr.arregion = &(top->m_axi_arregion);
    m_axi_ptr.arsize   = &(top->m_axi_arsize);
    m_axi_ptr.arvalid  = &(top->m_axi_arvalid);

    m_axi_ptr.rdata    = &(top->m_axi_rdata);
    m_axi_ptr.rid      = &(top->m_axi_rid);
    m_axi_ptr.rlast    = &(top->m_axi_rlast);
    m_axi_ptr.rready   = &(top->m_axi_rready);
    m_axi_ptr.rresp    = &(top->m_axi_rresp);
    m_axi_ptr.rvalid   = &(top->m_axi_rvalid);
}

/**
 * @brief Main testbench function
 */
int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    Vaxi_test* top = new Vaxi_test;
    VerilatedVcdC* tfp = new VerilatedVcdC;

    axi_ptr<256, 40, 16> axi_in_if;
    axi_ptr<256, 40, 16> axi_out_if;

    axi_connect(axi_in_if, axi_out_if, top);
    if (!axi_in_if.check()) {
        std::cerr << "axi_in_if connection failed!" << std::endl;
        return -1;
    }
    if (!axi_out_if.check()) {
        std::cerr << "axi_out_if connection failed!" << std::endl;
        return -1;
    }

    axi_master<256, 40, 16> axi_mst(axi_in_if);
    axi_slave<256, 40, 16> axi_slv(axi_out_if);

    top->trace(tfp, 100);
    tfp->open("waveform.vcd");

    top->clk = 0;
    top->rst = 1;

    int sim_time = 0;
    const int max_sim_time = 20000;

    while (!Verilated::gotFinish() && sim_time < max_sim_time) {
        sim_time++;
        top->clk = !top->clk;
        if (sim_time == 10) {
            top->rst = 0;
        }
        if (top->clk) {
            axi_mst.tick();
            top->eval(); // Propagate signals from Master to Slave
            axi_slv.tick();
        }
        if (sim_time == 20) {
            axi_mst.write(0x100, (uint32_t)0xABCD1234);
            axi_mst.write(0x200, (uint32_t)0x12121212);
            axi_mst.write(0x300, (uint32_t)0x10000000);
            
            // Burst Write (INCR)
            std::vector<uint8_t> burst_data;
            for(int i=0; i<256; i++) burst_data.push_back(i); // 256 bytes = 8 beats of 32 bytes
            axi_mst.write_burst_incr(0x400, burst_data);

            // Burst Write (FIXED)
            std::vector<uint8_t> fixed_data;
            for(int i=0; i<256; i++) fixed_data.push_back(0xAA);
            axi_mst.write_burst_fixed(0x500, fixed_data);

            // Vector Write (32 bytes for 256-bit width)
            std::vector<uint8_t> vec_data(32, 0x55); // 32 bytes of 0x55
            axi_mst.write(0x600, vec_data);
        }
        if (sim_time == 90) {
            axi_mst.read(0x100);
            axi_mst.read(0x200);
            axi_mst.read(0x300);
            
            // Burst Read
            axi_mst.read(0x400, 7); // Length 7 (8 beats)
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
