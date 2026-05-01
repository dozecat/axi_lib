![Language](https://img.shields.io/badge/Language-SystemVerilog-blue.svg) ![Simulation](https://img.shields.io/badge/Simulation-Verilator-007ec6.svg) [![vaxivip](https://img.shields.io/badge/vaxivip-github-f34b7d.svg)](https://github.com/dozecat/vaxivip.git) ![License](https://img.shields.io/badge/License-MIT-yellow.svg)

[English](#en) | [中文](#cn)

---

<span id="en">axi_lib</span>
===========================

**axi_lib** is a SystemVerilog AXI interconnect RTL library for FPGA/ASIC designs. Simulation uses [Verilator](https://www.veripool.org/verilator/) with BFMs from [vaxivip](https://github.com/dozecat/vaxivip.git). It provides AXI4 and AXI4-Lite crossbar interconnects plus primitive components (arbiter, FIFOs, skid buffer) for building AXI-based systems.

## ✨ Features

| Module | Type | Description |
|--------|------|-------------|
| **`axi_interconnect`** (`rtl/axi_interconnect.sv`) | AXI4 Crossbar | Multi-master, multi-slave AXI4 interconnect with configurable address map, burst support (FIXED/INCR/WRAP), and per-port buffering |
| **`axil_interconnect`** (`rtl/axil_interconnect.sv`) | AXI4-Lite Crossbar | Multi-master, multi-slave AXI4-Lite interconnect with address decode, arbitration, and per-port buffering |
| **`arbiter`** (`rtl/arbiter.sv`) | Arbiter | Parameterizable fixed-priority arbiter |

## 🚀 Quick Start

### 1. Install Dependencies
```bash
# macOS (with Homebrew)
brew install verilator

# Ubuntu/Debian
sudo apt-get install verilator g++ make
```

### 2. Run AXI Interconnect Simulation
```bash
cd sim/tb/axi_interconnect
make sim
```

### 3. Run AXI4-Lite Interconnect Simulation
```bash
cd sim/tb/axil_interconnect
make sim
```

### 4. View Waveform (optional)
```bash
make waves    # requires gtkwave
```

## 📖 Project Structure

```
.
├── rtl/                        # RTL source
│   ├── if_axi.sv               # AXI4 interface (modport master/slave)
│   ├── if_axil.sv              # AXI4-Lite interface
│   ├── if_axis.sv              # AXI4-Stream interface
│   ├── axi_interconnect.sv     # AXI4 crossbar interconnect
│   ├── axil_interconnect.sv    # AXI4-Lite crossbar interconnect
│   ├── arbiter.sv              # Priority arbiter
│   ├── sync_fifo.v             # Synchronous FIFO
│   ├── async_fifo.v            # Asynchronous FIFO (dual-clock)
│   └── skid_buffer.v           # Pipeline skid buffer
├── sim/
│   ├── bfm/                    # C++ BFMs
│   │   ├── axi/                # AXI4 master/slave/ptr/common
│   │   ├── axil/               # AXI4-Lite master/slave/ptr
│   │   ├── axis/               # AXI4-Stream master/slave/prt
│   │   ├── log.hpp             # Colored logging
│   │   └── sig.hpp             # Signal type helpers
│   └── tb/                     # Testbenches
│       ├── axi_interconnect/   # AXI4 crossbar TB
│       └── axil_interconnect/  # AXI4-Lite crossbar TB
├── AGENTS.md
└── README.md
```

## 🧩 RTL Modules

### AXI Interconnect (`axi_interconnect`)

Configurable master/slave to AXI connector with:
- **FIXED**, **INCR**, **WRAP** burst types
- Per-master and per-slave output buffering with configurable depth
- Slave address decoding with base/mask and optional keep-base address mode
- AW/AR channel arbitration with tracking for response routing
- Configurable via parameters: `MST_NUM`, `SLV_NUM`, `ADDR_WIDTH`, `DATA_WIDTH`, `ID_WIDTH`

### AXI4-Lite Interconnect (`axil_interconnect`)

Simplified memory-mapped crossbar with:
- Per-master and per-slave sync FIFO buffering
- AW/AR channel arbitration
- Address translation (base address subtraction)
- Parameter validation for buffer depth (power-of-2, >=2)

## 🔧 Testbench Usage

### BFM Simulation Loop Pattern

```cpp
// negedge: sample inputs from DUT
if (!clk) { bfm.update_input(); }
top->eval();
// posedge: drive outputs to DUT
if (clk) { bfm.update_output(); }
```

### BFM Operations

| BFM | Template Args | Ops |
|-----|---------------|-----|
| `axi_master/slave<D, A, I>` | DATA_WIDTH, ADDR_WIDTH, ID_WIDTH | `write_incr`, `read_incr`, `write_fixed`, `read_fixed`, `write_wrap`, `read_wrap` |
| `axil_master/slave<D, A>` | DATA_WIDTH, ADDR_WIDTH | `write_incr`, `read_incr` |
| `axis_master/slave<D>` | DATA_WIDTH | `send`, `recv` |

See `sim/tb/axi_interconnect/axi_interconnect_tb.cpp` for a complete example.

## 📝 Acknowledgements

The design of AXI interconnect references [axi-crossbar](https://github.com/dpretet/axi-crossbar.git).

## 📄 License

MIT License

Copyright (c) 2025 dozecat

---

<span id="cn">axi_lib</span>
===========================

**axi_lib** 是一个基于 SystemVerilog 的 AXI 互连 RTL 库，适用于 FPGA/ASIC 设计，采用 [Verilator](https://www.veripool.org/verilator/) 仿真，仿真模型使用 [vaxivip](https://github.com/dozecat/vaxivip.git) 库中的 BFM。它提供 AXI4 和 AXI4-Lite 交叉开关互连以及基本组件（仲裁器、FIFO、缓冲器）。

## ✨ 特性概览

| 模块 | 类型 | 功能描述 |
|------|------|----------|
| **`axi_interconnect`** (`rtl/axi_interconnect.sv`) | AXI4 交叉开关 | 多主多从 AXI4 互连，支持 FIXED/INCR/WRAP 突发和可配置地址映射 |
| **`axil_interconnect`** (`rtl/axil_interconnect.sv`) | AXI4-Lite 交叉开关 | 多主多从 AXI4-Lite 互连，带地址译码和仲裁 |
| **`arbiter`** (`rtl/arbiter.sv`) | 仲裁器 | 参数化固定优先级仲裁器 |

## 🚀 快速开始

### 1. 安装依赖
```bash
# macOS (使用 Homebrew)
brew install verilator

# Ubuntu/Debian
sudo apt-get install verilator g++ make
```

### 2. 运行 AXI 互连仿真
```bash
cd sim/tb/axi_interconnect
make sim
```

### 3. 运行 AXI4-Lite 互连仿真
```bash
cd sim/tb/axil_interconnect
make sim
```

### 4. 查看波形（可选）
```bash
make waves    # 需要 gtkwave
```

## 📖 项目结构

```
.
├── rtl/                        # RTL 源代码
│   ├── if_axi.sv               # AXI4 接口
│   ├── if_axil.sv              # AXI4-Lite 接口
│   ├── if_axis.sv              # AXI4-Stream 接口
│   ├── axi_interconnect.sv     # AXI4 交叉开关互连
│   ├── axil_interconnect.sv    # AXI4-Lite 交叉开关互连
│   ├── arbiter.sv              # 优先级仲裁器
│   ├── sync_fifo.v             # 同步 FIFO
│   ├── async_fifo.v            # 异步 FIFO（双时钟域）
│   └── skid_buffer.v           # 流水线缓冲器
├── sim/
│   ├── bfm/                    # C++ BFM
│   │   ├── axi/                # AXI4 主/从
│   │   ├── axil/               # AXI4-Lite 主/从
│   │   ├── axis/               # AXI4-Stream 主/从
│   │   ├── log.hpp             # 彩色日志
│   │   └── sig.hpp             # 信号类型辅助
│   └── tb/                     # 测试用例
│       ├── axi_interconnect/   # AXI4 交叉开关测试
│       └── axil_interconnect/  # AXI4-Lite 交叉开关测试
├── AGENTS.md
└── README.md
```

## 🧩 RTL 模块

### AXI 互连 (`axi_interconnect`)

可配置 master/slave 到 AXI 连接器，支持：
- **FIXED**、**INCR**、**WRAP** 突发类型
- 每主端口和每从端口的输出缓冲，深度可配置
- 基于基地址/掩码的从端口地址译码，支持 keep-base 地址模式
- AW/AR 通道仲裁，带事务跟踪用于响应路由

### AXI4-Lite 互连 (`axil_interconnect`)

简化的内存映射交叉开关，带：
- 每主端口和每从端口的同步 FIFO 缓冲
- AW/AR 通道仲裁
- 地址转换（基地址减法）
- 缓冲深度参数校验（2 的幂且 >= 2）

## 🔧 测试平台

### BFM 仿真循环模式

```cpp
// 下降沿：从 DUT 采样输入
if (!clk) { bfm.update_input(); }
top->eval();
// 上升沿：驱动输出到 DUT
if (clk) { bfm.update_output(); }
```

### BFM 操作

| BFM | 模板参数 | 操作 |
|-----|----------|------|
| `axi_master/slave<D, A, I>` | DATA_WIDTH, ADDR_WIDTH, ID_WIDTH | `write_incr`, `read_incr`, `write_fixed`, `read_fixed`, `write_wrap`, `read_wrap` |
| `axil_master/slave<D, A>` | DATA_WIDTH, ADDR_WIDTH | `write_incr`, `read_incr` |
| `axis_master/slave<D>` | DATA_WIDTH | `send`, `recv` |

完整示例请参考 `sim/tb/axi_interconnect/axi_interconnect_tb.cpp`。

## 📝 致谢

本项目的 AXI 互连设计参考了 [axi-crossbar](https://github.com/dpretet/axi-crossbar.git)。

## 📄 版权说明

MIT License

Copyright (c) 2025 dozecat
