`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/25 01:56:00
// Design Name: 
// Module Name: Q5_tb
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


module FindMode_tb;
reg clk;
reg rst;
reg next;
reg [7:0] number;
wire [7:0] out;

FindMode dut (
    .clk(clk),
    .rst(rst),
    .next(next),
    .number(number),
    .out(out)
);

initial begin
    clk = 1;
    forever #5 clk = ~clk;
end

initial begin
    rst = 1;
    next = 0;
    number = 0;
    #10 rst = 0;
    #10 next = 1;
    number = 8'h10;
    #10 next = 1;
    number = 8'h20;
    #10 next = 1;
    number = 8'h30;
    #10 next = 1;
    number = 8'h10;
    #10 next = 1;
    number = 8'h10;
    #10 next = 1;
    number = 8'h20;
    #10 next = 1;
    number = 8'h30;
    #10 next = 1;
    number = 8'h30;
    #10 next = 1;
    number = 8'h30;
    #10 next = 1;
    number = 8'h10;
    #10 next = 1;
    number = 8'h10;
    #10 next = 1;
    number = 8'h10;
    #10
    rst = 1;
    next = 0;
    number = 0;
    #10 rst = 0;
    #10 next = 1;
    number = 8'h10;
    #10 next = 1;
    number = 8'h20;
    #10 next = 1;
    number = 8'h30;
    #10 next = 1;
    number = 8'h10;
    #10 next = 1;
    number = 8'h10;
    #10 next = 1;
    number = 8'h20;
    #10 next = 1;
    number = 8'h30;
    #10 next = 1;
    number = 8'h30;
    #10 next = 1;
    number = 8'h30;
    #10 next = 1;
    number = 8'h10;
    #10 next = 1;
    number = 8'h10;
    #10 next = 1;
    number = 8'h10;
    $finish;
end
endmodule