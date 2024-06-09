;A file name and a decimal number (on 16 bits) are given (the decimal number is in the unsigned interpretation). 
;Create a file with the given name and write each digit composing the number on a different line to file.

bits 32

global start

extern exit, fopen, fclose, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    file_name db "output.txt", 0
    access_mode db "w", 0
    n dw 2345
    n_digits resb 5
    file_descriptor dd -1
    print_format db "%u", 10, 0
    number_to_print dd 0

segment code use32 class=code
    start:
        
        MOV ECX, 0  ; index = 0
        MOV AX, word [n]
        
    generate_digits_loop:
        MOV DX, 0   ; DX:AX = n
        MOV BX, 10  ; BX = 10
        DIV BX      ; AX = n/10; DX = n%10 ; the remainder being a digit, it will fit a byte, so it will be in DL
        MOV byte [n_digits + ECX], DL
        INC ECX
        CMP AX, 0
        JNZ generate_digits_loop
        
        ; in ECX we have the number of digits
        ; in n_digits we have a string of 'ECX' digits of the number (not the ascii code of the digits !!)
        
        ;---------------------------------------
        PUSH ECX
        
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2            
        mov [file_descriptor], eax
        
        cmp eax, 0
        je final
        
        POP ECX
        ;---------------------------------------
 
    
    ;---------------------------------------
    printing_loop:
        MOV EAX, 0
        MOV AL, BYTE [n_digits + ECX - 1]
        MOV dword [number_to_print], EAX
        
        PUSH ECX
        
        push dword [number_to_print]
        push dword print_format
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*3
        
        POP ECX
        
        loop printing_loop
    ;---------------------------------------
    
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        final:
        push    dword 0
        call    [exit]
