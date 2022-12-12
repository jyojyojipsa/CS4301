; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no205

_start:                                 
        call    ReadInt                 ; read int; value placed in eax
        mov     [I0],eax                ; store eax at x
        call    ReadInt                 ; read int; value placed in eax
        mov     [I1],eax                ; store eax at y
.L0:                                    ; while
        mov     eax,[I0]                ; AReg = x
        cmp     eax,[I1]                ; compare x and y
        jg      .L1                     ; if x > y then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L2                     ; unconditionally jump
.L1:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L2:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L3                     ; if T0 is false then jump to end while
        mov     eax,[I0]                ; AReg = x
        sub     eax,[I2]                ; AReg = x - 3
        mov     [I0],eax                ; x = AReg
        jmp     .L0                     ; end while
.L3:                                    
        mov     eax,[I0]                ; load x in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I1]                ; load y in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        Exit    {0}
                    
SECTION .data                           
I2      dd      3                       ; 3
FALSE   dd      0                       ; false
TRUE    dd      -1                      ; true

SECTION .bss                            
I0      resd    1                       ; x
I1      resd    1                       ; y
