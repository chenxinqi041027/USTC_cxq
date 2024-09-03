module Top(
    input wire [7:0] sw,
    output reg [7:0] led
);
wire temp;
multiple5 mul(
    .num(sw),
    .ismultiple5(temp)
);
always @(*) begin
    if(temp == 1) begin
        led = 8'b1111_1111;
    end else begin
        led = 8'b0000_0000; 
    end
end
endmodule