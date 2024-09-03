module Count4Ones(
    input       [2:0]         in,
    output reg  [1:0]         out
);
// Your codes should start from here.
    reg [1:0] temp1,temp2,temp3;

    always @(*) begin
        temp1 = (in[0])?1'b1:1'b0;
        temp2 = (in[1])?1'b1:1'b0;
        temp3 = (in[2])?1'b1:1'b0;
    end
    assign out = temp1+temp2+temp3;
// End of your codes.
endmodule