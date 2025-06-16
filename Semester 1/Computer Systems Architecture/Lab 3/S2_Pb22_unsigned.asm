bits 32
global start 
extern exit
import exit msvcrt.dll 

segment data use32 class=data
    a db 4
    b db 2
    c db 1
    e dd 2
    x dq 2
    ; unsigned

segment code use32 class=code
    start:
    
        ; a/2 + b*b - a*b*c + e + x 
        
        mov al, byte [a]
        mov ah, 0           ; ax = a
        mov bl, 2           ; bl = 2
        div bl              ; al = a/2
        mov bl, al          ; bl = a/2
        mov bh, 0           ; bx = a/2
        
        mov al, byte [b]    ; al = b    
        mul al              ; ax = b*b
        add bx, ax          ; bx = a/2 + b*b
        
        mov al, byte [a]    ; al = a
        mul byte [b]        ; ax = a*b
        mov cl, byte [c]
        mov ch, 0           ; cx = c
        mul cx              ; dx:ax = a*b*c
        
        mov cx, 0           ; cx:bx = a/2 + b*b
        sub bx, ax
        sbb cx, dx          ; cx:bx = a/2 + b*b - a*b*c
        
        mov ax, word [e]
        mov dx, word [e+2]  ; dx:ax = e
        add bx, ax
        adc cx, dx          ; cx:bx = a/2 + b*b - a*b*c + e
        
        push cx
        push bx
        pop ebx             ; ebx = a/2 + b*b - a*b*c + e
        mov ecx, 0          ; ecx:ebx = a/2 + b*b - a*b*c + e
        
        mov eax, dword [x]
        mov edx, dword [x+4]; edx:eax = x
        add ebx, eax
        adc ecx, edx        ; ecx:ebx = a/2 + b*b - a*b*c + e + x
        
        ; result in ecx:ebx  
    
        push    dword 0
        call    [exit] 
