/******************************************************************************
 * Copyright (C) 2025 WanderingKitsune. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axil.hpp
 * @brief       AXI4-Lite Master/Slave Bus Functional Model (BFM)
 * @see         https://github.com/WanderingKitsune/axi_lib.git
 *
 * @details     This module implements a Bus Functional Model for AXI4-Lite
 *              protocol verification, supporting both master and slave roles.
 *
 * Modification History:
 * Ver   Who  Date        Changes
 * ----  ---- ----------  -----------------------------------------------------
 * 1.0        2025/12/25  Initial release
 ******************************************************************************/

#ifndef AXIL_HPP
#define AXIL_HPP

#include <cstdint>
#include <set>
#include <cstring>
#include <queue>
#include <iostream>
#include <map>
#include "sig.hpp"

/**
 * @brief AXI4-Lite interface signals pointer structure
 */
template <
    size_t DATA_WIDTH = 32,
    size_t ADDR_WIDTH = 16
>
struct axil_ptr {
    sig(*awaddr , ADDR_WIDTH-1  , 0) = NULL;
    sig(*awprot , 2             , 0) = NULL;
    sig(*awready, 0             , 0) = NULL;
    sig(*awvalid, 0             , 0) = NULL;
    sig(*bready , 0             , 0) = NULL;
    sig(*bresp  , 1             , 0) = NULL;
    sig(*bvalid , 0             , 0) = NULL;
    sig(*wdata  , DATA_WIDTH-1  , 0) = NULL;
    sig(*wready , 0             , 0) = NULL;
    sig(*wstrb  , DATA_WIDTH/8-1, 0) = NULL;
    sig(*wvalid , 0             , 0) = NULL;
    sig(*araddr , ADDR_WIDTH-1  , 0) = NULL;
    sig(*arprot , 2             , 0) = NULL;
    sig(*arready, 0             , 0) = NULL;
    sig(*arvalid, 0             , 0) = NULL;
    sig(*rdata  , DATA_WIDTH-1  , 0) = NULL;
    sig(*rready , 0             , 0) = NULL;
    sig(*rresp  , 1             , 0) = NULL;
    sig(*rvalid , 0             , 0) = NULL;

    /// Check if all signal pointers are assigned
    bool check() {
        std::set<void*> s;
        s.insert((void*)awaddr);
        s.insert((void*)awprot);
        s.insert((void*)awready);
        s.insert((void*)awvalid);
        s.insert((void*)bready);
        s.insert((void*)bresp);
        s.insert((void*)bvalid);
        s.insert((void*)wdata);
        s.insert((void*)wready);
        s.insert((void*)wstrb);
        s.insert((void*)wvalid);
        s.insert((void*)araddr);
        s.insert((void*)arprot);
        s.insert((void*)arready);
        s.insert((void*)arvalid);
        s.insert((void*)rdata);
        s.insert((void*)rready);
        s.insert((void*)rresp);
        s.insert((void*)rvalid);
        return s.size() == 19 && s.count(NULL) == 0;
    }
};

enum resp_type_t {
    OKAY   = 0,
    EXOKAY = 1,
    SLVERR = 2,
    DECERR = 3
};

/// @brief AXI4-Lite Master BFM
template <
    size_t DATA_WIDTH = 32,
    size_t ADDR_WIDTH = 16
>
class axil_master {
public:
    axil_ptr<DATA_WIDTH> port;              ///< Interface signal pointers

    std::queue<uint32_t> wr_data_q;         ///< Write data queue
    std::queue<uint32_t> wr_addr_q;         ///< Write address queue
    std::queue<uint32_t> rd_addr_q;         ///< Read address queue
    std::queue<uint32_t> rd_data_q;         ///< Read data queue

    bool wr_active;                         ///< Write transaction active flag
    bool rd_active;                         ///< Read transaction active flag

    // Handshake flags for delayed clearing
    bool aw_hs, w_hs, b_hs, ar_hs, r_hs;

    // Store address for logging
    uint32_t current_wr_addr;
    uint32_t current_wr_data;
    uint32_t current_rd_addr;

    /// @brief Constructor
    axil_master(axil_ptr<DATA_WIDTH> port) : port(port) {
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
    void write(uint32_t addr, uint32_t data) {
        wr_addr_q.push(addr);
        wr_data_q.push(data);
    }

    /// @brief Initiate a read transaction
    void read(uint32_t addr) {
        rd_addr_q.push(addr);
    }

    /// @brief Retrieve read data
    bool get_read_data(uint32_t &data) {
        if (rd_data_q.empty()) return false;
        data = rd_data_q.front();
        rd_data_q.pop();
        return true;
    }

    // Internal helpers
    void waddr_set(uint32_t addr) {
        *(port.awaddr)  = addr;
        *(port.awvalid) = true;
    }

    void waddr_clr() {
        *(port.awaddr)  = 0;
        *(port.awvalid) = false;
    }

    void wdata_set(uint32_t data) {
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

    void raddr_set(uint32_t addr) {
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
            uint32_t data = *(port.rdata);
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
            uint32_t addr = wr_addr_q.front(); wr_addr_q.pop();
            uint32_t data = wr_data_q.front(); wr_data_q.pop();
            current_wr_addr = addr;
            current_wr_data = data;
            waddr_set(addr);
            wdata_set(data);
        }

        if (!rd_active && !rd_addr_q.empty()) {
            rd_active = true;
            uint32_t addr = rd_addr_q.front(); rd_addr_q.pop();
            current_rd_addr = addr;
            raddr_set(addr);
        }
    }
};

/// @brief AXI4-Lite Slave BFM
template <
    size_t DATA_WIDTH = 32,
    size_t ADDR_WIDTH = 16
>
class axil_slave {
public:
    axil_ptr<DATA_WIDTH> port;              ///< Interface signal pointers
    std::map<uint32_t, uint32_t> mem;       ///< Memory storage

    bool wr_addr_received;                  ///< Write address received flag
    uint32_t wr_addr;                       ///< Received write address
    bool wr_data_received;                  ///< Write data received flag
    uint32_t wr_data;                       ///< Received write data
    bool wr_resp_sent;                      ///< Write response sent flag

    bool rd_addr_received;                  ///< Read address received flag
    uint32_t rd_addr;                       ///< Received read address
    bool rd_data_sent;                      ///< Read data sent flag
    uint32_t rd_data_reg;                   ///< Read data register

    /// @brief Constructor
    axil_slave(axil_ptr<DATA_WIDTH> port) : port(port) {
        wr_addr_received = false;
        wr_data_received = false;
        wr_resp_sent = false;
        rd_addr_received = false;
        rd_data_sent = false;
        rd_data_reg = 0;
        
        // Default outputs
        *(port.awready) = false;
        *(port.wready) = false;
        *(port.bvalid) = false;
        *(port.arready) = false;
        *(port.rvalid) = false;
    }

    /// @brief Slave simulation tick function
    void tick() {
        // 1. Sample Inputs
        bool awvalid = *(port.awvalid);
        bool wvalid  = *(port.wvalid);
        bool bready  = *(port.bready);
        bool arvalid = *(port.arvalid);
        bool rready  = *(port.rready);

        // 2. Update State
        // Write Address
        if (!wr_addr_received && awvalid) {
            wr_addr = *(port.awaddr);
            wr_addr_received = true;
        }

        // Write Data
        if (!wr_data_received && wvalid) {
            wr_data = *(port.wdata);
            wr_data_received = true;
        }

        // Write Response
        if (wr_addr_received && wr_data_received && !wr_resp_sent) {
            mem[wr_addr] = wr_data;
            std::cout << "[AXIL-SLV] WR success !" << std::endl;
            std::cout << "ADDR:0x" << std::hex << wr_addr 
                      << "  DATA:0x" << wr_data << std::endl << std::endl;
            wr_resp_sent = true;
        } else if (wr_resp_sent && bready) {
            wr_resp_sent = false;
            wr_addr_received = false;
            wr_data_received = false;
        }

        // Read Address
        if (!rd_addr_received && arvalid) {
            rd_addr = *(port.araddr);
            rd_addr_received = true;
        }

        // Read Data
        if (rd_addr_received && !rd_data_sent) {
            uint32_t rdata = 0;
            if (mem.count(rd_addr)) {
                rdata = mem[rd_addr];
            }
            std::cout << "[AXIL-SLV] RD success !" << std::endl;
            std::cout << "ADDR:0x" << std::hex << rd_addr 
                      << "  DATA:0x" << rdata << std::endl << std::endl;
            rd_data_reg = rdata;
            rd_data_sent = true;
        } else if (rd_data_sent && rready) {
            rd_data_sent = false;
            rd_addr_received = false;
        }

        // 3. Drive Outputs
        *(port.awready) = !wr_addr_received;
        *(port.wready)  = !wr_data_received;
        *(port.bvalid)  = wr_resp_sent;
        *(port.bresp)   = OKAY;
        *(port.arready) = !rd_addr_received;
        *(port.rvalid)  = rd_data_sent;
        *(port.rresp)   = OKAY;
        if (rd_data_sent) {
            *(port.rdata) = rd_data_reg;
        }
    }
};

#endif
