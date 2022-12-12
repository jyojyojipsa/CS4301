; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no247

_start:                                 
        call    ReadInt                 ; read int; value placed in eax
        mov     [I0],eax                ; store eax at m
        call    ReadInt                 ; read int; value placed in eax
        mov     [I1],eax                ; store eax at n
        mov     eax,[I0]                ; load m in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I1]                ; load n in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I3]                ; AReg = 0
        mov     [I2],eax                ; cmp = AReg
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        jle     .L0                     ; if m <= n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L1                     ; unconditionally jump
.L0:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L1:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L2                     ; if T0 is false then jump to end of if
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        je      .L3                     ; if m = n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L4                     ; unconditionally jump
.L3:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L4:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L5                     ; if T0 is false then jump to end of if
        mov     eax,[I4]                ; AReg = 1
        mov     [I2],eax                ; cmp = AReg
        jmp     .L6                     ; jump to end if
.L5:                                    ; else
        mov     eax,[I5]                ; AReg = 2
        mov     [I2],eax                ; cmp = AReg
.L6:                                    ; end if
.L2:                                    ; end if
        mov     eax,[I2]                ; load cmp in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I3]                ; AReg = 0
        mov     [I2],eax                ; cmp = AReg
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        jle     .L7                     ; if m <= n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L8                     ; unconditionally jump
.L7:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L8:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L9                     ; if T0 is false then jump to end of if
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        je      .L10                    ; if m = n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L11                    ; unconditionally jump
.L10:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L11:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L12                    ; if T0 is false then jump to end of if
        mov     eax,[I4]                ; AReg = 1
        mov     [I2],eax                ; cmp = AReg
.L12:                                   ; end if
        jmp     .L13                    ; jump to end if
.L9:                                    ; else
        mov     eax,[I5]                ; AReg = 2
        mov     [I2],eax                ; cmp = AReg
.L13:                                   ; end if
        mov     eax,[I2]                ; load cmp in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        Exit    {0}
                    
SECTION .data                           
I3      dd      0                       ; 0
I4      dd      1                       ; 1
I5      dd      2                       ; 2
FALSE   dd      0                       ; false
TRUE    dd      -1                      ; true

SECTION .bss                            
I2      resd    1                       ; cmp
I0      resd    1                       ; m
I1      resd    1                       ; n
