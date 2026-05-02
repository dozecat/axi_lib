//*****************************************************************************
// Copyright (C) 2026 dozecat. All rights reserved.
// SPDX-License-Identifier: MIT
// 
// File:        axi_interconnect.sv
// Description: AXI4 Interconnect
// Repository:  https://github.com/dozecat/axi_lib.git
// 
// Modification History:
// Ver   Who       Date        Changes
// ----  ----  ----------  ----------------------------------------------------
// 1.0         2026/5/1    Initial release
//*****************************************************************************
`timescale 1ns / 1ps
`default_nettype none

module axi_interconnect
#(
   parameter MST_NUM             = 4,
   parameter SLV_NUM             = 4,
   parameter ADDR_WIDTH          = 32,
   parameter DATA_WIDTH          = 64,
   parameter ID_WIDTH            = 8,
   parameter PRIORITY_WIDTH      = 4,
   parameter TRK_DEPTH           = 4,
   parameter MST_BUF_EN          = {MST_NUM{1'b0}},
   parameter MST_BUF_DEPTH       = {MST_NUM{16'b0}},
   parameter MST_PRIORITY        = {MST_NUM*PRIORITY_WIDTH{1'b0}},
   parameter MST_ID_MASK         = {MST_NUM*ID_WIDTH{1'b0}},
   parameter SLV_BUF_EN          = {SLV_NUM{1'b0}},
   parameter SLV_BUF_DEPTH       = {SLV_NUM{16'b0}},
   parameter SLV_START_ADDR      = {SLV_NUM*ADDR_WIDTH{1'b0}},
   parameter SLV_END_ADDR        = {SLV_NUM*ADDR_WIDTH{1'b1}},
   parameter SLV_KEEP_BASE       = {SLV_NUM{1'b0}}
)(
   input  wire                   aclk,
   input  wire                   aresetn,

   if_axi.slave                  axi_slv_if [0:MST_NUM-1],
   if_axi.master                 axi_mst_if [0:SLV_NUM-1]
);

localparam STRB_WIDTH   = DATA_WIDTH / 8;
localparam LEN_WIDTH    = 8;
localparam RESP_WIDTH   = 2;

localparam AWCH_WIDTH = ADDR_WIDTH + ID_WIDTH + 29;
localparam WCH_WIDTH  = DATA_WIDTH + STRB_WIDTH + 1 + ID_WIDTH;
localparam BCH_WIDTH  = RESP_WIDTH + ID_WIDTH;
localparam RCH_WIDTH  = DATA_WIDTH + RESP_WIDTH + ID_WIDTH + 1;
localparam ARCH_WIDTH = AWCH_WIDTH;

localparam AW_ADDR_LSB = 0;
localparam AW_ID_LSB   = ADDR_WIDTH;

localparam W_LAST_LSB  = ID_WIDTH;

localparam B_ID_LSB    = 0;
localparam B_RESP_LSB  = ID_WIDTH;

localparam R_LAST_LSB  = 0;
localparam R_ID_LSB    = 1;
localparam R_RESP_LSB  = 1 + ID_WIDTH;
localparam R_DATA_LSB  = 1 + ID_WIDTH + RESP_WIDTH;

localparam INTF_ADDR_WIDTH = axi_slv_if[0].ADDR_WIDTH;
localparam INTF_DATA_WIDTH = axi_slv_if[0].DATA_WIDTH;
localparam INTF_ID_WIDTH   = axi_slv_if[0].ID_WIDTH;

// Flat signal declarations
genvar i, j;
logic [MST_NUM            -1:0]   i_awvalid;
logic [MST_NUM            -1:0]   i_awready;
logic [MST_NUM*AWCH_WIDTH -1:0]   i_awch;
logic [MST_NUM            -1:0]   i_wvalid;
logic [MST_NUM            -1:0]   i_wready;
logic [MST_NUM*WCH_WIDTH  -1:0]   i_wch;
logic [MST_NUM            -1:0]   i_bvalid;
logic [MST_NUM            -1:0]   i_bready;
logic [MST_NUM*BCH_WIDTH  -1:0]   i_bch;
logic [MST_NUM            -1:0]   i_arvalid;
logic [MST_NUM            -1:0]   i_arready;
logic [MST_NUM*ARCH_WIDTH -1:0]   i_arch;
logic [MST_NUM            -1:0]   i_rvalid;
logic [MST_NUM            -1:0]   i_rready;
logic [MST_NUM*RCH_WIDTH  -1:0]   i_rch;

logic [SLV_NUM            -1:0]   o_awvalid;
logic [SLV_NUM            -1:0]   o_awready;
logic [SLV_NUM*AWCH_WIDTH -1:0]   o_awch;
logic [SLV_NUM            -1:0]   o_wvalid;
logic [SLV_NUM            -1:0]   o_wready;
logic [SLV_NUM*WCH_WIDTH  -1:0]   o_wch;
logic [SLV_NUM            -1:0]   o_bvalid;
logic [SLV_NUM            -1:0]   o_bready;
logic [SLV_NUM*BCH_WIDTH  -1:0]   o_bch;
logic [SLV_NUM            -1:0]   o_arvalid;
logic [SLV_NUM            -1:0]   o_arready;
logic [SLV_NUM*ARCH_WIDTH -1:0]   o_arch;
logic [SLV_NUM            -1:0]   o_rvalid;
logic [SLV_NUM            -1:0]   o_rready;
logic [SLV_NUM*RCH_WIDTH  -1:0]   o_rch;

logic [MST_NUM*SLV_NUM    -1:0]   m2s_awvalid;
logic [MST_NUM*SLV_NUM    -1:0]   m2s_awready;
logic [MST_NUM*SLV_NUM    -1:0]   m2s_wvalid;
logic [MST_NUM*SLV_NUM    -1:0]   m2s_wready;
logic [MST_NUM*SLV_NUM    -1:0]   m2s_arvalid;
logic [MST_NUM*SLV_NUM    -1:0]   m2s_arready;

logic [SLV_NUM*MST_NUM    -1:0]   s2m_awvalid;
logic [SLV_NUM*MST_NUM    -1:0]   s2m_awready;
logic [SLV_NUM*MST_NUM    -1:0]   s2m_wvalid;
logic [SLV_NUM*MST_NUM    -1:0]   s2m_wready;
logic [SLV_NUM*MST_NUM    -1:0]   s2m_arvalid;
logic [SLV_NUM*MST_NUM    -1:0]   s2m_arready;

logic [SLV_NUM*MST_NUM    -1:0]   s2m_bvalid;
logic [SLV_NUM*MST_NUM    -1:0]   s2m_bready;
logic [SLV_NUM*MST_NUM    -1:0]   s2m_rvalid;
logic [SLV_NUM*MST_NUM    -1:0]   s2m_rready;
logic [SLV_NUM*BCH_WIDTH  -1:0]   s2m_bch;
logic [SLV_NUM*RCH_WIDTH  -1:0]   s2m_rch;

logic [MST_NUM*SLV_NUM    -1:0]   m2s_bvalid;
logic [MST_NUM*SLV_NUM    -1:0]   m2s_bready;
logic [MST_NUM*SLV_NUM    -1:0]   m2s_rvalid;
logic [MST_NUM*SLV_NUM    -1:0]   m2s_rready;

logic [MST_NUM             -1:0]  aw_misrouting;
logic [MST_NUM             -1:0]  ar_misrouting;


initial begin
   if (ADDR_WIDTH != INTF_ADDR_WIDTH)
      $error("ADDR_WIDTH mismatch: %0d != %0d", ADDR_WIDTH, INTF_ADDR_WIDTH);
end

initial begin
   if (DATA_WIDTH != INTF_DATA_WIDTH)
      $error("DATA_WIDTH mismatch: %0d != %0d", DATA_WIDTH, INTF_DATA_WIDTH);
end

initial begin
   if (ID_WIDTH != INTF_ID_WIDTH)
      $error("ID_WIDTH mismatch: %0d != %0d", ID_WIDTH, INTF_ID_WIDTH);
end

initial begin
   for (integer m = 0; m < MST_NUM; m++) begin
      if (MST_BUF_EN[m]) begin
         if (MST_BUF_DEPTH[m*16+:16] < 2)
            $error("MST_BUF_EN[%0d] enabled but MST_BUF_DEPTH[%0d]=%0d (< 2)", m, m, MST_BUF_DEPTH[m*16+:16]);
         if ((MST_BUF_DEPTH[m*16+:16] & (MST_BUF_DEPTH[m*16+:16] - 1)) != 0)
            $error("MST_BUF_EN[%0d] enabled but MST_BUF_DEPTH[%0d]=%0d (not power-of-2)", m, m, MST_BUF_DEPTH[m*16+:16]);
      end
   end
end

initial begin
   for (integer n = 0; n < SLV_NUM; n++) begin
      if (SLV_BUF_EN[n]) begin
         if (SLV_BUF_DEPTH[n*16+:16] < 2)
            $error("SLV_BUF_EN[%0d] enabled but SLV_BUF_DEPTH[%0d]=%0d (< 2)", n, n, SLV_BUF_DEPTH[n*16+:16]);
         if ((SLV_BUF_DEPTH[n*16+:16] & (SLV_BUF_DEPTH[n*16+:16] - 1)) != 0)
            $error("SLV_BUF_EN[%0d] enabled but SLV_BUF_DEPTH[%0d]=%0d (not power-of-2)", n, n, SLV_BUF_DEPTH[n*16+:16]);
      end
   end
end

// Slave Interface
generate
   for (i = 0; i < MST_NUM; i++) begin : slv_if
      logic [AWCH_WIDTH -1:0] awch;
      logic [WCH_WIDTH  -1:0] wch;
      logic [BCH_WIDTH  -1:0] bch;
      logic [ARCH_WIDTH -1:0] arch;
      logic [RCH_WIDTH  -1:0] rch;

      assign awch = {axi_slv_if[i].awregion, axi_slv_if[i].awqos, axi_slv_if[i].awprot,
                     axi_slv_if[i].awcache,  axi_slv_if[i].awlock, axi_slv_if[i].awburst,
                     axi_slv_if[i].awsize,   axi_slv_if[i].awlen,
                     axi_slv_if[i].awid,     axi_slv_if[i].awaddr};
      assign wch  = {axi_slv_if[i].wdata, axi_slv_if[i].wstrb, axi_slv_if[i].wlast, axi_slv_if[i].wid};
      assign arch = {axi_slv_if[i].arregion, axi_slv_if[i].arqos, axi_slv_if[i].arprot,
                     axi_slv_if[i].arcache,  axi_slv_if[i].arlock, axi_slv_if[i].arburst,
                     axi_slv_if[i].arsize,   axi_slv_if[i].arlen,
                     axi_slv_if[i].arid,     axi_slv_if[i].araddr};

      if (MST_BUF_EN[i]) begin : buffer_on
         localparam BD = MST_BUF_DEPTH[i*16+:16];
         wire aw_full, aw_empty, w_full, w_empty, b_full, b_empty;
         wire ar_full, ar_empty, r_full, r_empty;

         sync_fifo #(
            .WIDTH               ( AWCH_WIDTH ),
            .DEPTH               ( BD ),
            .FWFT                ( "true" )
         ) u_aw (
            .clk                 ( aclk ),
            .rst                 ( ~aresetn ),
            .wr_en               ( axi_slv_if[i].awvalid && !aw_full ),
            .wr_data             ( awch ),
            .full                ( aw_full ),
            .rd_en               ( i_awready[i] ),
            .rd_data             ( i_awch[i*AWCH_WIDTH+:AWCH_WIDTH] ),
            .empty               ( aw_empty ),
            .overflow            ( ),
            .underflow           ( ),
            .level               ( )
         );
         assign axi_slv_if[i].awready = !aw_full;
         assign i_awvalid[i] = !aw_empty;
         wire [ADDR_WIDTH-1:0] awaddr_dbg;
         assign awaddr_dbg = i_awch[i*AWCH_WIDTH+:ADDR_WIDTH];

         sync_fifo #(
            .WIDTH               ( WCH_WIDTH ),
            .DEPTH               ( BD ),
            .FWFT                ( "true" )
         ) u_w (
            .clk                 ( aclk ),
            .rst                 ( ~aresetn ),
            .wr_en               ( axi_slv_if[i].wvalid && !w_full ),
            .wr_data             ( wch ),
            .full                ( w_full ),
            .rd_en               ( i_wready[i] ),
            .rd_data             ( i_wch[i*WCH_WIDTH+:WCH_WIDTH] ),
            .empty               ( w_empty ),
            .overflow            ( ),
            .underflow           ( ),
            .level               ( )
         );
         assign axi_slv_if[i].wready = !w_full;
         assign i_wvalid[i] = !w_empty;

         sync_fifo #(
            .WIDTH               ( BCH_WIDTH ),
            .DEPTH               ( BD ),
            .FWFT                ( "true" )
         ) u_b (
            .clk                 ( aclk ),
            .rst                 ( ~aresetn ),
            .wr_en               ( i_bvalid[i] ),
            .wr_data             ( i_bch[i*BCH_WIDTH+:BCH_WIDTH] ),
            .full                ( b_full ),
            .rd_en               ( axi_slv_if[i].bready ),
            .rd_data             ( bch ),
            .empty               ( b_empty ),
            .overflow            ( ),
            .underflow           ( ),
            .level               ( )
         );
         assign i_bready[i] = !b_full;
         assign axi_slv_if[i].bvalid = !b_empty;

         sync_fifo #(
            .WIDTH               ( ARCH_WIDTH ),
            .DEPTH               ( BD ),
            .FWFT                ( "true" )
         ) u_ar (
            .clk                 ( aclk ),
            .rst                 ( ~aresetn ),
            .wr_en               ( axi_slv_if[i].arvalid && !ar_full ),
            .wr_data             ( arch ),
            .full                ( ar_full ),
            .rd_en               ( i_arready[i] ),
            .rd_data             ( i_arch[i*ARCH_WIDTH+:ARCH_WIDTH] ),
            .empty               ( ar_empty ),
            .overflow            ( ),
            .underflow           ( ),
            .level               ( )
         );
         assign axi_slv_if[i].arready = !ar_full;
         assign i_arvalid[i] = !ar_empty;
         wire [ADDR_WIDTH-1:0] araddr_dbg;
         assign araddr_dbg = i_arch[i*ARCH_WIDTH+:ADDR_WIDTH];

         sync_fifo #(
            .WIDTH               ( RCH_WIDTH ),
            .DEPTH               ( BD ),
            .FWFT                ( "true" )
         ) u_r (
            .clk                 ( aclk ),
            .rst                 ( ~aresetn ),
            .wr_en               ( i_rvalid[i] ),
            .wr_data             ( i_rch[i*RCH_WIDTH+:RCH_WIDTH] ),
            .full                ( r_full ),
            .rd_en               ( axi_slv_if[i].rready ),
            .rd_data             ( rch ),
            .empty               ( r_empty ),
            .overflow            ( ),
            .underflow           ( ),
            .level               ( )
         );
         assign i_rready[i] = !r_full;
         assign axi_slv_if[i].rvalid = !r_empty;

         assign {axi_slv_if[i].bresp, axi_slv_if[i].bid} = bch;
         assign {axi_slv_if[i].rdata, axi_slv_if[i].rresp, axi_slv_if[i].rid, axi_slv_if[i].rlast} = rch;

      end else begin : buffer_off
         assign i_awvalid[i] = axi_slv_if[i].awvalid;
         assign axi_slv_if[i].awready = i_awready[i];
         assign i_awch[i*AWCH_WIDTH+:AWCH_WIDTH] = awch;
         assign i_wvalid[i] = axi_slv_if[i].wvalid;
         assign axi_slv_if[i].wready = i_wready[i];
         assign i_wch[i*WCH_WIDTH+:WCH_WIDTH] = wch;
         assign axi_slv_if[i].bvalid = i_bvalid[i];
         assign i_bready[i] = axi_slv_if[i].bready;
         assign {axi_slv_if[i].bresp, axi_slv_if[i].bid} = i_bch[i*BCH_WIDTH+:BCH_WIDTH];
         assign i_arvalid[i] = axi_slv_if[i].arvalid;
         assign axi_slv_if[i].arready = i_arready[i];
         assign i_arch[i*ARCH_WIDTH+:ARCH_WIDTH] = arch;
         assign axi_slv_if[i].rvalid = i_rvalid[i];
         assign i_rready[i] = axi_slv_if[i].rready;
         assign {axi_slv_if[i].rdata, axi_slv_if[i].rresp, axi_slv_if[i].rid, axi_slv_if[i].rlast} = i_rch[i*RCH_WIDTH+:RCH_WIDTH];
      end
   end
endgenerate

// Write Address Decode + Register-based Tracking
generate
   for (i = 0; i < MST_NUM; i++) begin : slv_wr_switch
      logic [SLV_NUM-1:0] slv_aw_targeted;
      logic [SLV_NUM-1:0] w_trk_target;
      logic               w_trk_valid;
      logic               w_burst_active;
      logic               w_hs_started;
      logic               b_trk_valid;
      logic [SLV_NUM-1:0] b_trk_target;
      logic [ID_WIDTH-1:0] b_trk_id;
      logic               b_clear_pending;

      wire [ID_WIDTH-1:0]  awid_cur  = i_awch[i*AWCH_WIDTH+AW_ID_LSB+:ID_WIDTH];
      wire                 wlast_cur = i_wch[i*WCH_WIDTH+W_LAST_LSB];

      for (j = 0; j < SLV_NUM; j++) begin : decode
         assign slv_aw_targeted[j] =
            (i_awch[i*AWCH_WIDTH+:ADDR_WIDTH] >= SLV_START_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]) &&
            (i_awch[i*AWCH_WIDTH+:ADDR_WIDTH] <= SLV_END_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]);
      end

      // AW forward: gated by W tracking not active
      for (j = 0; j < SLV_NUM; j++) begin : fwd_aw
         assign m2s_awvalid[i*SLV_NUM+j] = slv_aw_targeted[j] && i_awvalid[i] && !w_trk_valid;
      end

      // W data forward
      for (j = 0; j < SLV_NUM; j++) begin : fwd_wdat
         assign m2s_wvalid[i*SLV_NUM+j] = w_burst_active && i_wvalid[i] && w_trk_target[j];
      end

      wire aw_hs_targeted = i_awvalid[i] && i_awready[i] && |slv_aw_targeted;

      // W data tracking
      always_ff @(posedge aclk or negedge aresetn) begin
         if (!aresetn) begin
            w_trk_valid <= 1'b0;
            w_trk_target <= '0;
            w_burst_active <= 1'b0;
            w_hs_started <= 1'b0;
         end else if (aw_hs_targeted && !w_trk_valid) begin
            w_trk_valid <= 1'b1;
            w_trk_target <= slv_aw_targeted;
            w_burst_active <= 1'b1;
         end else begin
            if (w_burst_active && i_wvalid[i] && i_wready[i] && wlast_cur) begin
               w_burst_active <= 1'b0;
               w_trk_valid <= 1'b0;
               w_hs_started <= 1'b0;
            end else if (w_burst_active && !w_hs_started && i_wvalid[i] && i_wready[i]) begin
               w_hs_started <= 1'b1;
            end
         end
      end

      // B response tracking
      always_ff @(posedge aclk or negedge aresetn) begin
         if (!aresetn) begin
            b_trk_valid <= 1'b0;
            b_trk_target <= '0;
            b_trk_id <= '0;
            b_clear_pending <= 1'b0;
         end else if (aw_hs_targeted && !w_trk_valid) begin
            b_trk_valid <= 1'b1;
            b_trk_target <= slv_aw_targeted;
            b_trk_id <= awid_cur;
         end else begin
            if (b_clear_pending) begin
               b_trk_valid <= 1'b0;
               b_clear_pending <= 1'b0;
            end else if (b_trk_valid && i_bvalid[i] && i_bready[i]) begin
               b_clear_pending <= 1'b1;
            end
         end
      end

      // Write misrouting
      logic                misr_wr_active;
      logic [LEN_WIDTH-1:0] misr_wr_cnt;
      logic [ID_WIDTH-1:0] misr_wr_id;
      logic                misr_b_pending;

      // AW misrouting one-shot pulse: fires for 1 cycle on unmapped AW
      always_ff @(posedge aclk or negedge aresetn) begin
         if (!aresetn)
            aw_misrouting[i] <= 1'b0;
         else if (aw_misrouting[i])
            aw_misrouting[i] <= 1'b0;
         else if (i_awvalid[i] && slv_aw_targeted == '0)
            aw_misrouting[i] <= 1'b1;
      end

      // W drain + DECERR for misrouted write
      always_ff @(posedge aclk or negedge aresetn) begin
         if (!aresetn) begin
            misr_wr_active <= 1'b0;
            misr_wr_cnt <= '0;
            misr_wr_id <= '0;
            misr_b_pending <= 1'b0;
         end else begin
            if (aw_misrouting[i] && i_awvalid[i] && i_awready[i]) begin
               misr_wr_active <= 1'b1;
               misr_wr_id <= awid_cur;
               misr_wr_cnt <= i_awch[i*AWCH_WIDTH+AW_ID_LSB+ID_WIDTH+:LEN_WIDTH];
            end else if (misr_wr_active && i_wvalid[i] && i_wready[i]) begin
               if (wlast_cur || misr_wr_cnt == 0) begin
                  misr_wr_active <= 1'b0;
                  misr_b_pending <= 1'b1;
               end else begin
                  misr_wr_cnt <= misr_wr_cnt - 1'b1;
               end
            end else if (misr_b_pending && i_bready[i]) begin
               misr_b_pending <= 1'b0;
            end
         end
      end

      always_comb begin
         i_awready[i] = 1'b0;
         if (aw_misrouting[i]) begin
            i_awready[i] = 1'b1;
         end else begin
            for (int k = 0; k < SLV_NUM; k++) begin
               if (slv_aw_targeted[k]) begin
                  i_awready[i] = m2s_awready[i*SLV_NUM+k];
                  break;
               end
            end
         end
      end

      always_comb begin
         i_wready[i] = 1'b0;
         if (misr_wr_active) begin
            i_wready[i] = 1'b1;
         end else if (w_burst_active) begin
            for (int k = 0; k < SLV_NUM; k++) begin
               if (w_trk_target[k]) begin
                  i_wready[i] = m2s_wready[i*SLV_NUM+k];
                  break;
               end
            end
         end
      end

      always_comb begin
         i_bvalid[i] = 1'b0;
         i_bch[i*BCH_WIDTH+:BCH_WIDTH] = '0;
         if (misr_b_pending) begin
            i_bvalid[i] = 1'b1;
            i_bch[i*BCH_WIDTH+B_RESP_LSB+:RESP_WIDTH] = 2'b11;
            i_bch[i*BCH_WIDTH+B_ID_LSB+:ID_WIDTH] = misr_wr_id;
         end else if (b_trk_valid) begin
            for (int k = 0; k < SLV_NUM; k++) begin
               if (b_trk_target[k]) begin
                  i_bvalid[i] = m2s_bvalid[i*SLV_NUM+k];
                  i_bch[i*BCH_WIDTH+:BCH_WIDTH] = s2m_bch[k*BCH_WIDTH+:BCH_WIDTH];
                  break;
               end
            end
         end
      end

      always_comb begin
         for (int k = 0; k < SLV_NUM; k++) begin
            m2s_bready[i*SLV_NUM+k] = 1'b0;
         end
         if (b_trk_valid) begin
            for (int k = 0; k < SLV_NUM; k++) begin
               if (b_trk_target[k]) begin
                  m2s_bready[i*SLV_NUM+k] = i_bready[i];
                  break;
               end
            end
         end
      end
   end
endgenerate

// Read Address Decode + Register-based Tracking
generate
   for (i = 0; i < MST_NUM; i++) begin : slv_rd_switch
      logic [SLV_NUM-1:0] slv_ar_targeted;
      logic [SLV_NUM-1:0] r_trk_target;
      logic               r_trk_valid;
      logic               r_burst_active;

      wire [ID_WIDTH-1:0]  arid_cur  = i_arch[i*ARCH_WIDTH+AW_ID_LSB+:ID_WIDTH];
      wire                 rlast_cur = i_rch[i*RCH_WIDTH+R_LAST_LSB];

      for (j = 0; j < SLV_NUM; j++) begin : decode
         assign slv_ar_targeted[j] =
            (i_arch[i*ARCH_WIDTH+:ADDR_WIDTH] >= SLV_START_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]) &&
            (i_arch[i*ARCH_WIDTH+:ADDR_WIDTH] <= SLV_END_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]);
      end

      for (j = 0; j < SLV_NUM; j++) begin : fwd_ar
         assign m2s_arvalid[i*SLV_NUM+j] = slv_ar_targeted[j] && i_arvalid[i] && !r_trk_valid;
      end

      wire ar_valid_targeted = i_arvalid[i] && |slv_ar_targeted;

      always_ff @(posedge aclk or negedge aresetn) begin
         if (!aresetn) begin
            r_trk_valid <= 1'b0;
            r_trk_target <= '0;
            r_burst_active <= 1'b0;
          end else if (ar_valid_targeted && !r_trk_valid) begin
             r_trk_valid <= 1'b1;
             r_trk_target <= slv_ar_targeted;
             r_burst_active <= 1'b1;
          end else if (r_burst_active && i_rvalid[i] && i_rready[i] && rlast_cur) begin
             r_burst_active <= 1'b0;
             r_trk_valid <= 1'b0;
          end
      end

      logic misr_rd_active;
      logic [LEN_WIDTH-1:0] misr_rd_cnt;
      logic [ID_WIDTH-1:0]  misr_rd_id;

      // AR misrouting one-shot pulse
      always_ff @(posedge aclk or negedge aresetn) begin
         if (!aresetn)
            ar_misrouting[i] <= 1'b0;
         else if (ar_misrouting[i])
            ar_misrouting[i] <= 1'b0;
         else if (i_arvalid[i] && slv_ar_targeted == '0)
            ar_misrouting[i] <= 1'b1;
      end

      // R drain + DECERR for misrouted read
      always_ff @(posedge aclk or negedge aresetn) begin
         if (!aresetn) begin
            misr_rd_active <= 1'b0;
            misr_rd_cnt <= '0;
            misr_rd_id <= '0;
         end else begin
            if (ar_misrouting[i] && i_arvalid[i] && i_arready[i]) begin
               misr_rd_active <= 1'b1;
               misr_rd_id <= arid_cur;
               misr_rd_cnt <= i_arch[i*ARCH_WIDTH+AW_ID_LSB+ID_WIDTH+:LEN_WIDTH];
            end else if (misr_rd_active && i_rvalid[i] && i_rready[i]) begin
               if (misr_rd_cnt == 0) begin
                  misr_rd_active <= 1'b0;
               end else begin
                  misr_rd_cnt <= misr_rd_cnt - 1'b1;
               end
            end
         end
      end

      always_comb begin
         i_arready[i] = 1'b0;
         if (ar_misrouting[i]) begin
            i_arready[i] = 1'b1;
         end else begin
            for (int k = 0; k < SLV_NUM; k++) begin
               if (slv_ar_targeted[k]) begin
                  i_arready[i] = m2s_arready[i*SLV_NUM+k];
                  break;
               end
            end
         end
      end

      always_comb begin
         i_rvalid[i] = 1'b0;
         i_rch[i*RCH_WIDTH+:RCH_WIDTH] = '0;
         if (misr_rd_active) begin
            i_rvalid[i] = 1'b1;
            i_rch[i*RCH_WIDTH+R_DATA_LSB+:DATA_WIDTH] = '0;
            i_rch[i*RCH_WIDTH+R_RESP_LSB+:RESP_WIDTH] = 2'b11;
            i_rch[i*RCH_WIDTH+R_ID_LSB+:ID_WIDTH] = misr_rd_id;
            i_rch[i*RCH_WIDTH+R_LAST_LSB] = (misr_rd_cnt == 0);
         end else if (r_burst_active) begin
            for (int k = 0; k < SLV_NUM; k++) begin
               if (r_trk_target[k]) begin
                  i_rvalid[i] = m2s_rvalid[i*SLV_NUM+k];
                  i_rch[i*RCH_WIDTH+:RCH_WIDTH] = s2m_rch[k*RCH_WIDTH+:RCH_WIDTH];
                  break;
               end
            end
         end
      end

      always_comb begin
         for (int k = 0; k < SLV_NUM; k++) begin
            m2s_rready[i*SLV_NUM+k] = 1'b0;
         end
         if (r_burst_active) begin
            for (int k = 0; k < SLV_NUM; k++) begin
               if (r_trk_target[k]) begin
                  m2s_rready[i*SLV_NUM+k] = i_rready[i];
                  break;
               end
            end
         end
      end
   end
endgenerate

// Matrix Transpose
generate
   for (i = 0; i < MST_NUM; i++) begin : tr_i
      for (j = 0; j < SLV_NUM; j++) begin : tr_j
         assign s2m_awvalid[j*MST_NUM+i] = m2s_awvalid[i*SLV_NUM+j];
         assign m2s_awready[i*SLV_NUM+j] = s2m_awready[j*MST_NUM+i];
         assign s2m_wvalid[j*MST_NUM+i]  = m2s_wvalid[i*SLV_NUM+j];
         assign m2s_wready[i*SLV_NUM+j]  = s2m_wready[j*MST_NUM+i];
         assign s2m_arvalid[j*MST_NUM+i] = m2s_arvalid[i*SLV_NUM+j];
         assign m2s_arready[i*SLV_NUM+j] = s2m_arready[j*MST_NUM+i];
         assign m2s_bvalid[i*SLV_NUM+j] = s2m_bvalid[j*MST_NUM+i];
         assign s2m_bready[j*MST_NUM+i] = m2s_bready[i*SLV_NUM+j];
         assign m2s_rvalid[i*SLV_NUM+j] = s2m_rvalid[j*MST_NUM+i];
         assign s2m_rready[j*MST_NUM+i] = m2s_rready[i*SLV_NUM+j];
      end
   end
endgenerate

generate
   for (j = 0; j < SLV_NUM; j++) begin : rch_share
      assign s2m_bch[j*BCH_WIDTH+:BCH_WIDTH] = o_bch[j*BCH_WIDTH+:BCH_WIDTH];
      assign s2m_rch[j*RCH_WIDTH+:RCH_WIDTH] = o_rch[j*RCH_WIDTH+:RCH_WIDTH];
   end
endgenerate

// Master-Side Write Switch
generate
   for (j = 0; j < SLV_NUM; j++) begin : mst_wr_switch
      logic [MST_NUM-1:0] aw_grant;
      logic               aw_arb_en;

      wire [MST_NUM-1:0] aw_req_masked;
      genvar awk;
      for (awk = 0; awk < MST_NUM; awk++) begin
         assign aw_req_masked[awk] = s2m_awvalid[j*MST_NUM+awk] &&
                                     !(aw_grant[awk] && o_awready[j]);
      end

      arbiter #(
         .PORTS               ( MST_NUM ),
         .PRIORITY_WIDTH      ( PRIORITY_WIDTH ),
         .PRIORITY_CFG        ( MST_PRIORITY )
      ) u_aw_arb (
         .clk                 ( aclk ),
         .rst                 ( !aresetn ),
         .en                  ( aw_arb_en ),
         .request             ( aw_req_masked ),
         .grant               ( aw_grant ),
         .selsect             (  )
      );

      assign o_awvalid[j] = |aw_grant;

      always_comb begin
         o_awch[j*AWCH_WIDTH+:AWCH_WIDTH] = '0;
         for (int k = 0; k < MST_NUM; k++) begin
            if (aw_grant[k]) begin
               o_awch[j*AWCH_WIDTH+:AWCH_WIDTH] = i_awch[k*AWCH_WIDTH+:AWCH_WIDTH];
            end
         end
      end

      always_comb begin
         for (int k = 0; k < MST_NUM; k++) begin
            s2m_awready[j*MST_NUM+k] = aw_grant[k] && o_awready[j];
         end
      end

      assign aw_arb_en = (|aw_grant) ? o_awready[j] : |s2m_awvalid[j*MST_NUM+:MST_NUM];

      wire wlast_from_grp = o_wch[j*WCH_WIDTH+W_LAST_LSB];

      // o_wvalid = any master has W data for this slave
      // W data mux = pick the master with W valid (priority-encoded)
      always_comb begin
         o_wvalid[j] = 1'b0;
         o_wch[j*WCH_WIDTH+:WCH_WIDTH] = '0;
         for (int k = 0; k < MST_NUM; k++) begin
            if (s2m_wvalid[j*MST_NUM+k]) begin
               o_wvalid[j] = 1'b1;
               o_wch[j*WCH_WIDTH+:WCH_WIDTH] = i_wch[k*WCH_WIDTH+:WCH_WIDTH];
               break;
            end
         end
      end

      // s2m_wready = grant W ready to whichever master has W data
      always_comb begin
         for (int k = 0; k < MST_NUM; k++) begin
            s2m_wready[j*MST_NUM+k] = s2m_wvalid[j*MST_NUM+k] && o_wready[j];
         end
      end

      // B response: ID mask routing
      wire [ID_WIDTH-1:0] bid_from_slv = o_bch[j*BCH_WIDTH+B_ID_LSB+:ID_WIDTH];

      always_comb begin
         for (int k = 0; k < MST_NUM; k++) begin
            s2m_bvalid[j*MST_NUM+k] = o_bvalid[j] &&
               ((MST_ID_MASK[k*ID_WIDTH+:ID_WIDTH] & bid_from_slv) == MST_ID_MASK[k*ID_WIDTH+:ID_WIDTH]);
         end
      end

      always_comb begin
         o_bready[j] = 1'b0;
         for (int k = 0; k < MST_NUM; k++) begin
            if (s2m_bvalid[j*MST_NUM+k]) begin
               o_bready[j] = s2m_bready[j*MST_NUM+k];
               break;
            end
         end
      end
   end
endgenerate

// Master-Side Read Switch
generate
   for (j = 0; j < SLV_NUM; j++) begin : mst_rd_switch
      logic [MST_NUM-1:0] ar_grant;
      logic               ar_arb_en;

      wire [MST_NUM-1:0] ar_req_masked;
      genvar ark;
      for (ark = 0; ark < MST_NUM; ark++) begin
         assign ar_req_masked[ark] = s2m_arvalid[j*MST_NUM+ark] &&
                                     !(ar_grant[ark] && o_arready[j]);
      end

      arbiter #(
         .PORTS               ( MST_NUM ),
         .PRIORITY_WIDTH      ( PRIORITY_WIDTH ),
         .PRIORITY_CFG        ( MST_PRIORITY )
      ) u_ar_arb (
         .clk                 ( aclk ),
         .rst                 ( !aresetn ),
         .en                  ( ar_arb_en ),
         .request             ( ar_req_masked ),
         .grant               ( ar_grant ),
         .selsect             (  )
      );

      assign o_arvalid[j] = |ar_grant;

      always_comb begin
         o_arch[j*ARCH_WIDTH+:ARCH_WIDTH] = '0;
         for (int k = 0; k < MST_NUM; k++) begin
            if (ar_grant[k]) begin
               o_arch[j*ARCH_WIDTH+:ARCH_WIDTH] = i_arch[k*ARCH_WIDTH+:ARCH_WIDTH];
            end
         end
      end

      always_comb begin
         for (int k = 0; k < MST_NUM; k++) begin
            s2m_arready[j*MST_NUM+k] = ar_grant[k] && o_arready[j];
         end
      end

      assign ar_arb_en = (|ar_grant) ? o_arready[j] : |s2m_arvalid[j*MST_NUM+:MST_NUM];

      wire [ID_WIDTH-1:0] rid_from_slv = o_rch[j*RCH_WIDTH+R_ID_LSB+:ID_WIDTH];

      always_comb begin
         for (int k = 0; k < MST_NUM; k++) begin
            s2m_rvalid[j*MST_NUM+k] = o_rvalid[j] &&
               ((MST_ID_MASK[k*ID_WIDTH+:ID_WIDTH] & rid_from_slv) == MST_ID_MASK[k*ID_WIDTH+:ID_WIDTH]);
         end
      end

      always_comb begin
         o_rready[j] = 1'b0;
         for (int k = 0; k < MST_NUM; k++) begin
            if (s2m_rvalid[j*MST_NUM+k]) begin
               o_rready[j] = s2m_rready[j*MST_NUM+k];
               break;
            end
         end
      end
   end
endgenerate

// Master Interface
generate
   for (j = 0; j < SLV_NUM; j++) begin : mst_if
      logic [ADDR_WIDTH-1:0] base = SLV_START_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH];
      logic [ADDR_WIDTH-1:0] awaddr_xlat;
      logic [ADDR_WIDTH-1:0] araddr_xlat;

      wire [ADDR_WIDTH-1:0] awaddr_raw = o_awch[j*AWCH_WIDTH+AW_ADDR_LSB+:ADDR_WIDTH];
      wire [ADDR_WIDTH-1:0] araddr_raw = o_arch[j*ARCH_WIDTH+AW_ADDR_LSB+:ADDR_WIDTH];

      if (SLV_KEEP_BASE[j]) begin
         assign awaddr_xlat = awaddr_raw;
         assign araddr_xlat = araddr_raw;
      end else begin
         assign awaddr_xlat = awaddr_raw - base;
         assign araddr_xlat = araddr_raw - base;
      end

      if (SLV_BUF_EN[j]) begin : buffer_on
         localparam BD = SLV_BUF_DEPTH[j*16+:16];
         wire [AWCH_WIDTH-1:0] aw_rd;
         wire [WCH_WIDTH-1:0]  w_rd;
         wire [ARCH_WIDTH-1:0] ar_rd;
         wire [ADDR_WIDTH-1:0] awaddr_buf = aw_rd[ADDR_WIDTH-1:0];
         wire [ADDR_WIDTH-1:0] araddr_buf = ar_rd[ADDR_WIDTH-1:0];
         wire [ADDR_WIDTH-1:0] awaddr_xlat_buf = SLV_KEEP_BASE[j] ? awaddr_buf : (awaddr_buf - base);
         wire [ADDR_WIDTH-1:0] araddr_xlat_buf = SLV_KEEP_BASE[j] ? araddr_buf : (araddr_buf - base);
         wire aw_full, aw_empty, w_full, w_empty, b_full, b_empty;
         wire ar_full, ar_empty, r_full, r_empty;

         sync_fifo #(
            .WIDTH               ( AWCH_WIDTH ),
            .DEPTH               ( BD ),
            .FWFT                ( "true" )
         ) u_aw (
            .clk                 ( aclk ),
            .rst                 ( ~aresetn ),
            .wr_en               ( o_awvalid[j] && !aw_full ),
            .wr_data             ( o_awch[j*AWCH_WIDTH+:AWCH_WIDTH] ),
            .full                ( aw_full ),
            .rd_en               ( axi_mst_if[j].awready ),
            .rd_data             ( aw_rd ),
            .empty               ( aw_empty ),
            .overflow            ( ),
            .underflow           ( ),
            .level               ( )
         );

         assign o_awready[j] = !aw_full;
         assign axi_mst_if[j].awvalid = !aw_empty;
         assign {axi_mst_if[j].awregion, axi_mst_if[j].awqos, axi_mst_if[j].awprot,
                 axi_mst_if[j].awcache,  axi_mst_if[j].awlock, axi_mst_if[j].awburst,
                 axi_mst_if[j].awsize,   axi_mst_if[j].awlen,
                 axi_mst_if[j].awid} = aw_rd[AWCH_WIDTH-1:ADDR_WIDTH];
         assign axi_mst_if[j].awaddr = awaddr_xlat_buf;

         sync_fifo #(
            .WIDTH               ( WCH_WIDTH ),
            .DEPTH               ( BD ),
            .FWFT                ( "true" )
         ) u_w (
            .clk                 ( aclk ),
            .rst                 ( ~aresetn ),
            .wr_en               ( o_wvalid[j] && !w_full ),
            .wr_data             ( o_wch[j*WCH_WIDTH+:WCH_WIDTH] ),
            .full                ( w_full ),
            .rd_en               ( axi_mst_if[j].wready ),
            .rd_data             ( w_rd ),
            .empty               ( w_empty ),
            .overflow            ( ),
            .underflow           ( ),
            .level               ( )
         );
         assign o_wready[j] = !w_full;
         assign axi_mst_if[j].wvalid = !w_empty;
         assign {axi_mst_if[j].wdata, axi_mst_if[j].wstrb, axi_mst_if[j].wlast, axi_mst_if[j].wid} = w_rd;

         sync_fifo #(
            .WIDTH               ( BCH_WIDTH ),
            .DEPTH               ( BD ),
            .FWFT                ( "true" )
         ) u_b (
            .clk                 ( aclk ),
            .rst                 ( ~aresetn ),
            .wr_en               ( axi_mst_if[j].bvalid && !b_full ),
            .wr_data             ( {axi_mst_if[j].bresp, axi_mst_if[j].bid} ),
            .full                ( b_full ),
            .rd_en               ( o_bready[j] ),
            .rd_data             ( o_bch[j*BCH_WIDTH+:BCH_WIDTH] ),
            .empty               ( b_empty ),
            .overflow            ( ),
            .underflow           ( ),
            .level               ( )
         );
         assign o_bvalid[j] = !b_empty;
         assign axi_mst_if[j].bready = !b_full;

         sync_fifo #(
            .WIDTH               ( ARCH_WIDTH ),
            .DEPTH               ( BD ),
            .FWFT                ( "true" )
         ) u_ar (
            .clk                 ( aclk ),
            .rst                 ( ~aresetn ),
            .wr_en               ( o_arvalid[j] && !ar_full ),
            .wr_data             ( o_arch[j*ARCH_WIDTH+:ARCH_WIDTH] ),
            .full                ( ar_full ),
            .rd_en               ( axi_mst_if[j].arready ),
            .rd_data             ( ar_rd ),
            .empty               ( ar_empty ),
            .overflow            ( ),
            .underflow           ( ),
            .level               ( )
         );
         assign o_arready[j] = !ar_full;
         assign axi_mst_if[j].arvalid = !ar_empty;
         assign {axi_mst_if[j].arregion, axi_mst_if[j].arqos, axi_mst_if[j].arprot,
                 axi_mst_if[j].arcache,  axi_mst_if[j].arlock, axi_mst_if[j].arburst,
                 axi_mst_if[j].arsize,   axi_mst_if[j].arlen,
                 axi_mst_if[j].arid} = ar_rd[ARCH_WIDTH-1:ADDR_WIDTH];
         assign axi_mst_if[j].araddr = araddr_xlat_buf;

         sync_fifo #(
            .WIDTH               ( RCH_WIDTH ),
            .DEPTH               ( BD ),
            .FWFT                ( "true" )
         ) u_r (
            .clk                 ( aclk ),
            .rst                 ( ~aresetn ),
            .wr_en               ( axi_mst_if[j].rvalid && !r_full ),
            .wr_data             ( {axi_mst_if[j].rdata, axi_mst_if[j].rresp, axi_mst_if[j].rid, axi_mst_if[j].rlast} ),
            .full                ( r_full ),
            .rd_en               ( o_rready[j] ),
            .rd_data             ( o_rch[j*RCH_WIDTH+:RCH_WIDTH] ),
            .empty               ( r_empty ),
            .overflow            ( ),
            .underflow           ( ),
            .level               ( )
         );
         assign o_rvalid[j] = !r_empty;
         assign axi_mst_if[j].rready = !r_full;

      end else begin : buffer_off
         wire [AWCH_WIDTH-1:0] aw_tmp = o_awch[j*AWCH_WIDTH+:AWCH_WIDTH];
         assign {axi_mst_if[j].awregion, axi_mst_if[j].awqos, axi_mst_if[j].awprot,
                 axi_mst_if[j].awcache,  axi_mst_if[j].awlock, axi_mst_if[j].awburst,
                 axi_mst_if[j].awsize,   axi_mst_if[j].awlen,
                 axi_mst_if[j].awid} = aw_tmp[AWCH_WIDTH-1:ADDR_WIDTH];
         assign axi_mst_if[j].awaddr = awaddr_xlat;
         assign axi_mst_if[j].awvalid = o_awvalid[j];
         assign o_awready[j] = axi_mst_if[j].awready;

         wire [WCH_WIDTH-1:0] w_tmp = o_wch[j*WCH_WIDTH+:WCH_WIDTH];
         assign {axi_mst_if[j].wdata, axi_mst_if[j].wstrb, axi_mst_if[j].wlast, axi_mst_if[j].wid} = w_tmp;
         assign axi_mst_if[j].wvalid = o_wvalid[j];
         assign o_wready[j] = axi_mst_if[j].wready;

         assign o_bch[j*BCH_WIDTH+:BCH_WIDTH] = {axi_mst_if[j].bresp, axi_mst_if[j].bid};
         assign o_bvalid[j] = axi_mst_if[j].bvalid;
         assign axi_mst_if[j].bready = o_bready[j];

         wire [ARCH_WIDTH-1:0] ar_tmp = o_arch[j*ARCH_WIDTH+:ARCH_WIDTH];
         assign {axi_mst_if[j].arregion, axi_mst_if[j].arqos, axi_mst_if[j].arprot,
                 axi_mst_if[j].arcache,  axi_mst_if[j].arlock, axi_mst_if[j].arburst,
                 axi_mst_if[j].arsize,   axi_mst_if[j].arlen,
                 axi_mst_if[j].arid} = ar_tmp[ARCH_WIDTH-1:ADDR_WIDTH];
         assign axi_mst_if[j].araddr = araddr_xlat;
         assign axi_mst_if[j].arvalid = o_arvalid[j];
         assign o_arready[j] = axi_mst_if[j].arready;

         assign o_rch[j*RCH_WIDTH+:RCH_WIDTH] = {axi_mst_if[j].rdata, axi_mst_if[j].rresp, axi_mst_if[j].rid, axi_mst_if[j].rlast};
         assign o_rvalid[j] = axi_mst_if[j].rvalid;
         assign axi_mst_if[j].rready = o_rready[j];
      end
   end
endgenerate

endmodule

`resetall
