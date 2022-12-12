; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no235

_start:                                 
        mov     eax,[I1]                ; AReg = 0
        mov     [I0],eax                ; t = AReg
.L0:                                    ; repeat
        mov     eax,[I2]                ; AReg = 1
        mov     [I0],eax                ; t = AReg
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
