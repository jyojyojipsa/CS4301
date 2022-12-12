; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no227

_start:                                 
        mov     eax,[I1]                ; AReg = 0
        mov     [I0],eax                ; a = AReg
        mov     eax,[TRUE]              ; AReg = true
        cmp     eax,0                   ; compare eax to 0
        je      .L0                     ; if true is false then jump to end of if
        mov     eax,[I2]                ; AReg = 1
        mov     [I0],eax                ; a = AReg
.L0:                                    ; end if
        mov     eax,[I0]                ; load a in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        Exit    {0}
                    
SECTION .data                           
I1      dd      0                       ; 0
I2      dd      1                       ; 1
TRUE    dd      -1                      ; true

SECTION .bss                            
I0      resd    1                       ; a
