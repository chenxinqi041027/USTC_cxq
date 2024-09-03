.ORIG x3000;
AND R0, R0, #0;
AND R1, R1, #0;
AND R2, R2, #0;
AND R3, R3, #0;
AND R4, R4, #0;

LD R0, S1_ADDR;将字符串S1的地址存储在R0中
LD R1, S2_ADDR; 将字符串S2的地址存储在R1中

LOOP 
LDR R3, R0, #0;
BRz Judge;判断R3的值是不是0，如果是0，则判断R4的值是不是0
LDR R4, R1, #0;当R3的值不是0时，可以继续运算，不需要考虑R4的值是否为0
Continue NOT R4, R4;
ADD R4, R4, #1;
ADD R2, R3, R4;R2=R3-R4
BRz NEXT;如果是0，则进行下一步
BRnp DONE;

Judge
LDR R4, R1, #0;
BRnp Continue;如果R4的值不是0则继续判断
AND R2, R2, #0;
BRnzp DONE;如果R3R4的值都为0则说明两个字符串相同

NEXT
ADD R0, R0, #1;
ADD R1, R1, #1;
BRnzp LOOP;

DONE STI R2, RESULT; 结束循环，保存结果
HALT

S1_ADDR .FILL x3100
S2_ADDR .FILL x3200
RESULT .FILL x3300

.END

.ORIG x3100
S1 .STRINGZ "FirstString"
.END

.ORIG x3200
S2 .STRINGZ "SecondString"
.END
