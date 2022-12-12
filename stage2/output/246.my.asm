; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no246

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
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        jl      .L0                     ; if m < n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L1                     ; unconditionally jump
.L0:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L1:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L2                     ; if T0 is false then jump to end of if
        mov     eax,[I3]                ; AReg = -1
        mov     [I2],eax                ; cmp = AReg
        jmp     .L3                     ; jump to end if
.L2:                                    ; else
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        je      .L4                     ; if m = n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L5                     ; unconditionally jump
.L4:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L5:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L6                     ; if T0 is false then jump to end of if
        mov     eax,[I4]                ; AReg = 0
        mov     [I2],eax                ; cmp = AReg
        jmp     .L7                     ; jump to end if
.L6:                                    ; else
        mov     eax,[I5]                ; AReg = 1
        mov     [I2],eax                ; cmp = AReg
.L7:                                    ; end if
.L3:                                    ; end if
        mov     eax,[I2]                ; load cmp in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        Exit    {0}
                    
SECTION .data                           
I3      dd      -1                      ; -1
I4      dd      0                       ; 0
I5      dd      1                       ; 1
FALSE   dd      0                       ; false
TRUE    dd      -1                      ; true

SECTION .bss                            
I2      resd    1                       ; cmp
I0      resd    1                       ; m
I1      resd    1                       ; n
