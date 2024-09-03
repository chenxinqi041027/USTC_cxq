`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/21 20:19:55
// Design Name: 
// Module Name: SRA
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


module way2(
    input                   [31 : 0]        src0,
    input                   [ 4 : 0]        src1,
    output                  [31 : 0]        res1_2,       //逻辑右移
    output                  [31 : 0]        res2_2        //算数右移
);

reg [31:0] temp1_1,temp1_2,temp1_3,temp1_4,temp1_5;
reg [31:0] temp2_1,temp2_2,temp2_3,temp2_4,temp2_5;

always @(*) begin
    if(src1[4] == 1) begin
        temp1_1 = {16'b0,src0[31:16]};
        temp2_1 = {{16{src0[31]}},src0[31:16]};
    end else begin
        temp1_1 = src0[31:0];
        temp2_1 = src0[31:0];
    end

    if(src1[3] == 1) begin
        temp1_2 = {8'b0,temp1_1[31:8]};
        temp2_2 = {{8{temp2_1[31]}},temp2_1[31:8]};
    end else begin
        temp1_2 = temp1_1[31:0];
        temp2_2 = temp2_1[31:0];
    end

    if(src1[2] == 1) begin
        temp1_3 = {4'b0,temp1_2[31:4]};
        temp2_3 = {{4{temp2_2[31]}},temp2_2[31:4]};
    end else begin
        temp1_3 = temp1_2[31:0];
        temp2_3 = temp2_2[31:0];
    end

    if(src1[1] == 1) begin
        temp1_4 = {2'b0,temp1_3[31:2]};
        temp2_4 = {{2{temp2_3[31]}},temp2_3[31:2]};
    end else begin
        temp1_4 = temp1_3[31:0];
        temp2_4 = temp2_3[31:0];
    end

    if(src1[0] == 1) begin
        temp1_5 = {1'b0,temp1_4[31:1]};
        temp2_5 = {temp2_4[31],temp2_4[31:1]};
    end else begin
        temp1_5 = temp1_4[31:0];
        temp2_5 = temp2_4[31:0];
    end
end

assign res1_2 = temp1_5;
assign res2_2 = temp2_5;


endmodule
