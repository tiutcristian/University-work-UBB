bits 32
global start 
extern exit
import exit msvcrt.dll 

segment data use32 class=data
    a db 2
    b db 4
    c db 1
    e dd 2
    x dq 2
    ; signed

segment code use32 class=code
    start:
    
        ; a/2 + b*b - a*b*c + e + x 
        
        mov al, byte [a]        ; al = a
        cbw                     ; ax = a
        mov bl, 2               ; bl = 2
        idiv bl                 ; al = a/2
        cbw                     ; ax = a/2
        cwde                    ; eax = a/2
        cdq                     ; edx:eax = a/2
        mov ebx, eax
        mov ecx, edx            ; ecx:ebx = a/2
        
        mov al, byte [b]        ; al = b
        imul al                 ; ax = b*b
        cwde                    ; eax = b*b
        cdq                     ; edx:eax = b*b
        add ebx, eax
        adc ecx, edx            ; ecx:ebx = a/2 + b*b
        
        mov al, byte [a]        ; al = a
        mov dl, byte [b]        ; dl = b    
        imul dl                 ; ax = a*b
        mov dx, ax              ; dx = a*b
        mov al, byte [c]        ; al = c
        cbw                     ; ax = c
        imul dx                 ; dx:ax = a*b*c
        push dx
        push ax
        pop eax                 ; eax = a*b*c
        cdq                     ; edx:eax = a*b*c
        sub ebx, eax
        sbb ecx, edx            ; ecx:ebx = a/2 + b*b - a*b*c
        
        mov eax, dword [e]      ; eax = e
        cdq                     ; edx:eax = e
        add ebx, eax
        adc ecx, edx            ; ecx:ebx = a/2 + b*b - a*b*c + e
        
        mov eax, dword [x]
        mov edx, dword [x+4]    ; edx:eax = x
        add ebx, eax
        adc ecx, edx            ; ecx:ebx = a/2 + b*b - a*b*c + e + x
        
    
        push    dword 0
        call    [exit] 
