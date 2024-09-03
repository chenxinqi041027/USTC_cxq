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
    input                   [ 0 : 0]            uart_din,
    output                  [ 0 : 0]            uart_dout,
    output                  [ 7 : 0]            led,
    output                  [ 2 : 0]            seg_an,
    output                  [ 3 : 0]            seg_data
);

wire rst = sw[7];
wire [0:0] uart_answer,uart_pause,uart_new;
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
//reg [11:0] target_number = 12'H123;
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
wire generate_random,random_en;
wire [11:0] target_number;
Random random(
    .clk(clk),
    .rst(rst),
    .generate_random(generate_random),
    .random_en(random_en),
    .random_data(target_number)
);
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
wire timer_en,timer_set;
//Timer
reg set,en;
wire [7:0] minute;
wire [7:0] second;
wire [11:0] micro_second;
wire finish,finish1,finish2,finish3;
Timer timer(
    .clk(clk),
    .rst(rst),
    .set(set),
    .en(en),
    .minute(minute),
    .second(second),
    .micro_second(micro_second),
    .finish(finish),
    .finish1(finish1),
    .finish2(finish2),
    .finish3(finish3)
);
//Hex2BCD
wire [7:0] out_minute,out_second;
wire [11:0] out_micro_second;
wire o_DV_minute,o_DV_second,o_DV_micro_second;
Hex2BCD #(
    .INPUT_WIDTH(8),
    .DECIMAL_DIGITS(2)
)hex2bcd_minute (
    .clk(clk),
    .i_Binary(minute),
    .i_Start(timer_en || timer_set),
    .o_BCD(out_minute),
    .o_DV(o_DV_minute)
);
Hex2BCD #(
    .INPUT_WIDTH(8),
    .DECIMAL_DIGITS(2)
)hex2bcd_second (
    .clk(clk),
    .i_Binary(second),
    .i_Start(timer_en || timer_set),
    .o_BCD(out_second),
    .o_DV(o_DV_second)
);
Hex2BCD #(
    .INPUT_WIDTH(12),
    .DECIMAL_DIGITS(3)
)hex2bcd_miro_second (
    .clk(clk),
    .i_Binary(micro_second),
    .i_Start(timer_en || timer_set),
    .o_BCD(out_micro_second),
    .o_DV(o_DV_micro_second)
);
reg [7:0] seg_minute,seg_second;
reg [11:0] seg_micro_second;
always @(posedge clk) begin
    if(set)begin
        seg_minute <= 8'b0000_0001;
        seg_second <= 8'b0000_0000;
        seg_micro_second <= 12'b0000_0000_0000;
    end else begin
        if(o_DV_minute) begin
            seg_minute <= out_minute;
        end
        if(o_DV_second) begin
            seg_second <= out_second;
        end
        if(o_DV_micro_second) begin
            seg_micro_second <= out_micro_second;
        end
    end
end
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
    .src0({{4'b0},{seg_minute},{seg_second},{seg_micro_second}}),
    .src1({{4'b0},{seg_minute},{seg_second},{seg_micro_second}}),
    .src2(32'H8888_8888),
    .src3(32'H4444_4444),
    .sel(seg_sel),
    .res(output_data)
);
reg [7:0] output_valid;
wire [1:0] output_sel; 
reg [31:0] counter;
reg [31:0] MAXNUM;
reg en1;
always @(posedge clk) begin
    if(en1)begin
        if(counter < MAXNUM)begin
            counter <= counter + 1;
        end else begin
            counter <= 0;
        end
    end
    if(!en1)begin
        counter <= 0;
    end
    case(output_sel)
    2'b00:begin
        output_valid <= 8'b11111111;
        en1 <= 0;
    end
    2'b01:begin
        en1 <= 1;
        MAXNUM <= 5000_0000;
        if(counter == MAXNUM) output_valid <= ~output_valid;
    end
    2'b10:begin
        en1 <= 1;
        MAXNUM <= 2500_0000;
        if(counter == MAXNUM) output_valid <= ~output_valid;
    end
    default:en1 <= 0;
    endcase
end
Segment segment(
    .clk(clk),
    .rst(rst),
    .output_data(output_data),
    .output_valid(output_valid),
    .seg_data(seg_data),
    .seg_an(seg_an)
);
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
    .finish1(finish1),
    .finish2(finish2),
    .finish3(finish3),
    .led_sel(led_sel),
    .uart_pause(uart_pause),
    .uart_new(uart_new),
    .seg_sel(seg_sel),
    .output_sel(output_sel),
    .generate_random(generate_random),
    .random_en(random_en)
);
always @(*) begin
    en = timer_en;
    set = timer_set;
    start_check = check_start;
end
//串口
UartIN uartin(
    .clk(clk),
    .rst(rst),
    .uart_din(uart_din),
    .uart_answer(uart_answer),
    .uart_pause(uart_pause),
    .uart_new(uart_new)
);

UartOUT uartout(
    .clk(clk),
    .rst(rst),
    .target_number(target_number),
    .print_en(uart_answer),
    .uart_dout(uart_dout)
);

endmodule
