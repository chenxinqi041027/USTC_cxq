`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/02 02:07:05
// Design Name: 
// Module Name: Top_tb
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
reg [7:0] sw;
wire [7:0] led;

initial begin
    sw = 0000_0000;
    #10;
    sw = 0000_0001;
    #10;
    sw = 0000_0011;
    #10;
    sw = 1000_0001;
    #10;
    sw = 1000_0000;
end

Top top(
    .sw(sw),
    .led(led)
);
endmodule
