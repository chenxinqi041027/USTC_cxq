`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/21 20:19:41
// Design Name: 
// Module Name: SRL
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


module way1(
    input                   [31 : 0]        src0,
    input                   [ 4 : 0]        src1,
    output  reg             [31 : 0]        res1_1,       //逻辑右移
    output  reg             [31 : 0]        res2_1        //算数右移
);

always @(*) begin
    case(src1)
        5'b00000 :begin
            res1_1 = {src0[31:0]};
            res2_1 = {src0[31:0]};
        end
        5'b00001 :begin
            res1_1 = {1'b0,src0[31:1]};
            res2_1 = {src0[31],src0[31:1]};
        end
        5'b00010 :begin
            res1_1 = {2'b0,src0[31:2]};
            res2_1 = {{2{src0[31]}},src0[31:2]};
        end
        5'b00011 :begin
            res1_1 = {3'b0,src0[31:3]};
            res2_1 = {{3{src0[31]}},src0[31:3]};
        end
        5'b00100 :begin
            res1_1 = {4'b0,src0[31:4]};
            res2_1 = {{4{src0[31]}},src0[31:4]};
        end
        5'b00101 :begin
            res1_1 = {5'b0,src0[31:5]};
            res2_1 = {{5{src0[31]}},src0[31:5]};
        end
        5'b00110 :begin
            res1_1 = {6'b0,src0[31:6]};
            res2_1 = {{6{src0[31]}},src0[31:6]};
        end
        5'b00111 :begin
            res1_1 = {7'b0,src0[31:7]};
            res2_1 = {{7{src0[31]}},src0[31:7]};
        end
        5'b01000 :begin
            res1_1 = {8'b0,src0[31:8]};
            res2_1 = {{8{src0[31]}},src0[31:8]};
        end
        5'b01001 :begin
            res1_1 = {9'b0,src0[31:9]};
            res2_1 = {{9{src0[31]}},src0[31:9]};
        end
        5'b01010 :begin
            res1_1 = {10'b0,src0[31:10]};
            res2_1 = {{10{src0[31]}},src0[31:10]};
        end
        5'b01011 :begin
            res1_1 = {11'b0,src0[31:11]};
            res2_1 = {{11{src0[31]}},src0[31:11]};
        end
        5'b01100 :begin
            res1_1 = {12'b0,src0[31:12]};
            res2_1 = {{12{src0[31]}},src0[31:12]};
        end
        5'b01101 :begin
            res1_1 = {13'b0,src0[31:13]};
            res2_1 = {{13{src0[31]}},src0[31:13]};
        end
        5'b01110 :begin
            res1_1 = {14'b0,src0[31:14]};
            res2_1 = {{14{src0[31]}},src0[31:14]};
        end
        5'b01111 :begin
            res1_1 = {15'b0,src0[31:15]};
            res2_1 = {{15{src0[31]}},src0[31:15]};
        end
        5'b10000 :begin
            res1_1 = {16'b0,src0[31:16]};
            res2_1 = {{16{src0[31]}},src0[31:16]};
        end
        5'b10001 :begin
            res1_1 = {17'b0,src0[31:17]};
            res2_1 = {{17{src0[31]}},src0[31:17]};
        end
        5'b10010 :begin
            res1_1 = {18'b0,src0[31:18]};
            res2_1 = {{18{src0[31]}},src0[31:18]};
        end
        5'b10011 :begin
            res1_1 = {19'b0,src0[31:19]};
            res2_1 = {{19{src0[31]}},src0[31:19]};
        end
        5'b10100 :begin
            res1_1 = {20'b0,src0[31:20]};
            res2_1 = {{20{src0[31]}},src0[31:20]};
        end
        5'b10101 :begin
            res1_1 = {21'b0,src0[31:21]};
            res2_1 = {{21{src0[31]}},src0[31:21]};
        end
        5'b10110 :begin
            res1_1 = {22'b0,src0[31:22]};
            res2_1 = {{22{src0[31]}},src0[31:22]};
        end
        5'b10111 :begin
            res1_1 = {23'b0,src0[31:23]};
            res2_1 = {{23{src0[31]}},src0[31:23]};
        end
        5'b11000 :begin
            res1_1 = {24'b0,src0[31:24]};
            res2_1 = {{24{src0[31]}},src0[31:24]};
        end
        5'b11001 :begin
            res1_1 = {25'b0,src0[31:25]};
            res2_1 = {{25{src0[31]}},src0[31:25]};
        end
        5'b11010 :begin
            res1_1 = {26'b0,src0[31:26]};
            res2_1 = {{26{src0[31]}},src0[31:26]};
        end
        5'b11011 :begin
            res1_1 = {27'b0,src0[31:27]};
            res2_1 = {{27{src0[31]}},src0[31:27]};
        end
        5'b11100 :begin
            res1_1 = {28'b0,src0[31:28]};
            res2_1 = {{28{src0[31]}},src0[31:28]};
        end
        5'b11101 :begin
            res1_1 = {29'b0,src0[31:29]};
            res2_1 = {{29{src0[31]}},src0[31:29]};
        end
        5'b11110 :begin
            res1_1 = {30'b0,src0[31:30]};
            res2_1 = {{30{src0[31]}},src0[31:30]};
        end
        5'b11111 :begin
            res1_1 = {31'b0,src0[31]};
            res2_1 = {32{src0[31]}};
        end
        default: ;
endcase
end
endmodule
