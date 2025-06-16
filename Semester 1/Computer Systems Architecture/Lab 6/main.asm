bits 32
global start        
extern exit
import exit msvcrt.dll

segment data use32 class=data
    input db 'Ana are mere.'
    input_len equ $-input
    src db 'nm'
    dst db 'mp'
    n equ $-dst
    output resb input_len

segment code use32 class=code
    start:
        ; initializations
        MOV ECX, input_len
        MOV ESI, input
        
        LOOP_1_START: ;"input/output [i]"
            PUSH ECX
            
            LODSB           ; AL = input[i] ; ESI = input[i] + 1
            PUSH ESI        ; PUSH input[i] + 1
            MOV ECX, n      ; ECX = n
            MOV EDI, src    ; EDI = src[0]
            
            LOOP_2_START: ;"src/dst [j]"
            
                SCASB       ; CMP AL, src[j]; EDI = src[j] + 1
                JNE NOT_EQUAL   ; continue
                
                    ; if equal: -------------------------
                    PUSH EDI    ; PUSH src[j] + 1
                    
                    ; move dst[j] in output[i]
                    XCHG ESI, EDI       ; ESI = src[j] + 1; EDI = input[i] + 1
                    ADD ESI, dst - src - 1          ; ESI = dst[j]
                    ADD EDI, output - input - 1     ; EDI = output[i]
                    MOVSB   ; output[i] = dst[j]; ESI = dst[j]+1; EDI = output[i]+1
                    
                    POP EDI     ; MOV EDI, src[j] + 1
                    JMP  END_LOOP_2
                    ;-------------------------------------
                
                NOT_EQUAL:
            
            LOOP LOOP_2_START
            
            ; if we arrive here we haven't put anything in output[i]
            ; so we store AL = input[i] in output[i]
            ; ESI = input[i] + 1
            LEA EDI, [ESI + output - input - 1]     ; EDI = output[i]
            STOSB   ; output[i] <- AL
            
            END_LOOP_2:     ; here we know that we have put sth in output[i]
            
            POP ESI     ; MOV ESI, input[i] + 1
            POP ECX
        LOOP LOOP_1_START
    
        push    dword 0
        call    [exit]
        
