`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/14 20:41:56
// Design Name: 
// Module Name: Shift_Reg
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


module ShiftReg(
    input                   [ 0 : 0]            clk,
    input                   [ 0 : 0]            rst,
    input                   [ 3 : 0]            hex,
    input                   [ 0 : 0]            pulse,
    output      reg         [31 : 0]            dout
);
always @(posedge clk) begin
    if (rst)
        dout <= 0;
    else if (pulse)
        dout <= {{dout[27: 0]}, {hex}};
end
endmodule

