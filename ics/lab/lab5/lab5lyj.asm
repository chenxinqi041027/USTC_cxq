        .ORIG x3000
        
LOOP    AND R4, R4, #0
        ADD R4, R4, #3
        LEA R0, STR1
        PUTS
        
        LD R1, CHAR1
        NOT R1, R1
        ADD R1, R1, #1
LOOP1   GETC
        OUT
        ADD R2, R0, R1
        BRnp LOOP1
        LD R0, CHAR2
        OUT
        LEA R0, STR2
        PUTS
        
LOOP4   LD R1, CHAR2
        NOT R1, R1
        ADD R1, R1, #1
        LEA R6, STRING
LOOP2   GETC
        OUT
        ADD R2, R0, R1
        BRz DONE
        STR R0, R6, #0
        ADD R6, R6, #1
        BRnzp LOOP2

DONE    AND R3, R3, #0
        STR R3, R6, #0 
        LEA R6, STRING
        LEA R5, STR3
LOOP3   LDR R0, R6, #0
        LDR R1, R5, #0
        BRnp GO_ON
        ADD R0, R0, #0
        BRz SUCCESS
        ADD R0, R0, #0
        BRnp FAIL1
GO_ON   NOT R1, R1
        ADD R1, R1, #1
        ADD R2, R1, R0
        BRnp FAIL1
        ADD R6, R6, #1
        ADD R5, R5, #1
        BRnzp LOOP3
        
FAIL1   ADD R4, R4, #-1
        BRz FAIL2
        LEA R0, STR4
        PUTS
        LD R0, CHAR3
        ADD R0, R4, R0
        OUT
        LEA R0, STR5
        PUTS
        BRnzp LOOP4
        
FAIL2   LEA R0, STR7
        PUTS
        BRnzp LOOP
        
SUCCESS LEA R0, STR6
        PUTS
        
        HALT
        
STR1    .STRINGZ "Welcome to the bank system! Type 'W' to withdraw some fund."
STR2    .STRINGZ "Please input your password:"
STR3    .STRINGZ "PB22111659"
STR4    .STRINGZ "Incorrect password! "
STR5    .STRINGZ " attempt(s) remain."
STR6    .STRINGZ "Success!"
STR7    .STRINGZ "Fails."
CHAR1   .FILL x0057 
CHAR2   .FILL x000A
CHAR3   .FILL x0030
STRING  .BLKW 100 
        
        .END