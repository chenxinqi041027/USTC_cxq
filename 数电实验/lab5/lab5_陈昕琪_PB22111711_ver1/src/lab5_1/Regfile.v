`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/09 00:43:02
// Design Name: 
// Module Name: Regfile
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



module Regfile (
    input                       clk,          // 时钟信号
    input           [4:0]       ra1,          // 读端口 1 地址
    input           [4:0]       ra2,          // 读端口 2 地址
    input           [4:0]       wa,           // 写端口地址
    input                       we,           // 写使能信号
    input           [31:0]      din,          // 写数据
    output  reg     [31:0]      dout1,        // 读端口 1 数据输出
    output  reg     [31:0]      dout2         // 读端口 2 数据输出
);
// Write your code here
reg [31:0] register [31:0];//32×32bits
// 写端口
always @(posedge clk) begin
    register[0] <= 32'b0;
    if (we && wa != 5'd0) begin
        register[wa] <= din;
    end else register[0] <= 32'b0;
end
always @(*)begin
    if(ra1 == wa)begin
        if (wa != 0) dout1 = din;
        else dout1 = 0;
    end else if(ra2 == wa)begin
        if (wa != 0) dout2 = din;
        else dout1 = 0;
    end else begin
        dout1 = register[ra1];
        dout2 = register[ra2]; 
    end
end
// End of your code
endmodule
