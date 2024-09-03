`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/12 14:35:26
// Design Name: 
// Module Name: Send
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


module Send(
    input                   [ 0 : 0]        clk, 
    input                   [ 0 : 0]        rst,

    output      reg         [ 0 : 0]        dout,

    input                   [ 0 : 0]        dout_vld,
    input                   [ 7 : 0]        dout_data
);

// Counter and parameters
localparam FullT        = 867;
localparam TOTAL_BITS   = 9;
reg [ 9 : 0] div_cnt;           
reg [ 4 : 0] dout_cnt;          
// Main FSM
localparam WAIT     = 0;
localparam SEND     = 1;
reg current_state, next_state;
always @(posedge clk) begin
    if (rst)
        current_state <= WAIT;
    else
        current_state <= next_state;
end
//Main FSM
always @(*) begin
    next_state = current_state;
    case (current_state)
        WAIT: begin
            if(dout_vld == 1) next_state = SEND;
            else next_state = WAIT;
        end 
        SEND:begin
            if(dout_cnt == TOTAL_BITS && div_cnt == FullT) next_state = WAIT;
            else next_state = SEND;
        end 
    endcase
end

// Counter,0~867
always @(posedge clk) begin
    if (rst)
        div_cnt <= 10'H0;
    else if (current_state == SEND) begin
        if(div_cnt != FullT) div_cnt <= div_cnt + 1'b1;
        else div_cnt <= 10'H0;
    end
    else
        div_cnt <= 10'H0;
end
always @(posedge clk) begin
    if (rst)
        dout_cnt <= 4'H0;
    else if (current_state == SEND) begin
        if(dout_cnt != TOTAL_BITS && div_cnt == FullT) dout_cnt <= dout_cnt + 1'b1;
        else if(dout_cnt == TOTAL_BITS && div_cnt == FullT) dout_cnt <= 4'H0;
    end
    else
        dout_cnt <= 4'H0;
end

reg [7 : 0] temp_data;
always @(posedge clk) begin
    if (rst)
        temp_data <= 8'H0;
    else if (current_state == WAIT && dout_vld)
        temp_data <= dout_data;
end

always @(posedge clk) begin
    if (rst)
        dout <= 1'B1;
    else begin
        if(next_state == WAIT) dout <= 1'B1;
        else 
        if(next_state == SEND)begin
           if(dout_cnt == 0) begin
            if(div_cnt == FullT) dout <= temp_data[dout_cnt];
            else dout <= 1'B0;
            end
            else begin
            if (div_cnt == FullT) begin
                if(dout_cnt != TOTAL_BITS-1) begin
                    dout <= temp_data[dout_cnt];
                end else dout <= 1'B1;
            end  else dout <= temp_data[dout_cnt-1];
            end
            if(dout_cnt == TOTAL_BITS) dout <= 1'B1;
        end
        end
end
endmodule

