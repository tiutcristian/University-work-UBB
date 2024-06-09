bits 32
global start 
extern exit
import exit msvcrt.dll 

segment data use32 class=data
    a db 2
    b db 1
    c db 3
    d dw 1

segment code use32 class=code
    start:
    
        ; [ (10+d) - (a*a-2*b) ] / c
        ;              dword  dword
        ;   dword      dword        
        ;     ----- dword -----        word
        ; result in word
        
        MOV EBX, 0              ; EBX = 0
        MOV BX, word [d]        ; BX = d
        ADD EBX, 10             ; EBX = d + 10
        
        MOV AL, byte [a]        ; AL = a
        MUL byte [a]            ; AX = a * a
        MOV ECX, 0              ; ECX = 0
        MOV CX, AX              ; ECX = a * a
        
        MOV EAX, 0
        MOV AH, byte [b]        ; AH = b
        MOV AL, 2               ; AL = 2
        MUL AH                  ; AX = 2 * b
                                ; EAX = 2 * b
        SUB ECX, EAX            ; ECX = a*a - 2*b
        
        SUB EBX, ECX            ; EBX = (d+10) - (a*a - 2*b)
        
        PUSH EBX
        POP AX
        POP DX                  ; DX:AX = (d+10) - (a*a - 2*b)
        
        MOV CL, byte [c]        ; CL = c
        MOV CH, 0               ; CX = c
        
        DIV CX                  ; AX = (d+10) - (a*a - 2*b) / c
        ; result in AX
         
         
        push    dword 0
        call    [exit] 