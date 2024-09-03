`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/14 14:48:00
// Design Name: 
// Module Name: Control
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


module Control (
    input                   [ 0 : 0]            clk,
    input                   [ 0 : 0]            rst,
    input                   [ 0 : 0]            btn,

    input                   [ 5 : 0]            check_result,
    output      reg         [ 0 : 0]            check_start,
    output      reg         [ 0 : 0]            timer_en,
    output      reg         [ 0 : 0]            timer_set,
    input                   [ 0 : 0]            timer_finish,
    input                   [ 0 : 0]            finish1,
    input                   [ 0 : 0]            finish2,
    input                   [ 0 : 0]            finish3,

    output      reg         [ 1 : 0]            led_sel,
    output      reg         [ 1 : 0]            seg_sel,
    output      reg         [ 1 : 0]            output_sel,
    output      reg         [ 0 : 0]            generate_random,
    output      reg         [ 0 : 0]            random_en,
    input                   [ 0 : 0]            uart_pause,
    input                   [ 0 : 0]            uart_new
);
localparam WAIT = 2'b00;//等待输入
localparam CHECK = 2'b01;//判断出结果
localparam RIGHT = 2'b10;//结果正确
localparam WRONG = 2'b11;//结果错误
reg [1:0] current_state,next_state;
initial begin
    current_state = WAIT;
end
always @(posedge clk) begin
    if(rst)
        current_state <= WAIT;
    else
        current_state <= next_state;
end
always @(*) begin
    case (current_state)
    WAIT: begin
        if(timer_finish != 1) begin
            if(uart_new == 1) begin
                next_state = WAIT;
            end else if(btn)begin
                if(check_result == 6'b100_000) begin
                    next_state = RIGHT;
                end else next_state = CHECK;
            end else begin
                next_state = WAIT;
            end
        end else begin
            next_state = WRONG;
        end
    end
    CHECK: begin
        if(timer_finish != 1) begin
            if(uart_new == 1) begin
                next_state = WAIT;
            end else if(btn) begin
                next_state = WAIT;
            end else next_state = CHECK;
        end else begin
            next_state = WRONG;
        end
    end
    RIGHT: begin
        if(uart_new == 1) begin
            next_state = WAIT;
        end else if (btn) begin
            next_state = WAIT;
        end else next_state = RIGHT;
    end
    WRONG: begin
        if(uart_new == 1) begin
            next_state = WAIT;
        end else if(btn) begin
            next_state = WAIT;
        end else begin
            next_state = WRONG;
        end
    end
    endcase
end
always @(posedge clk) begin
    if(rst) begin
        timer_en <= 0;//时间不开始计时
        timer_set <= 1;//时间重置
        generate_random <= 1;
        random_en <= 1;
    end else begin
    if(current_state == WAIT) begin
        if(uart_pause) begin
            timer_en <= 0;
            timer_set <= 0;
            random_en <= 0;
        end else if(uart_new) begin
                timer_en <= 0;
                timer_set <= 1;
                random_en <= 1;
            end else begin
            timer_en <= 1;
            timer_set <= 0;
            random_en <= 0;
        end
        check_start <= 1; 
        led_sel <= 2'b00;
        seg_sel <= 2'b00;
        if(finish1)begin
            output_sel <= 2'b00;
        end else if(finish2) begin
            output_sel <= 2'b01;
        end else if(finish3) begin
            output_sel <= 2'b10;
        end else output_sel <= 2'b00;
        generate_random <= 1;
    end
    if(current_state == CHECK) begin
        check_start <= 0;
        if(uart_pause) begin
            timer_en <= 0;
            timer_set <= 0;
            random_en <= 0;
        end else if(uart_new) begin
                timer_en <= 0;
                timer_set <= 1;
                random_en <= 1;
            end else begin
            timer_en <= 1;
            timer_set <= 0;
            random_en <= 0;
        end
        led_sel <= 2'b01;
        seg_sel <= 2'b01;
        if(finish1)begin
            output_sel <= 2'b00;
        end else if(finish2) begin
            output_sel <= 2'b01;
        end else if(finish3) begin
            output_sel <= 2'b10;
        end else output_sel <= 2'b00;
        generate_random <= 1;
    end
    if(current_state == WRONG) begin
        if(uart_pause) begin
            timer_en <= 0;
            timer_set <= 0;
            random_en <= 0;
        end else if(uart_new) begin
                timer_en <= 0;
                timer_set <= 1;
                random_en <= 1;
            end else begin
            timer_en <= 0;
            timer_set <= 1;
            if(next_state == WAIT)begin
                random_en <= 1;
            end else begin
                random_en <= 0;
            end
        end
        check_start <= 0;
        timer_en <= 0;
        timer_set <= 1;
        led_sel <= 2'b11;
        seg_sel <= 2'b11;
        output_sel <= 2'b00;
        generate_random <= 1;
    end
    if(current_state == RIGHT) begin
        if(uart_pause) begin
            timer_en <= 0;
            timer_set <= 0;
            random_en <= 0;
        end else if(uart_new) begin
                timer_en <= 0;
                timer_set <= 1;
                random_en <= 1;
            end else begin
            timer_en <= 0;
            timer_set <= 1;
            if(next_state == WAIT)begin
                random_en <= 1;
            end else begin
                random_en <= 0;
            end
        end
        check_start <= 0;
        timer_en <= 0;
        timer_set <= 1;
        led_sel <= 2'b10;
        seg_sel <= 2'b10;
        output_sel <= 2'b00;
        generate_random <= 1;
    end
end
end

endmodule
