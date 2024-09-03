`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/02 04:42:23
// Design Name: 
// Module Name: Segment
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


module Segment(
    input                       clk,
    input                       rst,
    input       [31:0]          output_data,

    output reg  [3:0]          seg_data,
    output reg  [2:0]          seg_an
);
// 计时器部分
reg [31:0] counter;
parameter TIME_CNT = 25_0000;//计数器的上限为2.5*10^5
always @(posedge clk) begin
    if (rst) begin
        counter <= 0;
    end else begin
        if (counter >= TIME_CNT) begin
            counter <= 0;
        end else begin
            counter <= counter + 1;
        end
    end
end

// 数码管编号部分
reg [2:0] seg_id;
always @(posedge clk) begin
    if (rst) begin
        seg_id <= 0;
    end else begin
        if(counter == 1) begin
            if (seg_id < 3'b111) begin
                seg_id <= seg_id + 1;
            end else seg_id <= 0;
        end else seg_id <= seg_id;
    end
end


// 数码管显示内容部分
always @(*) begin
    seg_data = 0;
    if(rst) seg_an = 3'b000;
    else begin 
        seg_an = seg_id;   // <- 对于所有情况都相同
        case (seg_an)
            0: seg_data = output_data[3:0];
            1: seg_data = output_data[7:4];
            2: seg_data = output_data[11:8];
            3: seg_data = output_data[15:12];
            4: seg_data = output_data[19:16];
            5: seg_data = output_data[23:20];
            6: seg_data = output_data[27:24];
            7: seg_data = output_data[31:28];
            default: ;
            // 可以根据需要继续添加其他编号的情况
        endcase
    end
end
endmodule
