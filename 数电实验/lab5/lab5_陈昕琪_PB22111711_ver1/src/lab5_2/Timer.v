`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/09 01:24:48
// Design Name: 
// Module Name: Timer
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


module TIMER (
    input                           clk,rst,
    output      wire     [3:0]       seg_data,
    output      wire     [2:0]       seg_an
);

    reg [3:0]outh ;
    reg [7:0] outmin;
    reg [7:0] outs;
    reg [39:0] count;//到10^8表示1s，最多为60×60s,即3600_0000_0000

    reg [32:0] temp; 
    always @(*) begin
        temp = {{12'h0}, {outh}, {outmin}, {outs}};
    end

    initial begin
        outh    = 4'h0;
        outmin   = 8'h0;
        outs   = 8'h0;
        count   = 40'h1;
    end
    
    //计数器部分
    always@ (posedge clk) begin
        if (rst) begin
            count <= 40'd1425_0000_0001;//bit流文件里是1425_0000_0001
        end
        else begin
            if (count > 40'd3600_0000_0000)//conut需要从1到3600_0000计数
                count <= 40'h1;
            else
                count <= count + 40'h1;
        end
    end

    /*使用 Lab3 实验练习中编写的数码管显示模块*/
    Segment segment(
        .clk                (clk),
        .rst                (rst),
        .output_data        (temp),
        .output_valid       (8'HFF),     // 如果你没有实现，可以不需要这个端口
        .seg_data           (seg_data),
        .seg_an             (seg_an)
    );

    always@ (posedge clk) begin
        if(rst) begin//复位为12345
            outh <= 4'h1;
            outmin <= 8'h23;
            outs <= 8'h45;
        end
        else begin
            if(count == 40'd3600_0000_0000) begin//bit流文件里是3600_0000_0000
                if(outh == 4'h9) begin
                    outh <= 4'h0;
                end else outh <= outh + 1;
            end else outh <= outh;
            
            if(count % 40'd60_0000_0000 ==0) begin//bit流文件里是60_0000_0000
                case(outmin)
                    8'h09:   outmin <= 8'h10;
                    8'h19:   outmin <= 8'h20;
                    8'h29:   outmin <= 8'h30;
                    8'h39:   outmin <= 8'h40;
                    8'h49:   outmin <= 8'h50;
                    8'h59:   outmin <= 8'h00;
                    default: outmin <= outmin + 1;
                endcase
                end else outmin <= outmin;

            if(count % 40'd1_0000_0000 == 0) begin//bit流文件里是1_0000_0000
                case(outs)
                    8'h09:   outs <= 8'h10;
                    8'h19:   outs <= 8'h20;
                    8'h29:   outs <= 8'h30;
                    8'h39:   outs <= 8'h40;
                    8'h49:   outs <= 8'h50;
                    8'h59:   outs <= 8'h00;
                    default: outs <= outs + 1;
                endcase
            end else outs <= outs;
        end
    end
endmodule

