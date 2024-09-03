`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/02 05:15:49
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
    input       [ 7:0]          output_valid,

    output reg  [ 3:0]          seg_data,
    output reg  [ 2:0]          seg_an
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
            1: if(output_valid[1] == 1) begin
                seg_data = output_data[7:4];
            end else begin 
                seg_an = 0;
                seg_data = output_data[3:0];
            end
            2:if(output_valid[2] == 1) begin 
                seg_data = output_data[11:8];
            end else begin 
                seg_an = 0;
                seg_data = output_data[3:0];
            end
            3: if(output_valid[3] == 1) begin
                seg_data = output_data[15:12];
            end else begin 
                seg_an = 0;
                seg_data = output_data[3:0];
            end
            4: if(output_valid[4] == 1) begin
                seg_data = output_data[19:16];
            end else begin 
                seg_an = 0;
                seg_data = output_data[3:0];
            end
            5: if(output_valid[5] == 1) begin
                seg_data = output_data[23:20];
            end else begin 
                seg_an = 0;
                seg_data = output_data[3:0];
            end
            6: if(output_valid[6] == 1) begin
                seg_data = output_data[27:24];
            end else begin 
                seg_an = 0;
                seg_data = output_data[3:0];
            end
            7: if(output_valid[7] == 1) begin
                seg_data = output_data[31:28];
            end else begin 
                seg_an = 0;
                seg_data = output_data[3:0];
            end
            default: ;
            // 可以根据需要继续添加其他编号的情况
        endcase
    end
end
endmodule