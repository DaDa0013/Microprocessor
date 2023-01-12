        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)

main    
        LDR R0, =0xf0f0f0f0
        LDR R1, =0x12345678
        
        MOV R2, #1
        MOV R3, #32
here        
        AND R4, R0, R2 
        CMP R4, #1
        BNE jmp1
        ADD R9, R9, #1
jmp1        
        AND R5, R1, R2
        CMP R5, #0
        BNE jmp2
        ADD R10, R10, #1        
jmp2        
        LSR R0, R0, #1
        LSR R1, R1, #1
        SUBS R3, R3, #1
        BNE here
        
        NOP

        END