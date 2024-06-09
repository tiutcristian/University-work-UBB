bits 32           

global replace_with_hundreds
              
segment code use32 public code

replace_with_hundreds:

	;STACK CONFIGURATION
	;|------------------|
	;|  return address  |  < esp
	;|------------------|
	;|    	  s2        |  < esp+4
	;|------------------|
	;|    	  s1        |  < esp+8
	;|------------------|
	;| 	no of integers  |  < esp+12
	;|------------------|

	mov ecx, [esp + 12]		; ecx = no of integers
	mov esi, [esp + 8]		; esi = offset of first element of s1
	mov edi, [esp + 4]		; edi = offset of first element of s2
	
	repeat:
	; load in eax the current int
		LODSD				; eax = [esi] = current int
		
	; get in eax the hundreds digit		
		cmp eax, 0		; compare curr-int with 0
		jge ge			; if it is greater or equal, jump to "ge" label
		neg eax			; if it is less than 0, eax = - eax
	ge:					; after this curr_int = abs(curr_int)
		mov edx, 0		; edx:eax = curr_int
		mov ebx, 1000	; ebx = 1000
		idiv ebx		; edx = curr_int % 1000
		mov eax, edx	; eax = curr_int % 1000
		mov edx, 0		; edx:eax = curr_int % 1000
		mov ebx, 100	; ebx = 100
		div ebx			; eax = (curr_int % 1000) / 100 = hundreds digit
		
	; move the digit from eax to the corresponding memory location in s2
		STOSD			; [edi] = eax
		
	loop repeat
	
	ret
; end replace_with_hundreds
