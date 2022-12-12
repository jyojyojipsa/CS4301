; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no234

_start:                                 
.L0:                                    ; repeat
        mov     eax,[TRUE]              ; AReg = TRUE
        cmp     eax,0                   ; compare eax to 0
        je      .L0                     ; until true is true
        Exit    {0}
                    
SECTION .data                           
TRUE    dd      -1                      ; true

SECTION .bss                            
