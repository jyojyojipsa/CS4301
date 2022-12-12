; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no232

_start:                                 
        mov     eax,[I2]                ; AReg = 0
        mov     [I0],eax                ; a = AReg
.L0:                                    ; repeat
        mov     eax,[I0]                ; AReg = a
        add     eax,[I3]                ; AReg = a + 1
        mov     [I0],eax                ; a = AReg
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        cmp     eax,[I4]                ; compare a and 10
        je      .L1                     ; if a = 10 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L2                     ; unconditionally jump
.L1:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L2:                                    
        mov     [B0],eax                ; f = AReg
        mov     eax,[I0]                ; AReg = a
        mov     [I1],eax                ; b = AReg
        mov     eax,[B0]                ; AReg = B0
        cmp     eax,0                   ; compare eax to 0
        je      .L0                     ; until f is true
        Exit    {0}
                    
SECTION .data                           
I2      dd      0                       ; 0
I3      dd      1                       ; 1
I4      dd      10                      ; 10
FALSE   dd      0                       ; false
TRUE    dd      -1                      ; true

SECTION .bss                            
I0      resd    1                       ; a
I1      resd    1                       ; b
B0      resd    1                       ; f
