; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no239

_start:                                 
        mov     eax,[I16]               ; AReg = 0
        mov     [I15],eax               ; counter = AReg
.L0:                                    ; repeat
        call    ReadInt                 ; read int; value placed in eax
        mov     [I0],eax                ; store eax at x
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I17]             ; AReg = x div 19
        xchg    eax,edx                 ; exchange quotient and remainder
        mov     [I1],eax                ; a = AReg
        mov     eax,[I0]                ; AReg = x
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I18]             ; AReg = x div 100
        mov     [I2],eax                ; b = AReg
        mov     eax,[I0]                ; AReg = x
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I18]             ; AReg = x div 100
        xchg    eax,edx                 ; exchange quotient and remainder
        mov     [I3],eax                ; c = AReg
        mov     eax,[I2]                ; AReg = b
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I19]             ; AReg = b div 4
        mov     [I4],eax                ; d = AReg
        mov     eax,[I2]                ; AReg = b
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I19]             ; AReg = b div 4
        xchg    eax,edx                 ; exchange quotient and remainder
        mov     [I5],eax                ; e = AReg
        mov     eax,[I2]                ; AReg = b
        add     eax,[I20]               ; AReg = b + 8
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I21]             ; AReg = T0 div 25
        mov     [I6],eax                ; f = AReg
        mov     eax,[I2]                ; AReg = b
        sub     eax,[I6]                ; AReg = b - f
        add     eax,[I22]               ; AReg = T0 + 1
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I23]             ; AReg = T0 div 3
        mov     [I7],eax                ; g = AReg
        mov     eax,[I17]               ; AReg = 19
        imul    dword [I1]              ; AReg = 19 * a
        add     eax,[I2]                ; AReg = T0 + b
        sub     eax,[I4]                ; AReg = T0 - d
        sub     eax,[I7]                ; AReg = T0 - g
        add     eax,[I24]               ; AReg = T0 + 15
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I25]             ; AReg = T0 div 30
        xchg    eax,edx                 ; exchange quotient and remainder
        mov     [I8],eax                ; h = AReg
        mov     eax,[I3]                ; AReg = c
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I19]             ; AReg = c div 4
        mov     [I9],eax                ; i = AReg
        mov     eax,[I3]                ; AReg = c
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I19]             ; AReg = c div 4
        xchg    eax,edx                 ; exchange quotient and remainder
        mov     [I10],eax               ; k = AReg
        mov     eax,[I27]               ; AReg = 2
        imul    dword [I5]              ; AReg = 2 * e
        add     eax,[I26]               ; AReg = T0 + 32
        mov     [T0],eax                ; deassign AReg
        mov     eax,[I27]               ; AReg = 2
        imul    dword [I9]              ; AReg = 2 * i
        add     eax,[T0]                ; AReg = T1 + T0
        sub     eax,[I8]                ; AReg = T0 - h
        sub     eax,[I10]               ; AReg = T0 - k
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I28]             ; AReg = T0 div 7
        xchg    eax,edx                 ; exchange quotient and remainder
        mov     [I11],eax               ; l = AReg
        mov     eax,[I29]               ; AReg = 11
        imul    dword [I8]              ; AReg = 11 * h
        add     eax,[I1]                ; AReg = T0 + a
        mov     [T0],eax                ; deassign AReg
        mov     eax,[I30]               ; AReg = 22
        imul    dword [I11]             ; AReg = 22 * l
        add     eax,[T0]                ; AReg = T1 + T0
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I31]             ; AReg = T0 div 451
        mov     [I12],eax               ; m = AReg
        mov     eax,[I8]                ; AReg = h
        add     eax,[I11]               ; AReg = h + l
        mov     [T0],eax                ; deassign AReg
        mov     eax,[I28]               ; AReg = 7
        imul    dword [I12]             ; AReg = 7 * m
        mov     [T1],eax                ; deassign AReg
        mov     eax,[T0]                ; AReg = T0
        sub     eax,[T1]                ; AReg = T0 - T1
        add     eax,[I32]               ; AReg = T0 + 114
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I33]             ; AReg = T0 div 31
        mov     [I13],eax               ; n = AReg
        mov     eax,[I8]                ; AReg = h
        add     eax,[I11]               ; AReg = h + l
        mov     [T0],eax                ; deassign AReg
        mov     eax,[I28]               ; AReg = 7
        imul    dword [I12]             ; AReg = 7 * m
        mov     [T1],eax                ; deassign AReg
        mov     eax,[T0]                ; AReg = T0
        sub     eax,[T1]                ; AReg = T0 - T1
        add     eax,[I32]               ; AReg = T0 + 114
        cdq                             ; sign extend dividend from eax to edx:eax
        idiv    dword [I33]             ; AReg = T0 div 31
        xchg    eax,edx                 ; exchange quotient and remainder
        mov     [I14],eax               ; p = AReg
        mov     eax,[I13]               ; load n in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I14]               ; AReg = p
        add     eax,[I22]               ; AReg = p + 1
        mov     [I14],eax               ; p = AReg
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I0]                ; load x in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I15]               ; AReg = counter
        add     eax,[I22]               ; AReg = counter + 1
        mov     [I15],eax               ; counter = AReg
        cmp     eax,[I34]               ; compare counter and 40
        je      .L1                     ; if counter = 40 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L2                     ; unconditionally jump
.L1:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L2:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L0                     ; until T0 is true
        Exit    {0}
                    
SECTION .data                           
I16     dd      0                       ; 0
I22     dd      1                       ; 1
I18     dd      100                     ; 100
I29     dd      11                      ; 11
I32     dd      114                     ; 114
I24     dd      15                      ; 15
I17     dd      19                      ; 19
I27     dd      2                       ; 2
I30     dd      22                      ; 22
I21     dd      25                      ; 25
I23     dd      3                       ; 3
I25     dd      30                      ; 30
I33     dd      31                      ; 31
I26     dd      32                      ; 32
I19     dd      4                       ; 4
I34     dd      40                      ; 40
I31     dd      451                     ; 451
I28     dd      7                       ; 7
I20     dd      8                       ; 8
FALSE   dd      0                       ; false
TRUE    dd      -1                      ; true

SECTION .bss                            
T0      resd    1                       ; T0
T1      resd    1                       ; T1
I1      resd    1                       ; a
I2      resd    1                       ; b
I3      resd    1                       ; c
I15     resd    1                       ; counter
I4      resd    1                       ; d
I5      resd    1                       ; e
I6      resd    1                       ; f
I7      resd    1                       ; g
I8      resd    1                       ; h
I9      resd    1                       ; i
I10     resd    1                       ; k
I11     resd    1                       ; l
I12     resd    1                       ; m
I13     resd    1                       ; n
I14     resd    1                       ; p
I0      resd    1                       ; x
