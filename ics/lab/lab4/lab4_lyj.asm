        .ORIG x3000
; Initialize variables
        LDI R0, ADDR1;int n
        AND R1, R1, #0;state
        LD R2, ADDR1;x3100
        LD R7, EXIT;halt
        LD R6, ADDR2
       
REMOVE  STR R7, R6, #0
        ADD R6, R6, #1
        
        ADD R0, R0, #0
        BRz OUTLP2
        
        ADD R0, R0, #-1
        BRz OUT1
        ADD R0, R0, #1
        
        ADD R0, R0, #-2
        JSR REMOVE
        
        ADD R0, R0, #2
        AND R3, R3, #0
        ADD R4, R3, #1
        ADD R3, R3, R0
        ADD R3, R3, #-1
LOOP1   BRz OUTLP1
        ADD R4, R4, R4
        ADD R3, R3, #-1
        BRnzp LOOP1
        
OUTLP1  ADD R1, R1, R4
        ADD R2, R2, #1
        STR R1, R2, #0
        
        ADD R0, R0, #-2
        JSR PUT
        
        ADD R0, R0, #1
        JSR REMOVE
        
        ADD R0, R0, #1
        BRnzp OUTLP2
        
OUT1    ADD R0, R0, #1
        ADD R1, R1, #1
        ADD R2, R2, #1
        STR R1, R2, #0
        
OUTLP2  ADD R6, R6, #-1
        LDR R7, R6, #0
        RET
        
PUT     STR R7, R6, #0
        ADD R6, R6, #1
        
        ADD R0, R0, #0
        BRz OUTLP4
        
        ADD R0, R0, #-1
        BRz OUT2
        ADD R0, R0, #1
        
        ADD R0, R0, #-2
        JSR PUT
        
        ADD R0, R0, #2
        AND R3, R3, #0
        ADD R4, R3, #1
        ADD R3, R3, R0
        ADD R3, R3, #-1
LOOP2   BRz OUTLP3
        ADD R4, R4, R4
        ADD R3, R3, #-1
        BRnzp LOOP2
        
OUTLP3  NOT R4, R4
        ADD R4, R4, #1
        ADD R1, R1, R4
        ADD R2, R2, #1
        STR R1, R2, #0
        
        ADD R0, R0, #-2
        JSR REMOVE
        
        ADD R0, R0, #1
        JSR PUT
        
        ADD R0, R0, #1
        BRnzp OUTLP4
        
OUT2    ADD R0, R0, #1
        ADD R1, R1, #-1
        ADD R2, R2, #1
        STR R1, R2, #0
        
OUTLP4  ADD R6, R6, #-1
        LDR R7, R6, #0
        RET

EXIT    HALT
        
ADDR1   .FILL x3100
ADDR2   .FILL x4100
        
        .END