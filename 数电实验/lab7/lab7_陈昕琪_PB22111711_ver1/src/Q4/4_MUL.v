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
reg [  WIDTH-1 : 0]     multiplicand;       // 被乘数寄存器
reg [2*WIDTH   : 0]     product;            // 乘积寄存器

localparam IDLE = 2'b00;            // 空闲状态。这个周期寄存器保持原值不变。当 start 为 1 时跳转到 INIT。
localparam INIT = 2'b01;            // 初始化。下个周期跳转到 CALC
localparam CALC = 2'b10;            // 计算中。计算完成时跳转到 DONE
localparam DONE = 2'b11;            // 计算完成。下个周期跳转到 IDLE
reg [1:0] current_state, next_state;
reg [31:0] n;
reg [2*WIDTH : 0]     temp;

always @(posedge clk) begin
    if(rst) begin
        current_state <= IDLE;
        multiplicand <= 4'b0;
        product <= 9'b0;
        res <= 9'b0;
        n <= 1'b0;
    end else  begin
        current_state <= next_state;
    end
    if(next_state == CALC && n != WIDTH) begin
        n <= n + 1;
    end else if(n == WIDTH) begin
        n <= 0;
    end
end
always @(posedge clk) begin
    if (next_state == CALC) begin
        if (product[0] == 1) begin
            product <= {1'b0,{temp[2*WIDTH:1]}} + {1'b0,product[2*WIDTH:1]};
        end else product <= {1'b0,product[2*WIDTH:1]};
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
            if(a[WIDTH-1] == 1) begin
                multiplicand = ~a + 1;
            end else multiplicand = a;
            if(b[WIDTH-1] == 1) begin
                product[WIDTH-1:0] = ~b + 1;
                product[2*WIDTH:WIDTH] = 0;
            end else product = b;
            temp = {1'b0,multiplicand[WIDTH-1:0],32'b0};
            finish = 0;
            n = 0;
            next_state = CALC;
        end

        CALC: begin
            if (n == WIDTH) begin
                next_state = DONE;
            end else begin
                next_state = CALC;
            end
        end

        DONE: begin
            next_state = IDLE;
        end
    endcase
end

always @(*)begin
    finish = (current_state == DONE);
    if(finish == 1) begin
        if(a[WIDTH-1] == b[WIDTH-1]) begin
            res = product;
        end else res = {1'b1,(~product[2*WIDTH-2:0]+1)};
    end else res = 0;
end
endmodule
   