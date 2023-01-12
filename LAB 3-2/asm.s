        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)

main    
       LDR r0, =0xFFFFFFF7
       LDR r1, =0x7FFFFFFF
       MOV r2, #00001111b
       
       ASR r3, r0, #4
       ASR r4, r1, #4
       LSL r5, r2, #4
       LSR r6, r2, #4
       ROR r7, r2, #4
       
       
        
       NOP

       END
