`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/12/12 15:01:24
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
    input                   [ 0 : 0]        btn,

    input                   [ 7 : 0]        sw,

    output                  [ 3 : 0]        seg_data,
    output                  [ 2 : 0]        seg_an,

    output                  [ 0 : 0]        uart_dout
);

wire [ 0 : 0]   rst = sw[7];
wire [ 7 : 0]   dout_data;
wire [ 0 : 0]   dout_vld;
reg  [31 : 0]   output_data;
reg sig_r1,sig_r2;
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
assign dout_vld = (sig_r1 && ~sig_r2) ? 1 : 0;
Send send (
    .clk            (clk), 
    .rst            (rst),
    .dout           (uart_dout),
    .dout_vld       (dout_vld),
    .dout_data      (dout_data)
);

Segment segment (
    .clk            (clk),
    .rst            (rst),
    .output_data    (output_data),
    .output_valid   (8'H03),
    .seg_data       (seg_data),
    .seg_an         (seg_an)
);

always @(posedge clk) begin
    if (rst)
        output_data <= 0;
    else
        output_data <= {25'B0, sw[6:0]};
end

assign dout_data = output_data[7:0];
endmodule

