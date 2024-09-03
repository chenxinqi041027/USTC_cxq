`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/22 01:21:52
// Design Name: 
// Module Name: way3
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


module way3(
    input                   [31 : 0]        src0,
    input                   [ 4 : 0]        src1,
    output                  [31 : 0]        res1_3,       //逻辑右移
    output                  [31 : 0]        res2_3        //算数右移
);

reg[31:0] temp1;
reg[31:0] temp2;

always @(*) begin
    case(src1[2:0])
        3'b000 :begin
            temp1 = {src0[31:0]};
            temp2 = {src0[31:0]};
        end
        3'b001 :begin
            temp1 = {1'b0,src0[31:1]};
            temp2 = {src0[31],src0[31:1]};
        end
        3'b010 :begin
            temp1 = {2'b0,src0[31:2]};
            temp2 = {{2{src0[31]}},src0[31:2]};
        end
        3'b011 :begin
            temp1 = {3'b0,src0[31:3]};
            temp2 = {{3{src0[31]}},src0[31:3]};
        end
        3'b100 :begin
            temp1 = {4'b0,src0[31:4]};
            temp2 = {{4{src0[31]}},src0[31:4]};
        end
        3'b101 :begin
            temp1 = {5'b0,src0[31:5]};
            temp2 = {{5{src0[31]}},src0[31:5]};
        end
        3'b110 :begin
            temp1 = {6'b0,src0[31:6]};
            temp2 = {{6{src0[31]}},src0[31:6]};
        end
        3'b111 :begin
            temp1 = {7'b0,src0[31:7]};
            temp2 = {{7{src0[31]}},src0[31:7]};
        end
    endcase
end

reg [31:0] temp1_1,temp1_2;
reg [31:0] temp2_1,temp2_2;

always @(*) begin
    if(src1[3] == 1) begin
        temp1_1 = {8'b0,temp1[31:8]};
        temp2_1 = {{8{temp2[31]}},temp2[31:8]};
    end else begin
        temp1_1 = temp1[31:0];
        temp2_1 = temp2[31:0];
    end

    if(src1[4] == 1) begin
        temp1_2 = {16'b0,temp1_1[31:16]};
        temp2_2 = {{16{temp2_1[31]}},temp2_1[31:16]};
    end else begin
        temp1_2 = temp1_1[31:0];
        temp2_2 = temp2_1[31:0];
    end
end

assign res1_3 = temp1_2;
assign res2_3 = temp2_2;

endmodule
