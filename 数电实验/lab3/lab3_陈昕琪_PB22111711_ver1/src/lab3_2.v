`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/02 02:51:27
// Design Name: 
// Module Name: Flash
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


module Flash(
    input clk,
    input btn,
    output reg [7:0] led
);

reg [31:0] count_1hz;
wire rst;
parameter TIME_CNT = 50_000_000;

initial begin
    led = 8'b1111_1111;
    count_1hz = 2;
end

assign rst = btn;   // Use button for RESET

always @(posedge clk) begin
    if (rst)
        count_1hz <= 0;
    else if (count_1hz >= TIME_CNT)
        count_1hz <= 0;
    else
        count_1hz <= count_1hz + 1;
end

always @(posedge clk) begin
    if (rst)
        led <= 8'b0000_0000;
    else if (count_1hz == 1) begin
        led <= ~led;
    end
end
endmodule
