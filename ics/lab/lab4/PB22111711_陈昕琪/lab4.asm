    .ORIG x3000;初始化
    AND R0, R0, #0;用来存储n的值
    AND R1, R1, #0;用来输出操作
    AND R2, R2, #0;用来存放地址值
    AND R3, R3, #0;用来计数
    AND R4, R4, #0;用来操作
    AND R6, R6, #0;n用于移位时计数
    AND R7, R7, #0;
        
    LDI R0, N_value;将n的值存入R0
    LD R2, N_value;存放地址值
    LD R6, Begin;存放指针
    LD R7, EXIT;存放地址

REMOVE  
    STR R7, R6, #0;
    ADD R6, R6, #1;
    ADD R0, R0, #0;
    BRz Base_r0;判断为是0
    ADD R0, R0, #-1;
    BRz Base_r1;判断为是1
        
    ADD R0, R0, #-1;n-2
    JSR REMOVE
        
    ADD R0, R0, #2;n
    AND R4, R4, #0;
    ADD R4, R4, #1;
    ADD R3, R0, #-1;
LOOP    
    BRz Remove_ist_ring
    ADD R4, R4, R4;
    ADD R3, R3, #-1;
    BRnzp LOOP
    
Remove_ist_ring
    ADD R1, R1, R4
    ADD R2, R2, #1
    STR R1, R2, #0
    
    ADD R0, R0, #-2;n-2
    JSR PUT
        
    ADD R0, R0, #1;n-1
    JSR REMOVE
        
    ADD R0, R0, #1;
        
RETURN_r 
    ADD R6, R6, #-1;弹栈
    LDR R7, R6, #0;
    RET


Base_r1
    ADD R0, R0, #1;
    ADD R1, R1, #1;
    ADD R2, R2, #1;
    STR R1, R2, #0;
Base_r0 
    BRnzp RETURN_r
        
        
PUT     
    STR R7, R6, #0;
    ADD R6, R6, #1;
    ADD R0, R0, #0;
    BRz Base_p0;判断为是0或1
    ADD R0, R0, #-1;
    BRz Base_p1;
    JSR PUT
    ADD R0, R0, #-1;n-2
    JSR REMOVE
        
    ADD R0, R0, #2;n
    AND R4, R4, #0;
    ADD R4, R4, #1;
    ADD R3, R0, #-1;
LOOP_p  
    BRz Put_ist_ring
    ADD R4, R4, R4;
    ADD R3, R3, #-1;
    BRnzp LOOP_p
    
Put_ist_ring
    NOT R4, R4
    ADD R4, R4, #1
    ADD R1, R1, R4
    ADD R2, R2, #1
    STR R1, R2, #0
        
    ADD R0, R0, #-2
    JSR PUT
    ADD R0, R0, #2;
RETURN_p       
    ADD R6, R6, #-1;弹栈
    LDR R7, R6, #0;
    RET


Base_p1 
    ADD R0, R0, #1;
    ADD R1, R1, #-1;判断为是1
    ADD R2, R2, #1;
    STR R1, R2, #0;
Base_p0 
    BRnzp RETURN_p



EXIT        HALT
N_value .FILL x3100;
Begin .FILL x4100;
.END