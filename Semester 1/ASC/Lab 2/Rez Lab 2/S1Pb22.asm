bits 32
global start
extern exit
import exit msvcrt.dll    

segment data use32 class=data

segment code use32 class=code
    start:
        
        MOV AX, 16  ; AX = 16
        MOV BL, 4   ; BL = 4   
		DIV BL      ; AL = 16/4
        
        ; result in AL
        
        push    dword 0
        call    [exit]
