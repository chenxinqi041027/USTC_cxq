`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/14 19:48:09
// Design Name: 
// Module Name: RadomNumber
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


module RadomNumber(
    input [0:0] clk,
    input [0:0] btn,
    output [11:0] target_number
);

integer seed;
reg [3:0] a,b,c;
always @(posedge clk) begin
    if(btn) begin
    a = ($random(seed))%6;
    b = ($random(seed+1))%6;
    c = ($random(seed+2))%6;
    end
end
assign target_number = {{a},{b},{c}};
endmodule

