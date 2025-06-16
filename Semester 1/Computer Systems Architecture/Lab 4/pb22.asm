bits 32 
global start        
extern exit
import exit msvcrt.dll

segment data use32 class=data
    a dd 11011001101110011011100111011001b
    b dw 1011100110111001b
    c dw 0h
    
segment code use32 class=code
    start:
    
    ; the bits 0-4 of C are the invert of the bits 20-24 of A
                            ;0001 1111 0000 0000 0000 0000 0000b = 1F00000h
    MOV EAX, 1F00000h      ; create mask
    AND EAX, dword [a]      ; get in bits 20-24 of EAX the bits 20-24 from a
    SHR EAX, 20             ; on bits 0-4 of EAX, bits 20-24 of a
    XOR EAX, 1Fh            ; invert bits 0-4 of EAX
    OR word [c], AX         ; move bits 0-4 of EAX to a  ==> c = 0000 0100 = 04h
    ;------------------------------------------
    
    
    
    ; the bits 5-8 of C have the value 1
                            ;0001 1110 0000b = 1E0h
    MOV AX, 1E0h       ; create mask
    OR word [c], AX      ; move 1111 to bits 5-8 of c ==> c = 0001 1110 0100 = 01 E4h
    ;------------------------------------------
    
    
    
    ; the bits 9-12 of C are the same as the bits 12-15 of B
                            ;1111 0000 0000 0000b = 1E00h
    MOV AX, 0F000h          ; create mask
    AND AX, word [b]       ; get in bits 12-15 of EAX the bits 12-15 of b
    SHR AX, 3               ; on bits 9-12 of EAX, bits 12-15 of b
    OR word [c], AX         ; move bits 9-12 of EAX to a ==> c = 0001 0111 1110 0100 = 17 E4h
    ;------------------------------------------
    
    
    
    ; the bits 13-15 of C are the same as the bits 7-9 of A
                            ;0011 1000 0000b = 380h
    MOV EAX, 380h         ; create mask
    AND EAX, dword [a]      ; get in bits 7-9 of EAX the bits 7-9 from a
    SHL EAX, 6             ; on bits 13-15 of EAX, bits 7-9 of a
    OR word [c], AX         ; move bits 13-15 of EAX to a  ==> a = 0111 0111 1110 0100 = 77 E4h
    ;------------------------------------------
    
      
    push dword 0      
    call [exit]       
