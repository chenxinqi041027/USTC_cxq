`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/09 02:05:44
// Design Name: 
// Module Name: Top
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


module Top(
    input                   clk,
    input                   btn,
    output [2:0]            seg_an,
    output [3:0]            seg_data
);
    TIMER timer(
        .clk(clk),
        .rst(btn),
        .seg_data(seg_data),
        .seg_an(seg_an)
    );
endmodule
/*module TIMER (
    input                           clk,rst,
    output      reg     [3:0]       seg_data,
    output      reg     [2:0]       seg_an
);*/