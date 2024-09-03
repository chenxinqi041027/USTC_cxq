module multiple5_tb();
reg [7:0] sw;
wire [7:0] led;
initial begin
    sw = 8'b0000_0000;//0
    #10;
    sw = 8'b0000_0101;//5
    #10;
    sw = 8'b0000_0110;//6
    #10;
    sw = 8'b0000_1010;//10
    #10;
    sw = 8'b0001_0100;//20
    #10;
    sw = 8'b0101_0000;//80
    #10;
    sw = 8'b0000_0001;//1
    #10;
end
Top multiple5_Top(
    .sw(sw),
    .led(led)
);
endmodule