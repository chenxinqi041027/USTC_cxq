    .ORIG x3000
    
Init        
    AND R4, R4, #0
    ADD R4, R4, #3
    LEA R0, STR1
    PUTS
        
    LD R1, CHAR1
    NOT R1, R1
    ADD R1, R1, #1

Is_W   
    GETC
    OUT
    ADD R2, R0, R1
    BRnp Is_W;不是W
    
    LD R0, CHAR4
    OUT
    LD R0, CHAR5
    OUT
    LEA R0, STR2
    PUTS
        
Is_Y  
    LD R1, CHAR2
    NOT R1, R1
    ADD R1, R1, #1
    LEA R6, STRING
    
Judge  
    GETC
    OUT
    ADD R2, R0, R1
    BRz DONE;判断为Y
    STR R0, R6, #0
    ADD R6, R6, #1
    BRnzp Judge

DONE
    AND R3, R3, #0
    STR R3, R6, #0
    LEA R6, STRING
    LEA R5, STR3
    
Strcmp
    LDR R0, R6, #0
    LDR R1, R5, #0
    BRnp continue
    ADD R0, R0, #0
    BRz SUCCESS
    ADD R0, R0, #0
    BRnp FAIL1
continue
    NOT R1, R1
    ADD R1, R1, #1
    ADD R2, R1, R0
    BRnp FAIL1
    ADD R6, R6, #1
    ADD R5, R5, #1
    BRnzp Strcmp

        
FAIL1
    ADD R4, R4, #-1
    BRz FAIL2
    LD R0, CHAR4
    OUT
    LD R0, CHAR5
    OUT
    LEA R0, STR4
    PUTS
    LD R0, CHAR3
    ADD R0, R4, R0
    OUT
    LEA R0, STR5
    PUTS
    LD R0, CHAR4
    OUT
    LD R0, CHAR5
    OUT
    BRnzp Is_Y
        
FAIL2  
    LEA R0, STR7
    PUTS
    LD R0, CHAR4
    OUT
    LD R0, CHAR5
    OUT
    BRnzp Init
        
SUCCESS
    LD R0, CHAR4
    OUT
    LD R0, CHAR5
    OUT
    
    LEA R0, STR6
    PUTS
        
    HALT
        
STR1    .STRINGZ "Welcome to the bank system! Type 'W' to withdraw some fund."
STR2    .STRINGZ "Please input your password:"
STR3    .STRINGZ "PB22111711"
STR4    .STRINGZ "Incorrect password! "
STR5    .STRINGZ " attempt(s) remain."
STR6    .STRINGZ "Success!"
STR7    .STRINGZ "Fails."
CHAR1   .FILL x0057 ;W
CHAR2   .FILL x0059 ;Y
CHAR3   .FILL x0030 ;0
CHAR4   .FILL x000D ;\r
CHAR5   .FILL x000A ;\n
STRING  .BLKW 100 
        
    .END