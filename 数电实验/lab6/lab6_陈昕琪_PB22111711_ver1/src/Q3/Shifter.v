`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/21 20:19:21
// Design Name: 
// Module Name: Shifter
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


module Shifter(
    input                   [31 : 0]        src0,
    input                   [ 4 : 0]        src1,
    output                  [31 : 0]        res1_1,       //第一种方法，逻辑右移
    output                  [31 : 0]        res1_2,       //第二种方法，逻辑右移
    output                  [31 : 0]        res2_1,       //第一种方法，算数右移
    output                  [31 : 0]        res2_2,       //第二种方法，算数右移
    output                  [31 : 0]        res3_1,       //第一种方法，逻辑右移
    output                  [31 : 0]        res3_2       //第二种方法，逻辑右移
);
// Write your code here
way1 w1(
    .src0(src0),
    .src1(src1),
    .res1_1(res1_1),
    .res2_1(res1_2)
);

way2 w2(
    .src0(src0),
    .src1(src1),
    .res1_2(res2_1),
    .res2_2(res2_2)
);

way3 w3(
    .src0(src0),
    .src1(src1),
    .res1_3(res3_1),
    .res2_3(res3_2)
);
// End of your code
endmodule
/*module way1(
    input                   [31 : 0]        src0,
    input                   [ 4 : 0]        src1,
    output  reg             [31 : 0]        res1_1,       //逻辑右移
    output  reg             [31 : 0]        res2_1        //算数右移
);*/
