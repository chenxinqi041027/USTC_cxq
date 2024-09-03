`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/21 17:48:08
// Design Name: 
// Module Name: Comp
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


module Comp(
    input [31:0] a,b,
    output ul,sl//ul,无符号比较;sl,有符号比较
    );
reg temp;
reg u;//sl1表示a,b同号，sl2表示a，b异号
wire [31:0] s;
wire co;

AddSub sub1(
    .a(a),
    .b(b),
    .out(s),
    .co(co)
);

//无符号比较
always @(*) begin
    if(a[31] == 1 && b[31] == 0) begin//a>b
        u = 0;
    end
    else if(a[31] == 0 && b[31] == 1) begin
        u = 1;
    end
    else if(a[31]==b[31]) begin
        u = ~co;//进位为1，表示a>b,u=0
    end
end
assign ul = u;
//有符号比较
always @(*) begin
    if(a[31] == b[31]) begin//ab同号
        temp = s[31];
    end else begin
        if(a[31] == 1 && b[31] == 0) begin//ab异号
            temp = 1;//a为负，b为正
        end else temp = 0;
    end
end
assign sl = temp;
endmodule
//有符号比较
//ab同号，a[31]==b[31],用减法
//ab异号，若a<b,则a[31]为1，b[31]为0
/*module AddSub (
    input                   [ 31 : 0]        a, b,
    input                   [ 0 : 0 ]        ci,
    output                  [ 31 : 0]        out,
    output                  [ 0 : 0]        co
);*/
