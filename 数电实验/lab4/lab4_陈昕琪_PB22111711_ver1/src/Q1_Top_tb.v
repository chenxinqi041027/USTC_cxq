module encode_tb();
    reg [3:0] sw;
    wire [7:0] led;
    initial begin
        sw = 4'b0000;
        #10;
        sw = 4'b1000;
        #10;
        sw = 4'b0100;
        #10;
        sw = 4'b0010;
        #10;
        sw = 4'b0001;
        #10;
        sw = 4'b0000;
    end
Top top(
    .sw(sw),
    .led(led)
);
endmodule