module MAX2 (
    input  [7:0]         num1, num2,
    output [7:0]         max
);
// Your codes should start from here.
    assign max = ((num1 >= num2)?num1:num2);
// End of your codes.
endmodule