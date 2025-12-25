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
#include "sig.hpp"

/**
 * @brief AXI4-Stream interface signals pointer structure
 */
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

    /// Check if all signal pointers are assigned
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

/**
 * @brief AXI4-Stream Master BFM
 */
template <uint32_t DATA_WIDTH = 64>
class axis_master {
public:
    std::queue <char> tx_buf;               ///< Current transaction buffer
    std::queue <std::queue<char> > tx_queue;///< Queue of pending transactions
    axis_ptr<DATA_WIDTH> port;              ///< Interface signal pointers
    bool tx_tuser;                          ///< TUSER value for current transaction
    int byte_width;                         ///< Data width in bytes

    /// Constructor
    axis_master(axis_ptr<DATA_WIDTH> port):port(port) {
        tx_tuser = false;
        byte_width = DATA_WIDTH/8;
        std::cerr << "[AXIS-MST][INFO] axis_master constructed." << std::endl;
    }

    /// Destructor
    ~axis_master() {
        while (!tx_buf.empty()) tx_buf.pop();
        while (!tx_queue.empty()) tx_queue.pop();
        std::cerr << "[AXIS-MST][INFO] axis_master destructed." << std::endl;
    }

    /**
     * @brief Send data through AXI Stream
     * @param with_tuser Assert TUSER (e.g. for frame start/end indication)
     */
    void send(const char *src_buf, ssize_t size, bool with_tuser = false) {
        std::queue <char> cur_buf;
        for (int i=0;i<size;i++) cur_buf.push(*(src_buf++));
        tx_queue.push(cur_buf);
        if ( with_tuser ) tx_tuser = true;
        std::cerr << "[AXIS-MST][INFO] Sent " << size << " bytes." << std::endl;
    }

    /// Set the TUSER signal value
    void set_tuser(uint32_t src_tuser) {
        *(port.tuser) = src_tuser;
    }

    /// Get the current TREADY state
    bool get_tready() {
        return *(port.tready);
    }

    /// Master simulation tick function
    void tick() {
        if (*(port.tready)) {
            *(port.tvalid) = false;
            // start new transaction
            if (tx_buf.empty() && !tx_queue.empty()) {
                tx_buf = tx_queue.front();
                tx_queue.pop();
            }
            if (!tx_buf.empty()) {
                int byte_pos = 0;
                *(port.tkeep) = 0;
                while (!tx_buf.empty() && byte_pos < byte_width) {
                    *(port.tkeep) = *(port.tkeep) | (1 << byte_pos);
                    ((char*)port.tdata)[byte_pos] = tx_buf.front();
                    tx_buf.pop();
                    byte_pos++;
                }
                if (tx_tuser) {
                    *(port.tuser) = *(port.tuser) | 0x1;
                    tx_tuser = false;
                } else {
                    *(port.tuser) = *(port.tuser) & (~0x1);
                }
                *(port.tlast) = tx_buf.empty();
                *(port.tvalid) = true;
            }
        }
    }
};

/**
 * @brief AXI4-Stream Slave BFM
 */
template <uint32_t DATA_WIDTH = 64>
class axis_slave {
public:
    std::vector <char> recv_buf;            ///< Buffer for currently receiving packet
    std::queue <std::vector<char>> rx_queue;///< Queue of received packets
    axis_ptr<DATA_WIDTH> port;              ///< Interface signal pointers

    /// Constructor
    axis_slave(axis_ptr<DATA_WIDTH> port):port(port) {
        *(port.tready) = true; // always tready
        std::cerr << "[AXIS-SLV][INFO] axis_slave constructed." << std::endl;
    }

    /// Destructor
    ~axis_slave() {
        recv_buf.clear();
        std::cerr << "[AXIS-SLV][INFO] axis_slave destructed." << std::endl;
    }

    /// Check if there is valid data received
    bool has_valid_data() {
        return !rx_queue.empty();
    }

    /**
     * @brief Receive data from the internal queue
     * @return Number of bytes actually read, or -1 if empty
     */
    ssize_t recv(int max_size, char *dst_buf) {
        if (rx_queue.empty()) {
            std::cerr << "[AXIS-SLV][WARN] Receive buffer is empty." << std::endl;
            return -1;
        } else {
            std::vector<char> data = rx_queue.front();
            rx_queue.pop();
            size_t copy_size = (data.size() <= (size_t)max_size) ? data.size() : (size_t)max_size;
            for (size_t i = 0; i < copy_size; i++) {
                dst_buf[i] = data[i];
            }
            std::cerr << "[AXIS-SLV][INFO] Received " << copy_size << " bytes." << std::endl;
            return copy_size;
        }
    }

    /// Slave simulation tick function
    void tick() {
        if (*(port.tvalid)) {
            for (int i=0;i<DATA_WIDTH/8;i++) {
                if ((*port.tkeep & (1 << i)) != 0) {
                    recv_buf.push_back(((char*)port.tdata)[i]);
                }
            }
            if (*(port.tlast)) {
                rx_queue.push(recv_buf);
                recv_buf.clear();
            }
        }
    }
};

#endif

