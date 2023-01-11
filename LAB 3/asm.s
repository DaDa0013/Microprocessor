        NAME    main
        
        PUBLIC  __iar_program_start
        
        SECTION .intvec : CODE (2)
        
__iar_program_start
        B       main

        
        SECTION .text : CODE (2)

main    
        MOV R0, #0x00001234 //R0�� #0x00001234 �� �ֱ�
        MOV R1, #0x00004567 //R1�� #0x00004567 �� �ֱ�
        MOV R2, #0xFFFFFFFF //R2�� #0xFFFFFFFF �� �ֱ�
        MOV R3, #0x00000002 //R3�� #0x00000002 �� �ֱ�
        
        ADD R4, R0, R1 //R4�� R0�� R1�� ���� �� �ֱ�
        ADDS R4, R0, R1 //R4�� R0�� R1�� ���� �� �ְ� APSR ������Ʈ
        ADD R5, R2, R3 //R5�� R2�� R3�� ���� �� �ֱ�
        ADDS R5, R2, R3 //R5�� R2�� R3�� ���� �� �ְ� APSR ������Ʈ
        
        SUB R4, R0, R1 //R4�� R0�� R1�� �� �� �ֱ�
        SUBS R4, R0, R1 //R4�� R0�� R1�� �� �� �ְ� APSR ������Ʈ
        SUB R5, R2, R3 //R5�� R2�� R3�� �� �� �ֱ�
        SUBS R5, R2, R3 //R5�� R2�� R3�� �� �� �ְ� APSR ������Ʈ
        
        SMULL R7, R6, R0, R2 //R6�� R7�� R0�� R1�� ���� ���� ��ȣ �����Ͽ� 32bit�� ���� �ֱ�
        UMULL R7, R6, R0, R2 //R6�� R7�� R0�� R1�� ���� ���� ��ȣ �������� �ʰ� 32bit�� ���� �ֱ�
        SMULL R9, R8, R1, R3 //R8�� R9�� R1�� R3�� ���� ���� ��ȣ �����Ͽ� 32bit�� ���� �ֱ�
        UMULL R9, R8, R1, R3 //R8�� R9�� R1�� R3�� ���� ���� ��ȣ �������� �ʰ� 32bit�� ���� �ֱ�
        END