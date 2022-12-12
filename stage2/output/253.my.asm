; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program mytest

_start:                                 
        mov     eax,[I0]                ; AReg = s
        add     eax,[I4]                ; AReg = s + -3
        mov     [I2],eax                ; t = AReg
        mov     eax,[I1]                ; AReg = a
        add     eax,[I5]                ; AReg = a + 2
        mov     [I3],eax                ; b = AReg
        mov     eax,[I2]                ; load t in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I3]                ; load b in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        Exit    {0}
                    
SECTION .data                           
I4      dd      -3                      ; -3
I5      dd      2                       ; 2
I1      dd      2                       ; a
I0      dd      -3                      ; s

SECTION .bss                            
I3      resd    1                       ; b
I2      resd    1                       ; t
