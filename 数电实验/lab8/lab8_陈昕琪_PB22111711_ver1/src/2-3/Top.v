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


module Top(
    input                   [ 0 : 0]        clk,
    input                   [ 0 : 0]        rst,
    input                   [ 0 : 0]        uart_din
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
localparam WAIT = 3'b000;
localparam a1 = 3'b001;
localparam a2 = 3'b010;
localparam n1 = 3'b011;
localparam n2 = 3'b100;
localparam p1 = 3'b101;
localparam p2 = 3'b110;
reg [2:0] current_state,next_state;
always @(posedge clk) begin
    if(rst)begin
        current_state <= next_state;
    end else begin
        current_state <= next_state;
    end
end
always @(*) begin
    case (current_state)
    WAIT:begin
        if(din_vld && din_data == 8'b0110_0001)begin
            next_state = a1;
        end else if(din_vld && din_data == 8'b0110_1110)begin
            next_state = n1;
        end else if(din_vld && din_data == 8'b0111_0000)begin
            next_state = p1;
        end else begin
            next_state = WAIT;
        end
    end 
    a1:begin
        if(din_vld && din_data == 8'b0011_1011)begin
            next_state = a2;
        end else if(din_vld && din_data != 8'b0011_1011)begin
            next_state = WAIT;
        end else begin
            next_state = a1;
        end
    end
    a2:begin
        next_state = WAIT;
    end
    n1:begin
        if(din_vld && din_data == 8'b0011_1011)begin
            next_state = n2;
        end else if(din_vld && din_data != 8'b0011_1011)begin
            next_state = WAIT;
        end else begin
            next_state = n1;
        end
    end
    n2:begin
        next_state = WAIT;
    end
    p1:begin
        if(din_vld && din_data == 8'b0011_1011)begin
            next_state = p2;
        end else if(din_vld && din_data != 8'b0011_1011)begin
            next_state = WAIT;
        end else begin
            next_state = p1;
        end
    end
    p2:begin
        next_state = WAIT;
    end
    endcase
end

endmodule

