`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/13 15:57:06
// Design Name: 
// Module Name: Input
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


module SW_Input(
    input                   [ 0 : 0]            clk,
    input                   [ 0 : 0]            rst,
    input                   [ 7 : 0]            sw,

    output      reg         [ 3 : 0]            hex,//表示动了哪一位
    output                  [ 0 : 0]            pulse//表示开关是关闭还是开启
);
// 三级寄存器边沿检测
reg [7:0] sw_reg_1, sw_reg_2, sw_reg_3;
always @(posedge clk) begin
    if (rst) begin
        sw_reg_1 <= 0;
        sw_reg_2 <= 0;
        sw_reg_3 <= 0;
    end
    else begin
        sw_reg_1 <= sw;
        sw_reg_2 <= sw_reg_1;
        sw_reg_3 <= sw_reg_2;
    end
end

wire [7:0] sw_change = sw_reg_3 ^ sw_reg_2;// TODO：检测上升沿

// TODO：编写代码，产生 hex 和 pulse 信号。
// Hint：这两个信号均为组合逻辑产生。
always @(*) begin
    case(sw_change)
     8'b0000_0001: begin
        hex = 0;
     end
     8'b0000_0010: begin
        hex = 1;
     end
     8'b0000_0100: begin
        hex = 2;
     end
     8'b0000_1000: begin
        hex = 3;
     end
     8'b0001_0000: begin
        hex = 4;
     end
     8'b0010_0000: begin
        hex = 5;
     end
     default: begin
        hex = 10;
     end
    endcase
end
//assign pulse = (sw_reg_3[hex] > sw[hex]);
assign pulse = ~(hex == 10);

endmodule

