; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no241

_start:                                 
        call    ReadInt                 ; read int; value placed in eax
        mov     [I1],eax                ; store eax at first
        call    ReadInt                 ; read int; value placed in eax
        mov     [I2],eax                ; store eax at second
        mov     eax,[I4]                ; AReg = 0
        mov     [I3],eax                ; ct = AReg
.L0:                                    ; while
        mov     eax,[I3]                ; AReg = ct
        cmp     eax,[I5]                ; compare ct and 47
        jl      .L1                     ; if ct < 47 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L2                     ; unconditionally jump
.L1:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L2:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L3                     ; if T0 is false then jump to end while
        mov     eax,[I1]                ; load first in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        add     eax,[I2]                ; AReg = first + second
        mov     [I2],eax                ; second = AReg
        sub     eax,[I1]                ; AReg = second - first
        mov     [I1],eax                ; first = AReg
        mov     eax,[I3]                ; AReg = ct
        add     eax,[I6]                ; AReg = ct + 1
        mov     [I3],eax                ; ct = AReg
        jmp     .L0                     ; end while
.L3:                                    
        Exit    {0}
                    
SECTION .data                           
I4      dd      0                       ; 0
I6      dd      1                       ; 1
I5      dd      47                      ; 47
FALSE   dd      0                       ; false
I0      dd      2147483647              ; largest
TRUE    dd      -1                      ; true

SECTION .bss                            
I3      resd    1                       ; ct
I1      resd    1                       ; first
I2      resd    1                       ; second
