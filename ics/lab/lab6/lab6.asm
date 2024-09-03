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
      


      


