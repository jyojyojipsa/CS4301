; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no228

_start:                                 
        mov     eax,[I1]                ; AReg = 0
        mov     [I0],eax                ; a = AReg
        mov     eax,[FALSE]             ; AReg = false
        cmp     eax,0                   ; compare eax to 0
        je      .L0                     ; if false is false then jump to end of if
        jmp     .L1                     ; jump to end if
.L0:                                    ; else
        mov     eax,[I2]                ; AReg = 1
        mov     [I0],eax                ; a = AReg
.L1:                                    ; end if
        mov     eax,[I0]                ; load a in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        Exit    {0}
                    
SECTION .data                           
I1      dd      0                       ; 0
I2      dd      1                       ; 1
FALSE   dd      0                       ; false

SECTION .bss                            
I0      resd    1                       ; a
