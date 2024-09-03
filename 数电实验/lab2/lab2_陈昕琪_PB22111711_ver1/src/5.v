module FindMode (
    input                               clk,
    input                               rst,
    input                               next,
    input       [7:0]                   number,
    output reg  [7:0]                   out
); 

reg [7:0] count[255:0]; // 记录每个数字出现的次数
reg [7:0] temp;         // 记录当前出现次数最大的数字
integer i;//用于数组赋初值
integer flag;//用于判断temp是否算出

always @(posedge clk) begin//上升沿
    //flag <= 0;
    if (rst) begin
        temp <= 0;
        for (i = 0; i <= 255; i = i + 1) begin
            count[i] <= 0;
        end
        //flag <= 1;
    end
    else if (next) begin
        count[number] <= count[number] + 1;
        if(count[number]+1 >= count[temp]) begin//比较
            temp <= number;
            //flag <= 1;
        end
        else begin
            temp <= temp;
            //flag <= 1;
        end
    end
end

//输出的是当前出现次数最大的值
//如果有相同的，输出的是新的number

always @(*) begin
    out = temp;
end

endmodule