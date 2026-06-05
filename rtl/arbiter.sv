//******************************************************************************
// arbiter.sv
// SPDX-License-Identifier: MIT
//
// Priority-based arbiter with round-robin among equal-priority requesters.
// Each port has a configurable priority via PRIORITY_CFG.  Among requesters
// at the highest active priority level, a round-robin pointer determines
// which port receives the grant.  Grant and binary-encoded select are both
// registered (1-cycle latency).
//
// Parameter ranges:
//   PORTS          >= 1
//   PRIORITY_WIDTH >= 1
//   PRIORITY_CFG   {PORTS*PRIORITY_WIDTH{1'b0}} (default: all zero)
//
// https://github.com/dozecat/axi_lib
//******************************************************************************

`timescale 1ns / 1ps
`default_nettype none

module arbiter
#(
   parameter PORTS                  = 4,
   parameter PRIORITY_WIDTH         = 4,
   parameter PRIORITY_CFG           = {PORTS*PRIORITY_WIDTH{1'b0}}
)(
   input  wire                      clk,
   input  wire                      rst,
   input  wire                      en,
   input  wire [PORTS         -1:0] request,
   output wire [PORTS         -1:0] grant,
   output wire [$clog2(PORTS) -1:0] select
);

// Per-port prio extraction
genvar g;

wire [PRIORITY_WIDTH-1:0] prio [0:PORTS-1];

generate
   for (g = 0; g < PORTS; g++) begin : prio_extract
      assign prio[g] = PRIORITY_CFG[g*PRIORITY_WIDTH+:PRIORITY_WIDTH];
   end
endgenerate

// Find highest prio among active requesters
logic [PRIORITY_WIDTH-1:0] max_prio;

always_comb begin
   max_prio = '0;
   for (int i = 0; i < PORTS; i++) begin
      if (request[i] && prio[i] > max_prio) begin
            max_prio = prio[i];
      end
   end
end

// Mask: only requesters at the highest prio level
wire [PORTS-1:0] high_prio_req;

generate
   for (g = 0; g < PORTS; g++) begin : prio_mask
      assign high_prio_req[g] = request[g] && (prio[g] == max_prio);
   end
endgenerate

// Round-robin among high-prio requesters
reg  [PORTS-1:0] mask;
wire [PORTS-1:0] masked_req;
logic [PORTS-1:0] grant_c;

assign masked_req = high_prio_req & mask;

always_comb begin
   grant_c = '0;
   if (|masked_req) begin
      for (int i = 0; i < PORTS; i++) begin
            if (masked_req[i]) begin
               grant_c[i] = 1'b1;
               break;
            end
      end
   end else if (|high_prio_req) begin
      for (int i = 0; i < PORTS; i++) begin
            if (high_prio_req[i]) begin
               grant_c[i] = 1'b1;
               break;
            end
      end
   end
end

// Registered grant
reg [PORTS-1:0] grant_r;

always_ff @ (posedge clk or posedge rst) begin
   if (rst) begin
      grant_r <= '0;
   end else begin
      grant_r <= grant_c;
   end
end

assign grant = grant_r;

// Round-robin mask update
always_ff @ (posedge clk or posedge rst) begin
   if (rst) begin
      mask <= '0;
   end else if (en && |grant) begin
      mask <= ~((grant << 1) - 1);
   end
end

// Select output: binary-encoded grant index
reg [$clog2(PORTS)-1:0] select_r;

always_comb begin
   select_r = '0;
   for (int i = 0; i < PORTS; i++) begin
      if (grant[i]) begin
            select_r = i[$clog2(PORTS)-1:0];
            break;
      end
   end
end

assign select = select_r;

endmodule

`resetall
