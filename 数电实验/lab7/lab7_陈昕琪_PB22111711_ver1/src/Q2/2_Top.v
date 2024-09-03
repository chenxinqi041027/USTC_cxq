`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/07 16:17:35
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
wire [7:0] res;
reg [7:0] res_temp;
initial begin
    res_temp = 0;
end
    MUL_4 mul(
    .clk(clk),
    .rst(sw[7]),
    .a({{1'b0},{sw[6:4]}}),
    .b(sw[3:0]),
    .start(btn),
    .res(res),
    .finish()
    );
always @(posedge clk) begin
    if(res != 0) begin
        res_temp <= res;
    end else res_temp <= res_temp;
end
    Segment segment(
        .clk(clk),
        .rst(btn),
        .output_data({{24'b0},{res_temp[7:0]}}),
        .seg_data(seg_data),
        .seg_an(seg_an)
    );
endmodule
/*module Segment(
    input                       clk,
    input                       rst,
    input       [31:0]          output_data,

    output reg  [3:0]          seg_data,
    output reg  [2:0]          seg_an
);*/
