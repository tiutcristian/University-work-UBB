; Read a string of integers s1 (represented on doublewords) in base 10. Determine and display the string s2 composed by the digits in the hundreds place of each integer in the string s1.
; Example:    
; The string s1: 5892, 456, 33, 7, 245
; The string s2: 8, 4, 0, 0, 2

bits 32
global start

extern scanf, printf, exit, replace_with_hundreds
import scanf msvcrt.dll
import printf msvcrt.dll
import exit msvcrt.dll

segment data use32
	format_read db "%d", 0
	format_print db "%d ", 0
	newline db 10, 0
	no_counter db 0
	curr_int dd 0
	s1 resd 100
	s2 resd 100

segment code use32 public code

start:


; reading
	mov edi, s1		; edi = offset(s1)
	
read_loop:
	push dword curr_int		; read in curr_int
	push dword format_read	; pointer to the format
	call [scanf]			; call function
	add esp, 2*4			; free up the stack
	
	cmp eax, 1				; check if scanf successfully read an integer
	jne end_read_loop		; if not, the input has finished
								; else we store the number and continue reading
	inc byte [no_counter]		; increase the numbers counter
	mov eax, dword [curr_int]	; eax = current int
	STOSD						; [edi] = current int ; edi += 4
	jmp read_loop		; repeat read loop
	
end_read_loop:			; arrive here when we don't have anything left to read
	

; calling the function
	mov eax, 0
	mov al, byte [no_counter]	; move to eax the no of integers

	push eax					; push the no of integers
	push dword s1				; push the offset of the string
	push dword s2				; push the offset of the result
	call replace_with_hundreds	; call the function to replace numbers with hundreds digit
	add esp, 4*3				; empty the stack
	
	
; printing numbers
	mov ecx, 0
	mov cl, byte [no_counter]	; ecx = [no_counter]
	mov esi, s2					; esi = offset(s2)
	
print_loop:
	push ecx			; save ecx
	
	LODSD				; eax = [esi] ; esi += 4
	
	push eax			; push the current int
	push format_print	; push the format
	call [printf]		; call the function
	add esp, 4*2		; empty the stack
	
	pop ecx				; restore ecx for looping
	loop print_loop		; loop the print loop
	
	push newline		
	call [printf]		; print newline
	add esp, 4			; empty the stack
	

; end
	push 0
	call [exit]
