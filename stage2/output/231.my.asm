; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no231

_start:                                 
.L0:                                    ; while
        mov     eax,[FALSE]             ; AReg = false
        cmp     eax,0                   ; compare eax to 0
        je      .L1                     ; if false is false then jump to end while
        jmp     .L0                     ; end while
.L1:                                    
        mov     eax,[I0]                ; load month in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        Exit    {0}
                    
SECTION .data                           
FALSE   dd      0                       ; false
I0      dd      12                      ; month

SECTION .bss                            
