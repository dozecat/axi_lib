//*****************************************************************************
// Copyright (C) 2026 dozecat. All rights reserved.
// SPDX-License-Identifier: MIT
//
// File:        axil_interconnect.sv
// Description: AXI4-Lite Interconnect
// Repository:  https://github.com/dozecat/axi_lib.git
//
// Modification History:
// Ver   Who       Date        Changes
// ----  ----  ----------  ----------------------------------------------------
// 1.0         2026/5/1    Initial release
//*****************************************************************************

`timescale 1ns / 1ps
`default_nettype none

module axil_interconnect
#(
   parameter S_NUM               = 4, // Slave interface number (connect to external masters)
   parameter M_NUM               = 4, // Master interface number (connect to external slaves)
   parameter ADDR_WIDTH          = 16,
   parameter DATA_WIDTH          = 32,
   parameter PRIORITY_WIDTH      = 4,
   parameter TRK_DEPTH           = 4,
   parameter TRK_RAM_STYLE       = "distributed",
   parameter S_SKID_EN           = {S_NUM{1'b0}},
   parameter S_PRIORITY          = {S_NUM*PRIORITY_WIDTH{1'b0}},
   parameter M_SKID_EN           = {M_NUM{1'b0}},
   parameter M_START_ADDR        = {M_NUM*ADDR_WIDTH{1'b0}},
   parameter M_END_ADDR          = {M_NUM*ADDR_WIDTH{1'b1}},
   parameter M_KEEP_BASE         = {M_NUM{1'b0}}
)(
   input  wire                   clk,
   input  wire                   rst,

   if_axil.slave                 s_axil_ifs [0:S_NUM-1],
   if_axil.master                m_axil_ifs [0:M_NUM-1]
);

// Local declarations
localparam STRB_WIDTH = DATA_WIDTH / 8;
localparam AWCH_WIDTH = ADDR_WIDTH + 3;
localparam WCH_WIDTH  = DATA_WIDTH + STRB_WIDTH;
localparam BCH_WIDTH  = 2;
localparam ARCH_WIDTH = ADDR_WIDTH + 3;
localparam RCH_WIDTH  = DATA_WIDTH + 2;
// Internal flat channel signals
genvar i, j;
logic [S_NUM            -1:0]    i_awvalid;
logic [S_NUM            -1:0]    i_awready;
logic [S_NUM*AWCH_WIDTH -1:0]    i_awch;
logic [S_NUM            -1:0]    i_wvalid;
logic [S_NUM            -1:0]    i_wready;
logic [S_NUM*WCH_WIDTH  -1:0]    i_wch;
logic [S_NUM            -1:0]    i_bvalid;
logic [S_NUM            -1:0]    i_bready;
logic [S_NUM*BCH_WIDTH  -1:0]    i_bch;
logic [S_NUM            -1:0]    i_arvalid;
logic [S_NUM            -1:0]    i_arready;
logic [S_NUM*ARCH_WIDTH -1:0]    i_arch;
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
   for (integer s = 0; s < S_NUM; s++) begin
      if (s_axil_ifs[s].ADDR_WIDTH != ADDR_WIDTH)
         $error("s_axil_ifs[%0d].ADDR_WIDTH (%0d) != ADDR_WIDTH (%0d)", s, s_axil_ifs[s].ADDR_WIDTH, ADDR_WIDTH);
      if (s_axil_ifs[s].DATA_WIDTH != DATA_WIDTH)
         $error("s_axil_ifs[%0d].DATA_WIDTH (%0d) != DATA_WIDTH (%0d)", s, s_axil_ifs[s].DATA_WIDTH, DATA_WIDTH);
   end
end

// SLAVE INTERFACE (per slave port)
generate
   for (i = 0; i < S_NUM; i++) begin : S_if
      logic [AWCH_WIDTH  -1:0]   awch;
      logic [WCH_WIDTH   -1:0]   wch;
      logic [BCH_WIDTH   -1:0]   bch;
      logic [ARCH_WIDTH  -1:0]   arch;
      logic [RCH_WIDTH   -1:0]   rch;

      assign awch = {s_axil_ifs[i].awprot, s_axil_ifs[i].awaddr};
      assign wch  = {s_axil_ifs[i].wdata,  s_axil_ifs[i].wstrb};
      assign arch = {s_axil_ifs[i].arprot, s_axil_ifs[i].araddr};

      if (S_SKID_EN[i]) begin : buffer_on

          skid_buffer #(
             .WIDTH               ( AWCH_WIDTH )
          ) u_aw (
             .clk                 ( clk ),
             .rst                 ( rst ),
             .data_i              ( awch ),
             .valid_i             ( s_axil_ifs[i].awvalid ),
             .ready_o             ( s_axil_ifs[i].awready ),
             .data_o              ( i_awch[i*AWCH_WIDTH+:AWCH_WIDTH] ),
             .valid_o             ( i_awvalid[i] ),
             .ready_i             ( i_awready[i] )
          );

          skid_buffer #(
             .WIDTH               ( WCH_WIDTH )
          ) u_w (
             .clk                 ( clk ),
             .rst                 ( rst ),
             .data_i              ( wch ),
             .valid_i             ( s_axil_ifs[i].wvalid ),
             .ready_o             ( s_axil_ifs[i].wready ),
             .data_o              ( i_wch[i*WCH_WIDTH+:WCH_WIDTH] ),
             .valid_o             ( i_wvalid[i] ),
             .ready_i             ( i_wready[i] )
          );

          skid_buffer #(
             .WIDTH               ( BCH_WIDTH )
          ) u_b (
             .clk                 ( clk ),
             .rst                 ( rst ),
             .data_i              ( i_bch[i*BCH_WIDTH+:BCH_WIDTH] ),
             .valid_i             ( i_bvalid[i] ),
             .ready_o             ( i_bready[i] ),
             .data_o              ( bch ),
             .valid_o             ( s_axil_ifs[i].bvalid ),
             .ready_i             ( s_axil_ifs[i].bready )
          );
          assign {s_axil_ifs[i].bresp} = bch;

          skid_buffer #(
             .WIDTH               ( ARCH_WIDTH )
          ) u_ar (
             .clk                 ( clk ),
             .rst                 ( rst ),
             .data_i              ( arch ),
             .valid_i             ( s_axil_ifs[i].arvalid ),
             .ready_o             ( s_axil_ifs[i].arready ),
             .data_o              ( i_arch[i*ARCH_WIDTH+:ARCH_WIDTH] ),
             .valid_o             ( i_arvalid[i] ),
             .ready_i             ( i_arready[i] )
          );

          skid_buffer #(
             .WIDTH               ( RCH_WIDTH )
          ) u_r (
             .clk                 ( clk ),
             .rst                 ( rst ),
             .data_i              ( i_rch[i*RCH_WIDTH+:RCH_WIDTH] ),
             .valid_i             ( i_rvalid[i] ),
             .ready_o             ( i_rready[i] ),
             .data_o              ( rch ),
             .valid_o             ( s_axil_ifs[i].rvalid ),
             .ready_i             ( s_axil_ifs[i].rready )
          );
          assign {s_axil_ifs[i].rdata, s_axil_ifs[i].rresp} = rch;

      end else begin : buffer_off

         assign i_awvalid[i] = s_axil_ifs[i].awvalid;
         assign s_axil_ifs[i].awready = i_awready[i];
         assign i_awch[i*AWCH_WIDTH+:AWCH_WIDTH] = awch;

         assign i_wvalid[i] = s_axil_ifs[i].wvalid;
         assign s_axil_ifs[i].wready = i_wready[i];
         assign i_wch[i*WCH_WIDTH+:WCH_WIDTH] = wch;

         assign s_axil_ifs[i].bvalid = i_bvalid[i];
         assign i_bready[i] = s_axil_ifs[i].bready;
         assign bch = i_bch[i*BCH_WIDTH+:BCH_WIDTH];
         assign {s_axil_ifs[i].bresp} = bch;

         assign i_arvalid[i] = s_axil_ifs[i].arvalid;
         assign s_axil_ifs[i].arready = i_arready[i];
         assign i_arch[i*ARCH_WIDTH+:ARCH_WIDTH] = arch;

         assign s_axil_ifs[i].rvalid = i_rvalid[i];
         assign i_rready[i] = s_axil_ifs[i].rready;
         assign rch = i_rch[i*RCH_WIDTH+:RCH_WIDTH];
         assign {s_axil_ifs[i].rdata, s_axil_ifs[i].rresp} = rch;
      end
   end
endgenerate

// ADDRESS DECODE + WRITE TRACKING (per slave port)
generate
   for (i = 0; i < S_NUM; i++) begin : S_wr_switch
      logic [M_NUM      -1:0] S_aw_targeted;
      logic [M_NUM      -1:0] S_w_target;
      logic [M_NUM      -1:0] S_b_target;
      logic                     w_trk_full;
      logic                     w_trk_empty;
      logic                     b_trk_full;
      logic                     b_trk_empty;

      for (j = 0; j < M_NUM; j++) begin : decode
         assign S_aw_targeted[j] =
            (i_awch[i*AWCH_WIDTH+:ADDR_WIDTH] >= M_START_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]) &&
            (i_awch[i*AWCH_WIDTH+:ADDR_WIDTH] <= M_END_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]);
      end

      for (j = 0; j < M_NUM; j++) begin : fwd
         assign m2s_awvalid[i*M_NUM+j] = S_aw_targeted[j] && i_awvalid[i] && !w_trk_full;
         assign m2s_wvalid[i*M_NUM+j]  = !w_trk_empty && S_w_target[j] && i_wvalid[i];
      end

      always_comb begin
         i_awready[i] = aw_misrouting[i];
         for (int k = 0; k < M_NUM; k++) begin
            if (S_aw_targeted[k]) begin
               i_awready[i] = m2s_awready[i*M_NUM+k];
               break;
            end
         end
      end

      sync_fifo #(
         .WIDTH               ( M_NUM ),
         .DEPTH               ( TRK_DEPTH ),
         .FWFT                ( "true" ),
         .RAM_STYLE           ( TRK_RAM_STYLE )
      ) u_wtrk (
         .clk                 ( clk ),
         .rst                 ( rst ),
         .wr_en               ( i_awvalid[i] && i_awready[i] ),
         .wr_data             ( S_aw_targeted ),
         .full                ( w_trk_full ),
         .rd_en               ( i_wvalid[i] && i_wready[i] ),
         .rd_data             ( S_w_target ),
         .empty               ( w_trk_empty ),
         .overflow            ( ),
         .underflow           ( ),
         .level               ( )
      );

      sync_fifo #(
         .WIDTH               ( M_NUM ),
         .DEPTH               ( TRK_DEPTH ),
         .FWFT                ( "true" ),
         .RAM_STYLE           ( TRK_RAM_STYLE )
      ) u_btrk (
         .clk                 ( clk ),
         .rst                 ( rst ),
         .wr_en               ( i_awvalid[i] && i_awready[i] ),
         .wr_data             ( S_aw_targeted ),
         .full                ( b_trk_full ),
         .rd_en               ( i_bvalid[i] && i_bready[i] ),
         .rd_data             ( S_b_target ),
         .empty               ( b_trk_empty ),
         .overflow            ( ),
         .underflow           ( ),
         .level               ( )
      );

      always_comb begin
         i_wready[i] = 1'b0;
         if (!w_trk_empty) begin
            for (int k = 0; k < M_NUM; k++) begin
               if (S_w_target[k]) begin
                  i_wready[i] = m2s_wready[i*M_NUM+k];
                  break;
               end
            end
         end
      end

      always_comb begin
         i_bvalid[i] = 1'b0;
         i_bch[i*BCH_WIDTH+:BCH_WIDTH] = '0;
         if (!b_trk_empty) begin
            for (int k = 0; k < M_NUM; k++) begin
               if (S_b_target[k]) begin
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
         if (!b_trk_empty) begin
            for (int k = 0; k < M_NUM; k++) begin
               if (S_b_target[k]) begin
                  m2s_bready[i*M_NUM+k] = i_bready[i];
                  break;
               end
            end
         end
      end

      always_ff @(posedge clk or posedge rst) begin
         if (rst) begin
            aw_misrouting[i] <= 1'b0;
         end else begin
            if (aw_misrouting[i]) begin
               aw_misrouting[i] <= 1'b0;
            end else if (i_awvalid[i] && S_aw_targeted == '0) begin
               aw_misrouting[i] <= 1'b1;
            end
         end
      end
   end
endgenerate

// ADDRESS DECODE + READ TRACKING (per slave port)
generate
   for (i = 0; i < S_NUM; i++) begin : S_rd_switch
      logic [M_NUM    -1:0] S_ar_targeted;
      logic [M_NUM    -1:0] S_r_target;
      logic                   r_trk_full;
      logic                   r_trk_empty;

      for (j = 0; j < M_NUM; j++) begin : decode
         assign S_ar_targeted[j] =
            (i_arch[i*ARCH_WIDTH+:ADDR_WIDTH] >= M_START_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]) &&
            (i_arch[i*ARCH_WIDTH+:ADDR_WIDTH] <= M_END_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]);
      end

      for (j = 0; j < M_NUM; j++) begin : fwd
         assign m2s_arvalid[i*M_NUM+j] = S_ar_targeted[j] && i_arvalid[i] && !r_trk_full;
      end

      always_comb begin
         i_arready[i] = ar_misrouting[i];
         for (int k = 0; k < M_NUM; k++) begin
            if (S_ar_targeted[k]) begin
               i_arready[i] = m2s_arready[i*M_NUM+k];
               break;
            end
         end
      end

      sync_fifo #(
         .WIDTH               ( M_NUM ),
         .DEPTH               ( TRK_DEPTH ),
         .FWFT                ( "true" ),
         .RAM_STYLE           ( TRK_RAM_STYLE )
      ) u_rtrk (
         .clk                 ( clk ),
         .rst                 ( rst ),
         .wr_en               ( i_arvalid[i] && i_arready[i] ),
         .wr_data             ( S_ar_targeted ),
         .full                ( r_trk_full ),
         .rd_en               ( i_rvalid[i] && i_rready[i] ),
         .rd_data             ( S_r_target ),
         .empty               ( r_trk_empty ),
         .overflow            ( ),
         .underflow           ( ),
         .level               ( )
      );

      always_comb begin
         i_rvalid[i] = 1'b0;
         i_rch[i*RCH_WIDTH+:RCH_WIDTH] = '0;
         if (!r_trk_empty) begin
            for (int k = 0; k < M_NUM; k++) begin
               if (S_r_target[k]) begin
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
         if (!r_trk_empty) begin
            for (int k = 0; k < M_NUM; k++) begin
               if (S_r_target[k]) begin
                  m2s_rready[i*M_NUM+k] = i_rready[i];
                  break;
               end
            end
         end
      end

      always_ff @(posedge clk or posedge rst) begin
         if (rst) begin
            ar_misrouting[i] <= 1'b0;
         end else begin
            if (ar_misrouting[i]) begin
               ar_misrouting[i] <= 1'b0;
            end else if (i_arvalid[i] && S_ar_targeted == '0) begin
               ar_misrouting[i] <= 1'b1;
            end
         end
      end
   end
endgenerate

// MATRIX TRANSPOSE
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
      assign o_bready[j] = |(s2m_bready[j*S_NUM+:S_NUM]);
      assign s2m_rch[j*RCH_WIDTH+:RCH_WIDTH] = o_rch[j*RCH_WIDTH+:RCH_WIDTH];
      assign o_rready[j] = |(s2m_rready[j*S_NUM+:S_NUM]);
   end
endgenerate

// MASTER-SIDE WRITE SWITCH (per master port)
generate
   for (j = 0; j < M_NUM; j++) begin : M_wr_switch
      logic [S_NUM      -1:0] aw_grant;
      logic [S_NUM      -1:0] aw_grant_r;
      logic [S_NUM      -1:0] w_grant;
      logic [S_NUM      -1:0] b_master;
      logic                     aw_gnt_full, aw_gnt_empty;
      logic                     b_trk_full, b_trk_empty;
      logic                     aw_arb_en;

      // Mask request of the slave port that just completed AW handshake
      // (prevents re-grant while BFM clears awvalid)
      wire [S_NUM-1:0] aw_req_masked;
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
         .select             ( )
      );

      always_ff @(posedge clk or posedge rst) begin
         if (rst) begin
            aw_grant_r <= '0;
         end else begin
            aw_grant_r <= aw_grant;
         end
      end

      logic o_awvalid_sel;
      always_comb begin
         o_awvalid_sel = 1'b0;
         for (int k = 0; k < S_NUM; k++) begin
            if (aw_grant[k] && s2m_awvalid[j*S_NUM+k]) begin
               o_awvalid_sel = 1'b1;
               break;
            end
         end
      end
      assign o_awvalid[j] = o_awvalid_sel;

      always_comb begin
         o_awch[j*AWCH_WIDTH+:AWCH_WIDTH] = '0;
         for (int k = 0; k < S_NUM; k++) begin
            if (aw_grant[k]) begin
               o_awch[j*AWCH_WIDTH+:AWCH_WIDTH] = i_awch[k*AWCH_WIDTH+:AWCH_WIDTH];
            end
         end
      end

      always_comb begin
         for (int k = 0; k < S_NUM; k++) begin
            s2m_awready[j*S_NUM+k] = aw_grant[k] && s2m_awvalid[j*S_NUM+k] && o_awready[j];
         end
      end

      assign aw_arb_en = (|aw_grant) ? o_awready[j] : |s2m_awvalid[j*S_NUM+:S_NUM];

      sync_fifo #(
         .WIDTH               ( S_NUM ),
         .DEPTH               ( TRK_DEPTH ),
         .FWFT                ( "true" ),
         .RAM_STYLE           ( TRK_RAM_STYLE )
      ) u_awgnt (
         .clk                 ( clk ),
         .rst                 ( rst ),
         .wr_en               ( o_awvalid[j] && o_awready[j] ),
         .wr_data             ( aw_grant ),
         .full                ( aw_gnt_full ),
         .rd_en               ( o_wvalid[j] && o_wready[j] ),
         .rd_data             ( w_grant ),
         .empty               ( aw_gnt_empty ),
         .overflow            ( ),
         .underflow           ( ),
         .level               ( )
      );

      sync_fifo #(
         .WIDTH               ( S_NUM ),
         .DEPTH               ( TRK_DEPTH ),
         .FWFT                ( "true" ),
         .RAM_STYLE           ( TRK_RAM_STYLE )
      ) u_btrk (
         .clk                 ( clk ),
         .rst                 ( rst ),
         .wr_en               ( o_awvalid[j] && o_awready[j] ),
         .wr_data             ( aw_grant ),
         .full                ( b_trk_full ),
         .rd_en               ( o_bvalid[j] && o_bready[j] ),
         .rd_data             ( b_master ),
         .empty               ( b_trk_empty ),
         .overflow            ( ),
         .underflow           ( ),
         .level               ( )
      );

      logic M_wvalid_sel;
      always_comb begin
         M_wvalid_sel = 1'b0;
         o_wch[j*WCH_WIDTH+:WCH_WIDTH] = '0;
         if (!aw_gnt_empty) begin
            for (int k = 0; k < S_NUM; k++) begin
               if (w_grant[k]) begin
                  M_wvalid_sel = s2m_wvalid[j*S_NUM+k];
                  o_wch[j*WCH_WIDTH+:WCH_WIDTH] = i_wch[k*WCH_WIDTH+:WCH_WIDTH];
                  break;
               end
            end
         end
      end
      assign o_wvalid[j] = M_wvalid_sel;

      always_comb begin
         for (int k = 0; k < S_NUM; k++) begin
            s2m_wready[j*S_NUM+k] = !aw_gnt_empty && w_grant[k] && o_wready[j];
         end
      end

      always_comb begin
         for (int k = 0; k < S_NUM; k++) begin
            s2m_bvalid[j*S_NUM+k] = 1'b0;
         end
         if (!b_trk_empty) begin
            for (int k = 0; k < S_NUM; k++) begin
               if (b_master[k]) begin
                  s2m_bvalid[j*S_NUM+k] = o_bvalid[j];
                  break;
               end
            end
         end
      end

      always_comb begin
         o_bready[j] = 1'b0;
         if (!b_trk_empty) begin
            for (int k = 0; k < S_NUM; k++) begin
               if (b_master[k]) begin
                  o_bready[j] = s2m_bready[j*S_NUM+k];
                  break;
               end
            end
         end
      end
   end
endgenerate

// MASTER-SIDE READ SWITCH (per master port)
generate
   for (j = 0; j < M_NUM; j++) begin : M_rd_switch

      logic [S_NUM      -1:0] ar_grant;
      logic                     ar_arb_en;
      logic [S_NUM      -1:0] r_master;
      logic                     r_trk_full, r_trk_empty;

      // Mask request of the slave port that just completed AR handshake
      // (prevents re-grant while BFM clears arvalid)
      wire [S_NUM-1:0] ar_req_masked;
      genvar ark;
      for (ark = 0; ark < S_NUM; ark++) begin
         assign ar_req_masked[ark] = s2m_arvalid[j*S_NUM+ark] &&
                                    !(ar_grant[ark] && o_arready[j]) &&
                                    !r_trk_full;
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
         .select             ( )
      );

      logic o_arvalid_sel;
      always_comb begin
         o_arvalid_sel = 1'b0;
         for (int k = 0; k < S_NUM; k++) begin
            if (ar_grant[k] && s2m_arvalid[j*S_NUM+k]) begin
               o_arvalid_sel = 1'b1;
               break;
            end
         end
      end

      assign o_arvalid[j] = o_arvalid_sel;
      always_comb begin
         o_arch[j*ARCH_WIDTH+:ARCH_WIDTH] = '0;
         for (int k = 0; k < S_NUM; k++) begin
            if (ar_grant[k]) begin
               o_arch[j*ARCH_WIDTH+:ARCH_WIDTH] = i_arch[k*ARCH_WIDTH+:ARCH_WIDTH];
            end
         end
      end

      always_comb begin
         for (int k = 0; k < S_NUM; k++) begin
            s2m_arready[j*S_NUM+k] = ar_grant[k] && s2m_arvalid[j*S_NUM+k] && o_arready[j];
         end
      end

      assign ar_arb_en = (|ar_grant) ? o_arready[j] : |s2m_arvalid[j*S_NUM+:S_NUM];

      sync_fifo #(
         .WIDTH               ( S_NUM ),
         .DEPTH               ( TRK_DEPTH ),
         .FWFT                ( "true" ),
         .RAM_STYLE           ( TRK_RAM_STYLE )
      ) u_rtrk (
         .clk                 ( clk ),
         .rst                 ( rst ),
         .wr_en               ( o_arvalid[j] && o_arready[j] ),
         .wr_data             ( ar_grant ),
         .full                ( r_trk_full ),
         .rd_en               ( o_rvalid[j] && o_rready[j] ),
         .rd_data             ( r_master ),
         .empty               ( r_trk_empty ),
         .overflow            ( ),
         .underflow           ( ),
         .level               ( )
      );

      always_comb begin
         for (int k = 0; k < S_NUM; k++) begin
            s2m_rvalid[j*S_NUM+k] = 1'b0;
         end
         if (!r_trk_empty) begin
            for (int k = 0; k < S_NUM; k++) begin
               if (r_master[k]) begin
                  s2m_rvalid[j*S_NUM+k] = o_rvalid[j];
                  break;
               end
            end
         end
      end

      always_comb begin
         o_rready[j] = 1'b0;
         if (!r_trk_empty) begin
            for (int k = 0; k < S_NUM; k++) begin
               if (r_master[k]) begin
                  o_rready[j] = s2m_rready[j*S_NUM+k];
                  break;
               end
            end
         end
      end
   end
endgenerate

// MASTER INTERFACE (per master port)
generate
   for (j = 0; j < M_NUM; j++) begin : M_if
      logic [BCH_WIDTH       -1:0] bch;
      logic [RCH_WIDTH       -1:0] rch;

      logic [ADDR_WIDTH-1:0] base = M_START_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH];
      logic [ADDR_WIDTH-1:0] awaddr_xlat;
      logic [ADDR_WIDTH-1:0] araddr_xlat;

      if (M_KEEP_BASE[j]) begin
         assign awaddr_xlat = o_awch[j*AWCH_WIDTH+:ADDR_WIDTH];
         assign araddr_xlat = o_arch[j*ARCH_WIDTH+:ADDR_WIDTH];
      end else begin
         assign awaddr_xlat = o_awch[j*AWCH_WIDTH+:ADDR_WIDTH] - base;
         assign araddr_xlat = o_arch[j*ARCH_WIDTH+:ADDR_WIDTH] - base;
      end

      if (M_SKID_EN[j]) begin : buffer_on

         wire [AWCH_WIDTH-1:0] aw_rd;
         wire [ARCH_WIDTH-1:0] ar_rd;
         wire [ADDR_WIDTH-1:0] awaddr_buf = aw_rd[ADDR_WIDTH-1:0];
         wire [ADDR_WIDTH-1:0] araddr_buf = ar_rd[ADDR_WIDTH-1:0];
         wire [ADDR_WIDTH-1:0] awaddr_xlat_buf = M_KEEP_BASE[j] ? awaddr_buf : (awaddr_buf - base);
         wire [ADDR_WIDTH-1:0] araddr_xlat_buf = M_KEEP_BASE[j] ? araddr_buf : (araddr_buf - base);

          skid_buffer #(
             .WIDTH               ( AWCH_WIDTH )
          ) u_aw (
             .clk                 ( clk ),
             .rst                 ( rst ),
             .data_i              ( o_awch[j*AWCH_WIDTH+:AWCH_WIDTH] ),
             .valid_i             ( o_awvalid[j] ),
             .ready_o             ( o_awready[j] ),
             .data_o              ( aw_rd ),
             .valid_o             ( m_axil_ifs[j].awvalid ),
             .ready_i             ( m_axil_ifs[j].awready )
          );
          assign m_axil_ifs[j].awprot = aw_rd[AWCH_WIDTH-1:ADDR_WIDTH];
          assign m_axil_ifs[j].awaddr = awaddr_xlat_buf;

          skid_buffer #(
             .WIDTH               ( WCH_WIDTH )
          ) u_w (
             .clk                 ( clk ),
             .rst                 ( rst ),
             .data_i              ( o_wch[j*WCH_WIDTH+:WCH_WIDTH] ),
             .valid_i             ( o_wvalid[j] ),
             .ready_o             ( o_wready[j] ),
             .data_o              ( {m_axil_ifs[j].wdata, m_axil_ifs[j].wstrb} ),
             .valid_o             ( m_axil_ifs[j].wvalid ),
             .ready_i             ( m_axil_ifs[j].wready )
          );

          skid_buffer #(
             .WIDTH               ( BCH_WIDTH )
          ) u_b (
             .clk                 ( clk ),
             .rst                 ( rst ),
             .data_i              ( m_axil_ifs[j].bresp ),
             .valid_i             ( m_axil_ifs[j].bvalid ),
             .ready_o             ( m_axil_ifs[j].bready ),
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
             .valid_o             ( m_axil_ifs[j].arvalid ),
             .ready_i             ( m_axil_ifs[j].arready )
          );
         assign m_axil_ifs[j].arprot = ar_rd[ARCH_WIDTH-1:ADDR_WIDTH];
         assign m_axil_ifs[j].araddr = araddr_xlat_buf;

          skid_buffer #(
             .WIDTH               ( RCH_WIDTH )
          ) u_r (
             .clk                 ( clk ),
             .rst                 ( rst ),
             .data_i              ( {m_axil_ifs[j].rdata, m_axil_ifs[j].rresp} ),
             .valid_i             ( m_axil_ifs[j].rvalid ),
             .ready_o             ( m_axil_ifs[j].rready ),
             .data_o              ( o_rch[j*RCH_WIDTH+:RCH_WIDTH] ),
             .valid_o             ( o_rvalid[j] ),
             .ready_i             ( o_rready[j] )
          );

      end else begin : buffer_off

         assign m_axil_ifs[j].awprot   = o_awch[j*AWCH_WIDTH+ADDR_WIDTH+:3];
         assign m_axil_ifs[j].awaddr   = awaddr_xlat;
         assign m_axil_ifs[j].awvalid  = o_awvalid[j];
         assign o_awready[j]       = m_axil_ifs[j].awready;

         assign {m_axil_ifs[j].wdata, m_axil_ifs[j].wstrb} = o_wch[j*WCH_WIDTH+:WCH_WIDTH];
         assign m_axil_ifs[j].wvalid   = o_wvalid[j];
         assign o_wready[j]        = m_axil_ifs[j].wready;

         assign bch                = {m_axil_ifs[j].bresp};
         assign o_bch[j*BCH_WIDTH+:BCH_WIDTH] = bch;
         assign o_bvalid[j]        = m_axil_ifs[j].bvalid;
         assign m_axil_ifs[j].bready   = o_bready[j];

         assign m_axil_ifs[j].arprot   = o_arch[j*ARCH_WIDTH+ADDR_WIDTH+:3];
         assign m_axil_ifs[j].araddr   = araddr_xlat;
         assign m_axil_ifs[j].arvalid  = o_arvalid[j];
         assign o_arready[j]       = m_axil_ifs[j].arready;

         assign rch                = {m_axil_ifs[j].rdata, m_axil_ifs[j].rresp};
         assign o_rch[j*RCH_WIDTH+:RCH_WIDTH] = rch;
         assign o_rvalid[j]        = m_axil_ifs[j].rvalid;
         assign m_axil_ifs[j].rready   = o_rready[j];
      end
   end
endgenerate

endmodule

`resetall
