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
   parameter                     M_NUM = 4,
   parameter                     S_NUM = 4,
   parameter                     ADDR_WIDTH = 32,
   parameter                     DATA_WIDTH = 64,
   parameter                     PRIORITY_WIDTH = 4,
   parameter                     AUX_RAM_STYLE = "distributed",
   parameter                     S_ID_WIDTH = 8,
   parameter bit                 S_BUF_EN    [0:S_NUM-1] = '{default:1'b0},
   parameter int                 S_BUF_DEPTH [0:S_NUM-1] = '{default:16'd0},
   parameter string              S_RAM_STYLE [0:S_NUM-1] = '{default:"block"},
   parameter                     S_PRIORITY = {S_NUM*PRIORITY_WIDTH{1'b0}},
   parameter                     M_ID_WIDTH = S_ID_WIDTH + $clog2(M_NUM),
   parameter bit                 M_BUF_EN    [0:M_NUM-1] = '{default:1'b0},
   parameter int                 M_BUF_DEPTH [0:M_NUM-1] = '{default:16'd0},
   parameter string              M_RAM_STYLE [0:M_NUM-1] = '{default:"block"},
   parameter                     M_START_ADDR = {M_NUM*ADDR_WIDTH{1'b0}},
   parameter                     M_END_ADDR = {M_NUM*ADDR_WIDTH{1'b1}},
   parameter                     M_KEEP_BASE = {M_NUM{1'b0}}
)(
   input  wire                   clk,
   input  wire                   rst,

   if_axi.slave                  s_axi_ifs [0:S_NUM-1],
   if_axi.master                 m_axi_ifs [0:M_NUM-1]
);

// Derived parameters
localparam STRB_WIDTH    = DATA_WIDTH / 8;
localparam LEN_WIDTH     = 8;
localparam RESP_WIDTH    = 2;
localparam EXTRA_ID_BITS = M_ID_WIDTH - S_ID_WIDTH;

localparam S_AWCH_WIDTH = ADDR_WIDTH + S_ID_WIDTH + 29;
localparam S_WCH_WIDTH  = DATA_WIDTH + STRB_WIDTH + 1 + S_ID_WIDTH;
localparam S_ARCH_WIDTH = S_AWCH_WIDTH;

localparam AWCH_WIDTH = ADDR_WIDTH + M_ID_WIDTH + 29;
localparam WCH_WIDTH  = DATA_WIDTH + STRB_WIDTH + 1 + M_ID_WIDTH;
localparam BCH_WIDTH  = RESP_WIDTH + M_ID_WIDTH;
localparam RCH_WIDTH  = DATA_WIDTH + RESP_WIDTH + M_ID_WIDTH + 1;
localparam ARCH_WIDTH = AWCH_WIDTH;

// Flat signal declarations
genvar i, j;
logic [S_NUM            -1:0]    i_awvalid;
logic [S_NUM            -1:0]    i_awready;
logic [S_NUM*S_AWCH_WIDTH -1:0]  i_awch;
logic [S_NUM            -1:0]    i_wvalid;
logic [S_NUM            -1:0]    i_wready;
logic [S_NUM*S_WCH_WIDTH -1:0]   i_wch;
logic [S_NUM            -1:0]    i_bvalid;
logic [S_NUM            -1:0]    i_bready;
logic [S_NUM*BCH_WIDTH  -1:0]    i_bch;
logic [S_NUM            -1:0]    i_arvalid;
logic [S_NUM            -1:0]    i_arready;
logic [S_NUM*S_ARCH_WIDTH -1:0]  i_arch;
logic [S_NUM            -1:0]    i_rvalid;
logic [S_NUM            -1:0]    i_rready;
logic [S_NUM*RCH_WIDTH  -1:0]    i_rch;

logic [M_NUM            -1:0]    o_awvalid;
logic [M_NUM            -1:0]    o_awready;
logic [M_NUM*AWCH_WIDTH -1:0]    o_awch;
logic [M_NUM            -1:0]    o_wvalid;
logic [M_NUM            -1:0]    o_wready;
logic [M_NUM*WCH_WIDTH  -1:0]    o_wch;
logic [M_NUM            -1:0]    o_bvalid;
logic [M_NUM            -1:0]    o_bready;
logic [M_NUM*BCH_WIDTH  -1:0]    o_bch;
logic [M_NUM            -1:0]    o_arvalid;
logic [M_NUM            -1:0]    o_arready;
logic [M_NUM*ARCH_WIDTH -1:0]    o_arch;
logic [M_NUM            -1:0]    o_rvalid;
logic [M_NUM            -1:0]    o_rready;
logic [M_NUM*RCH_WIDTH  -1:0]    o_rch;

logic [S_NUM*M_NUM      -1:0]    m2s_awvalid;
logic [S_NUM*M_NUM      -1:0]    m2s_awready;
logic [S_NUM*M_NUM      -1:0]    m2s_wvalid;
logic [S_NUM*M_NUM      -1:0]    m2s_wready;
logic [S_NUM*M_NUM      -1:0]    m2s_arvalid;
logic [S_NUM*M_NUM      -1:0]    m2s_arready;

logic [M_NUM*S_NUM      -1:0]    s2m_awvalid;
logic [M_NUM*S_NUM      -1:0]    s2m_awready;
logic [M_NUM*S_NUM      -1:0]    s2m_wvalid;
logic [M_NUM*S_NUM      -1:0]    s2m_wready;
logic [M_NUM*S_NUM      -1:0]    s2m_arvalid;
logic [M_NUM*S_NUM      -1:0]    s2m_arready;

logic [M_NUM*S_NUM      -1:0]    s2m_bvalid;
logic [M_NUM*S_NUM      -1:0]    s2m_bready;
logic [M_NUM*S_NUM      -1:0]    s2m_rvalid;
logic [M_NUM*S_NUM      -1:0]    s2m_rready;
logic [M_NUM*BCH_WIDTH  -1:0]    s2m_bch;
logic [M_NUM*RCH_WIDTH  -1:0]    s2m_rch;

logic [S_NUM*M_NUM      -1:0]    m2s_bvalid;
logic [S_NUM*M_NUM      -1:0]    m2s_bready;
logic [S_NUM*M_NUM      -1:0]    m2s_rvalid;
logic [S_NUM*M_NUM      -1:0]    m2s_rready;

logic [S_NUM            -1:0]    aw_misrouting;
logic [S_NUM            -1:0]    ar_misrouting;

initial begin
   for (integer m = 0; m < S_NUM; m++) begin
      if (s_axi_ifs[m].ADDR_WIDTH != ADDR_WIDTH)
         $error("s_axi_ifs[%0d].ADDR_WIDTH (%0d) != ADDR_WIDTH (%0d)", m, s_axi_ifs[m].ADDR_WIDTH, ADDR_WIDTH);
      if (s_axi_ifs[m].DATA_WIDTH != DATA_WIDTH)
         $error("s_axi_ifs[%0d].DATA_WIDTH (%0d) != DATA_WIDTH (%0d)", m, s_axi_ifs[m].DATA_WIDTH, DATA_WIDTH);
   end
end

initial begin
   for (integer m = 0; m < S_NUM; m++) begin
      if (s_axi_ifs[m].ID_WIDTH != S_ID_WIDTH)
         $error("s_axi_ifs[%0d].ID_WIDTH (%0d) != S_ID_WIDTH (%0d)", m, s_axi_ifs[m].ID_WIDTH, S_ID_WIDTH);
   end
end

initial begin
   for (integer n = 0; n < M_NUM; n++) begin
      if (m_axi_ifs[n].ID_WIDTH < M_ID_WIDTH)
         $error("m_axi_ifs[%0d].ID_WIDTH (%0d) < M_ID_WIDTH (%0d)", n, m_axi_ifs[n].ID_WIDTH, M_ID_WIDTH);
   end
end

initial begin
   if (M_ID_WIDTH < S_ID_WIDTH + $clog2(M_NUM)) begin
      $error("M_ID_WIDTH (%0d) must be >= S_ID_WIDTH (%0d) + $clog2(M_NUM) (%0d)",
             M_ID_WIDTH, S_ID_WIDTH, $clog2(M_NUM));
      $finish;
   end
end

initial begin
   for (integer m = 0; m < S_NUM; m++) begin
      if (S_BUF_EN[m]) begin
         if (S_BUF_DEPTH[m] < 2)
            $error("S_BUF_EN[%0d] enabled but S_BUF_DEPTH[%0d]=%0d (< 2)", m, m, S_BUF_DEPTH[m]);
         if ((S_BUF_DEPTH[m] & (S_BUF_DEPTH[m] - 1)) != 0)
            $error("S_BUF_EN[%0d] enabled but S_BUF_DEPTH[%0d]=%0d (not power-of-2)", m, m, S_BUF_DEPTH[m]);
      end
   end
end

initial begin
   for (integer n = 0; n < M_NUM; n++) begin
      if (M_BUF_EN[n]) begin
         if (M_BUF_DEPTH[n] < 2)
            $error("M_BUF_EN[%0d] enabled but M_BUF_DEPTH[%0d]=%0d (< 2)", n, n, M_BUF_DEPTH[n]);
         if ((M_BUF_DEPTH[n] & (M_BUF_DEPTH[n] - 1)) != 0)
            $error("M_BUF_EN[%0d] enabled but M_BUF_DEPTH[%0d]=%0d (not power-of-2)", n, n, M_BUF_DEPTH[n]);
      end
   end
end

// Slave Interface
generate
   for (i = 0; i < S_NUM; i++) begin : S_if
      logic [S_AWCH_WIDTH -1:0] awch;
      logic [S_WCH_WIDTH  -1:0] wch;
      logic [BCH_WIDTH    -1:0] bch;
      logic [S_ARCH_WIDTH -1:0] arch;
      logic [RCH_WIDTH    -1:0] rch;

      assign awch = {s_axi_ifs[i].awregion, s_axi_ifs[i].awqos, s_axi_ifs[i].awprot,
                     s_axi_ifs[i].awcache,  s_axi_ifs[i].awlock, s_axi_ifs[i].awburst,
                     s_axi_ifs[i].awsize,   s_axi_ifs[i].awlen,
                     s_axi_ifs[i].awid,     s_axi_ifs[i].awaddr};
      assign wch  = {s_axi_ifs[i].wdata, s_axi_ifs[i].wstrb, s_axi_ifs[i].wlast,
                     s_axi_ifs[i].wid};
      assign arch = {s_axi_ifs[i].arregion, s_axi_ifs[i].arqos, s_axi_ifs[i].arprot,
                     s_axi_ifs[i].arcache,  s_axi_ifs[i].arlock, s_axi_ifs[i].arburst,
                     s_axi_ifs[i].arsize,   s_axi_ifs[i].arlen,
                     s_axi_ifs[i].arid,     s_axi_ifs[i].araddr};

      if (S_BUF_EN[i]) begin : buffer_on
         wire w_full, w_empty, r_full, r_empty;

         skid_buffer #(
            .WIDTH               ( S_AWCH_WIDTH )
         ) u_aw (
            .clk                 ( clk ),
            .rst                 ( rst ),
            .data_i              ( awch ),
            .valid_i             ( s_axi_ifs[i].awvalid ),
            .ready_o             ( s_axi_ifs[i].awready ),
            .data_o              ( i_awch[i*S_AWCH_WIDTH+:S_AWCH_WIDTH] ),
            .valid_o             ( i_awvalid[i] ),
            .ready_i             ( i_awready[i] )
         );

          sync_fifo #(
            .WIDTH               ( S_WCH_WIDTH ),
            .DEPTH               ( S_BUF_DEPTH[i] ),
            .FWFT                ( "true" ),
            .RAM_STYLE           ( S_RAM_STYLE[i] )
          ) u_w (
            .clk                 ( clk ),
            .rst                 ( rst ),
            .wr_en               ( s_axi_ifs[i].wvalid && !w_full ),
            .wr_data             ( wch ),
            .full                ( w_full ),
            .rd_en               ( i_wready[i] ),
            .rd_data             ( i_wch[i*S_WCH_WIDTH+:S_WCH_WIDTH] ),
            .empty               ( w_empty ),
            .overflow            ( ),
            .underflow           ( ),
            .level               ( )
         );

         assign s_axi_ifs[i].wready = !w_full;
         assign i_wvalid[i] = !w_empty;

         skid_buffer #(
            .WIDTH               ( BCH_WIDTH )
         ) u_b (
            .clk                 ( clk ),
            .rst                 ( rst ),
            .data_i              ( i_bch[i*BCH_WIDTH+:BCH_WIDTH] ),
            .valid_i             ( i_bvalid[i] ),
            .ready_o             ( i_bready[i] ),
            .data_o              ( bch ),
            .valid_o             ( s_axi_ifs[i].bvalid ),
            .ready_i             ( s_axi_ifs[i].bready )
         );

         skid_buffer #(
            .WIDTH               ( S_ARCH_WIDTH )
         ) u_ar (
            .clk                 ( clk ),
            .rst                 ( rst ),
            .data_i              ( arch ),
            .valid_i             ( s_axi_ifs[i].arvalid ),
            .ready_o             ( s_axi_ifs[i].arready ),
            .data_o              ( i_arch[i*S_ARCH_WIDTH+:S_ARCH_WIDTH] ),
            .valid_o             ( i_arvalid[i] ),
            .ready_i             ( i_arready[i] )
         );

          sync_fifo #(
            .WIDTH               ( RCH_WIDTH ),
            .DEPTH               ( S_BUF_DEPTH[i] ),
            .FWFT                ( "true" ),
            .RAM_STYLE           ( S_RAM_STYLE[i] )
          ) u_r (
            .clk                 ( clk ),
            .rst                 ( rst ),
            .wr_en               ( i_rvalid[i] ),
            .wr_data             ( i_rch[i*RCH_WIDTH+:RCH_WIDTH] ),
            .full                ( r_full ),
            .rd_en               ( s_axi_ifs[i].rready ),
            .rd_data             ( rch ),
            .empty               ( r_empty ),
            .overflow            ( ),
            .underflow           ( ),
            .level               ( )
         );
         assign i_rready[i] = !r_full;
         assign s_axi_ifs[i].rvalid = !r_empty;

         assign s_axi_ifs[i].bid   = bch[0+:S_ID_WIDTH];
         assign s_axi_ifs[i].bresp = bch[M_ID_WIDTH+:RESP_WIDTH];
         assign s_axi_ifs[i].rlast = rch[0];
         assign s_axi_ifs[i].rid   = rch[1+:S_ID_WIDTH];
         assign s_axi_ifs[i].rresp = rch[1+M_ID_WIDTH+:RESP_WIDTH];
         assign s_axi_ifs[i].rdata = rch[1+M_ID_WIDTH+RESP_WIDTH+:DATA_WIDTH];

      end else begin : buffer_off
         assign i_awvalid[i] = s_axi_ifs[i].awvalid;
         assign s_axi_ifs[i].awready = i_awready[i];
         assign i_awch[i*S_AWCH_WIDTH+:S_AWCH_WIDTH] = awch;
         assign i_wvalid[i] = s_axi_ifs[i].wvalid;
         assign s_axi_ifs[i].wready = i_wready[i];
         assign i_wch[i*S_WCH_WIDTH+:S_WCH_WIDTH] = wch;
         assign s_axi_ifs[i].bvalid = i_bvalid[i];
         assign i_bready[i] = s_axi_ifs[i].bready;
         assign s_axi_ifs[i].bid   = i_bch[i*BCH_WIDTH+0+:S_ID_WIDTH];
         assign s_axi_ifs[i].bresp = i_bch[i*BCH_WIDTH+M_ID_WIDTH+:RESP_WIDTH];
         assign i_arvalid[i] = s_axi_ifs[i].arvalid;
         assign s_axi_ifs[i].arready = i_arready[i];
         assign i_arch[i*S_ARCH_WIDTH+:S_ARCH_WIDTH] = arch;
         assign s_axi_ifs[i].rvalid = i_rvalid[i];
         assign i_rready[i] = s_axi_ifs[i].rready;
         assign s_axi_ifs[i].rlast = i_rch[i*RCH_WIDTH+0];
         assign s_axi_ifs[i].rid   = i_rch[i*RCH_WIDTH+1+:S_ID_WIDTH];
         assign s_axi_ifs[i].rresp = i_rch[i*RCH_WIDTH+1+M_ID_WIDTH+:RESP_WIDTH];
         assign s_axi_ifs[i].rdata = i_rch[i*RCH_WIDTH+1+M_ID_WIDTH+RESP_WIDTH+:DATA_WIDTH];
      end
   end
endgenerate

// Write Address Decode + Register-based Tracking
generate
   for (i = 0; i < S_NUM; i++) begin : S_wr_switch
      logic [M_NUM-1:0] S_aw_targeted;
      logic [M_NUM-1:0] w_trk_target;
      logic               w_trk_valid;
      logic               w_burst_active;
      logic               w_hs_started;
      logic               b_trk_valid;
      logic [M_NUM-1:0] b_trk_target;
      logic [S_ID_WIDTH-1:0] b_trk_id;
      logic               b_clear_pending;

      wire [S_ID_WIDTH-1:0]  awid_cur  = i_awch[i*S_AWCH_WIDTH+ADDR_WIDTH+:S_ID_WIDTH];
      wire                 wlast_cur = i_wch[i*S_WCH_WIDTH+S_ID_WIDTH];

      for (j = 0; j < M_NUM; j++) begin : decode
         assign S_aw_targeted[j] =
            (i_awch[i*S_AWCH_WIDTH+:ADDR_WIDTH] >= M_START_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]) &&
            (i_awch[i*S_AWCH_WIDTH+:ADDR_WIDTH] <= M_END_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]);
      end

      // AW forward: gated by W tracking not active
      for (j = 0; j < M_NUM; j++) begin : fwd_aw
         assign m2s_awvalid[i*M_NUM+j] = S_aw_targeted[j] && i_awvalid[i] && !w_trk_valid;
      end

      // W data forward
      for (j = 0; j < M_NUM; j++) begin : fwd_wdat
         assign m2s_wvalid[i*M_NUM+j] = w_burst_active && i_wvalid[i] && w_trk_target[j];
      end

      wire aw_hs_targeted = i_awvalid[i] && i_awready[i] && |S_aw_targeted;

      // W data tracking
      always_ff @(posedge clk or posedge rst) begin
         if (rst) begin
            w_trk_valid <= 1'b0;
            w_trk_target <= '0;
            w_burst_active <= 1'b0;
            w_hs_started <= 1'b0;
         end else if (aw_hs_targeted && !w_trk_valid) begin
            w_trk_valid <= 1'b1;
            w_trk_target <= S_aw_targeted;
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
      always_ff @(posedge clk or posedge rst) begin
         if (rst) begin
            b_trk_valid <= 1'b0;
            b_trk_target <= '0;
            b_trk_id <= '0;
            b_clear_pending <= 1'b0;
         end else if (aw_hs_targeted && !w_trk_valid) begin
            b_trk_valid <= 1'b1;
            b_trk_target <= S_aw_targeted;
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
      logic [S_ID_WIDTH-1:0] misr_wr_id;
      logic                misr_b_pending;

      // AW misrouting one-shot pulse: fires for 1 cycle on unmapped AW
      always_ff @(posedge clk or posedge rst) begin
         if (rst)
            aw_misrouting[i] <= 1'b0;
         else if (aw_misrouting[i])
            aw_misrouting[i] <= 1'b0;
         else if (i_awvalid[i] && S_aw_targeted == '0)
            aw_misrouting[i] <= 1'b1;
      end

      // W drain + DECERR for misrouted write
      always_ff @(posedge clk or posedge rst) begin
         if (rst) begin
            misr_wr_active <= 1'b0;
            misr_wr_cnt <= '0;
            misr_wr_id <= '0;
            misr_b_pending <= 1'b0;
         end else begin
            if (aw_misrouting[i] && i_awvalid[i] && i_awready[i]) begin
               misr_wr_active <= 1'b1;
               misr_wr_id <= awid_cur;
               misr_wr_cnt <= i_awch[i*S_AWCH_WIDTH+ADDR_WIDTH+S_ID_WIDTH+:LEN_WIDTH];
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
            for (int k = 0; k < M_NUM; k++) begin
               if (S_aw_targeted[k]) begin
                  i_awready[i] = m2s_awready[i*M_NUM+k];
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
            for (int k = 0; k < M_NUM; k++) begin
               if (w_trk_target[k]) begin
                  i_wready[i] = m2s_wready[i*M_NUM+k];
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
            i_bch[i*BCH_WIDTH+M_ID_WIDTH+:RESP_WIDTH] = 2'b11;
            i_bch[i*BCH_WIDTH+0+:S_ID_WIDTH] = misr_wr_id;
         end else if (b_trk_valid) begin
            for (int k = 0; k < M_NUM; k++) begin
               if (b_trk_target[k]) begin
                  i_bvalid[i] = m2s_bvalid[i*M_NUM+k];
                  i_bch[i*BCH_WIDTH+:BCH_WIDTH] = s2m_bch[k*BCH_WIDTH+:BCH_WIDTH];
                  break;
               end
            end
         end
      end

      always_comb begin
         for (int k = 0; k < M_NUM; k++) begin
            m2s_bready[i*M_NUM+k] = 1'b0;
         end
         if (b_trk_valid) begin
            for (int k = 0; k < M_NUM; k++) begin
               if (b_trk_target[k]) begin
                  m2s_bready[i*M_NUM+k] = i_bready[i];
                  break;
               end
            end
         end
      end
   end
endgenerate

// Read Address Decode + Register-based Tracking
generate
   for (i = 0; i < S_NUM; i++) begin : S_rd_switch
      logic [M_NUM-1:0] S_ar_targeted;
      logic [M_NUM-1:0] r_trk_target;
      logic               r_trk_valid;
      logic               r_burst_active;

      wire [S_ID_WIDTH-1:0]  arid_cur  = i_arch[i*S_ARCH_WIDTH+ADDR_WIDTH+:S_ID_WIDTH];
      wire                rlast_cur = i_rch[i*RCH_WIDTH+0];

      for (j = 0; j < M_NUM; j++) begin : decode
         assign S_ar_targeted[j] =
            (i_arch[i*S_ARCH_WIDTH+:ADDR_WIDTH] >= M_START_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]) &&
            (i_arch[i*S_ARCH_WIDTH+:ADDR_WIDTH] <= M_END_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]);
      end

      for (j = 0; j < M_NUM; j++) begin : fwd_ar
         assign m2s_arvalid[i*M_NUM+j] = S_ar_targeted[j] && i_arvalid[i] && !r_trk_valid;
      end

      wire ar_valid_targeted = i_arvalid[i] && |S_ar_targeted;

      always_ff @(posedge clk or posedge rst) begin
         if (rst) begin
            r_trk_valid <= 1'b0;
            r_trk_target <= '0;
            r_burst_active <= 1'b0;
          end else if (ar_valid_targeted && !r_trk_valid) begin
            r_trk_valid <= 1'b1;
            r_trk_target <= S_ar_targeted;
            r_burst_active <= 1'b1;
          end else if (r_burst_active && i_rvalid[i] && i_rready[i] && rlast_cur) begin
            r_burst_active <= 1'b0;
            r_trk_valid <= 1'b0;
          end
      end

      logic misr_rd_active;
      logic [LEN_WIDTH-1:0] misr_rd_cnt;
      logic [S_ID_WIDTH-1:0]  misr_rd_id;

      // AR misrouting one-shot pulse
      always_ff @(posedge clk or posedge rst) begin
         if (rst)
            ar_misrouting[i] <= 1'b0;
         else if (ar_misrouting[i])
            ar_misrouting[i] <= 1'b0;
         else if (i_arvalid[i] && S_ar_targeted == '0)
            ar_misrouting[i] <= 1'b1;
      end

      // R drain + DECERR for misrouted read
      always_ff @(posedge clk or posedge rst) begin
         if (rst) begin
            misr_rd_active <= 1'b0;
            misr_rd_cnt <= '0;
            misr_rd_id <= '0;
         end else begin
            if (ar_misrouting[i] && i_arvalid[i] && i_arready[i]) begin
               misr_rd_active <= 1'b1;
               misr_rd_id <= arid_cur;
               misr_rd_cnt <= i_arch[i*S_ARCH_WIDTH+ADDR_WIDTH+S_ID_WIDTH+:LEN_WIDTH];
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
            for (int k = 0; k < M_NUM; k++) begin
               if (S_ar_targeted[k]) begin
                  i_arready[i] = m2s_arready[i*M_NUM+k];
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
            i_rch[i*RCH_WIDTH+1+M_ID_WIDTH+RESP_WIDTH+:DATA_WIDTH] = '0;
            i_rch[i*RCH_WIDTH+1+M_ID_WIDTH+:RESP_WIDTH] = 2'b11;
            i_rch[i*RCH_WIDTH+1+:S_ID_WIDTH] = misr_rd_id;
            i_rch[i*RCH_WIDTH+0] = (misr_rd_cnt == 0);
         end else if (r_burst_active) begin
            for (int k = 0; k < M_NUM; k++) begin
               if (r_trk_target[k]) begin
                  i_rvalid[i] = m2s_rvalid[i*M_NUM+k];
                  i_rch[i*RCH_WIDTH+:RCH_WIDTH] = s2m_rch[k*RCH_WIDTH+:RCH_WIDTH];
                  break;
               end
            end
         end
      end

      always_comb begin
         for (int k = 0; k < M_NUM; k++) begin
            m2s_rready[i*M_NUM+k] = 1'b0;
         end
         if (r_burst_active) begin
            for (int k = 0; k < M_NUM; k++) begin
               if (r_trk_target[k]) begin
                  m2s_rready[i*M_NUM+k] = i_rready[i];
                  break;
               end
            end
         end
      end
   end
endgenerate

// Matrix Transpose
generate
   for (i = 0; i < S_NUM; i++) begin : tr_i
      for (j = 0; j < M_NUM; j++) begin : tr_j
         assign s2m_awvalid[j*S_NUM+i] = m2s_awvalid[i*M_NUM+j];
         assign m2s_awready[i*M_NUM+j] = s2m_awready[j*S_NUM+i];
         assign s2m_wvalid[j*S_NUM+i]  = m2s_wvalid[i*M_NUM+j];
         assign m2s_wready[i*M_NUM+j]  = s2m_wready[j*S_NUM+i];
         assign s2m_arvalid[j*S_NUM+i] = m2s_arvalid[i*M_NUM+j];
         assign m2s_arready[i*M_NUM+j] = s2m_arready[j*S_NUM+i];
         assign m2s_bvalid[i*M_NUM+j] = s2m_bvalid[j*S_NUM+i];
         assign s2m_bready[j*S_NUM+i] = m2s_bready[i*M_NUM+j];
         assign m2s_rvalid[i*M_NUM+j] = s2m_rvalid[j*S_NUM+i];
         assign s2m_rready[j*S_NUM+i] = m2s_rready[i*M_NUM+j];
      end
   end
endgenerate

generate
   for (j = 0; j < M_NUM; j++) begin : rch_share
      assign s2m_bch[j*BCH_WIDTH+:BCH_WIDTH] = o_bch[j*BCH_WIDTH+:BCH_WIDTH];
      assign s2m_rch[j*RCH_WIDTH+:RCH_WIDTH] = o_rch[j*RCH_WIDTH+:RCH_WIDTH];
   end
endgenerate

// Master-Side Write Switch
generate
   for (j = 0; j < M_NUM; j++) begin : M_wr_switch
      logic [S_NUM-1:0] aw_grant;
      logic               aw_arb_en;

      wire [S_NUM-1:0] aw_req_masked;
      wire [$clog2(S_NUM)-1:0] aw_grant_encoded;
      genvar awk;
      for (awk = 0; awk < S_NUM; awk++) begin
         assign aw_req_masked[awk] = s2m_awvalid[j*S_NUM+awk] &&
                                     !(aw_grant[awk] && o_awready[j]);
      end

      arbiter #(
         .PORTS               ( S_NUM ),
         .PRIORITY_WIDTH      ( PRIORITY_WIDTH ),
         .PRIORITY_CFG        ( S_PRIORITY )
      ) u_aw_arb (
         .clk                 ( clk ),
         .rst                 ( rst ),
         .en                  ( aw_arb_en ),
         .request             ( aw_req_masked ),
         .grant               ( aw_grant ),
         .select             ( aw_grant_encoded )
      );

      assign o_awvalid[j] = |aw_grant;

      always_comb begin
         o_awch[j*AWCH_WIDTH+:AWCH_WIDTH] = '0;
         for (int k = 0; k < S_NUM; k++) begin
            if (aw_grant[k]) begin
               o_awch[j*AWCH_WIDTH+:AWCH_WIDTH] = {
                   i_awch[k*S_AWCH_WIDTH+:S_AWCH_WIDTH][S_AWCH_WIDTH-1 : ADDR_WIDTH+S_ID_WIDTH],
                   {EXTRA_ID_BITS{1'b0}},
                   i_awch[k*S_AWCH_WIDTH+:S_AWCH_WIDTH][ADDR_WIDTH+S_ID_WIDTH-1:0]
               };
            end
         end
         o_awch[j*AWCH_WIDTH+ADDR_WIDTH+:M_ID_WIDTH] |= ({{M_ID_WIDTH-$clog2(S_NUM){1'b0}}, aw_grant_encoded} << S_ID_WIDTH);
      end

      always_comb begin
         for (int k = 0; k < S_NUM; k++) begin
            s2m_awready[j*S_NUM+k] = aw_grant[k] && o_awready[j];
         end
      end

      assign aw_arb_en = (|aw_grant) ? o_awready[j] : |s2m_awvalid[j*S_NUM+:S_NUM];

      wire wlast_from_grp = o_wch[j*WCH_WIDTH+M_ID_WIDTH];

      // o_wvalid = any master has W data for this slave
      // W data mux = pick the master with W valid (priority-encoded)
      always_comb begin
         o_wvalid[j] = 1'b0;
         o_wch[j*WCH_WIDTH+:WCH_WIDTH] = '0;
         for (int k = 0; k < S_NUM; k++) begin
            if (s2m_wvalid[j*S_NUM+k]) begin
               o_wvalid[j] = 1'b1;
               o_wch[j*WCH_WIDTH+:WCH_WIDTH] = {
                   i_wch[k*S_WCH_WIDTH+:S_WCH_WIDTH][S_WCH_WIDTH-1 : 1+S_ID_WIDTH],
                   i_wch[k*S_WCH_WIDTH+:S_WCH_WIDTH][S_ID_WIDTH],
                   {EXTRA_ID_BITS{1'b0}},
                   i_wch[k*S_WCH_WIDTH+:S_WCH_WIDTH][S_ID_WIDTH-1:0]
               };
               break;
            end
         end
      end

      // s2m_wready = grant W ready only to the selected master
      always_comb begin
         for (int k = 0; k < S_NUM; k++) begin
            s2m_wready[j*S_NUM+k] = 1'b0;
         end
         for (int k = 0; k < S_NUM; k++) begin
            if (s2m_wvalid[j*S_NUM+k]) begin
               s2m_wready[j*S_NUM+k] = o_wready[j];
               break;
            end
         end
      end

      // B response: ID extension routing
      wire [M_ID_WIDTH-1:0] bid_from_slv = o_bch[j*BCH_WIDTH+0+:M_ID_WIDTH];
      wire [$clog2(S_NUM)-1:0] bid_M_idx = bid_from_slv >> S_ID_WIDTH;

      always_comb begin
         s2m_bvalid[j*S_NUM+:S_NUM] = '0;
         if (o_bvalid[j])
            s2m_bvalid[j*S_NUM+bid_M_idx] = 1'b1;
      end

      always_comb begin
         o_bready[j] = 1'b0;
         if (o_bvalid[j])
            o_bready[j] = s2m_bready[j*S_NUM+bid_M_idx];
      end
   end
endgenerate

// Master-Side Read Switch
generate
   for (j = 0; j < M_NUM; j++) begin : M_rd_switch
      logic [S_NUM-1:0] ar_grant;
      logic               ar_arb_en;

      wire [S_NUM-1:0] ar_req_masked;
      wire [$clog2(S_NUM)-1:0] ar_grant_encoded;
      genvar ark;
      for (ark = 0; ark < S_NUM; ark++) begin
         assign ar_req_masked[ark] = s2m_arvalid[j*S_NUM+ark] &&
                                     !(ar_grant[ark] && o_arready[j]);
      end

      arbiter #(
         .PORTS               ( S_NUM ),
         .PRIORITY_WIDTH      ( PRIORITY_WIDTH ),
         .PRIORITY_CFG        ( S_PRIORITY )
      ) u_ar_arb (
         .clk                 ( clk ),
         .rst                 ( rst ),
         .en                  ( ar_arb_en ),
         .request             ( ar_req_masked ),
         .grant               ( ar_grant ),
         .select             ( ar_grant_encoded )
      );

      assign o_arvalid[j] = |ar_grant;

      always_comb begin
         o_arch[j*ARCH_WIDTH+:ARCH_WIDTH] = '0;
         for (int k = 0; k < S_NUM; k++) begin
            if (ar_grant[k]) begin
               o_arch[j*ARCH_WIDTH+:ARCH_WIDTH] = {
                   i_arch[k*S_ARCH_WIDTH+:S_ARCH_WIDTH][S_ARCH_WIDTH-1 : ADDR_WIDTH+S_ID_WIDTH],
                   {EXTRA_ID_BITS{1'b0}},
                   i_arch[k*S_ARCH_WIDTH+:S_ARCH_WIDTH][ADDR_WIDTH+S_ID_WIDTH-1:0]
               };
            end
         end
         o_arch[j*ARCH_WIDTH+ADDR_WIDTH+:M_ID_WIDTH] |= ({{M_ID_WIDTH-$clog2(S_NUM){1'b0}}, ar_grant_encoded} << S_ID_WIDTH);
      end

      always_comb begin
         for (int k = 0; k < S_NUM; k++) begin
            s2m_arready[j*S_NUM+k] = ar_grant[k] && o_arready[j];
         end
      end

      assign ar_arb_en = (|ar_grant) ? o_arready[j] : |s2m_arvalid[j*S_NUM+:S_NUM];

      wire [M_ID_WIDTH-1:0] rid_from_slv = o_rch[j*RCH_WIDTH+1+:M_ID_WIDTH];
      wire [$clog2(S_NUM)-1:0] rid_M_idx = rid_from_slv >> S_ID_WIDTH;

      always_comb begin
         s2m_rvalid[j*S_NUM+:S_NUM] = '0;
         if (o_rvalid[j])
            s2m_rvalid[j*S_NUM+rid_M_idx] = 1'b1;
      end

      always_comb begin
         o_rready[j] = 1'b0;
         if (o_rvalid[j])
            o_rready[j] = s2m_rready[j*S_NUM+rid_M_idx];
      end
   end
endgenerate

// Master Interface
generate
   for (j = 0; j < M_NUM; j++) begin : M_if
      logic [ADDR_WIDTH-1:0] base = M_START_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH];
      logic [ADDR_WIDTH-1:0] awaddr_xlat;
      logic [ADDR_WIDTH-1:0] araddr_xlat;

      wire [ADDR_WIDTH-1:0] awaddr_raw = o_awch[j*AWCH_WIDTH+0+:ADDR_WIDTH];
      wire [ADDR_WIDTH-1:0] araddr_raw = o_arch[j*ARCH_WIDTH+0+:ADDR_WIDTH];

      if (M_KEEP_BASE[j]) begin
         assign awaddr_xlat = awaddr_raw;
         assign araddr_xlat = araddr_raw;
      end else begin
         assign awaddr_xlat = awaddr_raw - base;
         assign araddr_xlat = araddr_raw - base;
      end

      if (M_BUF_EN[j]) begin : buffer_on
         wire [AWCH_WIDTH-1:0] aw_rd;
         wire [WCH_WIDTH-1:0]  w_rd;
         wire [ARCH_WIDTH-1:0] ar_rd;
         wire [ADDR_WIDTH-1:0] awaddr_buf = aw_rd[ADDR_WIDTH-1:0];
         wire [ADDR_WIDTH-1:0] araddr_buf = ar_rd[ADDR_WIDTH-1:0];
         wire [ADDR_WIDTH-1:0] awaddr_xlat_buf = M_KEEP_BASE[j] ? awaddr_buf : (awaddr_buf - base);
         wire [ADDR_WIDTH-1:0] araddr_xlat_buf = M_KEEP_BASE[j] ? araddr_buf : (araddr_buf - base);
         wire w_full, w_empty, r_full, r_empty;

         skid_buffer #(
            .WIDTH               ( AWCH_WIDTH )
         ) u_aw (
            .clk                 ( clk ),
            .rst                 ( rst ),
            .data_i              ( o_awch[j*AWCH_WIDTH+:AWCH_WIDTH] ),
            .valid_i             ( o_awvalid[j] ),
            .ready_o             ( o_awready[j] ),
            .data_o              ( aw_rd ),
            .valid_o             ( m_axi_ifs[j].awvalid ),
            .ready_i             ( m_axi_ifs[j].awready )
         );
         assign {m_axi_ifs[j].awregion, m_axi_ifs[j].awqos, m_axi_ifs[j].awprot,
                 m_axi_ifs[j].awcache,  m_axi_ifs[j].awlock, m_axi_ifs[j].awburst,
                 m_axi_ifs[j].awsize,   m_axi_ifs[j].awlen,
                 m_axi_ifs[j].awid} = aw_rd[AWCH_WIDTH-1:ADDR_WIDTH];
         assign m_axi_ifs[j].awaddr = awaddr_xlat_buf;

          sync_fifo #(
            .WIDTH               ( WCH_WIDTH ),
            .DEPTH               ( M_BUF_DEPTH[j] ),
            .FWFT                ( "true" ),
            .RAM_STYLE           ( M_RAM_STYLE[j] )
           ) u_w (
            .clk                 ( clk ),
            .rst                 ( rst ),
            .wr_en               ( o_wvalid[j] && !w_full ),
            .wr_data             ( o_wch[j*WCH_WIDTH+:WCH_WIDTH] ),
            .full                ( w_full ),
            .rd_en               ( m_axi_ifs[j].wready ),
            .rd_data             ( w_rd ),
            .empty               ( w_empty ),
            .overflow            ( ),
            .underflow           ( ),
            .level               ( )
         );

         assign o_wready[j] = !w_full;
         assign m_axi_ifs[j].wvalid = !w_empty;
         assign {m_axi_ifs[j].wdata, m_axi_ifs[j].wstrb, m_axi_ifs[j].wlast, m_axi_ifs[j].wid} = w_rd;

         skid_buffer #(
            .WIDTH               ( BCH_WIDTH )
         ) u_b (
            .clk                 ( clk ),
            .rst                 ( rst ),
            .data_i              ( {m_axi_ifs[j].bresp, m_axi_ifs[j].bid} ),
            .valid_i             ( m_axi_ifs[j].bvalid ),
            .ready_o             ( m_axi_ifs[j].bready ),
            .data_o              ( o_bch[j*BCH_WIDTH+:BCH_WIDTH] ),
            .valid_o             ( o_bvalid[j] ),
            .ready_i             ( o_bready[j] )
         );

         skid_buffer #(
            .WIDTH               ( ARCH_WIDTH )
         ) u_ar (
            .clk                 ( clk ),
            .rst                 ( rst ),
            .data_i              ( o_arch[j*ARCH_WIDTH+:ARCH_WIDTH] ),
            .valid_i             ( o_arvalid[j] ),
            .ready_o             ( o_arready[j] ),
            .data_o              ( ar_rd ),
            .valid_o             ( m_axi_ifs[j].arvalid ),
            .ready_i             ( m_axi_ifs[j].arready )
         );
         assign {m_axi_ifs[j].arregion, m_axi_ifs[j].arqos, m_axi_ifs[j].arprot,
                 m_axi_ifs[j].arcache,  m_axi_ifs[j].arlock, m_axi_ifs[j].arburst,
                 m_axi_ifs[j].arsize,   m_axi_ifs[j].arlen,
                 m_axi_ifs[j].arid} = ar_rd[ARCH_WIDTH-1:ADDR_WIDTH];
         assign m_axi_ifs[j].araddr = araddr_xlat_buf;

         sync_fifo #(
            .WIDTH               ( RCH_WIDTH ),
            .DEPTH               ( M_BUF_DEPTH[j] ),
            .FWFT                ( "true" ),
            .RAM_STYLE           ( M_RAM_STYLE[j] )
           ) u_r (
            .clk                 ( clk ),
            .rst                 ( rst ),
            .wr_en               ( m_axi_ifs[j].rvalid && !r_full ),
            .wr_data             ( {m_axi_ifs[j].rdata, m_axi_ifs[j].rresp, m_axi_ifs[j].rid, m_axi_ifs[j].rlast} ),
            .full                ( r_full ),
            .rd_en               ( o_rready[j] ),
            .rd_data             ( o_rch[j*RCH_WIDTH+:RCH_WIDTH] ),
            .empty               ( r_empty ),
            .overflow            ( ),
            .underflow           ( ),
            .level               ( )
         );

         assign o_rvalid[j] = !r_empty;
         assign m_axi_ifs[j].rready = !r_full;

      end else begin : buffer_off
         wire [AWCH_WIDTH-1:0] aw_tmp = o_awch[j*AWCH_WIDTH+:AWCH_WIDTH];
         assign {m_axi_ifs[j].awregion, m_axi_ifs[j].awqos, m_axi_ifs[j].awprot,
                 m_axi_ifs[j].awcache,  m_axi_ifs[j].awlock, m_axi_ifs[j].awburst,
                 m_axi_ifs[j].awsize,   m_axi_ifs[j].awlen,
                 m_axi_ifs[j].awid} = aw_tmp[AWCH_WIDTH-1:ADDR_WIDTH];
         assign m_axi_ifs[j].awaddr = awaddr_xlat;
         assign m_axi_ifs[j].awvalid = o_awvalid[j];
         assign o_awready[j] = m_axi_ifs[j].awready;

         wire [WCH_WIDTH-1:0] w_tmp = o_wch[j*WCH_WIDTH+:WCH_WIDTH];
         assign {m_axi_ifs[j].wdata, m_axi_ifs[j].wstrb, m_axi_ifs[j].wlast, m_axi_ifs[j].wid} = w_tmp;
         assign m_axi_ifs[j].wvalid = o_wvalid[j];
         assign o_wready[j] = m_axi_ifs[j].wready;

         assign o_bch[j*BCH_WIDTH+:BCH_WIDTH] = {m_axi_ifs[j].bresp, m_axi_ifs[j].bid};
         assign o_bvalid[j] = m_axi_ifs[j].bvalid;
         assign m_axi_ifs[j].bready = o_bready[j];

         wire [ARCH_WIDTH-1:0] ar_tmp = o_arch[j*ARCH_WIDTH+:ARCH_WIDTH];
         assign {m_axi_ifs[j].arregion, m_axi_ifs[j].arqos, m_axi_ifs[j].arprot,
                 m_axi_ifs[j].arcache,  m_axi_ifs[j].arlock, m_axi_ifs[j].arburst,
                 m_axi_ifs[j].arsize,   m_axi_ifs[j].arlen,
                 m_axi_ifs[j].arid} = ar_tmp[ARCH_WIDTH-1:ADDR_WIDTH];
         assign m_axi_ifs[j].araddr = araddr_xlat;
         assign m_axi_ifs[j].arvalid = o_arvalid[j];
         assign o_arready[j] = m_axi_ifs[j].arready;

         assign o_rch[j*RCH_WIDTH+:RCH_WIDTH] = {m_axi_ifs[j].rdata, m_axi_ifs[j].rresp, m_axi_ifs[j].rid, m_axi_ifs[j].rlast};
         assign o_rvalid[j] = m_axi_ifs[j].rvalid;
         assign m_axi_ifs[j].rready = o_rready[j];
      end
   end
endgenerate

endmodule

`resetall
