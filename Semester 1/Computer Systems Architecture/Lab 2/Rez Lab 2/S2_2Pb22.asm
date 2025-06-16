bits 32
global start 
extern exit
import exit msvcrt.dll 

segment data use32 class=data
    a dw 2
    b dw 7
    c dw 1
    d dw 2

segment code use32 class=code
    start:
    
        ; (b-a) - (c+c+d)
        MOV AX, word [b]    ; AX = b
        MOV BX, word [a]    ; BX = a
        SUB AX, BX          ; AX = b - a
        MOV EBX, 0
        MOV BX, AX          ; EBX = b - a
        
        MOV AX, word [c]    ; AX = c
        MOV DX, 0
        ADD AX, word [c]
        ADC DX, 0           ; DX:AX = c + c
        ADD AX, word [d]
        ADC DX, 0           ; DX:AX = c + c + d
        
        PUSH DX
        PUSH AX
        POP EAX             ; EAX = c + c + d
        
        SUB EBX, EAX        ; EBX = (b-a) - (c+c+d)
        ; result is in EBX
        

        push    dword 0
        call    [exit] 
