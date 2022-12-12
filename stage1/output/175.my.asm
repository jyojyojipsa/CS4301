; Kangmin Kim, Jeff Caldwell       Sun Nov 27 09:52:21 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                                   
global  _start                          ; program stage1no175

_start:                                         
        call    ReadInt                 ; read int; value placed in eax
        mov     [I1],eax                ; store eax at a
        call    ReadInt                 ; read int; value placed in eax
        mov     [I2],eax                ; store eax at b
        mov     eax,[I1]                ; AReg = a
        neg     eax                     ; AReg = -AReg
        mov     [T0],eax                ; deassign AReg
        mov     eax,[I2]                ; AReg = b
        neg     eax                     ; AReg = -AReg
        cmp     eax,[T0]                ; compare T1 and T0
        jl      .L0                     ; if T1 < T0 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L1                     ; unconditionally jump
.L0:                                            
        mov     eax,[TRUE]              ; set eax to TRUE
.L1:                                            
        mov     [B1],eax                ; d = AReg
        mov     eax,[I1]                ; AReg = a
        neg     eax                     ; AReg = -AReg
        cmp     eax,[I2]                ; compare T0 and b
        jl      .L2                     ; if T0 < b then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L3                     ; unconditionally jump
.L2:                                            
        mov     eax,[TRUE]              ; set eax to TRUE
.L3:                                            
        mov     [B1],eax                ; d = AReg
        mov     eax,[I1]                ; AReg = a
        neg     eax                     ; AReg = -AReg
        cmp     eax,[I2]                ; compare T0 and b
        jl      .L4                     ; if T0 < b then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L5                     ; unconditionally jump
.L4:                                            
        mov     eax,[TRUE]              ; set eax to TRUE
.L5:                                            
        mov     [B1],eax                ; d = AReg
        mov     eax,[I2]                ; AReg = b
        neg     eax                     ; AReg = -AReg
        cmp     eax,[I1]                ; compare T0 and a
        jl      .L6                     ; if T0 < a then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L7                     ; unconditionally jump
.L6:                                            
        mov     eax,[TRUE]              ; set eax to TRUE
.L7:                                            
        mov     [B1],eax                ; d = AReg
        mov     eax,[I1]                ; AReg = a
        cmp     eax,[I2]                ; compare a and b
        jl      .L8                     ; if a < b then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L9                     ; unconditionally jump
.L8:                                            
        mov     eax,[TRUE]              ; set eax to TRUE
.L9:                                            
        mov     [B1],eax                ; d = AReg
        mov     eax,[I1]                ; AReg = a
        cmp     eax,[I2]                ; compare a and b
        jl      .L10                    ; if a < b then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L11                    ; unconditionally jump
.L10:                                           
        mov     eax,[TRUE]              ; set eax to TRUE
.L11:                                           
        mov     [B1],eax                ; d = AReg
        mov     eax,[I2]                ; AReg = b
        neg     eax                     ; AReg = -AReg
        cmp     eax,[I1]                ; compare T0 and a
        jl      .L12                    ; if T0 < a then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L13                    ; unconditionally jump
.L12:                                           
        mov     eax,[TRUE]              ; set eax to TRUE
.L13:                                           
        mov     [B1],eax                ; d = AReg
        mov     eax,[I1]                ; AReg = a
        cmp     eax,[I2]                ; compare a and b
        jl      .L14                    ; if a < b then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L15                    ; unconditionally jump
.L14:                                           
        mov     eax,[TRUE]              ; set eax to TRUE
.L15:                                           
        mov     [B1],eax                ; d = AReg
        mov     eax,[I1]                ; AReg = a
        cmp     eax,[I2]                ; compare a and b
        jl      .L16                    ; if a < b then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L17                    ; unconditionally jump
.L16:                                           
        mov     eax,[TRUE]              ; set eax to TRUE
.L17:                                           
        mov     [B1],eax                ; d = AReg
        mov     eax,[I3]                ; AReg = -4301
        cmp     eax,[I3]                ; compare -4301 and -4301
        jl      .L18                    ; if -4301 < -4301 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L19                    ; unconditionally jump
.L18:                                           
        mov     eax,[TRUE]              ; set eax to TRUE
.L19:                                           
        mov     [B1],eax                ; d = AReg
        mov     eax,[I3]                ; AReg = -4301
        cmp     eax,[I4]                ; compare -4301 and 4301
        jl      .L20                    ; if -4301 < 4301 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L21                    ; unconditionally jump
.L20:                                           
        mov     eax,[TRUE]              ; set eax to TRUE
.L21:                                           
        mov     [B1],eax                ; d = AReg
        mov     eax,[I3]                ; AReg = -4301
        cmp     eax,[I4]                ; compare -4301 and 4301
        jl      .L22                    ; if -4301 < 4301 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L23                    ; unconditionally jump
.L22:                                           
        mov     eax,[TRUE]              ; set eax to TRUE
.L23:                                           
        mov     [B1],eax                ; d = AReg
        mov     eax,[I4]                ; AReg = 4301
        cmp     eax,[I3]                ; compare 4301 and -4301
        jl      .L24                    ; if 4301 < -4301 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L25                    ; unconditionally jump
.L24:                                           
        mov     eax,[TRUE]              ; set eax to TRUE
.L25:                                           
        mov     [B1],eax                ; d = AReg
        mov     eax,[I4]                ; AReg = 4301
        cmp     eax,[I4]                ; compare 4301 and 4301
        jl      .L26                    ; if 4301 < 4301 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L27                    ; unconditionally jump
.L26:                                           
        mov     eax,[TRUE]              ; set eax to TRUE
.L27:                                           
        mov     [B1],eax                ; d = AReg
        mov     eax,[I4]                ; AReg = 4301
        cmp     eax,[I4]                ; compare 4301 and 4301
        jl      .L28                    ; if 4301 < 4301 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L29                    ; unconditionally jump
.L28:                                           
        mov     eax,[TRUE]              ; set eax to TRUE
.L29:                                           
        mov     [B1],eax                ; d = AReg
        mov     eax,[I4]                ; AReg = 4301
        cmp     eax,[I3]                ; compare 4301 and -4301
        jl      .L30                    ; if 4301 < -4301 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L31                    ; unconditionally jump
.L30:                                           
        mov     eax,[TRUE]              ; set eax to TRUE
.L31:                                           
        mov     [B1],eax                ; d = AReg
        mov     eax,[I4]                ; AReg = 4301
        cmp     eax,[I4]                ; compare 4301 and 4301
        jl      .L32                    ; if 4301 < 4301 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L33                    ; unconditionally jump
.L32:                                           
        mov     eax,[TRUE]              ; set eax to TRUE
.L33:                                           
        mov     [B1],eax                ; d = AReg
        mov     eax,[I4]                ; AReg = 4301
        cmp     eax,[I4]                ; compare 4301 and 4301
        jl      .L34                    ; if 4301 < 4301 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L35                    ; unconditionally jump
.L34:                                           
        mov     eax,[TRUE]              ; set eax to TRUE
.L35:                                           
        mov     [B1],eax                ; d = AReg
