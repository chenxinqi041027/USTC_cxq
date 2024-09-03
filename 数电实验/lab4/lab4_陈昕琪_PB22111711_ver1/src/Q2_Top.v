module Top(
    input wire [3:0] sw,
    output wire [7:0] led
);
wire [1:0] a;
wire [1:0] b;
wire [1:0] out;
wire [1:0] Count;
assign a = sw[3:2];
assign b = sw[1:0];
adder2bit adder(
    .a(a),
    .b(b),
    .out(out),
    .Cout(Cout)
);
assign led = {{5'b0}, {Cout}, {out}};
endmodule