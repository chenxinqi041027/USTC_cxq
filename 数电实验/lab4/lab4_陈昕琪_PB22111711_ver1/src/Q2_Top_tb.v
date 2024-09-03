module adder_tb();
reg [3:0] sw;
wire [7:0] led;
initial begin
    sw = 4'b0000;
    #10;
    sw = 4'b0001;
    #10;
    sw = 4'b0111;
    #10;
    sw = 4'b1010;
    #10;
    sw = 4'b1111;
    #10;
    sw = 4'b0000;
end
Top adder2bit_Top(
    .sw(sw),
    .led(led)
);
endmodule