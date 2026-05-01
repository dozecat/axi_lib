`timescale 1ns / 1ps
`default_nettype none

module axil_sc_fifo
    #(
        parameter DATA_W = 8,
        parameter ADDR_W = 2
    )(
        input  wire                   clk,
        input  wire                   rst_n,
        input  wire                   push,
        input  wire  [DATA_W    -1:0] data_in,
        output logic                  full,
        input  wire                   pop,
        output logic [DATA_W    -1:0] data_out,
        output logic                  empty
    );

    localparam DEPTH = 2 ** ADDR_W;

    reg  [DATA_W    -1:0] mem [0:DEPTH-1];
    reg  [ADDR_W     :0] wptr;
    reg  [ADDR_W     :0] rptr;

    wire [ADDR_W    -1:0] waddr = wptr[ADDR_W-1:0];
    wire [ADDR_W    -1:0] raddr = rptr[ADDR_W-1:0];

    assign full  = (wptr[ADDR_W] != rptr[ADDR_W]) && (waddr == raddr);
    assign empty = (wptr == rptr);

    always @ (posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            wptr <= '0;
        end else if (push && !full) begin
            wptr <= wptr + 1'b1;
        end
    end

    always @ (posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rptr <= '0;
        end else if (pop && !empty) begin
            rptr <= rptr + 1'b1;
        end
    end

    always @ (posedge clk) begin
        if (push && !full) begin
            mem[waddr] <= data_in;
        end
    end

    always @ (posedge clk) begin
        if (!empty && pop) begin
            data_out <= mem[raddr];
        end else if (!empty) begin
            data_out <= mem[raddr];
        end
    end

endmodule

`resetall
