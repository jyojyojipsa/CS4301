; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no240

_start:                                 
        call    ReadInt                 ; read int; value placed in eax
        mov     [I0],eax                ; store eax at h
.L0:                                    ; while
        mov     eax,[I0]                ; AReg = h
        cmp     eax,[I5]                ; compare h and 0
        jg      .L1                     ; if h > 0 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L2                     ; unconditionally jump
.L1:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L2:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L3                     ; if T0 is false then jump to end while
        call    ReadInt                 ; read int; value placed in eax
        mov     [I1],eax                ; store eax at u
        call    ReadInt                 ; read int; value placed in eax
        mov     [I2],eax                ; store eax at v
        mov     eax,[I1]                ; load u in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I2]                ; load v in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I1]                ; AReg = u
        cmp     eax,[I5]                ; compare u and 0
        jl      .L4                     ; if u < 0 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L5                     ; unconditionally jump
.L4:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L5:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L6                     ; if T0 is false then jump to end of if
        mov     eax,[I1]                ; AReg = u
        imul    dword [I6]              ; AReg = u * -1
        mov     [I1],eax                ; u = AReg
.L6:                                    ; end if
        mov     eax,[I2]                ; AReg = v
        cmp     eax,[I5]                ; compare v and 0
        jl      .L7                     ; if v < 0 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L8                     ; unconditionally jump
.L7:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L8:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L9                     ; if T0 is false then jump to end of if
        mov     eax,[I2]                ; AReg = v
        imul    dword [I6]              ; AReg = v * -1
        mov     [I2],eax                ; v = AReg
.L9:                                    ; end if
        mov     eax,[I1]                ; AReg = u
        cmp     eax,[I5]                ; compare u and 0
        je      .L10                    ; if u = 0 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L11                    ; unconditionally jump
.L10:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L11:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L12                    ; if T0 is false then jump to end of if
        mov     eax,[I2]                ; AReg = v
        mov     [I3],eax                ; gcd = AReg
        jmp     .L13                    ; jump to end if
.L12:                                   ; else
        mov     eax,[I2]                ; AReg = v
        cmp     eax,[I5]                ; compare v and 0
        je      .L14                    ; if v = 0 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L15                    ; unconditionally jump
.L14:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L15:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L16                    ; if T0 is false then jump to end of if
        mov     eax,[I1]                ; AReg = u
        mov     [I3],eax                ; gcd = AReg
        jmp     .L17                    ; jump to end if
.L16:                                   ; else
.L18:                                   ; repeat
        mov     eax,[I1]                ; AReg = u
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I2]              ; AReg = u div v
        xchg    eax,edx                 ; exchange quotient and remainder
        mov     [I4],eax                ; rem = AReg
        mov     eax,[I2]                ; AReg = v
        mov     [I1],eax                ; u = AReg
        mov     eax,[I4]                ; AReg = rem
        mov     [I2],eax                ; v = AReg
        mov     eax,[I4]                ; AReg = rem
        cmp     eax,[I5]                ; compare rem and 0
        je      .L19                    ; if rem = 0 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L20                    ; unconditionally jump
.L19:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L20:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L18                    ; until T0 is true
        mov     eax,[I1]                ; AReg = u
        mov     [I3],eax                ; gcd = AReg
.L17:                                   ; end if
.L13:                                   ; end if
        mov     eax,[I3]                ; load gcd in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I0]                ; AReg = h
        sub     eax,[I7]                ; AReg = h - 1
        mov     [I0],eax                ; h = AReg
        jmp     .L0                     ; end while
.L3:                                    
        Exit    {0}
                    
SECTION .data                           
I6      dd      -1                      ; -1
I5      dd      0                       ; 0
I7      dd      1                       ; 1
FALSE   dd      0                       ; false
TRUE    dd      -1                      ; true

SECTION .bss                            
I3      resd    1                       ; gcd
I0      resd    1                       ; h
I4      resd    1                       ; rem
I1      resd    1                       ; u
I2      resd    1                       ; v
