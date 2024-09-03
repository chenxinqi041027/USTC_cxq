.ORIG x3000
LD R1, xFF        ;v_1存在x3100中
LD R2, xFF        ;d_1存在x3101中
LD R3, xFF        ;N存在x3102中

check_digit
ADD R3, R3, #-1   ;R3<-R3-1
AND R4, R1, #7    ;取模运算
BRz up_date_d     ;如果为0则说明是八的倍数，更新d
ADD R5, R1, #0    ;
continue
ADD R5, R5, #-10  ;
BRp continue      ;
ADD R5, R5, #2    ;
BRz up_date_d     ;跳转到更新d
BRnzp caculate    ;跳转到运算

up_date_d
ADD R2, R2, #0    ;
BRp turn_0        ;
BRz turn_1        ;
turn_0
AND R2, R2, #0    ;
BRnzp caculate    ;
turn_1
ADD R2, R2, #1    ;

caculate
ADD R3, R3, #0    ;判断N是不是0
BRz final_result  ;
ADD R2, R2, #0    ;
BRp add_result    ;大于零则是加2
ADD R1, R1, R1    ;R1<-R1+R1
ADD R1, R1, #-2   ;减2
BRnzp check_digit;

add_result
ADD R1, R1, R1    ;R1<-R1+R1
ADD R1, R1, #2    ;R1<-R1+2
BRnzp check_digit ;

final_result
ST R1, xE6        ;
ST R2, xE6        ;

TRAP x25          ;
.END