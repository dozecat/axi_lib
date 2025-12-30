/******************************************************************************
 * Copyright (C) 2025 WanderingKitsune. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axil_master.hpp
 * @brief       AXI4-Lite Master VIP
 * @see         https://github.com/WanderingKitsune/axi_lib.git
 *
 * @details     This module implements the Master VIP for AXI4-Lite protocol verification.
 *
 * Modification History:
 * Ver   Who  Date        Changes
 * ----  ---- ----------  -----------------------------------------------------
 * 1.0        2025/12/30  Initial release
 ******************************************************************************/

#ifndef AXIL_MASTER_HPP
#define AXIL_MASTER_HPP

#include "axil.hpp"
#include <cstdint>
#include <queue>
#include <iostream>
#include <iomanip>

/// @brief AXI4-Lite Master BFM
template <
    size_t DATA_WIDTH = 32,
    size_t ADDR_WIDTH = 16
>
class axil_master {
public:
    axil_master_ptr<DATA_WIDTH, ADDR_WIDTH> port;              ///< Interface signal pointers

    std::queue<uint64_t> wr_data_q;         ///< Write data queue
    std::queue<uint64_t> wr_addr_q;         ///< Write address queue
    std::queue<uint64_t> rd_addr_q;         ///< Read address queue
    std::queue<uint64_t> rd_data_q;         ///< Read data queue

    bool wr_active;                         ///< Write transaction active flag
    bool rd_active;                         ///< Read transaction active flag

    // Handshake flags for delayed clearing
    bool aw_hs, w_hs, b_hs, ar_hs, r_hs;

    // Store address for logging
    uint64_t current_wr_addr;
    uint64_t current_wr_data;
    uint64_t current_rd_addr;

    /// @brief Constructor
    axil_master(axil_master_ptr<DATA_WIDTH, ADDR_WIDTH> port) : port(port) {
        clear();
        wr_active = false;
        rd_active = false;
        aw_hs = false;
        w_hs = false;
        b_hs = false;
        ar_hs = false;
        r_hs = false;
    }

    /// @brief Clear all signals
    void clear() {
        waddr_clr();
        wdata_clr();
        raddr_clr();
        rdata_clr();
        rresp_clr();
    }

    /// @brief Initiate a write transaction
    void write(uint64_t addr, uint64_t data) {
        wr_addr_q.push(addr);
        wr_data_q.push(data);
    }

    /// @brief Initiate a read transaction
    void read(uint64_t addr) {
        rd_addr_q.push(addr);
    }

    /// @brief Retrieve read data
    bool get_read_data(uint64_t &data) {
        if (rd_data_q.empty()) return false;
        data = rd_data_q.front();
        rd_data_q.pop();
        return true;
    }

    // Internal helpers
    void waddr_set(uint64_t addr) {
        *(port.awaddr)  = addr;
        *(port.awvalid) = true;
    }

    void waddr_clr() {
        *(port.awaddr)  = 0;
        *(port.awvalid) = false;
    }

    void wdata_set(uint64_t data) {
        *(port.wdata)   = data;
        *(port.wstrb)   = (1ULL << (DATA_WIDTH / 8)) - 1; // Enable all bytes
        *(port.wvalid)  = true;
    }

    void wdata_clr() {
        *(port.wdata)   = 0;
        *(port.wstrb)   = 0;
        *(port.wvalid)  = false;
    }

    void rresp_set() {
        *(port.bready)  = true;
    }

    void rresp_clr() {
        *(port.bready)  = false;
        wr_active = false;
    }

    void raddr_set(uint64_t addr) {
        *(port.araddr)  = addr;
        *(port.arvalid) = true;
    }

    void raddr_clr() {
        *(port.araddr)  = 0;
        *(port.arvalid) = false;
    }

    void rdata_set() {
        *(port.rready)  = true;
    }

    void rdata_clr() {
        *(port.rready)  = false;
        rd_active = false;
    }

    /// @brief Master simulation tick function
    void tick() {
        // 1. Process delayed clears from previous cycle handshakes
        if (aw_hs) { waddr_clr(); aw_hs = false; }
        if (w_hs)  { wdata_clr(); rresp_set(); w_hs = false; }
        if (b_hs)  { rresp_clr(); b_hs = false; }
        if (ar_hs) { raddr_clr(); rdata_set(); ar_hs = false; }
        if (r_hs)  { rdata_clr(); r_hs = false; }

        // 2. Detect Handshakes (Current Cycle)
        // Write Address
        if (*(port.awready) && *(port.awvalid) && !aw_hs) {
            aw_hs = true;
        }

        // Write Data
        if (*(port.wready) && *(port.wvalid) && !w_hs) {
            w_hs = true;
        }

        // Write Response
        if (*(port.bready) && *(port.bvalid) && !b_hs) {
            if (*(port.bresp) != OKAY) {
                std::cout << "[AXIL-MST][WARN] Write response not OKAY!" << std::endl;
            }
            b_hs = true;
            std::cout << "[AXIL-MST] WR success !" << std::endl;
            std::cout << "ADDR:0x" << std::hex << current_wr_addr 
                      << "  DATA:0x" << current_wr_data << std::endl << std::endl;
        }

        // Read Address
        if (*(port.arready) && *(port.arvalid) && !ar_hs) {
            ar_hs = true;
        }

        // Read Data
        if (*(port.rready) && *(port.rvalid) && !r_hs) {
            uint64_t data = *(port.rdata);
            rd_data_q.push(data);
            if (*(port.rresp) != OKAY) {
                std::cout << "[AXIL-MST][WARN] Read response not OKAY!" << std::endl;
            }
            r_hs = true;
            std::cout << "[AXIL-MST] RD success !" << std::endl;
            std::cout << "ADDR:0x" << std::hex << current_rd_addr 
                      << "  DATA:0x" << data << std::endl << std::endl;
        }

        // 3. Drive New Requests (if not busy and not in handshake process)
        if (!wr_active && !wr_addr_q.empty() && !wr_data_q.empty()) {
            wr_active = true;
            uint64_t addr = wr_addr_q.front(); wr_addr_q.pop();
            uint64_t data = wr_data_q.front(); wr_data_q.pop();
            current_wr_addr = addr;
            current_wr_data = data;
            waddr_set(addr);
            wdata_set(data);
        }

        if (!rd_active && !rd_addr_q.empty()) {
            rd_active = true;
            uint64_t addr = rd_addr_q.front(); rd_addr_q.pop();
            current_rd_addr = addr;
            raddr_set(addr);
        }
    }
};

#endif