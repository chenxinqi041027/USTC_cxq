`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/14 21:19:18
// Design Name: 
// Module Name: LED_Flow
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


module LED_Flow(
    input                   clk,
    input                   rst,
    output reg [7:0]        led
);

reg [31:0] count_1hz;
parameter TIME_CNT = 50_000_000;
initial begin
    count_1hz = 0;
    led = 8'b0000_1111;
end

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
        led <= 8'b0000_1111;
    else if (count_1hz == 1) begin
        led <= {led[6:0], led[7]};
    end
end
endmodule

