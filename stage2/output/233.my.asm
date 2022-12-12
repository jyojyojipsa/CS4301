; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no233

_start:                                 
.L0:                                    ; repeat
        mov     eax,[FALSE]             ; AReg = FALSE
        cmp     eax,0                   ; compare eax to 0
        je      .L0                     ; until false is true
        Exit    {0}
                    
SECTION .data                           
FALSE   dd      0                       ; false

SECTION .bss                            
