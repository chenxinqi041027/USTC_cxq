`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/02 02:03:09
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


module Top (
    input   [7:0]                       sw,
    output  [7:0]                       led
);
reg [7:0] temp;
// Write your codes here.
always @(*) begin
    temp[7] = sw[0];
    temp[6] = sw[1];
    temp[5] = sw[2];
    temp[4] = sw[3];
    temp[3] = sw[4];
    temp[2] = sw[5];
    temp[1] = sw[6];
    temp[0] = sw[7];
end

assign led=temp;

endmodule