//*****************************************************************************
// Copyright (C) 2025 WanderingKitsune. All rights reserved.
// SPDX-License-Identifier: MIT
// 
// File:        if_axi.sv
// Description: AXI4 Interface Definition
// Repository:  https://github.com/WanderingKitsune/axi_lib.git
// 
// Modification History:
// Ver   Who       Date        Changes
// ----  ----  ----------  ----------------------------------------------------
// 1.0         2025/12/25  Initial release
//*****************************************************************************

`timescale 1ns / 1ps

interface if_axi
#(
   parameter ADDR_WIDTH       = 32,          // Address width
   parameter DATA_WIDTH       = 64,          // Data width
   parameter ID_WIDTH         = 16,          // ID width
   parameter STRB_WIDTH       = DATA_WIDTH/8 // Strobe width
);

localparam BURST_TYPE_WIDTH   = 2;            // Burst type width
localparam CACHE_WIDTH        = 4;            // Cache type width
localparam LEN_WIDTH          = 8;            // Burst length width
localparam LOCK_WIDTH         = 1;            // Lock type width
localparam PROT_WIDTH         = 3;            // Protection type width
localparam QOS_WIDTH          = 4;            // QoS width
localparam REGION_WIDTH       = 4;            // Region width
localparam SIZE_WIDTH         = 3;            // Burst size width
localparam RESP_WIDTH         = 2;            // Response type width

// Read Address Channel
logic [ADDR_WIDTH-1:0]        araddr;
logic [BURST_TYPE_WIDTH-1:0]  arburst;
logic [CACHE_WIDTH-1:0]       arcache;
logic [ID_WIDTH-1:0]          arid;
logic [LEN_WIDTH-1:0]         arlen;
logic [LOCK_WIDTH-1:0]        arlock;
logic [PROT_WIDTH-1:0]        arprot;
logic [QOS_WIDTH-1:0]         arqos;
logic                         arready;
logic [REGION_WIDTH-1:0]      arregion;
logic [SIZE_WIDTH-1:0]        arsize;
logic                         arvalid;

// Write Address Channel
logic [ADDR_WIDTH-1:0]        awaddr;
logic [BURST_TYPE_WIDTH-1:0]  awburst;
logic [CACHE_WIDTH-1:0]       awcache;
logic [ID_WIDTH-1:0]          awid;
logic [LEN_WIDTH-1:0]         awlen;
logic [LOCK_WIDTH-1:0]        awlock;
logic [PROT_WIDTH-1:0]        awprot;
logic [QOS_WIDTH-1:0]         awqos;
logic                         awready;
logic [REGION_WIDTH-1:0]      awregion;
logic [SIZE_WIDTH-1:0]        awsize;
logic                         awvalid;

// Write Response Channel
logic [ID_WIDTH-1:0]          bid;
logic                         bready;
logic [RESP_WIDTH-1:0]        bresp;
logic                         bvalid;

// Read Data Channel
logic [DATA_WIDTH-1:0]        rdata;
logic [ID_WIDTH-1:0]          rid;
logic                         rlast;
logic                         rready;
logic [RESP_WIDTH-1:0]        rresp;
logic                         rvalid;

// Write Data Channel
logic [DATA_WIDTH-1:0]        wdata;
logic [ID_WIDTH-1:0]          wid;
logic                         wlast;
logic                         wready;
logic [STRB_WIDTH-1:0]        wstrb;
logic                         wvalid;

modport master (
   output araddr,
   output arburst,
   output arcache,
   output arid,
   output arlen,
   output arlock,
   output arprot,
   output arqos,
   input  arready,
   output arregion,
   output arsize,
   output arvalid,
   output awaddr,
   output awburst,
   output awcache,
   output awid,
   output awlen,
   output awlock,
   output awprot,
   output awqos,
   input  awready,
   output awregion,
   output awsize,
   output awvalid,
   input  bid,
   output bready,
   input  bresp,
   input  bvalid,
   input  rdata,
   input  rid,
   input  rlast,
   output rready,
   input  rresp,
   input  rvalid,
   output wdata,
   output wid,
   output wlast,
   input  wready,
   output wstrb,
   output wvalid
);

modport slave (
   input  araddr,
   input  arburst,
   input  arcache,
   input  arid,
   input  arlen,
   input  arlock,
   input  arprot,
   input  arqos,
   output arready,
   input  arregion,
   input  arsize,
   input  arvalid,
   input  awaddr,
   input  awburst,
   input  awcache,
   input  awid,
   input  awlen,
   input  awlock,
   input  awprot,
   input  awqos,
   output awready,
   input  awregion,
   input  awsize,
   input  awvalid,
   output bid,
   input  bready,
   output bresp,
   output bvalid,
   output rdata,
   output rid,
   output rlast,
   input  rready,
   output rresp,
   output rvalid,
   input  wdata,
   input  wid,
   input  wlast,
   output wready,
   input  wstrb,
   input  wvalid
);

endinterface
