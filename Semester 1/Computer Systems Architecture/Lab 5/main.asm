bits 32
global start        
extern exit
import exit msvcrt.dll

segment data use32 class=data
    s1 db 1, 3, 6, 2, 3, 7
    len equ $-s1
    s2 db 6, 3, 8, 1, 2, 5
    d resb len

segment code use32 class=code
    start:
        ; initializations
        MOV ECX, len
        MOV ESI, s1
        MOV EDI, d
        
        ; loop
        START_LOOP:    
                LODSB           ; AL = byte [ESI]
                MOV BL, AL      ; BL = byte [ESI] (s1)
                ADD ESI, len-1  ; move ESI to the address of the corresponding byte in s2
                LODSB           ; AL = byte [ESI] (s2)
                SUB ESI, len    ; move ESI to the address of the next byte in s1 for the next execution of the loop
                
                CMP BL, AL
                JA STORE        ; if s1[i] > s2[i] we store s2[i] which is in AL
                MOV AL, BL      ; otherwise we first move BL to AL so s1[i] is in AL
            STORE:
                STOSB
        LOOP START_LOOP
    
        push    dword 0
        call    [exit]
