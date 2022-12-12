; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no216

_start:                                 
        mov     eax,[I3]                ; AReg = 24
        mov     [I0],eax                ; x = AReg
        cmp     eax,[I4]                ; compare x and 0
        jg      .L0                     ; if x > 0 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L1                     ; unconditionally jump
.L0:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L1:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L2                     ; if T0 is false then jump to end of if
        mov     eax,[I4]                ; AReg = 0
        mov     [I2],eax                ; z = AReg
        jmp     .L3                     ; jump to end if
.L2:                                    ; else
.L3:                                    ; end if
.L4:                                    ; while
        mov     eax,[I0]                ; AReg = x
        cmp     eax,[I1]                ; compare x and y
        jg      .L5                     ; if x > y then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L6                     ; unconditionally jump
.L5:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L6:                                    
