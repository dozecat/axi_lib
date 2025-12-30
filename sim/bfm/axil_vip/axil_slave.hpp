/******************************************************************************
 * Copyright (C) 2025 WanderingKitsune. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axil_slave.hpp
 * @brief       AXI4-Lite Slave VIP
 * @see         https://github.com/WanderingKitsune/axi_lib.git
 *
 * @details     This module implements the Slave VIP for AXI4-Lite protocol verification.
 *
 * Modification History:
 * Ver   Who  Date        Changes
 * ----  ---- ----------  -----------------------------------------------------
 * 1.0        2025/12/30  Initial release
 ******************************************************************************/

#ifndef AXIL_SLAVE_HPP
#define AXIL_SLAVE_HPP

#include "axil.hpp"
#include <cstdint>
#include <map>
#include <iostream>
#include <iomanip>

/// @brief AXI4-Lite Slave BFM
template <
    size_t DATA_WIDTH = 32,
    size_t ADDR_WIDTH = 16
>
class axil_slave {
public:
    axil_slave_ptr<DATA_WIDTH, ADDR_WIDTH> port;              ///< Interface signal pointers
    std::map<uint64_t, uint64_t> mem;       ///< Memory storage

    bool wr_addr_received;                  ///< Write address received flag
    uint64_t wr_addr;                       ///< Received write address
    bool wr_data_received;                  ///< Write data received flag
    uint64_t wr_data;                       ///< Received write data
    bool wr_resp_sent;                      ///< Write response sent flag

    bool rd_addr_received;                  ///< Read address received flag
    uint64_t rd_addr;                       ///< Received read address
    bool rd_data_sent;                      ///< Read data sent flag
    uint64_t rd_data_reg;                   ///< Read data register

    /// @brief Constructor
    axil_slave(axil_slave_ptr<DATA_WIDTH, ADDR_WIDTH> port) : port(port) {
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
            uint64_t rdata = 0;
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
        *(port.rdata)   = rd_data_reg;
        *(port.rresp)   = OKAY;
    }
};

#endif