`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/09 02:04:19
// Design Name: 
// Module Name: Timer_tb
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


module Timer_tb();
reg clk,rst;
wire [3:0] seg_data;
wire [2:0] seg_an;
initial begin
    clk = 1;
    rst = 0;
    #10000000;
    rst = 1;
    #10;
    rst = 0;
end
TIMER timer(
    .clk(clk),
    .rst(rst),
    .seg_data(seg_data),
    .seg_an(seg_an)
);
always #5 clk = ~clk;
endmodule
/*module Top(
    input                   clk,
    input                   btn,
    output [2:0]            seg_an,
    output [3:0]            seg_data
);
module TIMER (
    input                           clk,rst,
    output      wire     [3:0]       seg_data,
    output      wire     [2:0]       seg_an
);*/