`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/19 17:19:41
// Design Name: 
// Module Name: UartOUT
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


module UartOUT(
    input                   [ 0 : 0]        clk,
    input                   [ 0 : 0]        rst,
    input                   [11 : 0]        target_number,
    input                   [ 0 : 0]        print_en,

    output                  [ 0 : 0]        uart_dout
);
// FSM
    localparam UOUT_WAIT        = 0;
    localparam UOUT_PRINT       = 1;
    localparam UOUT_tn = 2;
    reg [3 : 0] current_state, next_state;
    always @(posedge clk) begin
        if (rst)
            current_state <= UOUT_WAIT;
        else
            current_state <= next_state;
    end
    reg [7:0] code_r1,code_r2,code_r3,code_r4,code_r5,code_r6
    ,code_r7,code_r8,code_r9,code_r10,code_r11,code_r12,code_r13,code_r14
    ,code_r15,code_r16,code_r17,code_r18,code_r19,code_r20;
    always @(*) begin
        next_state = current_state;
        case (current_state) 
            UOUT_WAIT: begin 
                if (print_en)
                    next_state = UOUT_tn;
            end
    
            UOUT_tn: next_state = UOUT_PRINT;
    
            UOUT_PRINT: if (code_r1 == 0)
                next_state = UOUT_WAIT;      
        endcase
    end
    
    // Counter
    // 115200 bits/sec
    reg [19 : 0] div_cnt;
    always @(posedge clk) begin
        if (rst) 
            div_cnt <= 0;
        else if (current_state == UOUT_PRINT) begin
            if (div_cnt < 20'D12000)
                div_cnt <= div_cnt + 1;  
            else
                div_cnt <= 0;
        end             
        else
            div_cnt <= 0;
    end
    
    wire clk_100_pos = (div_cnt == 20'd11000);
    
    // Output
    localparam _N = 8'd10;      // "\n"
    localparam _R = 8'd13;      // "\r"
    always @(posedge clk) begin
        if (rst) begin
            code_r1 <= 0;
            code_r2 <= 0;
            code_r3 <= 0;
            code_r4 <= 0;
            code_r5 <= 0;
            code_r6 <= 0;
            code_r7 <= 0;
            code_r8 <= 0;
            code_r9 <= 0;
            code_r10 <= 0;
            code_r11 <= 0;
            code_r12 <= 0;
            code_r13 <= 0;
            code_r14 <= 0;
            code_r15 <= 0;
            code_r16 <= 0;
            code_r17 <= 0;
            code_r18 <= 0;
            code_r19 <= 0;
            code_r20 <= 0;
        end
        else case(current_state) 
            UOUT_tn: begin
                code_r1 <= "t";
                code_r2 <= "a";
                code_r3 <= "r";
                code_r4 <= "g";
                code_r5 <= "e";
                code_r6 <= "t";
                code_r7 <= "_";
                code_r8 <= "n";
                code_r9 <= "u";
                code_r10 <= "m";
                code_r11 <= "b";
                code_r12 <= "e";
                code_r13 <= "r";
                code_r14 <= ":";
                code_r15 <= target_number[11:8] + 48;
                code_r16 <= target_number[7:4] + 48;
                code_r17 <= target_number[3:0] + 48;
                code_r18 <= _N;
                code_r19 <= _R;
            end
    
            UOUT_PRINT: if (clk_100_pos) begin
                code_r1 <= code_r2; 
                code_r2 <= code_r3;
                code_r3 <= code_r4;
                code_r4 <= code_r5;
                code_r5 <= code_r6;
                code_r6 <= code_r7;
                code_r7 <= code_r8;
                code_r8 <= code_r9;
                code_r9 <= code_r10;
                code_r10 <= code_r11;
                code_r11 <= code_r12;
                code_r12 <= code_r13;
                code_r13 <= code_r14;
                code_r14 <= code_r15;
                code_r15 <= code_r16;
                code_r16 <= code_r17;
                code_r17 <= code_r18;
                code_r18 <= code_r19;
                code_r19 <= code_r20;
                code_r20 <= 0;     
            end
        endcase
    end
    reg dout_vld;
    // Uart dout
    wire [7:0] dout_data;
    assign dout_data = code_r1;
    always @(*)
        dout_vld = (div_cnt == 20'd100) && (current_state == UOUT_PRINT);
Send send(
    .clk(clk),
    .rst(rst),
    .dout(uart_dout),
    .dout_vld(dout_vld),
    .dout_data(dout_data)
);
endmodule
