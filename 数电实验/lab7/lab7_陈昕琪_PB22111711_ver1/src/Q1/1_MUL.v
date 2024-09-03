`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/04 18:49:55
// Design Name: 
// Module Name: MUL
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


module MUL #(
    parameter                               WIDTH = 32
) (
    input                   [ 0 : 0]            clk,
    input                   [ 0 : 0]            rst,
    input                   [ 0 : 0]            start,
    input                   [WIDTH-1 : 0]       a,
    input                   [WIDTH-1 : 0]       b,
    output      reg         [2*WIDTH-1:0]       res,
    output      reg         [ 0 : 0]            finish
);
reg [2*WIDTH-1 : 0]     multiplicand;       // 被乘数寄存器
reg [  WIDTH-1 : 0]     multiplier;         // 乘数寄存器
reg [2*WIDTH-1 : 0]     product;            // 乘积寄存器

localparam IDLE = 2'b00;            // 空闲状态。这个周期寄存器保持原值不变。当 start 为 1 时跳转到 INIT。
localparam INIT = 2'b01;            // 初始化。下个周期跳转到 CALC
localparam CALC = 2'b10;            // 计算中。计算完成时跳转到 DONE
localparam DONE = 2'b11;            // 计算完成。下个周期跳转到 IDLE
reg [1:0] current_state, next_state;
reg [31:0] n;

always @(posedge clk) begin
    if(rst) begin
        current_state <= IDLE;
        multiplicand <= 0;
        multiplier <= 0;
        product <= 0;
        res <= 0;
        n <=0;
    end else  begin
        current_state <= next_state;
    end
    if(next_state == CALC) begin
        if(multiplier[0] == 1) begin
            product <= multiplicand + product;
        end else product <= product;
        multiplicand <= {multiplicand[2*WIDTH-2:0],1'b0};
        multiplier <= {1'b0,multiplier[WIDTH-1:1]};
    end
    if(next_state == CALC && n != WIDTH) begin
        n <= n + 1;
    end else if(n == WIDTH) begin
        n <= 0;
    end
end
// 实现 FSM
always @(*) begin
    case(current_state)
        IDLE: begin
            if (start) next_state = INIT;
            else next_state = IDLE;
        end

        INIT: begin
            finish = 0;
            multiplicand = a;
            multiplier = b;
            product = 0;
            n = 0;
            next_state = CALC;
        end

        CALC: begin
            if (n == WIDTH) begin
                next_state = DONE;
            end else next_state = CALC;
        end
        
        DONE: begin
            next_state = IDLE;
        end
    endcase
end

always @(*)begin
    finish = (current_state == DONE);
    res = finish ? product : 0;
end
endmodule
