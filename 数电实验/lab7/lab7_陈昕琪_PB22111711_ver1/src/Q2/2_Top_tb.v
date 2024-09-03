`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/02 04:41:50
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


module Top_tb();
reg                   clk;
reg                   btn;
reg  [7:0]            sw;
wire [2:0]            seg_an;
wire [3:0]            seg_data;
initial begin
    clk = 0;
    btn = 0;
    sw = 8'b1_001_0001;
    #10;
    sw = 8'b0_001_0001;
    btn = 1;
    #10 btn = 0;
    #2000;
    sw = 8'b1_011_0001;
    #10;
    sw = 8'b0_011_0001;
    btn = 1;
    #10 btn = 0;
    #2000;
end
always #5 clk = ~clk;
Top top(
    .clk(clk),
    .btn(btn),
    .sw(sw),
    .seg_an(seg_an),
    .seg_data(seg_data)
);
endmodule
/*module Top(
    input                   clk,
    input                   btn,
    input  [7:0]            sw,
    output [2:0]            seg_an,
    output [3:0]            seg_data
);*/