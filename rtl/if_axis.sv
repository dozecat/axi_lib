//*****************************************************************************
// Copyright (C) 2025 dozecat. All rights reserved.
// SPDX-License-Identifier: MIT
//
// File:        if_axis.sv
// Description: AXI4-Stream Interface Definition
// Repository:  https://github.com/dozecat/axi_lib.git
//
// Modification History:
// Ver   Who       Date        Changes
// ----  ----  ----------  ----------------------------------------------------
// 1.0         2025/12/25  Initial release
//*****************************************************************************

`timescale 1ns / 1ps

interface if_axis
#(
   parameter DATA_WIDTH = 64,           // Data width
   parameter DEST_WIDTH = 1,            // Destination width
   parameter KEEP_WIDTH = DATA_WIDTH/8, // Keep width
   parameter STRB_WIDTH = DATA_WIDTH/8, // Strobe width
   parameter ID_WIDTH   = 8,            // ID width
   parameter USER_WIDTH = 1             // User width
);

logic [DATA_WIDTH-1:0]  tdata;
logic [DEST_WIDTH-1:0]  tdest;
logic [KEEP_WIDTH-1:0]  tkeep;
logic [STRB_WIDTH-1:0]  tstrb;
logic                   tlast;
logic                   tready;
logic [USER_WIDTH-1:0]  tuser;
logic [ID_WIDTH-1:0]    tid;
logic                   tvalid;

modport master
(
   output tdata,
   output tdest,
   output tkeep,
   output tstrb,
   output tlast,
   input  tready,
   output tuser,
   output tid,
   output tvalid
);

modport slave
(
   input  tdata,
   input  tdest,
   input  tkeep,
   input  tstrb,
   input  tlast,
   output tready,
   input  tuser,
   input  tid,
   input  tvalid
);

modport monitor
(
   input tdata,
   input tdest,
   input tkeep,
   input tstrb,
   input tlast,
   input tready,
   input tuser,
   input tid,
   input tvalid
);

endinterface
