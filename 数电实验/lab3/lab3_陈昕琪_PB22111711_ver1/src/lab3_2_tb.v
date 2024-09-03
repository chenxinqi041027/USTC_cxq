`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/02 03:06:14
// Design Name: 
// Module Name: Flash_tb
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


module Flash_tb();
reg clk,btn;
wire [7:0] led;

initial begin
    clk = 0; btn=0;
end

always #5 clk = ~clk;//T=10ns

Flash flash(
    .clk(clk),
    .btn(btn),
    .led(led)
);

endmodule
