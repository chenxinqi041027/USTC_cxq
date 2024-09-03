`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/09 00:52:37
// Design Name: 
// Module Name: Regfile_tb
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


module Regfile_tb();
reg clk;
reg [4:0] ra1, ra2, wa;
reg we;
reg [31:0] din;
wire [31:0] dout1, dout2;

Regfile regfile (
    .clk(clk),
    .ra1(ra1),
    .ra2(ra2),
    .wa(wa),
    .we(we),
    .din(din),
    .dout1(dout1),
    .dout2(dout2)
);

initial begin
    // 初始化信号
    clk = 0;
    #10;
    ra1 = 0;  // 读端口1地址
    ra2 = 0; // 读端口2地址
    wa = 1;  // 
    we = 1;   // 写使能
    din = 32'h11111111; // 写数据

    #10;
    ra1 = 0;  // 读端口1地址
    ra2 = 0; // 读端口2地址
    wa = 1;//地址
    we = 1;//使能
    din = 32'h00000001;

    #10
    wa = 2;//地址
    we = 1;//使能
    din = 32'h22222222;

    #10
    wa = 3;//地址
    we = 1;//使能
    din = 32'h33333333;

    #10
    wa = 30;//地址
    we = 1;//使能
    din = 32'h44444444;

    #10
    wa = 15;//地址
    we = 1;//使能
    din = 32'h55555555;

//前面写入了地址为0，1，2，30，15的数据
    #10;
    ra1 = 0;  // 读端口1地址
    ra2 = 1; // 读端口2地址
    wa = 4;//地址
    we = 1;//使能
    din = 32'h10;

    #10;
    ra1 = 2;  // 读端口1地址
    ra2 = 30; // 读端口2地址
    wa = 5;//地址
    we = 1;//使能
    din = 32'h15;

    //同时读写时，测试是否可以读入最新值
    #10;
    ra1 = 15;  // 读端口1地址
    ra2 = 5; // 读端口2地址
    wa = 15;
    we = 1;
    din = 32'h88888888;

end

always #5 clk = ~clk;

endmodule
