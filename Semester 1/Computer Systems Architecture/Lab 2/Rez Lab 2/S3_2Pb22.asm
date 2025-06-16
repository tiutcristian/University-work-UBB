bits 32
global start 
extern exit
import exit msvcrt.dll 

segment data use32 class=data
    a db 1
    b db 2
    c db 1

segment code use32 class=code
    start:
    
        ; (a+(b-c))*3
        ; result: EAX = 6
        
        MOV AL, byte [a]    ; AL = a
        MOV AH, 0           ; AX = a
        
        MOV BL, byte [b]    ; BL = b
        SUB BL, byte [c]    ; BL = b - c
        MOV BH, 0           ; BX = b - c
        
        ADD AX, BX          ; AX = a + (b - c)
        
        MOV BX, 3           ; BX = 3
        MUL BX              ; DX:AX = (a + (b - c)) * 3
        
        ; result in DX:AX

        push    dword 0
        call    [exit] 
