; Kangmin Kim, Jeff Caldwell       Sun Nov 27 09:52:21 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                                   
global  _start                          ; program stage1no171

_start:                                         
        mov     eax,[B0]                ; AReg = x
        not     eax                     ; AReg = !AReg
        mov     [B1],eax                ; d = AReg
        mov     eax,[FALSE]             ; AReg = false
        mov     [B1],eax                ; d = AReg
        mov     eax,[TRUE]              ; AReg = true
        mov     [B1],eax                ; d = AReg
        mov     eax,[B0]                ; AReg = x
        not     eax                     ; AReg = !AReg
        not     eax                     ; AReg = !AReg
        not     eax                     ; AReg = !AReg
        mov     [B1],eax                ; d = AReg
