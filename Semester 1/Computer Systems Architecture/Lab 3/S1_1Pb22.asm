bits 32
global start 
extern exit
import exit msvcrt.dll 

segment data use32 class=data
    a db 1
    b dw 1
    c dd 1
    d dq 7
    ; unsigned

segment code use32 class=code
    start:
    
        ; (d+c) - (c+b) - (b+a)
        
        MOV EBX, dword [d]
        MOV ECX, dword [d+4]    ; ECX:EBX = d
        MOV EAX, dword [c]      ; EAX = c
        ADD EBX, EAX
        ADC ECX, 0              ; ECX:EBX = d + c
        
        MOV EAX, dword [c]      ; EAX = c
        MOV EDX, 0
        MOV DX, word [b]        ; EDX = b
        ADD EAX, EDX            ; EAX = c + b
        
        SUB EBX, EAX
        SBB ECX, 0              ; ECX:EBX = (d+c) - (c+b)
        
        MOV AX, word [b]        ; AX = b
        MOV DL, byte [a]        ; DL = a
        MOV DH, 0               ; DX = a
        ADD AX, DX              ; AX = b + a
        
        MOV EDX, 0
        MOV DX, AX              ; EDX = b + a
        
        SUB EBX, EDX
        SBB ECX, 0              ; ECX:EBX = (d+c) - (c+b) - (b+a)
        
        ; result in ECX:EBX

        push    dword 0
        call    [exit] 
