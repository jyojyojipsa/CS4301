; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no242

_start:                                 
        call    ReadInt                 ; read int; value placed in eax
        mov     [I0],eax                ; store eax at m
        call    ReadInt                 ; read int; value placed in eax
        mov     [I1],eax                ; store eax at n
        mov     eax,[I0]                ; load m in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I1]                ; load n in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I3]                ; compare m and 0
        jl      .L0                     ; if m < 0 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L1                     ; unconditionally jump
.L0:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L1:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L2                     ; if T0 is false then jump to end of if
        mov     eax,[I4]                ; AReg = -1
        imul    dword [I0]              ; AReg = -1 * m
        mov     [I0],eax                ; m = AReg
.L2:                                    ; end if
        mov     eax,[I1]                ; AReg = n
        cmp     eax,[I3]                ; compare n and 0
        jl      .L3                     ; if n < 0 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L4                     ; unconditionally jump
.L3:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L4:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L5                     ; if T0 is false then jump to end of if
        mov     eax,[I1]                ; AReg = n
        neg     eax                     ; AReg = -AReg
        mov     [I1],eax                ; n = AReg
.L5:                                    ; end if
        mov     eax,[I0]                ; AReg = m
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I1]              ; AReg = m div n
        xchg    eax,edx                 ; exchange quotient and remainder
        mov     [I2],eax                ; rem = AReg
.L6:                                    ; while
        mov     eax,[I2]                ; AReg = rem
        cmp     eax,[I3]                ; compare rem and 0
        je      .L7                     ; if rem = 0 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L8                     ; unconditionally jump
.L7:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L8:                                    
        not     eax                     ; AReg = !AReg
        cmp     eax,0                   ; compare eax to 0
        je      .L9                     ; if T0 is false then jump to end while
        mov     eax,[I1]                ; AReg = n
        mov     [I0],eax                ; m = AReg
        mov     eax,[I2]                ; AReg = rem
        mov     [I1],eax                ; n = AReg
        mov     eax,[I0]                ; AReg = m
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I1]              ; AReg = m div n
        xchg    eax,edx                 ; exchange quotient and remainder
        mov     [I2],eax                ; rem = AReg
        jmp     .L6                     ; end while
.L9:                                    
        mov     eax,[I1]                ; load n in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        Exit    {0}
                    
SECTION .data                           
I4      dd      -1                      ; -1
I3      dd      0                       ; 0
FALSE   dd      0                       ; false
TRUE    dd      -1                      ; true

SECTION .bss                            
I0      resd    1                       ; m
I1      resd    1                       ; n
I2      resd    1                       ; rem
