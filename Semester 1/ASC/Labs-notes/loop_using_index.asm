bits 32
global start
extern exit
import exit msvcrt.dll
                          
segment data use32 class=data
    s db 1, 2, 3, 5, 4
    len equ $ - s
    sum db 0

segment code use32 class=code
    start:
        mov ebx, s
        mov esi, 0
        mov ecx, len
        jecxz final
        
    repeat:
        mov al, [ebx + esi]
        add byte [sum], al
        inc esi
    loop repeat
    final:
    
        mov ebx, 0
        mov bl, byte [sum]
    
        push    dword 0
        call    [exit]
