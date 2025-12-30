/******************************************************************************
 * Copyright (C) 2025 WanderingKitsune. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axi_slave.hpp
 * @brief       AXI4 Slave VIP
 * @see         https://github.com/WanderingKitsune/axi_lib.git
 *
 * @details     This module implements the Slave VIP for AXI4 protocol verification.
 *
 * Modification History:
 * Ver   Who  Date        Changes
 * ----  ---- ----------  -----------------------------------------------------
 * 1.0        2025/12/30  Initial release
 ******************************************************************************/

#ifndef AXI_SLAVE_HPP
#define AXI_SLAVE_HPP

#include "axi.hpp"
#include "axi_common.hpp"
#include <map>
#include <vector>
#include <iostream>

/// @brief AXI Slave BFM
template <
    size_t DATA_WIDTH = 32,
    size_t ADDR_WIDTH = 32,
    size_t ID_WIDTH = 16
>
class axi_slave {
public:
    axi_slave_ptr<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH> port;

    std::map<uint64_t, uint8_t> mem; // Byte-addressable memory
    
    // State variables
    bool aw_latch;
    bool w_active;
    uint64_t aw_addr;
    uint32_t aw_len;
    uint32_t aw_id;
    uint8_t aw_burst;
    uint32_t w_beat_count;
    bool w_done_pending;
    std::vector<uint8_t> w_data_accum;

    bool ar_latch;
    bool r_active;
    uint64_t ar_addr;
    uint32_t ar_len;
    uint32_t ar_id;
    uint8_t ar_burst;
    uint32_t r_beat_count;
    bool r_done_pending;
    std::vector<uint8_t> r_data_accum;

    /// @brief Calculate address for current beat
    uint64_t get_addr(uint64_t start_addr, uint32_t beat, uint32_t len, uint8_t burst, size_t bytes_per_beat) {
        if (burst == 0) { // FIXED
            return start_addr;
        } else if (burst == 1) { // INCR
            return start_addr + beat * bytes_per_beat;
        } else if (burst == 2) { // WRAP
            uint64_t total_bytes = bytes_per_beat * (len + 1);
            uint64_t lower_wrap_boundary = (start_addr / total_bytes) * total_bytes;
            uint64_t current_offset = (start_addr % total_bytes) + (beat * bytes_per_beat);
            return lower_wrap_boundary + (current_offset % total_bytes);
        }
        return start_addr;
    }

    /// @brief Constructor
    /// @param port Interface signals pointer
    axi_slave(axi_slave_ptr<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH> port) : port(port) {
        clear();
        aw_latch = false;
        w_active = false;
        w_done_pending = false;
        ar_latch = false;
        r_active = false;
        r_done_pending = false;
    }

    /// @brief Reset all signals
    void clear() {
        *(port.awready) = false;
        *(port.wready)  = false;
        *(port.bvalid)  = false;
        *(port.bresp)   = 0;
        *(port.bid)     = 0;

        *(port.arready) = false;
        *(port.rvalid)  = false;
        
        signal_clr(port.rdata);
        
        *(port.rresp)   = 0;
        *(port.rlast)   = false;
        *(port.rid)     = 0;
    }

    /// @brief Cycle tick
    void tick() {
        // Write Channel
        // AW Phase
        if (!aw_latch) {
            *(port.awready) = true;
            if (*(port.awvalid)) {
                aw_addr = *(port.awaddr);
                aw_id = *(port.awid);
                aw_len = *(port.awlen);
                aw_burst = *(port.awburst);
                aw_latch = true;
                w_active = true;
                w_beat_count = 0;
                w_data_accum.clear();
            }
        } else {
            *(port.awready) = false;
        }

        // W Phase
        if (w_done_pending) {
            w_active = false;
            *(port.wready) = false;
            w_done_pending = false;
            
            // Trigger B Phase
            *(port.bvalid) = true;
            *(port.bresp) = 0; // OKAY
            *(port.bid) = aw_id;
            return; // Ensure BVALID is held for at least one cycle
        }

        if (w_active) {
            *(port.wready) = true;
            if (*(port.wvalid)) {
                size_t bytes_per_beat = DATA_WIDTH/8;
                uint64_t base_addr = get_addr(aw_addr, w_beat_count, aw_len, aw_burst, bytes_per_beat);
                
                std::vector<uint8_t> beat_data;
                signal_get(port.wdata, beat_data, bytes_per_beat);

                // Get strobes
                std::vector<uint8_t> strb_vec;
                size_t strb_width_bytes = (bytes_per_beat + 7) / 8;
                signal_get(port.wstrb, strb_vec, strb_width_bytes);

                for (size_t i=0; i<bytes_per_beat; i++) {
                    bool strb_bit = (strb_vec[i/8] >> (i%8)) & 1;
                    if (strb_bit) {
                        w_data_accum.push_back(beat_data[i]);
                        mem[base_addr + i] = beat_data[i];
                    }
                }
                
                w_beat_count++;
                
                if (*(port.wlast) || w_beat_count > aw_len) { // awlen is 0-based
                    w_done_pending = true;
                    // Keep wready=1 for this cycle so Master sees it
                    return;
                }
            }
        } else {
             *(port.wready) = false;
        }

        // B Phase
        if (*(port.bvalid) && *(port.bready)) {
            *(port.bvalid) = false;
            aw_latch = false; // Ready for next transaction
            std::cout << "[AXI-SLV] " << burst_to_string(aw_burst) << " WR success !" << std::endl;
            std::cout << "ADDR:0x" << std::hex << aw_addr 
                      << "  LEN:" << std::dec << aw_len 
                      << "  SIZE:" << w_data_accum.size() << "  DATA:" << std::endl;
            print_data(w_data_accum);
            std::cout << std::endl;
        }

        // Read Channel
        // AR Phase
        if (!ar_latch) {
            *(port.arready) = true;
            if (*(port.arvalid)) {
                ar_addr = *(port.araddr);
                ar_id = *(port.arid);
                ar_len = *(port.arlen);
                ar_burst = *(port.arburst);
                ar_latch = true;
                r_active = true;
                r_beat_count = 0;
                r_data_accum.clear();
            }
        } else {
            *(port.arready) = false;
        }

        // R Phase
        if (r_done_pending) {
            r_active = false;
            *(port.rvalid) = false;
            *(port.rlast) = false;
            ar_latch = false; // Ready for next transaction
            r_done_pending = false;
            std::cout << "[AXI-SLV] " << burst_to_string(ar_burst) << " RD success !" << std::endl;
            std::cout << "ADDR:0x" << std::hex << ar_addr 
                      << "  LEN:" << std::dec << ar_len 
                      << "  SIZE:" << r_data_accum.size() << "  DATA:" << std::endl;
            print_data(r_data_accum);
            std::cout << std::endl;
            return;
        }

        if (r_active) {
            size_t bytes_per_beat = DATA_WIDTH/8;
            uint64_t current_addr = get_addr(ar_addr, r_beat_count, ar_len, ar_burst, bytes_per_beat);
            
            std::vector<uint8_t> beat_data;
            beat_data.reserve(bytes_per_beat);
            
            for (size_t i=0; i<bytes_per_beat; i++) {
                if (mem.find(current_addr + i) != mem.end()) {
                    beat_data.push_back(mem[current_addr + i]);
                } else {
                    beat_data.push_back(0);
                }
            }
            
            signal_set(port.rdata, beat_data, 0, bytes_per_beat);
            
            *(port.rvalid) = true;
            *(port.rresp) = 0; // OKAY
            *(port.rid) = ar_id;
            
            bool last = (r_beat_count == ar_len);
            *(port.rlast) = last;

            if (*(port.rready)) {
                r_data_accum.insert(r_data_accum.end(), beat_data.begin(), beat_data.end());
                r_beat_count++;
                if (last) {
                    r_done_pending = true;
                    return;
                }
            }
        }
    }
};

#endif
