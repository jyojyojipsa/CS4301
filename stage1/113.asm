; Kangmin Kim, Jeff Caldwell       Sun Nov 27 09:19:53 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                                   
global  _start                          ; program stage1no113

_start:                                         
        mov     eax,[I1]                ; AReg = five
        imul    dword [I2]              ; AReg = five * a
