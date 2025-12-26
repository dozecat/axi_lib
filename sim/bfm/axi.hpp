/******************************************************************************
 * Copyright (C) 2025 WanderingKitsune. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axi.hpp
 * @brief       AXI4 Master/Slave Bus Functional Model (BFM)
 * @see         https://github.com/WanderingKitsune/axi_lib.git
 *
 * @details     This module implements a Bus Functional Model for AXI4
 *              protocol verification, supporting both master and slave roles.
 *
 * Modification History:
 * Ver   Who  Date        Changes
 * ----  ---- ----------  -----------------------------------------------------
 * 1.0        2025/12/26  Initial release
 ******************************************************************************/

#ifndef AXI_HPP
#define AXI_HPP

#include <cstdint>
#include <set>
#include <cstring>
#include <queue>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <type_traits>
#include "sig.hpp"

// Trait to detect if T is VlWide (has m_storage)
template <typename T, typename = void>
struct is_vlwide : std::false_type {};

template <typename T>
struct is_vlwide<T, typename std::enable_if<sizeof(decltype(std::declval<T>().m_storage)) != 0>::type> : std::true_type {};

// Generic implementation for primitive types (CData, SData, IData, QData)
template <typename T>
typename std::enable_if<!is_vlwide<T>::value>::type
signal_set(T* sig, const std::vector<uint8_t>& data, size_t start_byte, size_t num_bytes) {
    uint64_t val = 0;
    for (size_t i = 0; i < num_bytes && i < 8; ++i) {
        if (start_byte + i < data.size()) {
            val |= ((uint64_t)data[start_byte + i] << (i * 8));
        }
    }
    *sig = (T)val;
}

template <typename T>
typename std::enable_if<!is_vlwide<T>::value>::type
signal_get(T* sig, std::vector<uint8_t>& data, size_t num_bytes) {
    uint64_t val = *sig;
    for (size_t i = 0; i < num_bytes; ++i) {
        data.push_back((val >> (i * 8)) & 0xFF);
    }
}

template <typename T>
typename std::enable_if<!is_vlwide<T>::value>::type
signal_clr(T* sig) {
    *sig = 0;
}

// Overloads for VlWide
template <typename T>
typename std::enable_if<is_vlwide<T>::value>::type
signal_set(T* sig, const std::vector<uint8_t>& data, size_t start_byte, size_t num_bytes) {
    // T is VlWide<N>
    int N = sizeof((*sig).m_storage) / sizeof(uint32_t);
    for (int w = 0; w < N; ++w) {
        uint32_t word_val = 0;
        for (int b = 0; b < 4; ++b) {
            size_t byte_idx = w * 4 + b;
            if (byte_idx < num_bytes) {
                if (start_byte + byte_idx < data.size()) {
                    word_val |= ((uint32_t)data[start_byte + byte_idx] << (b * 8));
                }
            }
        }
        (*sig).m_storage[w] = word_val;
    }
}

template <typename T>
typename std::enable_if<is_vlwide<T>::value>::type
signal_get(T* sig, std::vector<uint8_t>& data, size_t num_bytes) {
    int N = sizeof((*sig).m_storage) / sizeof(uint32_t);
    for (size_t i = 0; i < num_bytes; ++i) {
        int w = i / 4;
        int b = i % 4;
        if (w < N) {
            uint32_t word_val = (*sig).m_storage[w];
            data.push_back((word_val >> (b * 8)) & 0xFF);
        } else {
            data.push_back(0);
        }
    }
}

template <typename T>
typename std::enable_if<is_vlwide<T>::value>::type
signal_clr(T* sig) {
    int N = sizeof((*sig).m_storage) / sizeof(uint32_t);
    for(int i=0; i<N; ++i) (*sig).m_storage[i] = 0;
}

// Helper to convert burst type to string
static std::string burst_to_string(uint8_t b) {
    switch(b) {
        case 0: return "FIXED";
        case 1: return "INCR";
        case 2: return "WRAP";
        default: return "RSVD";
    }
}

// Helper to print data in hex dump format
static void print_data(const std::vector<uint8_t>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        if (i > 0 && i % 16 == 0) std::cout << std::endl;
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)data[i] << " ";
    }
    std::cout << std::endl;
}

/// @brief AXI Interface signals pointer structure
/// Holds pointers to the actual Verilator signals
template <
    size_t DATA_WIDTH = 32,
    size_t ADDR_WIDTH = 32,
    size_t ID_WIDTH = 16
>
struct axi_ptr {
    // Constants for signal widths
    static constexpr size_t LEN_WIDTH  = 8;
    static constexpr size_t LOCK_WIDTH = 1;
    static constexpr size_t QOS_WIDTH  = 4;
    static constexpr size_t REGION_WIDTH = 4;

    // Write Address Channel
    sig(*awaddr   , ADDR_WIDTH-1  , 0) = NULL; ///< Write address
    sig(*awburst  , 1             , 0) = NULL; ///< Burst type
    sig(*awcache  , 3             , 0) = NULL; ///< Cache type
    sig(*awid     , ID_WIDTH-1    , 0) = NULL; ///< Write address ID
    sig(*awlen    , LEN_WIDTH-1   , 0) = NULL; ///< Burst length
    sig(*awlock   , LOCK_WIDTH-1  , 0) = NULL; ///< Lock type
    sig(*awprot   , 2             , 0) = NULL; ///< Protection type
    sig(*awqos    , QOS_WIDTH-1   , 0) = NULL; ///< Quality of Service
    sig(*awready  , 0             , 0) = NULL; ///< Write address ready
    sig(*awregion , REGION_WIDTH-1, 0) = NULL; ///< Region identifier
    sig(*awsize   , 2             , 0) = NULL; ///< Burst size
    sig(*awvalid  , 0             , 0) = NULL; ///< Write address valid

    // Write Data Channel
    sig(*wdata    , DATA_WIDTH-1  , 0) = NULL; ///< Write data
    sig(*wid      , ID_WIDTH-1    , 0) = NULL; ///< Write ID
    sig(*wlast    , 0             , 0) = NULL; ///< Write last
    sig(*wready   , 0             , 0) = NULL; ///< Write ready
    sig(*wstrb    , DATA_WIDTH/8-1, 0) = NULL; ///< Write strobes
    sig(*wvalid   , 0             , 0) = NULL; ///< Write valid

    // Write Response Channel
    sig(*bid      , ID_WIDTH-1    , 0) = NULL; ///< Response ID
    sig(*bready   , 0             , 0) = NULL; ///< Response ready
    sig(*bresp    , 1             , 0) = NULL; ///< Write response
    sig(*bvalid   , 0             , 0) = NULL; ///< Response valid

    // Read Address Channel
    sig(*araddr   , ADDR_WIDTH-1  , 0) = NULL; ///< Read address
    sig(*arburst  , 1             , 0) = NULL; ///< Burst type
    sig(*arcache  , 3             , 0) = NULL; ///< Cache type
    sig(*arid     , ID_WIDTH-1    , 0) = NULL; ///< Read address ID
    sig(*arlen    , LEN_WIDTH-1   , 0) = NULL; ///< Burst length
    sig(*arlock   , LOCK_WIDTH-1  , 0) = NULL; ///< Lock type
    sig(*arprot   , 2             , 0) = NULL; ///< Protection type
    sig(*arqos    , QOS_WIDTH-1   , 0) = NULL; ///< Quality of Service
    sig(*arready  , 0             , 0) = NULL; ///< Read address ready
    sig(*arregion , REGION_WIDTH-1, 0) = NULL; ///< Region identifier
    sig(*arsize   , 2             , 0) = NULL; ///< Burst size
    sig(*arvalid  , 0             , 0) = NULL; ///< Read address valid

    // Read Data Channel
    sig(*rdata    , DATA_WIDTH-1  , 0) = NULL; ///< Read data
    sig(*rid      , ID_WIDTH-1    , 0) = NULL; ///< Read ID
    sig(*rlast    , 0             , 0) = NULL; ///< Read last
    sig(*rready   , 0             , 0) = NULL; ///< Read ready
    sig(*rresp    , 1             , 0) = NULL; ///< Read response
    sig(*rvalid   , 0             , 0) = NULL; ///< Read valid

    /// @brief Check if all signal pointers are assigned
    /// @return true if all signals are non-NULL
    bool check() {
        std::set<void*> s;
        s.insert((void*)awaddr); s.insert((void*)awburst); s.insert((void*)awcache);
        s.insert((void*)awid);   s.insert((void*)awlen);   s.insert((void*)awlock);
        s.insert((void*)awprot); s.insert((void*)awqos);   s.insert((void*)awready);
        s.insert((void*)awregion); s.insert((void*)awsize); s.insert((void*)awvalid);

        s.insert((void*)wdata);  s.insert((void*)wid);     s.insert((void*)wlast);
        s.insert((void*)wready); s.insert((void*)wstrb);   s.insert((void*)wvalid);

        s.insert((void*)bid);    s.insert((void*)bready);  s.insert((void*)bresp);
        s.insert((void*)bvalid);

        s.insert((void*)araddr); s.insert((void*)arburst); s.insert((void*)arcache);
        s.insert((void*)arid);   s.insert((void*)arlen);   s.insert((void*)arlock);
        s.insert((void*)arprot); s.insert((void*)arqos);   s.insert((void*)arready);
        s.insert((void*)arregion); s.insert((void*)arsize); s.insert((void*)arvalid);

        s.insert((void*)rdata);  s.insert((void*)rid);     s.insert((void*)rlast);
        s.insert((void*)rready); s.insert((void*)rresp);   s.insert((void*)rvalid);

        // Total signals: 12 (AW) + 6 (W) + 4 (B) + 12 (AR) + 6 (R) = 40
        return s.size() == 40 && s.count(NULL) == 0;
    }
};

/// @brief AXI Master BFM
template <
    size_t DATA_WIDTH = 32,
    size_t ADDR_WIDTH = 32,
    size_t ID_WIDTH = 16
>
class axi_master {
public:
    axi_ptr<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH> port;

    struct WriteTransaction {
        uint64_t addr;
        std::vector<uint8_t> data;
        uint32_t len; // Burst length (0-based, so 0 means 1 beat)
        uint8_t burst; // 0=FIXED, 1=INCR, 2=WRAP
    };

    struct ReadTransaction {
        uint64_t addr;
        uint32_t len; // Burst length (0-based)
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
    axi_master(axi_ptr<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH> port) : port(port) {
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

    /// @brief Write data using INCR burst type
    /// @param addr Start address
    /// @param data Data to write
    void write_burst_incr(uint64_t addr, const std::vector<uint8_t>& data) {
        if (data.empty()) return;
        WriteTransaction t;
        t.addr = addr;
        t.data = data;
        size_t bytes_per_beat = DATA_WIDTH/8;
        t.len = (data.size() + bytes_per_beat - 1) / bytes_per_beat - 1;
        t.burst = 1; // INCR
        wr_q.push(t);
    }

    /// @brief Write data using FIXED burst type
    /// @param addr Start address
    /// @param data Data to write
    void write_burst_fixed(uint64_t addr, const std::vector<uint8_t>& data) {
        if (data.empty()) return;
        WriteTransaction t;
        t.addr = addr;
        t.data = data;
        size_t bytes_per_beat = DATA_WIDTH/8;
        t.len = (data.size() + bytes_per_beat - 1) / bytes_per_beat - 1;
        t.burst = 0; // FIXED
        wr_q.push(t);
    }

    /// @brief Helper for scalar write (automatically converts to vector)
    /// @tparam T Integer type
    /// @param addr Address
    /// @param data Scalar data
    template <typename T>
    typename std::enable_if<std::is_integral<T>::value>::type
    write(uint64_t addr, T data) {
        std::vector<uint8_t> bytes(sizeof(T));
        for(size_t i=0; i<sizeof(T); i++) bytes[i] = (data >> (i*8)) & 0xFF;
        write_burst_incr(addr, bytes);
    }

    /// @brief Helper for vector write (defaults to INCR)
    /// @param addr Address
    /// @param data Data vector
    void write(uint64_t addr, const std::vector<uint8_t>& data) {
        write_burst_incr(addr, data);
    }

    /// @brief Request a read transaction
    /// @param addr Address
    /// @param len Burst length (0-based)
    void read(uint64_t addr, uint32_t len = 0) {
        ReadTransaction t;
        t.addr = addr;
        t.len = len;
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

    void raddr_set(uint64_t addr, uint32_t len) {
        *(port.araddr)  = addr;
        *(port.arvalid) = true;
        *(port.arburst) = 1; // INCR
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
            raddr_set(t.addr, t.len);
        } else if (rd_active) {
            ReadTransaction& t = rd_q.front();

            // AR Handshake
            if (!ar_hs && *(port.arready) && *(port.arvalid)) {
                ar_hs = true;
                rdata_set();
            } else if (ar_hs) {
                raddr_clr();
            }

            // R Handshake
            if (ar_hs) {
                if (!r_hs && *(port.rvalid) && *(port.rready)) {
                    size_t bytes_per_beat = DATA_WIDTH/8;
                    
                    std::vector<uint8_t> beat_data;
                    signal_get(port.rdata, beat_data, bytes_per_beat);
                    
                    current_rd_burst.insert(current_rd_burst.end(), beat_data.begin(), beat_data.end());

                    if (*(port.rlast)) {
                        r_hs = true;
                        rd_data_q.push(current_rd_burst);
                        std::cout << "[AXI-MST] INCR RD success !" << std::endl;
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

/// @brief AXI Slave BFM
template <
    size_t DATA_WIDTH = 32,
    size_t ADDR_WIDTH = 32,
    size_t ID_WIDTH = 16
>
class axi_slave {
public:
    axi_ptr<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH> port;

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

    /// @brief Constructor
    /// @param port Interface signals pointer
    axi_slave(axi_ptr<DATA_WIDTH, ADDR_WIDTH, ID_WIDTH> port) : port(port) {
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
                uint64_t base_addr;
                if (aw_burst == 0) { // FIXED
                    base_addr = aw_addr;
                } else { // INCR
                    base_addr = aw_addr + w_beat_count * bytes_per_beat;
                }
                
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
            uint64_t current_addr = ar_addr + r_beat_count * bytes_per_beat;
            
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
