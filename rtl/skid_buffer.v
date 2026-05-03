//******************************************************************************
// skid_buffer.v
// SPDX-License-Identifier: MIT
//
// Skid buffer for pipeline backpressure handling.  When downstream stalls,
// stores the current beat in a skid register so the upstream pipeline can
// continue issuing new data without bubbling.
//
// States:
//   EMPTY — no valid data; output is invalid, input always accepted
//   ONE   — one beat in the pipeline register; output is valid
//   SKID  — one beat in pipeline + one in skid; output shows skid (oldest)
//
// In SKID state, ready_o remains high so upstream never stalls.
// Output valid_o is always asserted when state != EMPTY.
//
// https://github.com/dozecat/memory_lib
//******************************************************************************

`timescale 1 ns / 1 ps
`default_nettype none

module skid_buffer
#(
   parameter WIDTH           = 8
)(
   input  wire               clk,
   input  wire               rst,

   input  wire [WIDTH-1:0]   data_i,
   input  wire               valid_i,
   output reg                ready_o,

   output reg  [WIDTH-1:0]   data_o,
   output reg                valid_o,
   input  wire               ready_i
);

// state encoding
localparam [1:0]
   EMPTY = 2'b00,
   ONE   = 2'b01,
   SKID  = 2'b10;

reg [1:0] state;
reg [WIDTH-1:0] pipe_data;
reg [WIDTH-1:0] skid_data;

// combinational outputs
always @(*) begin
   valid_o = 1'b0;
   data_o  = {WIDTH{1'b0}};
   ready_o = 1'b0;
   case (state)
      EMPTY: begin
         ready_o = 1'b1;
      end
      ONE: begin
         valid_o = 1'b1;
         data_o  = pipe_data;
         ready_o = ready_i;
      end
      SKID: begin
         valid_o = 1'b1;
         data_o  = skid_data;
         ready_o = 1'b1;
      end
      default: begin
         ready_o = 1'b1;
      end
   endcase
end

// state and data registers
always @(posedge clk or posedge rst) begin
   if (rst) begin
      state <= EMPTY;
   end else begin
      case (state)
         EMPTY: begin
            if (valid_i) begin
               pipe_data <= data_i;
               state <= ONE;
            end
         end

         ONE: begin
            if (ready_i) begin
               if (valid_i) begin
                  pipe_data <= data_i;
               end else begin
                  state <= EMPTY;
               end
            end else if (valid_i) begin
               skid_data <= pipe_data;
               pipe_data <= data_i;
               state <= SKID;
            end
         end

         SKID: begin
            if (ready_i) begin
               if (valid_i) begin
                  skid_data <= pipe_data;
                  pipe_data <= data_i;
               end else begin
                  state <= ONE;
               end
            end else if (valid_i) begin
               skid_data <= pipe_data;
               pipe_data <= data_i;
            end
         end
         default: begin
            state <= EMPTY;
         end
      endcase
   end
end

endmodule

`resetall
