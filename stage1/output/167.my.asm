; Kangmin Kim, Jeff Caldwell       Sun Nov 27 09:52:21 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                                   
global  _start                          ; program stage1no167

_start:                                         
        call    ReadInt                 ; read int; value placed in eax
        mov     [I1],eax                ; store eax at a
