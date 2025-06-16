bits 32
global start 
extern exit
import exit msvcrt.dll 

segment data use32 class=data
    a db 1
    b dw 1
    c dd 1
    d dq 1
    ; signed

segment code use32 class=code
    start:
    
        ; c + b - (a - d + b)
        
        MOV EBX, dword [c]      ; EBX = c
        MOV AX, word [b]        ; AX = b
        CWDE                    ; EAX = b
        ADD EBX, EAX            ; EBX = c + b
        PUSH EBX                ; c + b (dword) in stack
        
        MOV AL, byte [a]        ; AL = a
        CBW                     ; AX = a
        CWDE                    ; EAX = a
        CDQ                     ; EDX:EAX = a

        SUB EAX, dword [d]
        SBB EDX, dword [d+4]    ; EDX:EAX = a - d
        MOV EBX, EAX
        MOV ECX, EDX            ; ECX:EBX = a - d
        
        MOV AX, word [b]        ; AX = b
        CWDE                    ; EAX = b
        CDQ                     ; EDX:EAX = b
        
        ADD EBX, EAX
        ADC ECX, EDX            ; ECX:EBX = a - d + b
        
        POP EAX                 ; EAX = c + b
        CDQ                     ; EDX:EAX = c + b
        
        SUB EAX, EBX
        SBB EDX, ECX            ; EDX:EAX = c + b - (a - d + b)
        
        ; result in EDX:EAX
    
        push    dword 0
        call    [exit] 
