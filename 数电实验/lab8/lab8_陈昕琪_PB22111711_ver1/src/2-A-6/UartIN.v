`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/12 17:21:58
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


module UartIN(
    input                   [ 0 : 0]        clk,
    input                   [ 0 : 0]        rst,
    input                   [ 0 : 0]        uart_din,
    output         reg                         uart_answer,
    output         reg                         uart_pause,
    output         reg                         uart_new
);

wire [ 7 : 0]   din_data;
wire [ 0 : 0]   din_vld;

Receive receive (
    .clk        (clk),
    .rst        (rst),
    .din        (uart_din),
    .din_vld    (din_vld),
    .din_data   (din_data)
);
localparam WAIT = 4'b0000;
localparam a1 = 4'b0001;
localparam a2 = 4'b0010;
localparam n1 = 4'b0011;
localparam n2 = 4'b0100;
localparam p1 = 4'b0101;
localparam p2 = 4'b0110;
localparam p3 = 4'b0111;
localparam p4 = 4'b1000;
reg [3:0] current_state,next_state;
always @(posedge clk) begin
    if(rst)begin
        current_state <= WAIT;
    end else begin
        current_state <= next_state;
    end
end
always @(*) begin
    case (current_state)
    WAIT:begin
        if(din_vld && din_data == "a")begin
            next_state = a1;
        end else if(din_vld && din_data == "n")begin
            next_state = n1;
        end else if(din_vld && din_data == "p")begin
            next_state = p1;
        end else begin
            next_state = WAIT;
        end
    end 
    a1:begin
        if(din_vld && din_data == ";")begin
            next_state = a2;
        end else if(din_vld && din_data != ";")begin
            if(uart_pause)begin
                next_state = p2;
            end else begin
                next_state = WAIT; 
            end
        end else begin
            next_state = a1;
        end
    end
    a2:begin
        if(uart_pause) begin
            next_state = p2;
        end else begin
            next_state = WAIT; 
        end
    end
    n1:begin
        if(din_vld && din_data == ";")begin
            next_state = n2;
        end else if(din_vld && din_data != ";")begin
            next_state = WAIT;
        end else begin
            next_state = n1;
        end
    end
    n2:begin
        next_state = WAIT;
    end
    p1:begin
        if(din_vld && din_data == ";")begin
            next_state = p2;
        end else if(din_vld && din_data != ";")begin
            next_state = WAIT;
        end else begin
            next_state = p1;
        end
    end
    p2:begin
        if(din_vld && din_data == "p") begin
            next_state = p3;
        end else if(din_vld && din_data == "a")begin
            next_state = a1;
        end else begin
            next_state = p2;
        end
    end
    p3:begin
        if(din_vld && din_data == ";")begin
            next_state = p4;
        end else if(din_vld && din_data != ";")begin
            next_state = p3;
        end else begin
            next_state = p3;
        end
    end
    p4:begin
        next_state = WAIT;
    end
    default: next_state = WAIT;
    endcase
end
always @(posedge clk) begin
    case (current_state)
    WAIT:begin
        uart_answer <= 0;
        uart_pause <= 0;
        uart_new <= 0;
    end
    a1:begin
        uart_answer <= 0;
        uart_new <= 0;
        if(uart_pause)begin
            uart_pause <= 1;
        end else uart_pause <= 0;
    end
    a2:begin
        uart_answer <= 1;
        if(uart_pause)begin
            uart_pause <= 1;
        end else uart_pause <= 0;
        uart_new <= 0;
    end
    n1:begin
        uart_answer <= 0;
        uart_pause <= 0;
        uart_new <= 0;
    end
    n2:begin
        uart_answer <= 0;
        uart_pause <= 0;
        uart_new <= 1;
    end
    p1:begin
        uart_answer <= 0;
        uart_pause <= 0;
        uart_new <= 0;
    end
    p2:begin
        uart_answer <= 0;
        uart_pause <= 1;
        uart_new <= 0;
    end
    p3:begin
        uart_answer <= 0;
        uart_pause <= 1;
        uart_new <= 0;
    end
    p4:begin
        uart_answer <= 0;
        uart_pause <= 0;
        uart_new <= 0;
    end
    endcase
end
endmodule

