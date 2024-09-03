`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/14 21:59:04
// Design Name: 
// Module Name: MUL7_tb
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


module MUL7_tb();
reg clk,rst;
reg [31:0] src;
reg src_valid;
wire ready,res,res_valid;

initial begin
    clk = 0;
    rst = 1;

    #10;
    rst = 0;
    src = 32'b111;//7
    src_valid = 1;

    #330
    rst = 1;
    #10;
    rst = 0;
    src = 32'b1110;//14
    src_valid = 1;

    #330
    rst = 1;
    #10;
    rst = 0;
    src = 32'b1111;//15
    src_valid = 1;
    #20
    src = 32'b1110;//14
    src_valid = 1;

    #310
    rst = 1;
    #10;
    rst = 0;
    src = 32'b1110000000;//896
    src_valid = 1;

    #330
    rst = 1;
    #10;
    rst = 0;
    src = 32'b0;//0
    src_valid = 1;

    #330
    rst = 1;
    #10;
    rst = 0;
    src = 32'b1;//1
    src_valid = 1;

    #330
    rst = 1;
    #10;
    rst = 0;
    src = 32'b1010_0101;//165
    src_valid = 1;



end
always #5 clk = ~ clk;

MUL7 mul(
    .clk(clk),            
    .rst(rst),            
    .src(src),            
    .src_valid(src_valid),      
    .ready(ready),          
    .res(res),           
    .res_valid(res_valid)
);
endmodule
/*
module MUL7(
    input                               clk,            // 时钟信号
    input                               rst,            // 复位信号，使状态机回到初始态
    input               [31 : 0]        src,            // 输入数据
    input                               src_valid,      // 表明输入结果是否有效
    output      reg                     ready,          // 表明是否正在检测
    output      reg                     res,            // 输出结果
    output      reg                     res_valid       // 表明输出结果是否有效
);
*/
