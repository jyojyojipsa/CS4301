; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no221

_start:                                 
        call    ReadInt                 ; read int; value placed in eax
        mov     [I1],eax                ; store eax at b
        call    ReadInt                 ; read int; value placed in eax
        mov     [I2],eax                ; store eax at c
        call    ReadInt                 ; read int; value placed in eax
        mov     [I3],eax                ; store eax at d
        call    ReadInt                 ; read int; value placed in eax
        mov     [I4],eax                ; store eax at e
        mov     eax,[I0]                ; AReg = a
        cmp     eax,[I1]                ; compare a and b
        jl      .L0                     ; if a < b then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L1                     ; unconditionally jump
.L0:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L1:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L2                     ; if T0 is false then jump to end of if
        mov     eax,[I1]                ; AReg = b
        add     eax,[I2]                ; AReg = b + c
        mov     [T0],eax                ; deassign AReg
        mov     eax,[I2]                ; AReg = c
        add     eax,[I3]                ; AReg = c + d
        mov     [T1],eax                ; deassign AReg
        mov     eax,[I3]                ; AReg = d
        add     eax,[I4]                ; AReg = d + e
        add     eax,[T1]                ; AReg = T2 + T1
        add     eax,[T0]                ; AReg = T1 + T0
        mov     [I0],eax                ; a = AReg
        jmp     .L3                     ; jump to end if
.L2:                                    ; else
        mov     eax,[I0]                ; AReg = a
        add     eax,[I2]                ; AReg = a + c
        mov     [I1],eax                ; b = AReg
.L3:                                    ; end if
        mov     eax,[I0]                ; load a in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I1]                ; load b in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I2]                ; load c in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I3]                ; load d in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I4]                ; load e in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        Exit    {0}
                    
SECTION .data                           
FALSE   dd      0                       ; false
TRUE    dd      -1                      ; true

SECTION .bss                            
T0      resd    1                       ; T0
T1      resd    1                       ; T1
I0      resd    1                       ; a
I1      resd    1                       ; b
I2      resd    1                       ; c
I3      resd    1                       ; d
I4      resd    1                       ; e
