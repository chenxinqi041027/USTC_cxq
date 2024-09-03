`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/19 01:54:29
// Design Name: 
// Module Name: Q3_tb
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


module Q3_tb();
reg clk,a,b;
reg [7:0] c;

initial begin
    c = 8'b0000_0000;
    clk = 1'b1;
    a = 1'b1;
    b = 1'b0;
    #10;

    c = 8'b0000_0001;
    #10;

    b = ~b;
    #5;
    
    b = ~b;
    #5;

    c = 8'b0000_0010;
    #10;

    a = ~a;
    b = ~b;
    #10;

    a = ~a;
    c = 8'b0000_0011;
    #20;

    a = ~a;
    b = ~b;
    #5;

    b=~b;
    #5;

    c = 8'b0000_0100;
    a = ~a;
    #10;

    b = ~b;
end

always #5 clk = ~clk;
endmodule
