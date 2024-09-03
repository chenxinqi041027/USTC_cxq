module test( 
    input  [7:0]        a, b, 
    output [7:0]        c, d, e, f, g, h, i, j, k, l
); 
assign c = a & b; //按位与 c = 8'b0011_0000
assign d = a || b; //逻辑或 d = 8'bxxxx_xxx1
assign e = a ^ b; //按位异或 e = 8'b1100_0011
assign f = ~a; //按位非 f = 8'b1100_1100
assign g = {a[2:0], b[3:0], {1'b1}};//拼接运算符 g = 8'0110_0001
assign h = b >>> 3;//算数右移 h = 8'b1111_1110
assign i = &b; //归约与 i = 8'bxxxx_xxx0
assign j = (a > b) ? a : b;//判断最大值 j = 8'b1111_0000
assign k = a - b; //减 k = 8'b0100_0011
assign l = !a;//逻辑非 l = 8'bxxxx_xxx0
endmodule