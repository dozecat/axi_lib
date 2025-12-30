/******************************************************************************
 * Copyright (C) 2025 WanderingKitsune. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axi_master.hpp
 * @brief       AXI4 Master VIP
 * @see         https://github.com/WanderingKitsune/axi_lib.git
 *
 * @details     This module implements the Master VIP for AXI4 protocol verification.
 *
 * Modification History:
 * Ver   Who  Date        Changes
 * ----  ---- ----------  -----------------------------------------------------
 * 1.0        2025/12/30  Initial release
 ******************************************************************************/

#ifndef AXI_MASTER_HPP
#define AXI_MASTER_HPP

#include "axi.hpp"
#include "axi_common.hpp"
#include <queue>
#include <vector>
#include <iostream>
#include <type_traits>

/// @brief AXI Master BFM
template <
    size_t DATA_WIDTH = 32,
    size_t ADDR_WIDTH = 32,
    size_t ID_WIDTH = 16
>
class axi_master {
public:
    axi_master_ptr<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH> port;

    struct WriteTransaction {
        uint64_t addr;
        std::vector<uint8_t> data;
        uint32_t len; // Burst length (0-based, so 0 means 1 beat)
        uint8_t burst; // 0=FIXED, 1=INCR, 2=WRAP
    };

    struct ReadTransaction {
        uint64_t addr;
        uint32_t len; // Burst length (0-based)
        uint8_t burst; // 0=FIXED, 1=INCR, 2=WRAP
    };

    std::queue<WriteTransaction> wr_q;
    std::queue<ReadTransaction> rd_q;
    std::queue<std::vector<uint8_t>> rd_data_q;
    std::vector<uint8_t> current_rd_burst;

    bool wr_active;
    bool rd_active;

    // Handshake flags
    bool aw_hs, w_hs, b_hs, ar_hs, r_hs;
    
    // Burst tracking
    uint32_t w_beat_count;
    uint32_t r_beat_count;

    /// @brief Constructor
    /// @param port Interface signals pointer
    axi_master(axi_master_ptr<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH> port) : port(port) {
        clear();
        wr_active = false;
        rd_active = false;
        aw_hs = false;
        w_hs = false;
        b_hs = false;
        ar_hs = false;
        r_hs = false;
        w_beat_count = 0;
        r_beat_count = 0;
    }

    /// @brief Reset all signals
    void clear() {
        waddr_clr();
        wdata_clr();
        raddr_clr();
        rdata_clr();
        rresp_clr();
    }

    /// @brief Write data using FIXED burst type
    /// @param addr Start address
    /// @param data Data to write
    void write_fixed(uint64_t addr, const std::vector<uint8_t>& data) {
        if (data.empty()) return;
        WriteTransaction t;
        t.addr = addr;
        t.data = data;
        size_t bytes_per_beat = DATA_WIDTH/8;
        t.len = (data.size() + bytes_per_beat - 1) / bytes_per_beat - 1;
        t.burst = 0; // FIXED
        wr_q.push(t);
    }

    /// @brief Write data using INCR burst type
    /// @param addr Start address
    /// @param data Data to write
    void write_incr(uint64_t addr, const std::vector<uint8_t>& data) {
        if (data.empty()) return;
        WriteTransaction t;
        t.addr = addr;
        t.data = data;
        size_t bytes_per_beat = DATA_WIDTH/8;
        t.len = (data.size() + bytes_per_beat - 1) / bytes_per_beat - 1;
        t.burst = 1; // INCR
        wr_q.push(t);
    }

    /// @brief Write data using WRAP burst type
    /// @param addr Start address
    /// @param data Data to write
    void write_wrap(uint64_t addr, const std::vector<uint8_t>& data) {
        if (data.empty()) return;
        WriteTransaction t;
        t.addr = addr;
        t.data = data;
        size_t bytes_per_beat = DATA_WIDTH/8;
        t.len = (data.size() + bytes_per_beat - 1) / bytes_per_beat - 1;
        t.burst = 2; // WRAP
        wr_q.push(t);
    }

    /// @brief Request a read transaction (FIXED)
    /// @param addr Address
    /// @param len Burst length (0-based)
    void read_fixed(uint64_t addr, uint32_t len = 0) {
        ReadTransaction t;
        t.addr = addr;
        t.len = len;
        t.burst = 0; // FIXED
        rd_q.push(t);
    }

    /// @brief Request a read transaction (INCR)
    /// @param addr Address
    /// @param len Burst length (0-based)
    void read_incr(uint64_t addr, uint32_t len = 0) {
        ReadTransaction t;
        t.addr = addr;
        t.len = len;
        t.burst = 1; // INCR
        rd_q.push(t);
    }

    /// @brief Request a read transaction (WRAP)
    /// @param addr Address
    /// @param len Burst length (0-based)
    void read_wrap(uint64_t addr, uint32_t len = 0) {
        ReadTransaction t;
        t.addr = addr;
        t.len = len;
        t.burst = 2; // WRAP
        rd_q.push(t);
    }

    /// @brief Get received read data
    /// @param data Output vector
    /// @return true if data available
    bool get_read_data(std::vector<uint8_t> &data) {
        if (rd_data_q.empty()) return false;
        data = rd_data_q.front();
        rd_data_q.pop();
        return true;
    }

private:
    // Internal helpers
    uint8_t get_axsize() {
        size_t bytes = DATA_WIDTH / 8;
        uint8_t size = 0;
        while (bytes >>= 1) size++;
        return size;
    }

    void waddr_set(uint64_t addr, uint32_t len, uint8_t burst) {
        *(port.awaddr)  = addr;
        *(port.awvalid) = true;
        *(port.awburst) = burst;
        *(port.awcache) = 0;
        *(port.awid)    = 0;
        *(port.awlen)   = len;
        *(port.awlock)  = 0;
        *(port.awprot)  = 0;
        *(port.awqos)   = 0;
        *(port.awregion)= 0;
        *(port.awsize)  = get_axsize();
    }

    void waddr_clr() {
        *(port.awaddr)  = 0;
        *(port.awvalid) = false;
        *(port.awlen)   = 0;
    }

    void wdata_set(const std::vector<uint8_t>& data, uint32_t beat, bool last) {
        size_t bytes_per_beat = DATA_WIDTH/8;
        size_t start_idx = beat * bytes_per_beat;
        
        signal_set(port.wdata, data, start_idx, bytes_per_beat);

        // Calculate strobe based on valid data bytes in this beat
        size_t bytes_in_this_beat = 0;
        if (start_idx < data.size()) {
            bytes_in_this_beat = data.size() - start_idx;
            if (bytes_in_this_beat > bytes_per_beat) bytes_in_this_beat = bytes_per_beat;
        }

        // Strobe width in bits is bytes_per_beat
        // Strobe width in bytes (for storage)
        size_t strb_vec_size = (bytes_per_beat + 7) / 8;
        std::vector<uint8_t> strb_val(strb_vec_size, 0);

        for (size_t i = 0; i < bytes_in_this_beat; ++i) {
            strb_val[i / 8] |= (1 << (i % 8));
        }

        signal_set(port.wstrb, strb_val, 0, strb_vec_size);

        *(port.wvalid)  = true;
        *(port.wlast)   = last;
        *(port.wid)     = 0;
    }

    void wdata_clr() {
        signal_clr(port.wdata);
        *(port.wstrb)   = 0;
        *(port.wvalid)  = false;
        *(port.wlast)   = false;
    }

    void rresp_set() {
        *(port.bready)  = true;
    }

    void rresp_clr() {
        *(port.bready)  = false;
        wr_active = false;
    }

    void raddr_set(uint64_t addr, uint32_t len, uint8_t burst) {
        *(port.araddr)  = addr;
        *(port.arvalid) = true;
        *(port.arburst) = burst;
        *(port.arcache) = 0;
        *(port.arid)    = 0;
        *(port.arlen)   = len;
        *(port.arlock)  = 0;
        *(port.arprot)  = 0;
        *(port.arqos)   = 0;
        *(port.arregion)= 0;
        *(port.arsize)  = get_axsize();
    }

    void raddr_clr() {
        *(port.araddr)  = 0;
        *(port.arvalid) = false;
        *(port.arlen)   = 0;
    }

    void rdata_set() {
        *(port.rready)  = true;
    }

    void rdata_clr() {
        *(port.rready)  = false;
    }

public:
    /// @brief Cycle tick
    void tick() {
        // Write Channel
        if (!wr_active && !wr_q.empty()) {
            wr_active = true;
            w_beat_count = 0;
            aw_hs = false;
            w_hs = false;
            b_hs = false;
            
            WriteTransaction& t = wr_q.front();
            waddr_set(t.addr, t.len, t.burst);
            wdata_set(t.data, 0, (t.len == 0));
        } else if (wr_active) {
            WriteTransaction& t = wr_q.front();

            // AW Handshake
            if (!aw_hs && *(port.awready) && *(port.awvalid)) {
                aw_hs = true;
            } else if (aw_hs) {
                waddr_clr();
            }

            // W Handshake
            if (!w_hs && *(port.wready) && *(port.wvalid)) {
                w_beat_count++;
                if (w_beat_count > t.len) {
                    w_hs = true;
                } else {
                    // Next beat
                    bool last = (w_beat_count == t.len);
                    wdata_set(t.data, w_beat_count, last);
                }
            } else if (w_hs) {
                wdata_clr();
            }

            // B Handshake
            if (aw_hs && w_hs) {
                if (!b_hs) {
                    rresp_set();
                    if (*(port.bvalid) && *(port.bready)) {
                        b_hs = true;
                        std::cout << "[AXI-MST] " << burst_to_string(t.burst) << " WR success !" << std::endl;
                        std::cout << "ADDR:0x" << std::hex << t.addr 
                                  << "  LEN:" << std::dec << t.len 
                                  << "  SIZE:" << t.data.size() << "  DATA:" << std::endl;
                        print_data(t.data);
                        std::cout << std::endl;
                    }
                } else {
                    rresp_clr();
                    wr_q.pop(); // Transaction done
                    wr_active = false; // Reset active flag
                }
            }
        }

        // Read Channel
        if (!rd_active && !rd_q.empty()) {
            rd_active = true;
            ar_hs = false;
            r_hs = false;
            r_beat_count = 0;
            current_rd_burst.clear();
            
            ReadTransaction& t = rd_q.front();
            raddr_set(t.addr, t.len, t.burst);
        } else if (rd_active) {
            ReadTransaction& t = rd_q.front();

            // AR Handshake
            bool ar_hs_edge = false;
            if (!ar_hs && *(port.arready) && *(port.arvalid)) {
                ar_hs = true;
                ar_hs_edge = true;
                rdata_set();
            } else if (ar_hs) {
                raddr_clr();
            }

            // R Handshake
            if (ar_hs && !ar_hs_edge) {
                if (!r_hs && *(port.rvalid) && *(port.rready)) {
                    size_t bytes_per_beat = DATA_WIDTH/8;
                    
                    std::vector<uint8_t> beat_data;
                    signal_get(port.rdata, beat_data, bytes_per_beat);
                    
                    current_rd_burst.insert(current_rd_burst.end(), beat_data.begin(), beat_data.end());

                    if (*(port.rlast)) {
                        r_hs = true;
                        rd_data_q.push(current_rd_burst);
                        std::cout << "[AXI-MST] " << burst_to_string(t.burst) << " RD success !" << std::endl;
                        std::cout << "ADDR:0x" << std::hex << t.addr 
                                  << "  LEN:" << std::dec << t.len 
                                  << "  SIZE:" << current_rd_burst.size() << "  DATA:" << std::endl;
                        print_data(current_rd_burst);
                        std::cout << std::endl;
                    }
                } else if (r_hs) {
                    rdata_clr();
                    rd_active = false;
                    rd_q.pop();
                }
            }
        }
    }
};

#endif
