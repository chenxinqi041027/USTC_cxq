`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/14 19:22:46
// Design Name: 
// Module Name: Top
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


module Top (
    input                   [ 0 : 0]            clk,
    input                   [ 0 : 0]            btn,
    input                   [ 7 : 0]            sw,

    output                  [ 7 : 0]            led,
    output                  [ 2 : 0]            seg_an,
    output                  [ 3 : 0]            seg_data
);

wire rst = sw[7];
//btn边缘检测
reg sig_r1, sig_r2;
wire pos_btn;
always @(posedge clk) begin
    if (rst) begin
        sig_r1 <= 0;
        sig_r2 <= 0;
    end
    else begin
        sig_r1 <= btn;
        sig_r2 <= sig_r1;
    end
end
assign pos_btn = (sig_r1 && ~sig_r2) ? 1 : 0;
reg [11:0] target_number = 12'H123;
reg [11:0] input_number;
wire [3:0]hex;
wire pulse;
wire [31:0] dout;
//SW_Input
SW_Input in(
    .clk(clk),
    .rst(rst),
    .sw(sw),
    .hex(hex),
    .pulse(pulse)
);
ShiftReg shiftreg(
    .clk(clk),
    .rst(rst),
    .hex(hex),
    .pulse(pulse),
    .dout(dout)
);
always @(*) begin
    input_number = dout[11:0];
end

//Check
reg start_check;
wire [5:0] check_result;
Check check(
    .clk(clk),
    .rst(rst),
    .input_number(input_number),
    .target_number(target_number),
    .start_check(start_check),
    .check_result(check_result)
);
reg [5:0] result;
always @(posedge clk) begin
    if(check_result)begin
        result <= check_result; 
    end
end
//Timer
reg set,en;
wire [7:0] minute;
wire [7:0] second;
wire [11:0] micro_second;
wire finish;
Timer timer(
    .clk(clk),
    .rst(rst),
    .set(set),
    .en(en),
    .minute(minute),
    .second(second),
    .micro_second(micro_second),
    .finish(finish)
);

//MUX
wire [7:0] ledflow;
wire [1:0] led_sel; 
MUX4 #(
    .WIDTH(8)
) mux_led(
    .src0(ledflow),//流水灯
    .src1({{2'b00},{result}}),//显示结果
    .src2(8'b1111_1111),//正确
    .src3(8'b0000_0000),//错误
    .sel(led_sel),
    .res(led)
);
LED_Flow led_flow(
    .clk(clk),
    .rst(rst),
    .led(ledflow)
);
wire [1:0] seg_sel;
wire [31:0] output_data;
MUX4 #(
    .WIDTH(32)
) mux_seg(
    .src0({{4'b0},{minute},{second},{micro_second}}),
    .src1({{4'b0},{minute},{second},{micro_second}}),
    .src2(32'H8888_8888),
    .src3(32'H4444_4444),
    .sel(seg_sel),
    .res(output_data)
);

Segment segment(
    .clk(clk),
    .rst(rst),
    .output_data(output_data),
    .output_valid(8'Hff),
    .seg_data(seg_data),
    .seg_an(seg_an)
);
wire timer_en,timer_set;
wire check_start;
Control control(
    .clk(clk),
    .rst(rst),
    .btn(pos_btn),
    .check_result(check_result),
    .check_start(check_start),
    .timer_en(timer_en),
    .timer_set(timer_set),
    .timer_finish(finish),
    .led_sel(led_sel),
    .seg_sel(seg_sel)
);
always @(*) begin
    en = timer_en;
    set = timer_set;
    start_check = check_start;
end
endmodule
