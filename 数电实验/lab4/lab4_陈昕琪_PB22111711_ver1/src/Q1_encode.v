module encode(
    input [3:0]         I,
    output reg [1:0]    Y,
    output reg          en
);
// Write your codes here 
always @(*) begin
    case (I)
        4'b1000: begin
            Y = 2'b11; en = 1;
        end
        4'b0100: begin
            Y = 2'b10; en = 1;
        end
        4'b0010: begin
            Y = 2'b01; en = 1;
        end
        4'b0001: begin
            Y = 2'b00; en = 1;
        end
        default: begin
            Y = 2'b00; 
            if(I !== 4'b0000) begin
                en = 1;
            end
            else begin
                en = 0;
            end
        end
    endcase
end
// End of your codes
endmodule
