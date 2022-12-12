; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no249

_start:                                 
        call    ReadInt                 ; read int; value placed in eax
        mov     [I3],eax                ; store eax at v0
        call    ReadInt                 ; read int; value placed in eax
        mov     [I4],eax                ; store eax at v1
        call    ReadInt                 ; read int; value placed in eax
        mov     [I5],eax                ; store eax at v2
        call    ReadInt                 ; read int; value placed in eax
        mov     [I6],eax                ; store eax at v3
        call    ReadInt                 ; read int; value placed in eax
        mov     [I7],eax                ; store eax at v4
        call    ReadInt                 ; read int; value placed in eax
        mov     [I8],eax                ; store eax at v5
        call    ReadInt                 ; read int; value placed in eax
        mov     [I9],eax                ; store eax at v6
        call    ReadInt                 ; read int; value placed in eax
        mov     [I10],eax               ; store eax at v7
        call    ReadInt                 ; read int; value placed in eax
        mov     [I11],eax               ; store eax at v8
        call    ReadInt                 ; read int; value placed in eax
        mov     [I12],eax               ; store eax at v9
        mov     eax,[I3]                ; load v0 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I4]                ; load v1 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I5]                ; load v2 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I6]                ; load v3 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I7]                ; load v4 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I8]                ; load v5 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I9]                ; load v6 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I10]               ; load v7 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I11]               ; load v8 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I12]               ; load v9 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I13]               ; AReg = 0
        mov     [I1],eax                ; pass = AReg
.L0:                                    ; while
        mov     eax,[I1]                ; AReg = pass
        cmp     eax,[I0]                ; compare pass and n
        jl      .L1                     ; if pass < n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L2                     ; unconditionally jump
.L1:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L2:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L3                     ; if T0 is false then jump to end while
        mov     eax,[I3]                ; AReg = v0
        cmp     eax,[I4]                ; compare v0 and v1
        jg      .L4                     ; if v0 > v1 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L5                     ; unconditionally jump
.L4:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L5:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L6                     ; if T0 is false then jump to end of if
        mov     eax,[I3]                ; AReg = v0
        mov     [I2],eax                ; temp = AReg
        mov     eax,[I4]                ; AReg = v1
        mov     [I3],eax                ; v0 = AReg
        mov     eax,[I2]                ; AReg = temp
        mov     [I4],eax                ; v1 = AReg
.L6:                                    ; end if
        mov     eax,[I4]                ; AReg = v1
        cmp     eax,[I5]                ; compare v1 and v2
        jg      .L7                     ; if v1 > v2 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L8                     ; unconditionally jump
.L7:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L8:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L9                     ; if T0 is false then jump to end of if
        mov     eax,[I4]                ; AReg = v1
        mov     [I2],eax                ; temp = AReg
        mov     eax,[I5]                ; AReg = v2
        mov     [I4],eax                ; v1 = AReg
        mov     eax,[I2]                ; AReg = temp
        mov     [I5],eax                ; v2 = AReg
.L9:                                    ; end if
        mov     eax,[I5]                ; AReg = v2
        cmp     eax,[I6]                ; compare v2 and v3
        jg      .L10                    ; if v2 > v3 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L11                    ; unconditionally jump
.L10:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L11:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L12                    ; if T0 is false then jump to end of if
        mov     eax,[I5]                ; AReg = v2
        mov     [I2],eax                ; temp = AReg
        mov     eax,[I6]                ; AReg = v3
        mov     [I5],eax                ; v2 = AReg
        mov     eax,[I2]                ; AReg = temp
        mov     [I6],eax                ; v3 = AReg
.L12:                                   ; end if
        mov     eax,[I6]                ; AReg = v3
        cmp     eax,[I7]                ; compare v3 and v4
        jg      .L13                    ; if v3 > v4 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L14                    ; unconditionally jump
.L13:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L14:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L15                    ; if T0 is false then jump to end of if
        mov     eax,[I6]                ; AReg = v3
        mov     [I2],eax                ; temp = AReg
        mov     eax,[I7]                ; AReg = v4
        mov     [I6],eax                ; v3 = AReg
        mov     eax,[I2]                ; AReg = temp
        mov     [I7],eax                ; v4 = AReg
.L15:                                   ; end if
        mov     eax,[I7]                ; AReg = v4
        cmp     eax,[I8]                ; compare v4 and v5
        jg      .L16                    ; if v4 > v5 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L17                    ; unconditionally jump
.L16:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L17:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L18                    ; if T0 is false then jump to end of if
        mov     eax,[I7]                ; AReg = v4
        mov     [I2],eax                ; temp = AReg
        mov     eax,[I8]                ; AReg = v5
        mov     [I7],eax                ; v4 = AReg
        mov     eax,[I2]                ; AReg = temp
        mov     [I8],eax                ; v5 = AReg
.L18:                                   ; end if
        mov     eax,[I8]                ; AReg = v5
        cmp     eax,[I9]                ; compare v5 and v6
        jg      .L19                    ; if v5 > v6 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L20                    ; unconditionally jump
.L19:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L20:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L21                    ; if T0 is false then jump to end of if
        mov     eax,[I8]                ; AReg = v5
        mov     [I2],eax                ; temp = AReg
        mov     eax,[I9]                ; AReg = v6
        mov     [I8],eax                ; v5 = AReg
        mov     eax,[I2]                ; AReg = temp
        mov     [I9],eax                ; v6 = AReg
.L21:                                   ; end if
        mov     eax,[I9]                ; AReg = v6
        cmp     eax,[I10]               ; compare v6 and v7
        jg      .L22                    ; if v6 > v7 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L23                    ; unconditionally jump
.L22:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L23:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L24                    ; if T0 is false then jump to end of if
        mov     eax,[I9]                ; AReg = v6
        mov     [I2],eax                ; temp = AReg
        mov     eax,[I10]               ; AReg = v7
        mov     [I9],eax                ; v6 = AReg
        mov     eax,[I2]                ; AReg = temp
        mov     [I10],eax               ; v7 = AReg
.L24:                                   ; end if
        mov     eax,[I10]               ; AReg = v7
        cmp     eax,[I11]               ; compare v7 and v8
        jg      .L25                    ; if v7 > v8 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L26                    ; unconditionally jump
.L25:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L26:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L27                    ; if T0 is false then jump to end of if
        mov     eax,[I10]               ; AReg = v7
        mov     [I2],eax                ; temp = AReg
        mov     eax,[I11]               ; AReg = v8
        mov     [I10],eax               ; v7 = AReg
        mov     eax,[I2]                ; AReg = temp
        mov     [I11],eax               ; v8 = AReg
.L27:                                   ; end if
        mov     eax,[I11]               ; AReg = v8
        cmp     eax,[I12]               ; compare v8 and v9
        jg      .L28                    ; if v8 > v9 then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L29                    ; unconditionally jump
.L28:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L29:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L30                    ; if T0 is false then jump to end of if
        mov     eax,[I11]               ; AReg = v8
        mov     [I2],eax                ; temp = AReg
        mov     eax,[I12]               ; AReg = v9
        mov     [I11],eax               ; v8 = AReg
        mov     eax,[I2]                ; AReg = temp
        mov     [I12],eax               ; v9 = AReg
.L30:                                   ; end if
        mov     eax,[I1]                ; AReg = pass
        add     eax,[I14]               ; AReg = pass + 1
        mov     [I1],eax                ; pass = AReg
        jmp     .L0                     ; end while
.L3:                                    
        mov     eax,[I3]                ; load v0 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I4]                ; load v1 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I5]                ; load v2 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I6]                ; load v3 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I7]                ; load v4 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I8]                ; load v5 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I9]                ; load v6 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I10]               ; load v7 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I11]               ; load v8 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I12]               ; load v9 in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        Exit    {0}
                    
SECTION .data                           
I13     dd      0                       ; 0
I14     dd      1                       ; 1
FALSE   dd      0                       ; false
I0      dd      10                      ; n
TRUE    dd      -1                      ; true

SECTION .bss                            
I1      resd    1                       ; pass
I2      resd    1                       ; temp
I3      resd    1                       ; v0
I4      resd    1                       ; v1
I5      resd    1                       ; v2
I6      resd    1                       ; v3
I7      resd    1                       ; v4
I8      resd    1                       ; v5
I9      resd    1                       ; v6
I10     resd    1                       ; v7
I11     resd    1                       ; v8
I12     resd    1                       ; v9
