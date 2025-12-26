# AXI Verification Library (Verilator BFM)

This repository contains a lightweight verification library for **AXI4**, **AXI4-Lite**, and **AXI4-Stream** protocols, designed specifically for use with **Verilator**. It provides SystemVerilog interface definitions and corresponding C++ Bus Functional Models (BFMs) to facilitate easy and efficient simulation.

## Features

- **Protocols Supported**:
  - **AXI4**: Full AXI4 Master and Slave support (Burst types: FIXED, INCR, WRAP).
  - **AXI4-Lite**: Simplified memory-mapped interface for register access.
  - **AXI4-Stream**: Streaming interface for high-speed data transmission.
- **Header-Only C++**: Easy integration into Verilator C++ testbenches.
- **Dual Roles**: Master and Slave BFMs available for all protocols.
- **Rich Logging**: Built-in formatted logging (Hex dump style) for transactions.
- **Flexible Data Widths**: Templated classes to support various data and address widths.

## Directory Structure

```text
.
├── rtl/                # SystemVerilog Interface Definitions
│   ├── if_axi.sv       # AXI4 Interface
│   ├── if_axil.sv      # AXI4-Lite Interface
│   └── if_axis.sv      # AXI4-Stream Interface
├── sim/
│   ├── bfm/            # C++ BFM Implementations
│   │   ├── axi.hpp     # AXI4 Master/Slave Class
│   │   ├── axil.hpp    # AXI4-Lite Master/Slave Class
│   │   ├── axis.hpp    # AXI4-Stream Master/Slave Class
│   │   └── sig.hpp     # Signal helper utilities
│   └── tb/             # Example Testbenches
│       ├── axi/        # AXI4 Testbench
│       ├── axil/       # AXI4-Lite Testbench
│       └── axis/       # AXI4-Stream Testbench
└── README.md
```

## Usage

### Prerequisites
- Verilator (v5.0 or later recommended)
- C++ Compiler (GCC/Clang) with C++11 support or higher
- Make

### 1. AXI4-Lite Example

**Master Write/Read:**
```cpp
#include "axil.hpp"

// Instantiate Master BFM
// Template args: <DATA_WIDTH, ADDR_WIDTH>
axil_master<32, 32> master(port_ptr);

// Write to address 0x100
master.write(0x100, 0x12345678);

// Read from address 0x100
master.read(0x100);

// In simulation loop
if (clk) {
    master.tick();
}
```

### 2. AXI4 Example

**Master Burst Write:**
```cpp
#include "axi.hpp"

// Instantiate Master BFM
// Template args: <DATA_WIDTH, ADDR_WIDTH, ID_WIDTH>
axi_master<256, 40, 16> master(port_ptr);

// Prepare data
std::vector<uint8_t> data = {0x01, 0x02, 0x03, 0x04};

// Write burst (INCR)
master.write(0x1000, data);

// In simulation loop
if (clk) {
    master.tick();
}
```

### 3. AXI4-Stream Example

**Master Send:**
```cpp
#include "axis.hpp"

// Instantiate Master BFM
// Template args: <DATA_WIDTH>
axis_master<64> master(port_ptr);

// Send data packet
const char* data = "Hello";
master.send(data, 5, true); // true = assert TLAST

// In simulation loop
if (clk) {
    master.tick();
}
```

## Running Examples

Navigate to the testbench directories and run `make`:

```bash
# Run AXI4 Test
cd sim/tb/axi
make

# Run AXI4-Lite Test
cd sim/tb/axil
make

# Run AXI4-Stream Test
cd sim/tb/axis
make
```

## License

MIT License
