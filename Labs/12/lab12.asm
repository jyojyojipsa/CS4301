;;; Name
;;; CS 3304
;;; Lab12
 
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"
 


SECTION .data
buffer  times   128 db 				   0
buflen  equ     ($ - buffer)	
true       	db      	' is valid'  , 0
false     	db      	' is invalid', 0 
A        	dd        				   0
B        	dd        				   0
ex			dd		  				   0

global  _start
_start:
.L0:
	mov     edx,buffer
    mov     ecx,buflen
	call    ReadString
	jz      .L11      
	mov     esi,0
.L1:
	mov     al,[buffer+esi]
    call    WriteChar
	
	cmp     byte [buffer+esi], 97
	je		.L5 
	cmp     byte [buffer+esi], 97
	jne		.L2 
.L2:
	cmp		byte [buffer+esi], 98
	je		.L6
.L3:
	cmp		byte [buffer+esi], 98
	jne		.L7
.L4:
	inc		esi
	cmp		byte [buffer+esi], 0
	je		.L8
	cmp		byte [buffer+esi], 0
	jne		.L1
.L5:
	mov		eax,[A]
	inc		eax
	mov		[A],eax
	jmp		.L2
.L6:
	mov		eax,[B]
	inc		eax
	mov		[B],eax
	jmp		.L3
.L7:
	jmp		.L4
.L8:
	jnz		.L10
	mov     eax,[B]
    add     eax,[B]
    mov     ebx,[A]
    cmp     eax,ebx
    je		.L9
    cmp        eax,ebx
	jne		.L10
.L9:
	mov 	edx,true
	call	WriteString
	call	Crlf
	mov		eax,0
	mov		[A],eax
	mov		[B],eax
	jmp		.L0
.L10:
	mov 	edx,false
	call	WriteString
	call	Crlf
	mov		eax,0
	mov		[A],eax
	mov		[B],eax
	jmp		.L0
.L11:
	Exit    {0}
 
SECTION .bss