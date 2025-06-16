bits 32

global start

extern exit
import exit msvcrt.dll

extern printf
import printf msvcrt.dll

extern scanf
import scanf msvcrt.dll

segment data use32 class=data
    k equ 2
    a dd 0
    b dd 0
    sum dd 0
    read_format db '%d%d', 0
    print_format db '%d', 0

segment code use32 class=code
    start:
        
        push dword b
        push dword a
        push dword read_format
        call [scanf]
        add esp, 4*3
        
        mov eax, dword [a]
        add eax, dword [b]
        mov ecx, k
        mul ecx             
        mov dword [sum], eax
        
        push dword [sum]
        push dword print_format
        call [printf]
        add esp, 4*2
        
        push    dword 0
        call    [exit]
