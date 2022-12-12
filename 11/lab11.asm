;;; NASM - The Netwide Assembler https://www.nasm.us
 
;; 
;; CS 4301
;; Lab 11
 
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"
 


SECTION .text
global  _start

_start: 
		call    ReadDec ;;
		mov		[inputState],eax ;; moved this one to show the state 
		mov		ecx, [inputState] ;; copy eax to ecx
				;; a,b : a is the place going, and b is the source
		mov     edx,fib1 ;;fib(
        call    WriteString
        mov     eax,[currentState] ;;0
        call    WriteDec
		mov     edx,fib2 ;;) = 
		call    WriteString
		mov     eax,[n1] ;; 0
		call	WriteDec
		call	Crlf
		
		mov		eax, 0
		cmp		[inputState], eax
		je 		.L1			;jump equal
		
		mov     edx,fib1 ;;fib(
        call    WriteString
        mov     eax,[currentState] ;;1
		inc		eax
		mov		[currentState],eax
        call    WriteDec
		mov     edx,fib2 ;;) = 
		call    WriteString	
		mov     eax,[n2] ;; 1
		call	WriteDec
		call	Crlf
		mov     eax,[currentState] ;;1
		inc		eax
		mov		[currentState],eax
		mov		eax, 1 
		cmp		[inputState], eax
		je 		.L1	
		mov		eax, 2
		cmp		[inputState], eax
		je		.L0
		jb		.L0
		
		
		

.L0:	
		mov		ecx,[inputState]
		dec		ecx
		mov		[inputState],ecx
		mov     edx,fib1 ;;fib(
        call    WriteString
        mov     eax,[currentState] ;;0
        call    WriteDec
		mov     edx,fib2 ;;) = 
		call    WriteString
		mov		eax,[n1]
		add		eax,[n2]
		call	WriteDec
		mov		eax,[n2]
		mov		[tmp],eax
		mov		eax,[n2]
		add		eax,[n1]
		mov		[n2],eax
		mov		eax,[tmp]
		mov		[n1],eax
		mov		eax,[currentState] ;;bring currentState
		add		eax,1 ;; add currentState
		mov		[currentState],eax
		call    Crlf
		loop	.L0
.L1:
		

        Exit    {0}
		;; : = near pointer
SECTION .data
fib1    		db      'fib(',0 ;; ensure that we have NULL character at the end
fib2    		db      ') = ' , 0 ;; put NULL character at the end
currentState	dd		0 ;; Declaring double word
n1				dd		0
n2				dd		1
tmp					dd		0
SECTION .bss
inputState	resd	1 ;; reserve a double word , res = reserve  resw = reserve a word