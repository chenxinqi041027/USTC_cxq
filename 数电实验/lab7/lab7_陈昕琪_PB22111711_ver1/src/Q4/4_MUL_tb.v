`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/07 12:01:08
// Design Name: 
// Module Name: MUL_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module MUL_tb #(
    parameter WIDTH = 32
) ();
reg  [WIDTH-1:0]    a, b;
reg                 rst, clk, start;
wire [2*WIDTH-1:0]  res;
wire                finish;
integer             seed;

initial begin
    clk = 0;
    seed = 2023; // 种子值
    forever begin
        #5 clk = ~clk;
    end
end

initial begin
    rst = 1;
    start = 0;
    #20;
    rst = 0;
    #20;
    a = 32'h12345678;
    b = 32'h23456789;
    start = 1;
    #20 start = 0;
    #380;
    a = 32'hf2345678;
    b = 32'h23456789;
    start = 1;
    #20 start = 0;
    #380;
    a = 32'hf2345678;
    b = 32'hf3456789;
    start = 1;
    #20 start = 0;
    #380;
    $finish;
end

MUL mul(
    .clk        (clk),
    .rst        (rst),
    .start      (start),
    .a          (a),
    .b          (b),
    .res        (res),
    .finish     (finish)
);
endmodule
