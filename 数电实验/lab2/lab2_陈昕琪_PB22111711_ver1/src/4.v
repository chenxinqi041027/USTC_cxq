`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/10/19 13:05:11
// Design Name: 
// Module Name: Q4
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


module Counter #(
    parameter   MIN_VALUE = 8'd0,
    parameter   MAX_VALUE = 8'd100
)(
    input                   clk,
    input                   rst,
    input                   enable,
    output                  out
);

reg [7:0] counter;

always @(posedge clk) begin
    if (rst) begin
        counter <= 0;//复位为0
    end else if (enable) begin//enable为高电平
        if (counter >= MAX_VALUE) begin//max和min之间工作
            counter <= MIN_VALUE;
        end
        else if(counter >= MIN_VALUE)
            counter <= counter + 1;
        else counter <= MIN_VALUE;
    end 
    else 
        counter <= 0;//counter复位为0
end

assign out = (counter == MAX_VALUE);

endmodule

