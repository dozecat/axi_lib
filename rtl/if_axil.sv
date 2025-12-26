//*****************************************************************************
// Copyright (C) 2025 WanderingKitsune. All rights reserved.
// SPDX-License-Identifier: MIT
// 
// File:        if_axil.sv
// Description: AXI4-Lite Interface Definition
// Repository:  https://github.com/WanderingKitsune/axi_lib.git
// 
// Modification History:
// Ver   Who       Date        Changes
// ----  ----  ----------  ----------------------------------------------------
// 1.0         2025/12/25  Initial release
//*****************************************************************************

`timescale 1ns / 1ps

interface if_axil
#(
   parameter ADDR_WIDTH = 16,           // Address width
   parameter DATA_WIDTH = 32,           // Data width
   parameter STRB_WIDTH = DATA_WIDTH/8  // Strobe width
);

localparam PROT_WIDTH   = 3;            // Protection type width
localparam RESP_WIDTH   = 2;            // Response type width

// Write Address Channel
logic [ADDR_WIDTH-1:0]  awaddr;
logic [PROT_WIDTH-1:0]  awprot;
logic                   awready;
logic                   awvalid;

// Write Response Channel
logic                   bready;
logic [RESP_WIDTH-1:0]  bresp;
logic                   bvalid;

// Write Data Channel
logic [DATA_WIDTH-1:0]  wdata;
logic                   wready;
logic [STRB_WIDTH-1:0]  wstrb;
logic                   wvalid;

// Read Address Channel
logic [ADDR_WIDTH-1:0]  araddr;
logic [PROT_WIDTH-1:0]  arprot;
logic                   arready;
logic                   arvalid;

// Read Data Channel
logic [DATA_WIDTH-1:0]  rdata;
logic                   rready;
logic [RESP_WIDTH-1:0]  rresp;
logic                   rvalid;

modport master (
   output araddr,
   output arprot,
   input  arready,
   output arvalid,
   output awaddr,
   output awprot,
   input  awready,
   output awvalid,
   output bready,
   input  bresp,
   input  bvalid,
   input  rdata,
   output rready,
   input  rresp,
   input  rvalid,
   output wdata,
   input  wready,
   output wstrb,
   output wvalid
);

modport slave (
   input  araddr,
   input  arprot,
   output arready,
   input  arvalid,
   input  awaddr,
   input  awprot,
   output awready,
   input  awvalid,
   input  bready,
   output bresp,
   output bvalid,
   output rdata,
   input  rready,
   output rresp,
   output rvalid,
   input  wdata,
   output wready,
   input  wstrb,
   input  wvalid
);

endinterface
