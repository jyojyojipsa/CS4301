; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no213

_start:                                 
        mov     eax,[B0]                ; AReg = why
        cmp     eax,0                   ; compare eax to 0
        je      .L0                     ; if why is false then jump to end of if
        mov     eax,[I3]                ; AReg = 0
        mov     [I2],eax                ; z = AReg
        jmp     .L1                     ; jump to end if
.L0:                                    ; else
        mov     eax,[I4]                ; AReg = -3
        mov     [I2],eax                ; z = AReg
.L1:                                    ; end if
.L2:                                    ; while
        mov     eax,[B0]                ; AReg = why
        cmp     eax,0                   ; compare eax to 0
        je      .L3                     ; if why is false then jump to end while
        mov     eax,[I1]                ; AReg = y
        add     eax,[I5]                ; AReg = y + 2
        mov     [I0],eax                ; x = AReg
        cmp     eax,[I6]                ; compare x and 3
        je      .L4                     ; if x = 3 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L5                     ; unconditionally jump
.L4:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L5:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L6                     ; if T0 is false then jump to end of if
.L6:                                    ; end if
        jmp     .L2                     ; end while
.L3:                                    
