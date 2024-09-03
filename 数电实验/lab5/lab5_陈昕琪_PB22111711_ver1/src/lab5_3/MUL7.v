`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/09 14:44:23
// Design Name: 
// Module Name: MUL7
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


module MUL7(
    input                               clk,            // 时钟信号
    input                               rst,            // 复位信号，使状态机回到初始态
    input               [31 : 0]        src,            // 输入数据
    input                               src_valid,      // 表明输入结果是否有效
    output      reg                     ready,          // 表明是否正在检测
    output      reg                     res,            // 输出结果
    output      reg                     res_valid       // 表明输出结果是否有效
);

// Write your code here
    // 状态机定义  
    localparam IDLE = 3'b000;
    localparam S1 = 3'b001;  
    localparam S2 = 3'b010;
    localparam S3 = 3'b011;
    localparam S4 = 3'b100;
    localparam S5 = 3'b101;
    localparam S6 = 3'b110;
    localparam S7 = 3'b111;
    reg [5:0] i;
    reg [2:0] current_state,next_state; 
    reg [31:0] temp; 

initial begin
    i = 32;
end

    always @(posedge clk) begin  
        if (rst) begin//表示复位
            current_state <= IDLE;  
            ready <= 1'b1;//未在检测
            res <= 32'h0;
            res_valid <= 1'b0;//输出无效
            i <= 32;
        end
        else if (src_valid && i > 0) begin//开始输入
            current_state <= next_state;
            i = i - 1;
            ready <= 1'b0;
        end else if(i == 0) begin//表示未在检测
            ready <= 1'b1;
            res_valid  <= 1'b0;
            res <= 1'b0;
        end
    end

    always@(*) begin
        if(i == 31 && ready == 0) begin
            temp <= src;//正在检测且输入数据
        end
    end

    always@(*) begin
        next_state = current_state;
        if(i <= 31) begin
            case (current_state)
            IDLE: begin  
                if (src_valid) begin  
                    if(temp[i] == 1)begin
                        next_state = S1;
                    end else next_state = S7;
                    ready <= 1'b0;
                end else begin  
                        ready <= 1'b1;
                        res_valid  <= 1'b1;
                    end  
                end  
            S1: begin  
                if (src_valid) begin 
                    if(temp[i] == 1)begin
                        next_state = S3;
                    end else next_state = S2; 
                    ready <= 1'b0;
                end else begin  
                        ready <= 1'b1;
                        res_valid  <= 1'b1;
                    end  
                end  
            S2: begin  
                if (src_valid) begin 
                    if(temp[i] == 1)begin
                        next_state = S5;
                    end else next_state = S4;
                    ready <= 1'b0;
                end else begin  
                        ready <= 1'b1;
                        res_valid  <= 1'b1;
                    end  
                end
            S3: begin  
                if (src_valid) begin
                    if(temp[i] == 1)begin
                        next_state = S7;
                    end else next_state = S6;  
                    ready <= 1'b0;
                end else begin  
                        ready <= 1'b1;
                        res_valid  <= 1'b1;
                    end  
                end
            S4: begin  
                if (src_valid) begin
                    if(temp[i] == 1)begin
                        next_state = S2;
                    end else next_state = S1; 
                    ready <= 1'b0;
                end else begin  
                        ready <= 1'b1;
                        res_valid  <= 1'b1;
                    end  
                end
            S5: begin  
                    if (src_valid) begin
                        if(temp[i] == 1)begin
                            next_state = S4;
                        end else next_state = S3; 
                        ready <= 1'b0;
                    end else begin  
                            ready <= 1'b1;
                            res_valid  <= 1'b1;
                        end  
                    end
            S6: begin  
                if (src_valid) begin
                    if(temp[i] == 1)begin
                        next_state = S6;
                    end else next_state = S5;   
                    ready <= 1'b0;
                end else begin  
                        ready <= 1'b1;
                        res_valid  <= 1'b1;
                    end  
                end
            S7: begin  
                    if (src_valid) begin
                        if(temp[i] == 1)begin
                            next_state = S1;
                        end else next_state = S7;  
                        ready <= 1'b0;
                    end else begin  
                            ready <= 1'b1;
                            res_valid  <= 1'b1;
                        end  
                    end
            endcase
        end
        if(i == 0) begin
            res = (next_state == S7);
            ready = 0;
            res_valid = 1;
        end
    end 
// End of your code
endmodule