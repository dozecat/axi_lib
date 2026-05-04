![Language](https://img.shields.io/badge/Language-SystemVerilog-dbe1c5.svg) ![Simulation](https://img.shields.io/badge/Simulation-Verilator-005ea6.svg) [![BFM｜vaxivip](https://img.shields.io/badge/BFM-vaxivip-9b59b6.svg)](https://github.com/dozecat/vaxivip.git) ![License](https://img.shields.io/badge/License-MIT-green.svg)

[English](#en) | [中文](#cn)

---

<span id="en">axi_lib</span>
===========================

**axi_lib** is a SystemVerilog AXI RTL library for FPGA/ASIC designs. It provides AXI4/AXI4-Lite/AXI4-Stream interconnect and function modules, plus primitive components (arbiter, sync/async FIFOs, skid buffer). Simulation uses [Verilator](https://www.veripool.org/verilator/) with BFMs from [vaxivip](https://github.com/dozecat/vaxivip.git).

## ✨ Features

- AXI4, AXI4-Lite and AXI4-Stream functional modules
- Parameterized design: flexible port count, address map and burst type configuration
- Reusable primitive components: arbiter, FIFOs, skid buffer
- Verilator-verified with C++ BFM testbenches
- MIT licensed

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
│   ├── axi2axil.sv             # AXI4 to AXI4-Lite bridge
│   ├── axil2axi.sv             # AXI4-Lite to AXI4 bridge
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
│       ├── axil_interconnect/  # AXI4-Lite crossbar TB
│       ├── axi2axil/           # AXI4 to AXI4-Lite bridge TB
│       └── axil2axi/           # AXI4-Lite to AXI4 bridge TB
├── AGENTS.md
└── README.md
```

## 🧩 RTL Modules

| Module | Protocol | Description |
|--------|----------|-------------|
| **`axi_interconnect`** (`rtl/axi_interconnect.sv`) | **AXI4** | Configurable multi-master multi-slave crossbar with arbitration, optional per-port input/output FIFO buffering, address decode routing |
| **`axil_interconnect`** (`rtl/axil_interconnect.sv`) | **AXI4-Lite** | Configurable multi-master multi-slave crossbar with arbitration, optional per-port skid buffer, address decode routing |
| **`axi2axil`** (`rtl/axi2axil.sv`) | **AXI4 → AXI4-Lite** | Burst-to-single-beat bridge, supports FIXED/INCR/WRAP, single outstanding transaction |
| **`axil2axi`** (`rtl/axil2axi.sv`) | **AXI4-Lite → AXI4** | Single-beat bridge, maps AXI4-Lite to AXI4 len=0 transactions |

### Module Structure

<b><font color="blue">`axi_interconnect`</font></b> — per-master decode → matrix → per-slave arbiter + buffer

```
  AW ─► [skid] ─► decoder ─┐  ┌──────┐  ┌── arbiter ─► [skid] ─► AW
  W  ─► [FIFO] ────────────├──│matrix│──┤── mux     ─► [FIFO] ─► W
                           │  └──────┘  │
  B  ◄─ [skid] ◄───────────┘            └── demux   ◄─ [skid] ◄─ B

  AR ─► [skid] ─► decoder ─┐  ┌──────┐  ┌── arbiter ─► [skid] ─► AR
                           ├──│matrix│──┤
  R  ◄── [FIFO] ◄──────────┘  └──────┘  └── demux   ◄─ [FIFO] ◄── R
```

- **decoder**: AW/AR address decode → determines target slave; W/B/R flow is gated by register-based burst tracking
- **arbiter** (AW/AR): per-slave fixed-priority arbitration across competing masters
- **demux** (B/R): ID-embedded response routing back to correct master
- **mux** (W): follows current arbiter grant, single-cycle

<b><font color="blue">`axil_interconnect`</font></b> — tracking FIFOs replace register tracking, multi-outstanding

```
  AW ─► [skid] ─► decoder ─┐  ┌──────┐  ┌── arbiter ──► [skid] ─► AW
  W  ─► [skid] ── wtrk  ───├──│matrix│──┤── awgnt   ──► [skid] ─► W
                           │  └──────┘  │
  B  ◄─ [skid] ── btrk  ◄──┘            └── btrk   ◄─── [skid] ◄─ B

  AR ─► [skid] ─► decoder ─┐  ┌──────┐  ┌── arbiter ──► [skid] ─► AR
                           ├──│matrix│──┤
  R  ◄─ [skid] ── rtrk  ◄──┘  └──────┘  └── rtrk   ◄─── [skid] ◄─ R
```

- **wtrk/btrk/rtrk**: tracking FIFOs per-channel, store target slave / grant vector per outstanding transaction (`TRK_DEPTH`)
- **awgnt**: stores arbiter grant, routes W data to the winning master
- **skid**: all channels use register-based 2-deep elastic buffer (zero BRAM)
- Tracking FIFO RAM style configurable via `TRK_RAM_STYLE`

## 🧪 Testbench

Simulation uses C++ BFMs from [vaxivip](https://github.com/dozecat/vaxivip.git). The BFMs follow an `update_input()` → `eval()` → `update_output()` pattern for clock-edge-accurate signal timing.

### Simulation Loop

```cpp
top->clk = 1;
top->eval();

// negedge: sample DUT outputs
axi_mst.update_input();
axi_slv.update_input();

top->clk = 0;
top->eval();

if (top->clk) {
    // posedge: initiate transactions
    if (cycle == 10) axi_mst.write_incr(0x1000, {0xAA, 0xBB});
}

// posedge: drive DUT inputs
axi_mst.update_output();
axi_slv.update_output();
```

### BFM Modules

| Module | Protocol | Description |
|--------|----------|-------------|
| **`axi`** (`src/axi/`) | AXI4 | Master/Slave interface supporting FIXED, INCR, WRAP burst |
| **`axil`** (`src/axil/`) | AXI4-Lite | Master/Slave interface |

See `sim/tb/axi_interconnect/axi_interconnect_tb.cpp` for a complete example.

## 📝 Acknowledgements

Design references [axi-crossbar](https://github.com/dpretet/axi-crossbar.git).

## 📄 License

MIT License

Copyright (c) 2025 dozecat

---

<span id="cn">axi_lib</span>
===========================

**axi_lib** 是一个 SystemVerilog AXI RTL 库，适用于 FPGA/ASIC。提供 AXI4/AXI4-Lite/AXI4-Stream 互连与功能模块，以及仲裁器、FIFO、skid buffer 等基础组件。仿真采用 [Verilator](https://www.veripool.org/verilator/)，BFM 来自 [vaxivip](https://github.com/dozecat/vaxivip.git)。

## ✨ 特性概览

- 提供 AXI4、AXI4-Lite、AXI4-Stream 相关的功能模块
- 参数化设计：灵活配置端口数量、地址映射和突发类型
- 内置仲裁器、FIFO、skid buffer 等基础组件，可独立复用
- Verilator 验证，配套 C++ BFM 测试平台
- MIT 许可

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
│   ├── axi2axil.sv             # AXI4 转 AXI4-Lite 桥接器
│   ├── axil2axi.sv             # AXI4-Lite 转 AXI4 桥接器
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
│       ├── axil_interconnect/  # AXI4-Lite 交叉开关测试
│       ├── axi2axil/           # AXI4 转 AXI4-Lite 桥接测试
│       └── axil2axi/           # AXI4-Lite 转 AXI4 桥接测试
├── AGENTS.md
└── README.md
```

## 🧩 RTL 模块

| 模块 | 协议 | 功能描述 |
|------|------|----------|
| **`axi_interconnect`** (`rtl/axi_interconnect.sv`) | **AXI4** | 主机/从机数量可配置的多路仲裁交叉开关，每端口可选输入/输出 FIFO 缓冲，地址译码路由到对应从机 |
| **`axil_interconnect`** (`rtl/axil_interconnect.sv`) | **AXI4-Lite** | 主机/从机数量可配置的多路仲裁交叉开关，每端口可选 skid buffer 缓冲，地址译码路由到对应从机 |
| **`axi2axil`** (`rtl/axi2axil.sv`) | **AXI4 → AXI4-Lite** | 突发转单拍桥接器，支持 FIXED/INCR/WRAP，单笔 outstanding |
| **`axil2axi`** (`rtl/axil2axi.sv`) | **AXI4-Lite → AXI4** | 单拍桥接器，AXI4-Lite 映射为 AXI4 len=0 事务 |

### 模块结构

<b><font color="blue">`axi_interconnect`</font></b> — 每 master 译码 → matrix → 每 slave 仲裁 + 缓冲

```
  AW ─► [skid] ─► 译码器 ─┐  ┌──────┐  ┌── 仲裁器 ─► [skid] ─► AW
  W  ─► [FIFO] ──────────├──│matrix│──┤── mux   ─► [FIFO] ─► W
                         │  └──────┘  │
  B  ◄─ [skid] ◄─────────┘            └── demux ◄─ [skid] ◄─ B

  AR ─► [skid] ─► 译码器 ─┐  ┌──────┐  ┌── 仲裁器 ─► [skid] ─► AR
                         ├──│matrix│──┤
  R  ◄─ [FIFO] ◄─────────┘  └──────┘  └── demux ◄─ [FIFO] ◄─ R
```

- **译码器**：AW/AR 地址译码，确定目标从机；W/B/R 由寄存器实现的 burst 跟踪门控
- **仲裁器**（AW/AR）：每从机固定优先级仲裁
- **demux**（B/R）：ID 位解复用，响应路由回正确 master
- **mux**（W）：跟随当前仲裁器 grant，单周期

<b><font color="blue">`axil_interconnect`</font></b> — 跟踪 FIFO 替代寄存器跟踪，支持多 outstanding

```
  AW ─► [skid] ─► 译码器 ─┐  ┌──────┐  ┌── 仲裁器 ──► [skid] ─► AW
  W  ─► [skid] ── wtrk ──├──│matrix│──┤── awgnt ──► [skid] ─► W
                         │  └──────┘  │
  B  ◄─ [skid] ── btrk ◄─┘            └── btrk ◄─── [skid] ◄─ B

  AR ─► [skid] ─► 译码器 ─┐  ┌──────┐  ┌── 仲裁器 ──► [skid] ─► AR
                         ├──│matrix│──┤
  R  ◄─ [skid] ── rtrk ◄─┘  └──────┘  └── rtrk ◄─── [skid] ◄─ R
```

- **wtrk/btrk/rtrk**：跟踪 FIFO 每通道独立，存储目标从机/grant 向量（`TRK_DEPTH`）
- **awgnt**：存储仲裁器 grant，W 路由到获得仲裁的 master
- **skid**：全通道 2 级寄存器弹性缓冲（零 BRAM）
- 跟踪 FIFO RAM 类型通过 `TRK_RAM_STYLE` 控制

## 🧪 测试平台

仿真使用 [vaxivip](https://github.com/dozecat/vaxivip.git) 的 C++ BFM 驱动。BFM 遵循 `update_input()` → `eval()` → `update_output()` 时序模式实现时钟沿对齐的信号采样与驱动。

### 仿真循环

```cpp
top->clk = 1;
top->eval();

// 下降沿：采样 DUT 输出
axi_mst.update_input();
axi_slv.update_input();

top->clk = 0;
top->eval();

if (top->clk) {
    // 上升沿：发起事务
    if (cycle == 10) axi_mst.write_incr(0x1000, {0xAA, 0xBB});
}

// 上升沿：驱动 DUT 输入
axi_mst.update_output();
axi_slv.update_output();
```

### BFM 模块

| 模块 | 协议 | 功能描述 |
|------|------|----------|
| **axi**（`src/axi/`） | AXI4 | Master/Slave 接口，支持 FIXED（固定）、INCR（递增）、WRAP（回环）突发 |
| **axil**（`src/axil/`） | AXI4-Lite | Master/Slave 接口 |

完整示例请参考 `sim/tb/axi_interconnect/axi_interconnect_tb.cpp`。

## 📝 致谢

参考了 [axi-crossbar](https://github.com/dpretet/axi-crossbar.git) 的设计。

## 📄 版权说明

MIT License

Copyright (c) 2025 dozecat
