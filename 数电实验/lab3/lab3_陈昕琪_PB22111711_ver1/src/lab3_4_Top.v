`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/02 05:32:34
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
    input  [7:0]            sw,
    output [2:0]            seg_an,
    output [3:0]            seg_data
);
    Segment segment(
        .clk(clk),
        .rst(btn),
        .output_data(32'h22111711),// <- 改为你学号中的 8 位数字
        .output_valid(sw),   
        .seg_data(seg_data),
        .seg_an(seg_an)
    );
endmodule
