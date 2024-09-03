`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/12 17:27:03
// Design Name: 
// Module Name: Receive
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


module Receive(
    input                   [ 0 : 0]        clk,
    input                   [ 0 : 0]        rst,

    input                   [ 0 : 0]        din,

    output      reg         [ 0 : 0]        din_vld,
    output      reg         [ 7 : 0]        din_data
);

// Counter and parameters
localparam FullT        = 867;//
localparam HalfT        = 433;//起始位中间时刻
localparam TOTAL_BITS   = 8;//总位数
reg [ 9 : 0] div_cnt;       // 分频计数器，范围 0 ~ 867
reg [ 3 : 0] din_cnt;       // 位计数器，范围 0 ~ 8

// Main FSM
localparam WAIT     = 0;
localparam RECEIVE  = 1;
reg current_state, next_state;
always @(posedge clk) begin
    if (rst)
        current_state <= WAIT;
    else
        current_state <= next_state;
end

always @(*) begin
    next_state = current_state;
    case (current_state)
        WAIT : begin
            if(div_cnt >= HalfT + 1) next_state = RECEIVE;
            else next_state = WAIT;
        end
        RECEIVE : begin
            if(din_cnt < 8) next_state = RECEIVE;
            else if(din_cnt >= 8 && div_cnt >= FullT)
                next_state = WAIT;
        end
    endcase
end

// Counter
//分频计数器
always @(posedge clk) begin
    if (rst)
        div_cnt <= 10'D0;
    else if (current_state == WAIT) begin // STATE WAIT
        if(din == 0) begin
            if(div_cnt != HalfT + 1) div_cnt <= div_cnt + 1;
            else div_cnt <= 0;
        end
    end
    else begin  // STATE RECEIVE
        if(div_cnt != FullT) begin
            div_cnt <= div_cnt + 1;
        end else div_cnt <= 0;
    end
end
//位计数器
always @(posedge clk) begin
    if (rst)
        din_cnt <= 0;
    else begin
        if(div_cnt == FullT) begin
            if(din_cnt != TOTAL_BITS) din_cnt <= din_cnt + 1;
            else din_cnt <= 0;
        end
    end
end

// Output signals
reg [ 0 : 0] accept_din;    // 位采样信号
always @(*) begin
    //accept_din = 1'B0;
    accept_din = (div_cnt == FullT && next_state == RECEIVE);
end

always @(*) begin
    din_vld = (din_cnt == TOTAL_BITS && next_state == WAIT);
end

always @(posedge clk) begin
    if (rst)
        din_data <= 8'B0;
    else if (current_state == WAIT)
        din_data <= 8'B0;
    else if (accept_din)
        din_data <= din_data | (din << din_cnt);
end
endmodule

