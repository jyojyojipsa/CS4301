; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no223

_start:                                 
        call    ReadInt                 ; read int; value placed in eax
        mov     [I1],eax                ; store eax at month
        call    ReadInt                 ; read int; value placed in eax
        mov     [I2],eax                ; store eax at year
        mov     eax,[I1]                ; AReg = month
        cmp     eax,[I3]                ; compare month and 1
        je      .L0                     ; if month = 1 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L1                     ; unconditionally jump
.L0:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L1:                                    
        mov     [T0],eax                ; deassign AReg
        mov     eax,[I1]                ; AReg = month
        cmp     eax,[I4]                ; compare month and 2
        je      .L2                     ; if month = 2 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L3                     ; unconditionally jump
.L2:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L3:                                    
        or      eax,[T0]                ; AReg = T1 or T0
        cmp     eax,0                   ; compare eax to 0
        je      .L4                     ; if T0 is false then jump to end of if
        mov     eax,[I1]                ; AReg = month
        add     eax,[I5]                ; AReg = month + 10
        mov     [I0],eax                ; a = AReg
        mov     eax,[I2]                ; AReg = year
        sub     eax,[I3]                ; AReg = year - 1
        mov     [I2],eax                ; year = AReg
        jmp     .L5                     ; jump to end if
.L4:                                    ; else
        mov     eax,[I1]                ; AReg = month
        sub     eax,[I4]                ; AReg = month - 2
        mov     [I0],eax                ; a = AReg
        mov     eax,[I2]                ; AReg = year
        add     eax,[I3]                ; AReg = year + 1
        mov     [I2],eax                ; year = AReg
.L5:                                    ; end if
        mov     eax,[I0]                ; load a in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I1]                ; load month in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I2]                ; load year in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        Exit    {0}
                    
SECTION .data                           
I3      dd      1                       ; 1
I5      dd      10                      ; 10
I4      dd      2                       ; 2
FALSE   dd      0                       ; false
TRUE    dd      -1                      ; true

SECTION .bss                            
T0      resd    1                       ; T0
I0      resd    1                       ; a
I1      resd    1                       ; month
I2      resd    1                       ; year
