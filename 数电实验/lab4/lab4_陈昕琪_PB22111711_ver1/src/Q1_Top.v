module Top(
    input wire [3:0] sw,
    output wire [7:0] led
);
wire [1:0] Y;
wire en;
endode encode_top(
    .I(sw),
    .Y(Y),
    .en(en)
);
assign led = {{en}, {5'b0}, {Y}};
endmodule