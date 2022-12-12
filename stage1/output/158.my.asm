; Kangmin Kim, Jeff Caldwell       Sun Nov 27 09:52:21 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                                   
global  _start                          ; program stage1no158

_start:                                         
        call    ReadInt                 ; read int; value placed in eax
        mov     [I4],eax                ; store eax at i
        call    ReadInt                 ; read int; value placed in eax
        mov     [I5],eax                ; store eax at j
