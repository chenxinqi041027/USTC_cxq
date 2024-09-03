module multiple5(
    input           [7:0]          num,
    output   reg                   ismultiple5
);
// Write your code here
// Use the 2-bits adder, or you will not get the score!
wire [2:0] sum1;
wire [2:0] sum2;
reg [3:0] sum;
adder2bit add1(
    .a(num[7:6]),
    .b(num[3:2]),
    .sum(sum1)
);
adder2bit add2(
    .a(num[5:4]),
    .b(num[1:0]),
    .sum(sum2)
);

always @(*) begin
    sum=((sum1 >= sum2)?(sum1-sum2):(sum2-sum1));
    if(sum == 4'b0000 | sum == 4'b0101) begin
        ismultiple5 = 1;
    end else begin
        ismultiple5 = 0;
    end
end
// End of your code
endmodule