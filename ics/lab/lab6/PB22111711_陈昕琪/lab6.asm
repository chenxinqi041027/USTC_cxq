; Unfortunately we have not YET installed Windows or Linux on the LC-3,
; so we are going to have to write some operating system code to enable
; keyboard interrupts. The OS code does three things:
;
;    (1) Initializes the interrupt vector table with the starting
;        address of the interrupt service routine. The keyboard
;        interrupt vector is x80 and the interrupt vector table begins
;        at memory location x0100. The keyboard interrupt service routine
;        begins at x1000. Therefore, we must initialize memory location
;        x0180 with the value x1000.
;    (2) Sets bit 14 of the KBSR to enable interrupts.
;    (3) Pushes a PSR and PC to the system stack so that it can jump
;        to the user program at x3000 using an RTI instruction.

        .ORIG x800
        ; (1) Initialize interrupt vector table.
        LD    R0, VEC
        LD    R1, ISR
        STR   R1, R0, #0

        ; (2) Set bit 14 of KBSR.
        LDI   R0, KBSR
        LD    R1, MASK
        NOT   R1, R1
        AND   R0, R0, R1
        NOT   R1, R1
        ADD   R0, R0, R1
        STI   R0, KBSR

        ; (3) Set up system stack to enter user space.
        LD    R0, PSR
        ADD   R6, R6, #-1
        STR   R0, R6, #0
        LD    R0, PC
        ADD   R6, R6, #-1
        STR   R0, R6, #0
        ; Enter user space.
        RTI
        
VEC     .FILL x0180
ISR     .FILL x1000
KBSR    .FILL xFE00
MASK    .FILL x4000
PSR     .FILL x8002
PC      .FILL x3000
        .END

        .ORIG x3000
        ; *** Begin user program code here ***
        JSR   DELAY         
DELAY	ST    R1, SAVER1		
		LD    R1, COUNT
REP 	ADD   R1, R1, #-1   ;循环计数
		BRp   REP
		LEA   R0, STUID     ;输出
        PUTS
		LD    R1, SAVER1
		RET

COUNT	.FILL #15000        ;每到15000就输出
SAVER1  .FILL x5000
STUID	.STRINGZ "PB22111711 "
        ; *** End user program code here ***
        .END

        .ORIG x3FFF
        ; *** Begin factorial data here ***
FACT_N .FILL xFFFF
        ; *** End factorial data here ***
        .END

        .ORIG x1000
        ; *** Begin interrupt service routine code here ***
        LD    R0, NEWLINE   ;回车
        OUT
        GETC                ;输入N
        OUT                 ;输出

CHECK   ADD   R5, R0, #0    ;检查是否为数字
        ADD   R4, R0, #0
        LD    R3, ASCIIZ
        ADD   R0, R0, R3    ; N-'0'
        BRn   ERROR         ;不是数字
        LD    R3, ASCIIN     
        ADD   R0, R5, R3    ; N-'9'
        BRp   ERROR         ;不是数字
        LEA   R0, OUTPUT2
        PUTS
        LD    R0, NEWLINE
        OUT
        LD    R3, ASCIIE
        AND   R5, R5, #0
        ADD   R5, R5, R4
        ADD   R0, R5, R3    ; N-'8'
        BRzp  OVERFL        ;溢出
        AND   R0, R0, #0
        LD    R3, ASCIIZ
        ADD   R0, R4, R3    ;存储数字值
        BRnzp CALC
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

CALC    AND   R2, R2, #0; 打表输出
        ADD   R2, R0, #0
        ADD   R0, R4, #0
        OUT
        LEA   R0,OUTPUT3
        PUTS                                                                                                           
        ADD   R2, R2, #-1
        BRn   FAC01
        ADD   R2, R2, #-1
        BRn   FAC01
        ADD   R2, R2, #-1
        BRn   FAC2
        ADD   R2, R2, #-1
        BRn   FAC3
        ADD   R2, R2, #-1
        BRn   FAC4
        ADD   R2, R2, #-1
        BRn   FAC5
        ADD   R2, R2, #-1
        BRn   FAC6
        ADD   R2, R2, #-1
        BRn   FAC7

FAC01   LEA R0 RESULT0
        PUTS
        BRnzp FINISH
FAC2    LEA R0 RESULT2
        PUTS
        BRnzp FINISH
FAC3    LEA R0 RESULT3
        PUTS
        BRnzp FINISH
FAC4    LEA R0 RESULT4
        PUTS
        BRnzp FINISH
FAC5    LEA R0 RESULT5
        PUTS
        BRnzp FINISH
FAC6    LEA R0 RESULT6
        PUTS
        BRnzp FINISH
FAC7    LEA R0 RESULT7
        PUTS
        BRnzp FINISH
;输出值

FINISH  HALT

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
RESULT0     .STRINGZ "1"
RESULT2     .STRINGZ "2"
RESULT3     .STRINGZ "6"
RESULT4     .STRINGZ "24"
RESULT5     .STRINGZ "120"
RESULT6     .STRINGZ "720"
RESULT7     .STRINGZ "5040"
; *** End interrupt service routine code here ***
        .END
      


