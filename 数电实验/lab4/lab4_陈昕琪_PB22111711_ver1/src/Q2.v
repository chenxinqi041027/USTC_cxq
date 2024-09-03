module adder2bit(
    input           [1:0]         a,
    input           [1:0]         b,
    output   reg    [1:0]         out,
    output   reg                  Cout
);

// Write your code here
always @(*) begin
    Cout = (a[0] & b[1] & b[0]) | (a[1] & b[1]) | (a[1] & a[0] & b[0]);
    out[0] = (~a[0] & b[0]) | (a[0] & ~b[0]);
    out[1] = (~a[1] & ~a[0] & b[1]) |
             (~a[1] & b[1] & ~b[0]) | 
             (a[0] & ~a[1] & b[0] & ~b[1]) | 
             (a[1] & ~a[0] & ~b[1]) |
             (a[1] & ~b[1] & ~b[0]) |
             (a[1] & a[0] & b[1] & b[0]); 
end
// End of your code
endmodule