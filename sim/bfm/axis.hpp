/******************************************************************************
 * Copyright (C) 2025 WanderingKitsune. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * @file        axis.hpp
 * @brief       AXI4-Stream Master/Slave Bus Functional Model (BFM)
 * @see         https://github.com/WanderingKitsune/axi_lib.git
 *
 * @details     This module implements a Bus Functional Model for AXI4-Stream
 *              protocol verification, supporting both master and slave roles.
 *
 * Modification History:
 * Ver   Who  Date        Changes
 * ----  ---- ----------  -----------------------------------------------------
 * 1.0        2025/12/25  Initial release
 ******************************************************************************/

#ifndef AXIS_HPP
#define AXIS_HPP
#include <cstdint>
#include <set>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>
#include <iomanip>
#include "sig.hpp"

// Helper to print data in hex dump format
static void print_data(const std::vector<uint8_t>& data) {
    for (size_t i = 0; i < data.size(); ++i) {
        if (i > 0 && i % 16 == 0) std::cout << std::endl;
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)data[i] << " ";
    }
    std::cout << std::endl;
}

/// @brief AXI4-Stream interface signals pointer structure
template <
    size_t DATA_WIDTH = 64,
    size_t ID_WIDTH = 8,
    size_t DEST_WIDTH = 1,
    size_t USER_WIDTH = 1
>
struct axis_ptr {
    sig(*tdata , DATA_WIDTH-1  , 0) = NULL;
    sig(*tkeep , DATA_WIDTH/8-1, 0) = NULL;
    sig(*tstrb , DATA_WIDTH/8-1, 0) = NULL;
    sig(*tid   , ID_WIDTH-1    , 0) = NULL;
    sig(*tdest , DEST_WIDTH-1  , 0) = NULL;
    sig(*tuser , USER_WIDTH-1  , 0) = NULL;
    sig(*tlast , 0             , 0) = NULL;
    sig(*tvalid, 0             , 0) = NULL;
    sig(*tready, 0             , 0) = NULL;

    /// @brief Check if all signal pointers are assigned
    bool check() {
        std::set <void*> s;
        s.insert((void*)tdata  );
        s.insert((void*)tkeep  );
        s.insert((void*)tstrb  );
        s.insert((void*)tid    );
        s.insert((void*)tdest  );
        s.insert((void*)tuser  );
        s.insert((void*)tlast  );
        s.insert((void*)tvalid );
        s.insert((void*)tready );
        return s.size() == 9 && s.count(NULL) == 0;
    }
};

/// @brief AXI4-Stream Master BFM
template <uint32_t DATA_WIDTH = 64>
class axis_master {
public:
    std::vector<uint8_t> tx_buf;            ///< Current transaction buffer
    size_t tx_buf_idx;                      ///< Current index in tx_buf
    std::queue<std::vector<uint8_t>> tx_queue;///< Queue of pending transactions
    axis_ptr<DATA_WIDTH> port;              ///< Interface signal pointers
    bool tx_tuser;                          ///< TUSER value for current transaction
    int byte_width;                         ///< Data width in bytes

    /// @brief Constructor
    axis_master(axis_ptr<DATA_WIDTH> port):port(port) {
        tx_tuser = false;
        byte_width = DATA_WIDTH/8;
        tx_buf_idx = 0;
    }

    /// @brief Destructor
    ~axis_master() {
        tx_buf.clear();
        while (!tx_queue.empty()) tx_queue.pop();
    }

    /// @brief Send data through AXI Stream
    /// @param with_tuser Assert TUSER (e.g. for frame start/end indication)
    void send(const char *src_buf, ssize_t size, bool with_tuser = false) {
        std::vector<uint8_t> cur_buf;
        for (int i=0;i<size;i++) cur_buf.push_back((uint8_t)src_buf[i]);
        tx_queue.push(cur_buf);
        if ( with_tuser ) tx_tuser = true;
    }

    /// @brief Set the TUSER signal value
    void set_tuser(uint32_t src_tuser) {
        *(port.tuser) = src_tuser;
    }

    /// @brief Get the current TREADY state
    bool get_tready() {
        return *(port.tready);
    }

    /// @brief Master simulation tick function
    void tick() {
        if (*(port.tready)) {
            *(port.tvalid) = false;
            // start new transaction
            if (tx_buf.empty() && !tx_queue.empty()) {
                tx_buf = tx_queue.front();
                tx_queue.pop();
                tx_buf_idx = 0;
            }
            if (!tx_buf.empty()) {
                int byte_pos = 0;
                *(port.tkeep) = 0;
                while (tx_buf_idx < tx_buf.size() && byte_pos < byte_width) {
                    *(port.tkeep) = *(port.tkeep) | (1 << byte_pos);
                    ((char*)port.tdata)[byte_pos] = tx_buf[tx_buf_idx];
                    tx_buf_idx++;
                    byte_pos++;
                }
                if (tx_tuser) {
                    *(port.tuser) = *(port.tuser) | 0x1;
                    tx_tuser = false;
                } else {
                    *(port.tuser) = *(port.tuser) & (~0x1);
                }
                
                bool last = (tx_buf_idx >= tx_buf.size());
                *(port.tlast) = last;
                *(port.tvalid) = true;

                if (last) {
                    std::cout << "[AXIS-MST] SEND success !" << std::endl;
                    std::cout << "SIZE:" << std::dec << tx_buf.size() << "  DATA:" << std::endl;
                    print_data(tx_buf);
                    std::cout << std::endl;
                    tx_buf.clear();
                    tx_buf_idx = 0;
                }
            }
        }
    }
};

/// @brief AXI4-Stream Slave BFM
template <uint32_t DATA_WIDTH = 64>
class axis_slave {
public:
    std::vector<uint8_t> recv_buf;          ///< Buffer for currently receiving packet
    std::queue<std::vector<uint8_t>> rx_queue;///< Queue of received packets
    axis_ptr<DATA_WIDTH> port;              ///< Interface signal pointers

    /// @brief Constructor
    axis_slave(axis_ptr<DATA_WIDTH> port):port(port) {
        *(port.tready) = true; // always tready
    }

    /// @brief Destructor
    ~axis_slave() {
        recv_buf.clear();
    }

    /// @brief Check if there is valid data received
    bool has_valid_data() {
        return !rx_queue.empty();
    }

    /// @brief Receive data from the internal queue
    /// @return Number of bytes actually read, or -1 if empty
    ssize_t recv(int max_size, char *dst_buf) {
        if (rx_queue.empty()) {
            return -1;
        } else {
            std::vector<uint8_t> data = rx_queue.front();
            rx_queue.pop();
            size_t copy_size = (data.size() <= (size_t)max_size) ? data.size() : (size_t)max_size;
            for (size_t i = 0; i < copy_size; i++) {
                dst_buf[i] = (char)data[i];
            }
            return copy_size;
        }
    }

    /// @brief Slave simulation tick function
    void tick() {
        if (*(port.tvalid)) {
            for (int i=0;i<DATA_WIDTH/8;i++) {
                if ((*port.tkeep & (1 << i)) != 0) {
                    recv_buf.push_back(((char*)port.tdata)[i]);
                }
            }
            if (*(port.tlast)) {
                rx_queue.push(recv_buf);
                std::cout << "[AXIS-SLV] RECV success !" << std::endl;
                std::cout << "SIZE:" << std::dec << recv_buf.size() << "  DATA:" << std::endl;
                print_data(recv_buf);
                std::cout << std::endl;
                recv_buf.clear();
            }
        }
    }
};

#endif

