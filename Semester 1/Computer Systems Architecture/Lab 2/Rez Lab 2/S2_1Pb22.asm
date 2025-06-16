bits 32
global start
extern exit
import exit msvcrt.dll    

segment data use32 class=data ; a,b,c,d byte
    a db 1
    b db 4
    c db 10010010b
    d db 10010010b

segment code use32 class=code
    start:
        MOV AL, byte [a]
        MOV AH, 0           ; AX = a
        
        ADD AL, byte [b]
        ADC AH, 0           ; AX = a + b
        
        ADD AL, byte [b]
        ADC AH, 0           ; AX = a + b + b
        
        MOV BL, byte [c]
        MOV BH, 0           ; BX = c
        
        ADD BL, byte [d]
        ADC BH, 0           ; BX = c + d
        
        SUB AL, BL
        SBB AH, BH          ; AX = (a + b + b) - (c + d)        
    
        push    dword 0
        call    [exit]
