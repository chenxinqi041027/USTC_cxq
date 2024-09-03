`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/02 15:36:34
// Design Name: 
// Module Name: Top_tb
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


module Top_tb();
reg clk,btn;
reg [7:0] sw;
wire [2:0] seg_an;
wire [2:0] seg_data;

initial begin
    clk = 0;
    btn = 1;
    sw = 8'b0000_0000;
    #10 btn = 0;
    #250_000_000;//250ms,1/4s
    sw = 8'b100_0000;
    #250_000_000;
    sw = 8'b1000_0000;
    #250_000_000;
    sw = 8'b0010_0000;
    #250_000_000;
    sw = 8'b1000_0011;
end
always #5 clk = ~clk;//T=10ns



Top top(
    .clk(clk),
    .btn(btn),
    .sw(sw),
    .seg_an(seg_an),
    .seg_data(seg_data)
);

endmodule
/*module Top(
    input                   clk,
    input                   btn,
    input  [7:0]            sw,
    output [2:0]            seg_an,
    output [3:0]            seg_data
);
    Segment segment(
        .clk(clk),
        .rst(btn),
        .output_data(32'h22111711),// <- 改为你学号中的 8 位数字
        .output_valid(sw),   
        .seg_data(seg_data),
        .seg_an(seg_an)
    );
endmodule*/
