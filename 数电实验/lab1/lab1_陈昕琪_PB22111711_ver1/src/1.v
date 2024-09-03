module top_module(
    input  [7:0] in,
    output [7:0] out
);
// Your codes should start from here.
    reg [7:0] temp;

    always @ (*) begin
        temp[7] = in[0];
        temp[6] = in[1];
        temp[5] = in[2];
        temp[4] = in[3];
        temp[3] = in[4];
        temp[2] = in[5];
        temp[1] = in[6];
        temp[0] = in[7];
    end

    assign out = temp;
// End of your codes.
endmodule