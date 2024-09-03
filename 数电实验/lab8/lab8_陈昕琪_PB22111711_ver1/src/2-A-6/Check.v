`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/14 20:57:36
// Design Name: 
// Module Name: Check
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


module Check(
    input                   [ 0 : 0]            clk,
    input                   [ 0 : 0]            rst,

    input                   [11 : 0]            input_number,
    input                   [11 : 0]            target_number,
    input                   [ 0 : 0]            start_check,

    output                  [ 5 : 0]            check_result
);
// 模块内部用寄存器暂存输入信号，从而避免外部信号突变带来的影响
reg [11:0] current_input_data, current_target_data;
always @(posedge clk) begin
    if (rst) begin
        current_input_data <= 0;
        current_target_data <= 0;
    end
    else if (start_check) begin 
        current_input_data <= input_number;
        current_target_data <= target_number;
    end
end

// 使用组合逻辑产生比较结果
wire [3:0] target_number_3, target_number_2, target_number_1;
wire [3:0] input_number_3, input_number_2, input_number_1;
assign input_number_1 = current_input_data[3:0];
assign input_number_2 = current_input_data[7:4];
assign input_number_3 = current_input_data[11:8];
assign target_number_1 = current_target_data[3:0];
assign target_number_2 = current_target_data[7:4];
assign target_number_3 = current_target_data[11:8];

reg i1t1, i1t2, i1t3, i2t1, i2t2, i2t3, i3t1, i3t2, i3t3;
always @(*) begin
    i1t1 = (input_number_1 == target_number_1);//1，正确且位置正确
    i1t2 = (input_number_1 == target_number_2);//1，正但位置错误
    i1t3 = (input_number_1 == target_number_3);//1，正确但位置错误
    i2t1 = (input_number_2 == target_number_1);//1，
    i2t2 = (input_number_2 == target_number_2);//1，正确且位置正确
    i2t3 = (input_number_2 == target_number_3);//1，
    i3t1 = (input_number_3 == target_number_1);//1，
    i3t2 = (input_number_3 == target_number_2);//1，
    i3t3 = (input_number_3 == target_number_3);//1，正确且位置正确
end
reg [2:0] num_1,num_2;
always @(*) begin
        num_1 = 0;
        num_2 = 0;
    if(start_check)begin
        if(i1t1)begin//001,000
            if(i2t2)begin//010,000
                if(i3t3)begin
                    num_1 = 3'b100;
                    num_2 = 3'b000;
                end else if(i3t1 || i3t2)begin
                    num_1 = 3'b010;
                    num_2 = 3'b001;
                end else begin
                    num_1 = 3'b010;
                    num_2 = 3'b000;
                end
            end else if(i2t1 || i2t3)begin//001,001
                if(i3t3)begin
                    num_1 = 3'b010;
                    num_2 = 3'b001;
                end else if(i3t1 || i3t2)begin
                    num_1 = 3'b001;
                    num_2 = 3'b010;
                end else begin
                    num_1 = 3'b001;
                    num_2 = 3'b001;
                end
            end else begin//001,000
                if(i3t3)begin
                    num_1 = 3'b010;
                    num_2 = 3'b000;
                end else if(i3t1 || i3t2)begin
                    num_1 = 3'b001;
                    num_2 = 3'b001;
                end else begin
                    num_1 = 3'b001;
                    num_2 = 3'b000;
                end
                end
        end else if(i1t2 || i1t3) begin//000,001
            if(i2t2)begin//001,001
                if(i3t3)begin
                    num_1 = 3'b010;
                    num_2 = 3'b001;
                end else if(i3t1 || i3t2)begin
                    num_1 = 3'b001;
                    num_2 = 3'b010;
                end else begin
                    num_1 = 3'b001;
                    num_2 = 3'b001;
                end
            end else if(i2t1 || i2t3)begin//000,010
                if(i3t3)begin
                    num_1 = 3'b001;
                    num_2 = 3'b010;
                end else if(i3t1 || i3t2)begin
                    num_1 = 3'b000;
                    num_2 = 3'b100;
                end else begin
                    num_1 = 3'b000;
                    num_2 = 3'b010;
                end
            end else begin//000,001
                if(i3t3)begin
                    num_1 = 3'b001;
                    num_2 = 3'b001;
                end else if(i3t1 || i3t2)begin
                    num_1 = 3'b000;
                    num_2 = 3'b010;
                end else begin
                    num_1 = 3'b000;
                    num_2 = 3'b001;
                end
                end
        end else begin//000,000
            if(i2t2)begin//001,000
                if(i3t3)begin
                    num_1 = 3'b010;
                    num_2 = 3'b000;
                end else if(i3t1 || i3t2)begin
                    num_1 = 3'b001;
                    num_2 = 3'b001;
                end else begin
                    num_1 = 3'b001;
                    num_2 = 3'b000;
                end
            end else if(i2t1 || i2t3)begin//000,001
                if(i3t3)begin
                    num_1 = 3'b001;
                    num_2 = 3'b001;
                end else if(i3t1 || i3t2)begin
                    num_1 = 3'b000;
                    num_2 = 3'b010;
                end else begin
                    num_1 = 3'b000;
                    num_2 = 3'b001;
                end
            end else begin//000,000
                if(i3t3)begin
                    num_1 = 3'b001;
                    num_2 = 3'b000;
                end else if(i3t1 || i3t2)begin
                    num_1 = 3'b000;
                    num_2 = 3'b001;
                end else begin
                    num_1 = 3'b000;
                    num_2 = 3'b000;
                end
                end
        end
    end else begin
        num_1 = 3'b000;
        num_2 = 3'b000;
    end
end
assign check_result = {{num_1},{num_2}};
endmodule
