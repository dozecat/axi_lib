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
   parameter SLV_NUM             = 4, // Slave interface number (connect to external masters)
   parameter MST_NUM             = 4, // Master interface number (connect to external slaves)
   parameter ADDR_WIDTH          = 16,
   parameter DATA_WIDTH          = 32,
   parameter PRIORITY_WIDTH      = 4,
   parameter TRK_DEPTH           = 4,
   parameter TRK_RAM_STYLE       = "distributed",
   parameter SLV_SKID_EN         = {SLV_NUM{1'b0}},
   parameter SLV_PRIORITY        = {SLV_NUM*PRIORITY_WIDTH{1'b0}},
   parameter MST_SKID_EN         = {MST_NUM{1'b0}},
   parameter MST_START_ADDR      = {MST_NUM*ADDR_WIDTH{1'b0}},
   parameter MST_END_ADDR        = {MST_NUM*ADDR_WIDTH{1'b1}},
   parameter MST_KEEP_BASE       = {MST_NUM{1'b0}}
)(
   input  wire                   aclk,
   input  wire                   aresetn,

   if_axil.slave                 axil_slv_if [0:SLV_NUM-1],
   if_axil.master                axil_mst_if [0:MST_NUM-1]
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
logic [SLV_NUM          -1:0]    i_awvalid;
logic [SLV_NUM          -1:0]    i_awready;
logic [SLV_NUM*AWCH_WIDTH -1:0]  i_awch;
logic [SLV_NUM          -1:0]    i_wvalid;
logic [SLV_NUM          -1:0]    i_wready;
logic [SLV_NUM*WCH_WIDTH -1:0]   i_wch;
logic [SLV_NUM          -1:0]    i_bvalid;
logic [SLV_NUM          -1:0]    i_bready;
logic [SLV_NUM*BCH_WIDTH -1:0]   i_bch;
logic [SLV_NUM          -1:0]    i_arvalid;
logic [SLV_NUM          -1:0]    i_arready;
logic [SLV_NUM*ARCH_WIDTH -1:0]  i_arch;
logic [SLV_NUM          -1:0]    i_rvalid;
logic [SLV_NUM          -1:0]    i_rready;
logic [SLV_NUM*RCH_WIDTH -1:0]   i_rch;

logic [MST_NUM          -1:0]    o_awvalid;
logic [MST_NUM          -1:0]    o_awready;
logic [MST_NUM*AWCH_WIDTH -1:0]  o_awch;
logic [MST_NUM          -1:0]    o_wvalid;
logic [MST_NUM          -1:0]    o_wready;
logic [MST_NUM*WCH_WIDTH -1:0]   o_wch;
logic [MST_NUM          -1:0]    o_bvalid;
logic [MST_NUM          -1:0]    o_bready;
logic [MST_NUM*BCH_WIDTH -1:0]   o_bch;
logic [MST_NUM          -1:0]    o_arvalid;
logic [MST_NUM          -1:0]    o_arready;
logic [MST_NUM*ARCH_WIDTH -1:0]  o_arch;
logic [MST_NUM          -1:0]    o_rvalid;
logic [MST_NUM          -1:0]    o_rready;
logic [MST_NUM*RCH_WIDTH  -1:0]  o_rch;

logic [SLV_NUM*MST_NUM   -1:0]   m2s_awvalid;
logic [SLV_NUM*MST_NUM   -1:0]   m2s_awready;
logic [SLV_NUM*MST_NUM   -1:0]   m2s_wvalid;
logic [SLV_NUM*MST_NUM   -1:0]   m2s_wready;
logic [SLV_NUM*MST_NUM   -1:0]   m2s_arvalid;
logic [SLV_NUM*MST_NUM   -1:0]   m2s_arready;

logic [MST_NUM*SLV_NUM   -1:0]   s2m_awvalid;
logic [MST_NUM*SLV_NUM   -1:0]   s2m_awready;
logic [MST_NUM*SLV_NUM   -1:0]   s2m_wvalid;
logic [MST_NUM*SLV_NUM   -1:0]   s2m_wready;
logic [MST_NUM*SLV_NUM   -1:0]   s2m_arvalid;
logic [MST_NUM*SLV_NUM   -1:0]   s2m_arready;

logic [MST_NUM*SLV_NUM   -1:0]   s2m_bvalid;
logic [MST_NUM*SLV_NUM   -1:0]   s2m_bready;
logic [MST_NUM*SLV_NUM   -1:0]   s2m_rvalid;
logic [MST_NUM*SLV_NUM   -1:0]   s2m_rready;
logic [MST_NUM*BCH_WIDTH -1:0]   s2m_bch;
logic [MST_NUM*RCH_WIDTH -1:0]   s2m_rch;

logic [SLV_NUM*MST_NUM   -1:0]   m2s_bvalid;
logic [SLV_NUM*MST_NUM   -1:0]   m2s_bready;
logic [SLV_NUM*MST_NUM   -1:0]   m2s_rvalid;
logic [SLV_NUM*MST_NUM   -1:0]   m2s_rready;

logic [SLV_NUM           -1:0]   aw_misrouting;
logic [SLV_NUM           -1:0]   ar_misrouting;

initial begin
   for (integer s = 0; s < SLV_NUM; s++) begin
      if (axil_slv_if[s].ADDR_WIDTH != ADDR_WIDTH)
         $error("axil_slv_if[%0d].ADDR_WIDTH (%0d) != ADDR_WIDTH (%0d)", s, axil_slv_if[s].ADDR_WIDTH, ADDR_WIDTH);
      if (axil_slv_if[s].DATA_WIDTH != DATA_WIDTH)
         $error("axil_slv_if[%0d].DATA_WIDTH (%0d) != DATA_WIDTH (%0d)", s, axil_slv_if[s].DATA_WIDTH, DATA_WIDTH);
   end
end

// SLAVE INTERFACE (per slave port)
generate
   for (i = 0; i < SLV_NUM; i++) begin : slv_if
      logic [AWCH_WIDTH  -1:0]   awch;
      logic [WCH_WIDTH   -1:0]   wch;
      logic [BCH_WIDTH   -1:0]   bch;
      logic [ARCH_WIDTH  -1:0]   arch;
      logic [RCH_WIDTH   -1:0]   rch;

      assign awch = {axil_slv_if[i].awprot, axil_slv_if[i].awaddr};
      assign wch  = {axil_slv_if[i].wdata,  axil_slv_if[i].wstrb};
      assign arch = {axil_slv_if[i].arprot, axil_slv_if[i].araddr};

      if (SLV_SKID_EN[i]) begin : buffer_on

          skid_buffer #(
             .WIDTH               ( AWCH_WIDTH )
          ) u_aw (
             .clk                 ( aclk ),
             .rst                 ( ~aresetn ),
             .data_i              ( awch ),
             .valid_i             ( axil_slv_if[i].awvalid ),
             .ready_o             ( axil_slv_if[i].awready ),
             .data_o              ( i_awch[i*AWCH_WIDTH+:AWCH_WIDTH] ),
             .valid_o             ( i_awvalid[i] ),
             .ready_i             ( i_awready[i] )
          );

          skid_buffer #(
             .WIDTH               ( WCH_WIDTH )
          ) u_w (
             .clk                 ( aclk ),
             .rst                 ( ~aresetn ),
             .data_i              ( wch ),
             .valid_i             ( axil_slv_if[i].wvalid ),
             .ready_o             ( axil_slv_if[i].wready ),
             .data_o              ( i_wch[i*WCH_WIDTH+:WCH_WIDTH] ),
             .valid_o             ( i_wvalid[i] ),
             .ready_i             ( i_wready[i] )
          );

          skid_buffer #(
             .WIDTH               ( BCH_WIDTH )
          ) u_b (
             .clk                 ( aclk ),
             .rst                 ( ~aresetn ),
             .data_i              ( i_bch[i*BCH_WIDTH+:BCH_WIDTH] ),
             .valid_i             ( i_bvalid[i] ),
             .ready_o             ( i_bready[i] ),
             .data_o              ( bch ),
             .valid_o             ( axil_slv_if[i].bvalid ),
             .ready_i             ( axil_slv_if[i].bready )
          );
          assign {axil_slv_if[i].bresp} = bch;

          skid_buffer #(
             .WIDTH               ( ARCH_WIDTH )
          ) u_ar (
             .clk                 ( aclk ),
             .rst                 ( ~aresetn ),
             .data_i              ( arch ),
             .valid_i             ( axil_slv_if[i].arvalid ),
             .ready_o             ( axil_slv_if[i].arready ),
             .data_o              ( i_arch[i*ARCH_WIDTH+:ARCH_WIDTH] ),
             .valid_o             ( i_arvalid[i] ),
             .ready_i             ( i_arready[i] )
          );

          skid_buffer #(
             .WIDTH               ( RCH_WIDTH )
          ) u_r (
             .clk                 ( aclk ),
             .rst                 ( ~aresetn ),
             .data_i              ( i_rch[i*RCH_WIDTH+:RCH_WIDTH] ),
             .valid_i             ( i_rvalid[i] ),
             .ready_o             ( i_rready[i] ),
             .data_o              ( rch ),
             .valid_o             ( axil_slv_if[i].rvalid ),
             .ready_i             ( axil_slv_if[i].rready )
          );
          assign {axil_slv_if[i].rdata, axil_slv_if[i].rresp} = rch;

      end else begin : buffer_off

         assign i_awvalid[i] = axil_slv_if[i].awvalid;
         assign axil_slv_if[i].awready = i_awready[i];
         assign i_awch[i*AWCH_WIDTH+:AWCH_WIDTH] = awch;

         assign i_wvalid[i] = axil_slv_if[i].wvalid;
         assign axil_slv_if[i].wready = i_wready[i];
         assign i_wch[i*WCH_WIDTH+:WCH_WIDTH] = wch;

         assign axil_slv_if[i].bvalid = i_bvalid[i];
         assign i_bready[i] = axil_slv_if[i].bready;
         assign bch = i_bch[i*BCH_WIDTH+:BCH_WIDTH];
         assign {axil_slv_if[i].bresp} = bch;

         assign i_arvalid[i] = axil_slv_if[i].arvalid;
         assign axil_slv_if[i].arready = i_arready[i];
         assign i_arch[i*ARCH_WIDTH+:ARCH_WIDTH] = arch;

         assign axil_slv_if[i].rvalid = i_rvalid[i];
         assign i_rready[i] = axil_slv_if[i].rready;
         assign rch = i_rch[i*RCH_WIDTH+:RCH_WIDTH];
         assign {axil_slv_if[i].rdata, axil_slv_if[i].rresp} = rch;
      end
   end
endgenerate

// ADDRESS DECODE + WRITE TRACKING (per slave port)
generate
   for (i = 0; i < SLV_NUM; i++) begin : slv_wr_switch
      logic [MST_NUM      -1:0] slv_aw_targeted;
      logic [MST_NUM      -1:0] slv_w_target;
      logic [MST_NUM      -1:0] slv_b_target;
      logic                     w_trk_full;
      logic                     w_trk_empty;
      logic                     b_trk_full;
      logic                     b_trk_empty;

      for (j = 0; j < MST_NUM; j++) begin : decode
         assign slv_aw_targeted[j] =
            (i_awch[i*AWCH_WIDTH+:ADDR_WIDTH] >= MST_START_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]) &&
            (i_awch[i*AWCH_WIDTH+:ADDR_WIDTH] <= MST_END_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]);
      end

      for (j = 0; j < MST_NUM; j++) begin : fwd
         assign m2s_awvalid[i*MST_NUM+j] = slv_aw_targeted[j] && i_awvalid[i] && !w_trk_full;
         assign m2s_wvalid[i*MST_NUM+j]  = !w_trk_empty && slv_w_target[j] && i_wvalid[i];
      end

      always_comb begin
         i_awready[i] = aw_misrouting[i];
         for (int k = 0; k < MST_NUM; k++) begin
            if (slv_aw_targeted[k]) begin
               i_awready[i] = m2s_awready[i*MST_NUM+k];
               break;
            end
         end
      end

      sync_fifo #(
         .WIDTH               ( MST_NUM ),
         .DEPTH               ( TRK_DEPTH ),
         .FWFT                ( "true" ),
         .RAM_STYLE           ( TRK_RAM_STYLE )
      ) u_wtrk (
         .clk                 ( aclk ),
         .rst                 ( ~aresetn ),
         .wr_en               ( i_awvalid[i] && i_awready[i] ),
         .wr_data             ( slv_aw_targeted ),
         .full                ( w_trk_full ),
         .rd_en               ( i_wvalid[i] && i_wready[i] ),
         .rd_data             ( slv_w_target ),
         .empty               ( w_trk_empty ),
         .overflow            ( ),
         .underflow           ( ),
         .level               ( )
      );

      sync_fifo #(
         .WIDTH               ( MST_NUM ),
         .DEPTH               ( TRK_DEPTH ),
         .FWFT                ( "true" ),
         .RAM_STYLE           ( TRK_RAM_STYLE )
      ) u_btrk (
         .clk                 ( aclk ),
         .rst                 ( ~aresetn ),
         .wr_en               ( i_awvalid[i] && i_awready[i] ),
         .wr_data             ( slv_aw_targeted ),
         .full                ( b_trk_full ),
         .rd_en               ( i_bvalid[i] && i_bready[i] ),
         .rd_data             ( slv_b_target ),
         .empty               ( b_trk_empty ),
         .overflow            ( ),
         .underflow           ( ),
         .level               ( )
      );

      always_comb begin
         i_wready[i] = 1'b0;
         if (!w_trk_empty) begin
            for (int k = 0; k < MST_NUM; k++) begin
               if (slv_w_target[k]) begin
                  i_wready[i] = m2s_wready[i*MST_NUM+k];
                  break;
               end
            end
         end
      end

      always_comb begin
         i_bvalid[i] = 1'b0;
         i_bch[i*BCH_WIDTH+:BCH_WIDTH] = '0;
         if (!b_trk_empty) begin
            for (int k = 0; k < MST_NUM; k++) begin
               if (slv_b_target[k]) begin
                  i_bvalid[i] = m2s_bvalid[i*MST_NUM+k];
                  i_bch[i*BCH_WIDTH+:BCH_WIDTH] = s2m_bch[k*BCH_WIDTH+:BCH_WIDTH];
                  break;
               end
            end
         end
      end

      always_comb begin
         for (int k = 0; k < MST_NUM; k++) begin
            m2s_bready[i*MST_NUM+k] = 1'b0;
         end
         if (!b_trk_empty) begin
            for (int k = 0; k < MST_NUM; k++) begin
               if (slv_b_target[k]) begin
                  m2s_bready[i*MST_NUM+k] = i_bready[i];
                  break;
               end
            end
         end
      end

      always_ff @(posedge aclk or negedge aresetn) begin
         if (!aresetn) begin
            aw_misrouting[i] <= 1'b0;
         end else begin
            if (aw_misrouting[i]) begin
               aw_misrouting[i] <= 1'b0;
            end else if (i_awvalid[i] && slv_aw_targeted == '0) begin
               aw_misrouting[i] <= 1'b1;
            end
         end
      end
   end
endgenerate

// ADDRESS DECODE + READ TRACKING (per slave port)
generate
   for (i = 0; i < SLV_NUM; i++) begin : slv_rd_switch
      logic [MST_NUM    -1:0] slv_ar_targeted;
      logic [MST_NUM    -1:0] slv_r_target;
      logic                   r_trk_full;
      logic                   r_trk_empty;

      for (j = 0; j < MST_NUM; j++) begin : decode
         assign slv_ar_targeted[j] =
            (i_arch[i*ARCH_WIDTH+:ADDR_WIDTH] >= MST_START_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]) &&
            (i_arch[i*ARCH_WIDTH+:ADDR_WIDTH] <= MST_END_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH]);
      end

      for (j = 0; j < MST_NUM; j++) begin : fwd
         assign m2s_arvalid[i*MST_NUM+j] = slv_ar_targeted[j] && i_arvalid[i] && !r_trk_full;
      end

      always_comb begin
         i_arready[i] = ar_misrouting[i];
         for (int k = 0; k < MST_NUM; k++) begin
            if (slv_ar_targeted[k]) begin
               i_arready[i] = m2s_arready[i*MST_NUM+k];
               break;
            end
         end
      end

      sync_fifo #(
         .WIDTH               ( MST_NUM ),
         .DEPTH               ( TRK_DEPTH ),
         .FWFT                ( "true" ),
         .RAM_STYLE           ( TRK_RAM_STYLE )
      ) u_rtrk (
         .clk                 ( aclk ),
         .rst                 ( ~aresetn ),
         .wr_en               ( i_arvalid[i] && i_arready[i] ),
         .wr_data             ( slv_ar_targeted ),
         .full                ( r_trk_full ),
         .rd_en               ( i_rvalid[i] && i_rready[i] ),
         .rd_data             ( slv_r_target ),
         .empty               ( r_trk_empty ),
         .overflow            ( ),
         .underflow           ( ),
         .level               ( )
      );

      always_comb begin
         i_rvalid[i] = 1'b0;
         i_rch[i*RCH_WIDTH+:RCH_WIDTH] = '0;
         if (!r_trk_empty) begin
            for (int k = 0; k < MST_NUM; k++) begin
               if (slv_r_target[k]) begin
                  i_rvalid[i] = m2s_rvalid[i*MST_NUM+k];
                  i_rch[i*RCH_WIDTH+:RCH_WIDTH] = s2m_rch[k*RCH_WIDTH+:RCH_WIDTH];
                  break;
               end
            end
         end
      end

      always_comb begin
         for (int k = 0; k < MST_NUM; k++) begin
            m2s_rready[i*MST_NUM+k] = 1'b0;
         end
         if (!r_trk_empty) begin
            for (int k = 0; k < MST_NUM; k++) begin
               if (slv_r_target[k]) begin
                  m2s_rready[i*MST_NUM+k] = i_rready[i];
                  break;
               end
            end
         end
      end

      always_ff @(posedge aclk or negedge aresetn) begin
         if (!aresetn) begin
            ar_misrouting[i] <= 1'b0;
         end else begin
            if (ar_misrouting[i]) begin
               ar_misrouting[i] <= 1'b0;
            end else if (i_arvalid[i] && slv_ar_targeted == '0) begin
               ar_misrouting[i] <= 1'b1;
            end
         end
      end
   end
endgenerate

// MATRIX TRANSPOSE
generate
   for (i = 0; i < SLV_NUM; i++) begin : tr_i
      for (j = 0; j < MST_NUM; j++) begin : tr_j
         assign s2m_awvalid[j*SLV_NUM+i] = m2s_awvalid[i*MST_NUM+j];
         assign m2s_awready[i*MST_NUM+j] = s2m_awready[j*SLV_NUM+i];
         assign s2m_wvalid[j*SLV_NUM+i]  = m2s_wvalid[i*MST_NUM+j];
         assign m2s_wready[i*MST_NUM+j]  = s2m_wready[j*SLV_NUM+i];
         assign s2m_arvalid[j*SLV_NUM+i] = m2s_arvalid[i*MST_NUM+j];
         assign m2s_arready[i*MST_NUM+j] = s2m_arready[j*SLV_NUM+i];

         assign m2s_bvalid[i*MST_NUM+j] = s2m_bvalid[j*SLV_NUM+i];
         assign s2m_bready[j*SLV_NUM+i] = m2s_bready[i*MST_NUM+j];
         assign m2s_rvalid[i*MST_NUM+j] = s2m_rvalid[j*SLV_NUM+i];
         assign s2m_rready[j*SLV_NUM+i] = m2s_rready[i*MST_NUM+j];
      end
   end
endgenerate

generate
   for (j = 0; j < MST_NUM; j++) begin : rch_share
      assign s2m_bch[j*BCH_WIDTH+:BCH_WIDTH] = o_bch[j*BCH_WIDTH+:BCH_WIDTH];
      assign o_bready[j] = |(s2m_bready[j*SLV_NUM+:SLV_NUM]);
      assign s2m_rch[j*RCH_WIDTH+:RCH_WIDTH] = o_rch[j*RCH_WIDTH+:RCH_WIDTH];
      assign o_rready[j] = |(s2m_rready[j*SLV_NUM+:SLV_NUM]);
   end
endgenerate

// MASTER-SIDE WRITE SWITCH (per master port)
generate
   for (j = 0; j < MST_NUM; j++) begin : mst_wr_switch
      logic [SLV_NUM      -1:0] aw_grant;
      logic [SLV_NUM      -1:0] aw_grant_r;
      logic [SLV_NUM      -1:0] w_grant;
      logic [SLV_NUM      -1:0] b_master;
      logic                     aw_gnt_full, aw_gnt_empty;
      logic                     b_trk_full, b_trk_empty;
      logic                     aw_arb_en;

      // Mask request of the slave port that just completed AW handshake
      // (prevents re-grant while BFM clears awvalid)
      wire [SLV_NUM-1:0] aw_req_masked;
      genvar awk;
      for (awk = 0; awk < SLV_NUM; awk++) begin
         assign aw_req_masked[awk] = s2m_awvalid[j*SLV_NUM+awk] &&
                                     !(aw_grant[awk] && o_awready[j]);
      end

      arbiter #(
         .PORTS               ( SLV_NUM ),
         .PRIORITY_WIDTH      ( PRIORITY_WIDTH ),
         .PRIORITY_CFG        ( SLV_PRIORITY )
      ) u_aw_arb (
         .clk                 ( aclk ),
         .rst                 ( !aresetn ),
         .en                  ( aw_arb_en ),
         .request             ( aw_req_masked ),
         .grant               ( aw_grant ),
         .selsect             ( )
      );

      always_ff @(posedge aclk or negedge aresetn) begin
         if (!aresetn) begin
            aw_grant_r <= '0;
         end else begin
            aw_grant_r <= aw_grant;
         end
      end

      logic o_awvalid_sel;
      always_comb begin
         o_awvalid_sel = 1'b0;
         for (int k = 0; k < SLV_NUM; k++) begin
            if (aw_grant[k] && s2m_awvalid[j*SLV_NUM+k]) begin
               o_awvalid_sel = 1'b1;
               break;
            end
         end
      end
      assign o_awvalid[j] = o_awvalid_sel;

      always_comb begin
         o_awch[j*AWCH_WIDTH+:AWCH_WIDTH] = '0;
         for (int k = 0; k < SLV_NUM; k++) begin
            if (aw_grant[k]) begin
               o_awch[j*AWCH_WIDTH+:AWCH_WIDTH] = i_awch[k*AWCH_WIDTH+:AWCH_WIDTH];
            end
         end
      end

      always_comb begin
         for (int k = 0; k < SLV_NUM; k++) begin
            s2m_awready[j*SLV_NUM+k] = aw_grant[k] && s2m_awvalid[j*SLV_NUM+k] && o_awready[j];
         end
      end

      assign aw_arb_en = (|aw_grant) ? o_awready[j] : |s2m_awvalid[j*SLV_NUM+:SLV_NUM];

      sync_fifo #(
         .WIDTH               ( SLV_NUM ),
         .DEPTH               ( TRK_DEPTH ),
         .FWFT                ( "true" ),
         .RAM_STYLE           ( TRK_RAM_STYLE )
      ) u_awgnt (
         .clk                 ( aclk ),
         .rst                 ( ~aresetn ),
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
         .WIDTH               ( SLV_NUM ),
         .DEPTH               ( TRK_DEPTH ),
         .FWFT                ( "true" ),
         .RAM_STYLE           ( TRK_RAM_STYLE )
      ) u_btrk (
         .clk                 ( aclk ),
         .rst                 ( ~aresetn ),
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

      logic mst_wvalid_sel;
      always_comb begin
         mst_wvalid_sel = 1'b0;
         o_wch[j*WCH_WIDTH+:WCH_WIDTH] = '0;
         if (!aw_gnt_empty) begin
            for (int k = 0; k < SLV_NUM; k++) begin
               if (w_grant[k]) begin
                  mst_wvalid_sel = s2m_wvalid[j*SLV_NUM+k];
                  o_wch[j*WCH_WIDTH+:WCH_WIDTH] = i_wch[k*WCH_WIDTH+:WCH_WIDTH];
                  break;
               end
            end
         end
      end
      assign o_wvalid[j] = mst_wvalid_sel;

      always_comb begin
         for (int k = 0; k < SLV_NUM; k++) begin
            s2m_wready[j*SLV_NUM+k] = !aw_gnt_empty && w_grant[k] && o_wready[j];
         end
      end

      always_comb begin
         for (int k = 0; k < SLV_NUM; k++) begin
            s2m_bvalid[j*SLV_NUM+k] = 1'b0;
         end
         if (!b_trk_empty) begin
            for (int k = 0; k < SLV_NUM; k++) begin
               if (b_master[k]) begin
                  s2m_bvalid[j*SLV_NUM+k] = o_bvalid[j];
                  break;
               end
            end
         end
      end

      always_comb begin
         o_bready[j] = 1'b0;
         if (!b_trk_empty) begin
            for (int k = 0; k < SLV_NUM; k++) begin
               if (b_master[k]) begin
                  o_bready[j] = s2m_bready[j*SLV_NUM+k];
                  break;
               end
            end
         end
      end
   end
endgenerate

// MASTER-SIDE READ SWITCH (per master port)
generate
   for (j = 0; j < MST_NUM; j++) begin : mst_rd_switch

      logic [SLV_NUM      -1:0] ar_grant;
      logic                     ar_arb_en;
      logic [SLV_NUM      -1:0] r_master;
      logic                     r_trk_full, r_trk_empty;

      // Mask request of the slave port that just completed AR handshake
      // (prevents re-grant while BFM clears arvalid)
      wire [SLV_NUM-1:0] ar_req_masked;
      genvar ark;
      for (ark = 0; ark < SLV_NUM; ark++) begin
         assign ar_req_masked[ark] = s2m_arvalid[j*SLV_NUM+ark] &&
                                    !(ar_grant[ark] && o_arready[j]) &&
                                    !r_trk_full;
      end

      arbiter #(
         .PORTS               ( SLV_NUM ),
         .PRIORITY_WIDTH      ( PRIORITY_WIDTH ),
         .PRIORITY_CFG        ( SLV_PRIORITY )
      ) u_ar_arb (
         .clk                 ( aclk ),
         .rst                 ( !aresetn ),
         .en                  ( ar_arb_en ),
         .request             ( ar_req_masked ),
         .grant               ( ar_grant ),
         .selsect             ( )
      );

      logic o_arvalid_sel;
      always_comb begin
         o_arvalid_sel = 1'b0;
         for (int k = 0; k < SLV_NUM; k++) begin
            if (ar_grant[k] && s2m_arvalid[j*SLV_NUM+k]) begin
               o_arvalid_sel = 1'b1;
               break;
            end
         end
      end

      assign o_arvalid[j] = o_arvalid_sel;
      always_comb begin
         o_arch[j*ARCH_WIDTH+:ARCH_WIDTH] = '0;
         for (int k = 0; k < SLV_NUM; k++) begin
            if (ar_grant[k]) begin
               o_arch[j*ARCH_WIDTH+:ARCH_WIDTH] = i_arch[k*ARCH_WIDTH+:ARCH_WIDTH];
            end
         end
      end

      always_comb begin
         for (int k = 0; k < SLV_NUM; k++) begin
            s2m_arready[j*SLV_NUM+k] = ar_grant[k] && s2m_arvalid[j*SLV_NUM+k] && o_arready[j];
         end
      end

      assign ar_arb_en = (|ar_grant) ? o_arready[j] : |s2m_arvalid[j*SLV_NUM+:SLV_NUM];

      sync_fifo #(
         .WIDTH               ( SLV_NUM ),
         .DEPTH               ( TRK_DEPTH ),
         .FWFT                ( "true" ),
         .RAM_STYLE           ( TRK_RAM_STYLE )
      ) u_rtrk (
         .clk                 ( aclk ),
         .rst                 ( ~aresetn ),
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
         for (int k = 0; k < SLV_NUM; k++) begin
            s2m_rvalid[j*SLV_NUM+k] = 1'b0;
         end
         if (!r_trk_empty) begin
            for (int k = 0; k < SLV_NUM; k++) begin
               if (r_master[k]) begin
                  s2m_rvalid[j*SLV_NUM+k] = o_rvalid[j];
                  break;
               end
            end
         end
      end

      always_comb begin
         o_rready[j] = 1'b0;
         if (!r_trk_empty) begin
            for (int k = 0; k < SLV_NUM; k++) begin
               if (r_master[k]) begin
                  o_rready[j] = s2m_rready[j*SLV_NUM+k];
                  break;
               end
            end
         end
      end
   end
endgenerate

// MASTER INTERFACE (per master port)
generate
   for (j = 0; j < MST_NUM; j++) begin : mst_if
      logic [BCH_WIDTH       -1:0] bch;
      logic [RCH_WIDTH       -1:0] rch;

      logic [ADDR_WIDTH-1:0] base = MST_START_ADDR[j*ADDR_WIDTH+:ADDR_WIDTH];
      logic [ADDR_WIDTH-1:0] awaddr_xlat;
      logic [ADDR_WIDTH-1:0] araddr_xlat;

      if (MST_KEEP_BASE[j]) begin
         assign awaddr_xlat = o_awch[j*AWCH_WIDTH+:ADDR_WIDTH];
         assign araddr_xlat = o_arch[j*ARCH_WIDTH+:ADDR_WIDTH];
      end else begin
         assign awaddr_xlat = o_awch[j*AWCH_WIDTH+:ADDR_WIDTH] - base;
         assign araddr_xlat = o_arch[j*ARCH_WIDTH+:ADDR_WIDTH] - base;
      end

      if (MST_SKID_EN[j]) begin : buffer_on

         wire [AWCH_WIDTH-1:0] aw_rd;
         wire [ARCH_WIDTH-1:0] ar_rd;
         wire [ADDR_WIDTH-1:0] awaddr_buf = aw_rd[ADDR_WIDTH-1:0];
         wire [ADDR_WIDTH-1:0] araddr_buf = ar_rd[ADDR_WIDTH-1:0];
         wire [ADDR_WIDTH-1:0] awaddr_xlat_buf = MST_KEEP_BASE[j] ? awaddr_buf : (awaddr_buf - base);
         wire [ADDR_WIDTH-1:0] araddr_xlat_buf = MST_KEEP_BASE[j] ? araddr_buf : (araddr_buf - base);

          skid_buffer #(
             .WIDTH               ( AWCH_WIDTH )
          ) u_aw (
             .clk                 ( aclk ),
             .rst                 ( ~aresetn ),
             .data_i              ( o_awch[j*AWCH_WIDTH+:AWCH_WIDTH] ),
             .valid_i             ( o_awvalid[j] ),
             .ready_o             ( o_awready[j] ),
             .data_o              ( aw_rd ),
             .valid_o             ( axil_mst_if[j].awvalid ),
             .ready_i             ( axil_mst_if[j].awready )
          );
          assign axil_mst_if[j].awprot = aw_rd[AWCH_WIDTH-1:ADDR_WIDTH];
          assign axil_mst_if[j].awaddr = awaddr_xlat_buf;

          skid_buffer #(
             .WIDTH               ( WCH_WIDTH )
          ) u_w (
             .clk                 ( aclk ),
             .rst                 ( ~aresetn ),
             .data_i              ( o_wch[j*WCH_WIDTH+:WCH_WIDTH] ),
             .valid_i             ( o_wvalid[j] ),
             .ready_o             ( o_wready[j] ),
             .data_o              ( {axil_mst_if[j].wdata, axil_mst_if[j].wstrb} ),
             .valid_o             ( axil_mst_if[j].wvalid ),
             .ready_i             ( axil_mst_if[j].wready )
          );

          skid_buffer #(
             .WIDTH               ( BCH_WIDTH )
          ) u_b (
             .clk                 ( aclk ),
             .rst                 ( ~aresetn ),
             .data_i              ( axil_mst_if[j].bresp ),
             .valid_i             ( axil_mst_if[j].bvalid ),
             .ready_o             ( axil_mst_if[j].bready ),
             .data_o              ( o_bch[j*BCH_WIDTH+:BCH_WIDTH] ),
             .valid_o             ( o_bvalid[j] ),
             .ready_i             ( o_bready[j] )
          );

          skid_buffer #(
             .WIDTH               ( ARCH_WIDTH )
          ) u_ar (
             .clk                 ( aclk ),
             .rst                 ( ~aresetn ),
             .data_i              ( o_arch[j*ARCH_WIDTH+:ARCH_WIDTH] ),
             .valid_i             ( o_arvalid[j] ),
             .ready_o             ( o_arready[j] ),
             .data_o              ( ar_rd ),
             .valid_o             ( axil_mst_if[j].arvalid ),
             .ready_i             ( axil_mst_if[j].arready )
          );
         assign axil_mst_if[j].arprot = ar_rd[ARCH_WIDTH-1:ADDR_WIDTH];
         assign axil_mst_if[j].araddr = araddr_xlat_buf;

          skid_buffer #(
             .WIDTH               ( RCH_WIDTH )
          ) u_r (
             .clk                 ( aclk ),
             .rst                 ( ~aresetn ),
             .data_i              ( {axil_mst_if[j].rdata, axil_mst_if[j].rresp} ),
             .valid_i             ( axil_mst_if[j].rvalid ),
             .ready_o             ( axil_mst_if[j].rready ),
             .data_o              ( o_rch[j*RCH_WIDTH+:RCH_WIDTH] ),
             .valid_o             ( o_rvalid[j] ),
             .ready_i             ( o_rready[j] )
          );

      end else begin : buffer_off

         assign axil_mst_if[j].awprot   = o_awch[j*AWCH_WIDTH+ADDR_WIDTH+:3];
         assign axil_mst_if[j].awaddr   = awaddr_xlat;
         assign axil_mst_if[j].awvalid  = o_awvalid[j];
         assign o_awready[j]       = axil_mst_if[j].awready;

         assign {axil_mst_if[j].wdata, axil_mst_if[j].wstrb} = o_wch[j*WCH_WIDTH+:WCH_WIDTH];
         assign axil_mst_if[j].wvalid   = o_wvalid[j];
         assign o_wready[j]        = axil_mst_if[j].wready;

         assign bch                = {axil_mst_if[j].bresp};
         assign o_bch[j*BCH_WIDTH+:BCH_WIDTH] = bch;
         assign o_bvalid[j]        = axil_mst_if[j].bvalid;
         assign axil_mst_if[j].bready   = o_bready[j];

         assign axil_mst_if[j].arprot   = o_arch[j*ARCH_WIDTH+ADDR_WIDTH+:3];
         assign axil_mst_if[j].araddr   = araddr_xlat;
         assign axil_mst_if[j].arvalid  = o_arvalid[j];
         assign o_arready[j]       = axil_mst_if[j].arready;

         assign rch                = {axil_mst_if[j].rdata, axil_mst_if[j].rresp};
         assign o_rch[j*RCH_WIDTH+:RCH_WIDTH] = rch;
         assign o_rvalid[j]        = axil_mst_if[j].rvalid;
         assign axil_mst_if[j].rready   = o_rready[j];
      end
   end
endgenerate

endmodule

`resetall
