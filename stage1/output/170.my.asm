; Kangmin Kim, Jeff Caldwell       Sun Nov 27 09:52:21 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                                   
global  _start                          ; program stage1no170

_start:                                         
        call    ReadInt                 ; read int; value placed in eax
        mov     [I1],eax                ; store eax at a
        mov     eax,[I6]                ; AReg = -5
        mov     [I4],eax                ; d = AReg
        neg     eax                     ; AReg = -AReg
        mov     [I4],eax                ; d = AReg
        neg     eax                     ; AReg = -AReg
        neg     eax                     ; AReg = -AReg
        neg     eax                     ; AReg = -AReg
        mov     [I4],eax                ; d = AReg
