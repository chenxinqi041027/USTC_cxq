module MAX2 (
    input      [7:0]            num1, num2,
    output reg [7:0]            max
);
always @(*) begin
    if (num1 > num2)
        max = num1;
    else
        max = num2;
end
endmodule


module MAX3 (
    input   [7:0]         num1, num2, num3,
    output  [7:0]         max
);
    reg [7:0] temp;
// Your codes should start from here.
    MAX2 max2_1 (.num1(num1), .num2(num2), .max(temp));
    MAX2 max2_2 (.num1(num3), .num2(temp), .max(max));
// End of your codes.
endmodule