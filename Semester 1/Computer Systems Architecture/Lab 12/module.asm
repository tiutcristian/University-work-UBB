bits 32

global _bin_to_hex

segment data public data use32
    bin_len dd 0
    bin_nr_address dd 0
    hex_nr_address dd 0

segment code public code use32
; void bin_to_hex(int bin_len, char bin_nr[], char hex_nr[]);
_bin_to_hex:      
    push ebp
    mov ebp, esp   
    pushad 
    
    ; store the parameters
    mov eax, [ebp+8]
    mov [bin_len], eax
    mov eax, [ebp+12]
    mov [bin_nr_address], eax
    mov eax, [ebp+16]
    mov [hex_nr_address], eax

    mov ecx, [bin_len]
    mov edi, [hex_nr_address]   ; edi = address of result string
    mov esi, [bin_nr_address]   ; esi = address of initial string
conversion_loop:
    ; take corresponding nibble (+ save ecx and prepareit for inner loop)
    cmp ecx, 4
    jb below_4
        ; if here, ecx >= 4
        sub ecx, 3  ; subtract 4 from bin_len for the corresponding 4 bytes of the number that are being processed
        push ecx    ; save ecx
        mov ecx, 4  ; prepare ecx for inner_loop
        jmp end_if
    below_4:
        ; if here, ecx < 4
        push dword 1    ; push 0 as the remaining length of the bin_len ; ecx is already prepared for inner_loop
    end_if:

    ; generate current hex digit
    mov bl, 1   ; bl =  curr_power
    mov dl, 0   ; dl = curr_hex_digit
    inner_loop:
        lodsb   ; al = curr_bin_digit
        cmp al, '0'
        je end_cmp
            ; arrive here when curr_bin_digit = 1
            add dl, bl
        end_cmp:    
            ; arrive here when curr_bin_digit = 0
        shl bl, 1   ; prepare power for next iteration
    loop inner_loop

    ; store current hex digit
    mov al, dl  ; al = curr_hex_digit (represented as a number e.g. 6, 2, 10, 15)
    add al, '0' ; respresent the digit as a character
    stosb

    pop ecx
loop conversion_loop
    
    ; add '\0' at the end of the result string
    mov byte [edi], 0

    popad
    mov esp, ebp
    pop ebp 
    ret