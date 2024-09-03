`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/19 13:07:04
// Design Name: 
// Module Name: Q4_tb
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


module q4_tb();
reg clk, rst, en;
wire out_TA;
initial begin
    clk = 0; rst = 1; en = 0;
    #10;
    rst = 0;
    #10;
    en = 1;
    #20;
    en = 0;
    #20;
    en = 1;
    #20;
    rst = 1;
    #20;
    rst = 0;
    #200;
    en = 0;
end
always #5 clk = ~clk;
Counter #(
    .MIN_VALUE(8'd10), 
    .MAX_VALUE(8'd13)
) counter (
    .clk(clk),
    .rst(rst),
    .enable(en),
    .out(out_TA)
);
endmodule



