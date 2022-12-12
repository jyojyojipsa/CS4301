; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no209

_start:                                 
        mov     eax,[I4]                ; AReg = 3
        mov     [I0],eax                ; a = AReg
        mov     eax,[I1]                ; AReg = b
        imul    dword [I2]              ; AReg = b * c
        add     eax,[I0]                ; AReg = T0 + a
        mov     [I3],eax                ; d = AReg
        mov     eax,[I0]                ; AReg = a
        imul    dword [I1]              ; AReg = a * b
        add     eax,[I2]                ; AReg = T0 + c
        mov     [I1],eax                ; b = AReg
        add     eax,[I0]                ; AReg = b + a
        add     eax,[I2]                ; AReg = T0 + c
        mov     [I0],eax                ; a = AReg
        imul    dword [I1]              ; AReg = a * b
        imul    dword [I2]              ; AReg = T0 * c
        mov     [I3],eax                ; d = AReg
        mov     eax,[I0]                ; AReg = a
        add     eax,[I1]                ; AReg = a + b
        mov     [I3],eax                ; d = AReg
        Exit    {0}
                    
SECTION .data                           
I4      dd      3                       ; 3

SECTION .bss                            
I0      resd    1                       ; a
I1      resd    1                       ; b
I2      resd    1                       ; c
I3      resd    1                       ; d
