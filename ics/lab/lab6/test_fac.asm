.ORIG x1000
        ; *** Begin interrupt service routine code here ***
        ;LD    R0, NEWLINE   ;回车
        ;OUT
        ;GETC                ;输入N
        ;OUT                 ;输出

CHECK   ADD   R5, R0, #0    ;检查是否为数字
        ADD   R4, R0, #0
        LD    R3, ASCIIZ
        ADD   R0, R0, R3    ; N-'0'
        BRn   ERROR         ;不是数字
        LD    R3, ASCIIN     
        ADD   R0, R5, R3    ; N-'9'
        BRp   ERROR         ;不是数字
        ;LEA   R0, OUTPUT2
        ;PUTS
        ;LD    R0, NEWLINE
        ;OUT
        LD    R3, ASCIIE
        AND   R5, R5, #0
        ADD   R5, R5, R4
        ADD   R0, R5, R3    ; N-'8'
        BRzp  OVERFL        ;溢出
        AND   R0, R0, #0
        LD    R3, ASCIIZ
        ADD   R0, R4, R3    ;存储数字值
        BRnzp FACT
ERROR   LEA   R0, OUTPUT1
        PUTS
        LD    R0, NEWLINE
        OUT
        RTI
OVERFL  AND   R0, R0, #0
        ADD   R0, R0, R4
        OUT
        LEA   R0, OUTPUT4
        PUTS
        LD    R0, NEWLINE
        OUT
        HALT
        
FACT    AND   R2, R2, #0
        ADD   R2, R0, #0
        ADD   R0, R4, #0
        OUT
        LEA   R0,OUTPUT3
        PUTS
        AND R5, R5, #0
        ADD R5, R5, #1
        AND R4, R4, #0
LOOP1
        ADD R4, R4, #1
        NOT R3, R4
        ADD R3, R3, #1
        ADD R3, R2, R3
        BRn QDEC
        AND R6, R6, #0
        ADD R6, R6, #1
        ADD R0, R5, #0
LOOP2   NOT R7, R6
        ADD R7, R7, #1
        ADD R7, R7, R4
        BRnz LOOP1
        ADD R5, R5, R0
        ADD R6, R6, #1
        BRnzp LOOP2

QDEC    LEA   R4, RESPTR      ;
DLOOP   AND   R3, R3, #0
DIVL    ADD   R3, R3, #1      ; R3 helps store subtraction rest so we can do the next loop
        ADD   R5, R5, #-10    ; substract 10 from R5
        BRzp  DIVL
        ADD   R5, R5, #10     ; get the lowest digit(decimal)
        LD    R2, OUTASC      ; convert to ASCII
        ADD   R5, R2, R5
        STR   R5, R4, #-1     ; store the digit
        ADD   R4, R4, #-1     ; move the pointer
        ADD   R5, R3, #-1     ; continue to loop
        BRp   DLOOP
        ADD   R0, R4, #0      ; set R0 to the (string)fact(N)
        PUTS                  ; print the factorial as a string
        LD    R0, BKSPCE      ; delete the tail of string
        OUT
        HALT

ASCIIZ      .FILL xFFD0
ASCIIN      .FILL xFFC7 
ASCIIE      .FILL xFFC8
OUTASC      .FILL x0030
BKSPCE      .FILL x0008
NEWLINE     .FILL x000A
OUTPUT1     .STRINGZ " is not a decimal digit. " ; 
OUTPUT2     .STRINGZ " is a decimal digit. "     ; 
OUTPUT3     .STRINGZ "!="
OUTPUT4     .STRINGZ " is too large for LC-3."
RESPTR      .FILL x6000
; *** End interrupt service routine code here ***
        .END
      


      


