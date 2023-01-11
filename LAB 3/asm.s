        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)

main    
        MOV R0, #0x00001234 //R0에 #0x00001234 값 넣기
        MOV R1, #0x00004567 //R1에 #0x00004567 값 넣기
        MOV R2, #0xFFFFFFFF //R2에 #0xFFFFFFFF 값 넣기
        MOV R3, #0x00000002 //R3에 #0x00000002 값 넣기
        
        ADD R4, R0, R1 //R4에 R0와 R1을 더한 값 넣기
        ADDS R4, R0, R1 //R4에 R0와 R1을 더한 값 넣고 APSR 업데이트
        ADD R5, R2, R3 //R5에 R2와 R3을 더한 값 넣기
        ADDS R5, R2, R3 //R5에 R2와 R3을 더한 값 넣고 APSR 업데이트
        
        SUB R4, R0, R1 //R4에 R0에 R1을 뺀 값 넣기
        SUBS R4, R0, R1 //R4에 R0에 R1을 뺀 값 넣고 APSR 업데이트
        SUB R5, R2, R3 //R5에 R2에 R3을 뺀 값 넣기
        SUBS R5, R2, R3 //R5에 R2에 R3을 뺀 값 넣고 APSR 업데이트
        
        SMULL R7, R6, R0, R2 //R6와 R7에 R0와 R1을 곱한 값을 부호 포함하여 32bit씩 나눠 넣기
        UMULL R7, R6, R0, R2 //R6와 R7에 R0와 R1을 곱한 값을 부호 포함하지 않고 32bit씩 나눠 넣기
        SMULL R9, R8, R1, R3 //R8와 R9에 R1와 R3을 곱한 값을 부호 포함하여 32bit씩 나눠 넣기
        UMULL R9, R8, R1, R3 //R8와 R9에 R1와 R3을 곱한 값을 부호 포함하지 않고 32bit씩 나눠 넣기
        END