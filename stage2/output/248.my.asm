; Kangmin Kim, Jeff Caldwell       Wed Dec  7 00:20:48 2022
%INCLUDE "Along32.inc"
%INCLUDE "Macros_Along.inc"

SECTION .text                           
global  _start                          ; program stage2no248

_start:                                 
        call    ReadInt                 ; read int; value placed in eax
        mov     [I3],eax                ; store eax at x
        call    ReadInt                 ; read int; value placed in eax
        mov     [I4],eax                ; store eax at y
        mov     eax,[I3]                ; load x in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I4]                ; load y in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I5]                ; AReg = 0
        mov     [I2],eax                ; cmp = AReg
        mov     eax,[I3]                ; AReg = x
        mov     [I0],eax                ; m = AReg
        mov     eax,[I4]                ; AReg = y
        mov     [I1],eax                ; n = AReg
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        jl      .L0                     ; if m < n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L1                     ; unconditionally jump
.L0:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L1:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L2                     ; if T0 is false then jump to end of if
        mov     eax,[I2]                ; AReg = cmp
        add     eax,[I6]                ; AReg = cmp + 1
        mov     [I2],eax                ; cmp = AReg
.L2:                                    ; end if
        mov     eax,[I2]                ; AReg = cmp
        add     eax,[I7]                ; AReg = cmp + 2
        mov     [I2],eax                ; cmp = AReg
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I5]                ; AReg = 0
        mov     [I2],eax                ; cmp = AReg
        mov     eax,[I3]                ; AReg = x
        mov     [I0],eax                ; m = AReg
        mov     eax,[I4]                ; AReg = y
        mov     [I1],eax                ; n = AReg
.L3:                                    ; while
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        jl      .L4                     ; if m < n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L5                     ; unconditionally jump
.L4:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L5:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L6                     ; if T0 is false then jump to end while
        mov     eax,[I0]                ; AReg = m
        add     eax,[I6]                ; AReg = m + 1
        mov     [I0],eax                ; m = AReg
        cmp     eax,[I1]                ; compare m and n
        jl      .L7                     ; if m < n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L8                     ; unconditionally jump
.L7:                                    
        mov     eax,[TRUE]              ; set eax to TRUE
.L8:                                    
        cmp     eax,0                   ; compare eax to 0
        je      .L9                     ; if T0 is false then jump to end of if
        mov     eax,[I2]                ; AReg = cmp
        add     eax,[I6]                ; AReg = cmp + 1
        mov     [I2],eax                ; cmp = AReg
.L9:                                    ; end if
        jmp     .L3                     ; end while
.L6:                                    
        mov     eax,[I2]                ; load cmp in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I5]                ; AReg = 0
        mov     [I2],eax                ; cmp = AReg
        mov     eax,[I3]                ; AReg = x
        mov     [I0],eax                ; m = AReg
        mov     eax,[I4]                ; AReg = y
        mov     [I1],eax                ; n = AReg
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        jl      .L10                    ; if m < n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L11                    ; unconditionally jump
.L10:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L11:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L12                    ; if T0 is false then jump to end of if
        mov     eax,[I6]                ; AReg = 1
        mov     [I2],eax                ; cmp = AReg
.L12:                                   ; end if
        mov     eax,[I2]                ; load cmp in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I5]                ; AReg = 0
        mov     [I2],eax                ; cmp = AReg
        mov     eax,[I3]                ; AReg = x
        mov     [I0],eax                ; m = AReg
        mov     eax,[I4]                ; AReg = y
        mov     [I1],eax                ; n = AReg
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        jl      .L13                    ; if m < n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L14                    ; unconditionally jump
.L13:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L14:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L15                    ; if T0 is false then jump to end of if
        mov     eax,[I6]                ; AReg = 1
        mov     [I2],eax                ; cmp = AReg
.L15:                                   ; end if
        mov     eax,[I2]                ; load cmp in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I5]                ; AReg = 0
        mov     [I2],eax                ; cmp = AReg
        mov     eax,[I3]                ; AReg = x
        mov     [I0],eax                ; m = AReg
        mov     eax,[I4]                ; AReg = y
        mov     [I1],eax                ; n = AReg
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        jl      .L16                    ; if m < n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L17                    ; unconditionally jump
.L16:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L17:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L18                    ; if T0 is false then jump to end of if
        mov     eax,[I6]                ; AReg = 1
        mov     [I2],eax                ; cmp = AReg
.L18:                                   ; end if
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        je      .L19                    ; if m = n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L20                    ; unconditionally jump
.L19:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L20:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L21                    ; if T0 is false then jump to end of if
        mov     eax,[I7]                ; AReg = 2
        mov     [I2],eax                ; cmp = AReg
.L21:                                   ; end if
        mov     eax,[I2]                ; load cmp in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I5]                ; AReg = 0
        mov     [I2],eax                ; cmp = AReg
        mov     eax,[I3]                ; AReg = x
        mov     [I0],eax                ; m = AReg
        mov     eax,[I4]                ; AReg = y
        mov     [I1],eax                ; n = AReg
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        jl      .L22                    ; if m < n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L23                    ; unconditionally jump
.L22:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L23:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L24                    ; if T0 is false then jump to end of if
        mov     eax,[I6]                ; AReg = 1
        mov     [I2],eax                ; cmp = AReg
.L24:                                   ; end if
.L25:                                   ; while
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        jl      .L26                    ; if m < n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L27                    ; unconditionally jump
.L26:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L27:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L28                    ; if T0 is false then jump to end while
        mov     eax,[I0]                ; AReg = m
        add     eax,[I6]                ; AReg = m + 1
        mov     [I0],eax                ; m = AReg
        cmp     eax,[I1]                ; compare m and n
        jl      .L29                    ; if m < n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L30                    ; unconditionally jump
.L29:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L30:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L31                    ; if T0 is false then jump to end of if
        mov     eax,[I2]                ; AReg = cmp
        add     eax,[I6]                ; AReg = cmp + 1
        mov     [I2],eax                ; cmp = AReg
.L31:                                   ; end if
        jmp     .L25                    ; end while
.L28:                                   
        mov     eax,[I2]                ; load cmp in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I5]                ; AReg = 0
        mov     [I2],eax                ; cmp = AReg
        mov     eax,[I3]                ; AReg = x
        mov     [I0],eax                ; m = AReg
        mov     eax,[I4]                ; AReg = y
        mov     [I1],eax                ; n = AReg
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        jl      .L32                    ; if m < n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L33                    ; unconditionally jump
.L32:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L33:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L34                    ; if T0 is false then jump to end of if
        mov     eax,[I6]                ; AReg = 1
        mov     [I2],eax                ; cmp = AReg
.L34:                                   ; end if
.L35:                                   ; repeat
        mov     eax,[I0]                ; AReg = m
        add     eax,[I6]                ; AReg = m + 1
        mov     [I0],eax                ; m = AReg
        cmp     eax,[I1]                ; compare m and n
        jl      .L36                    ; if m < n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L37                    ; unconditionally jump
.L36:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L37:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L38                    ; if T0 is false then jump to end of if
        mov     eax,[I2]                ; AReg = cmp
        add     eax,[I6]                ; AReg = cmp + 1
        mov     [I2],eax                ; cmp = AReg
.L38:                                   ; end if
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        jge     .L39                    ; if m >= n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L40                    ; unconditionally jump
.L39:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L40:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L35                    ; until T0 is true
        mov     eax,[I2]                ; load cmp in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I5]                ; AReg = 0
        mov     [I2],eax                ; cmp = AReg
        mov     eax,[I3]                ; AReg = x
        mov     [I0],eax                ; m = AReg
        mov     eax,[I4]                ; AReg = y
        mov     [I1],eax                ; n = AReg
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        jl      .L41                    ; if m < n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L42                    ; unconditionally jump
.L41:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L42:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L43                    ; if T0 is false then jump to end of if
        mov     eax,[I6]                ; AReg = 1
        mov     [I2],eax                ; cmp = AReg
.L43:                                   ; end if
        mov     eax,[I2]                ; load cmp in eax
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        mov     eax,[I5]                ; AReg = 0
        mov     [I2],eax                ; cmp = AReg
        mov     eax,[I3]                ; AReg = x
        mov     [I0],eax                ; m = AReg
        mov     eax,[I4]                ; AReg = y
        mov     [I1],eax                ; n = AReg
        mov     eax,[I0]                ; AReg = m
        cmp     eax,[I1]                ; compare m and n
        jl      .L44                    ; if m < n then jump to set eax to TRUE
        mov     eax,[FALSE]             ; else set eax to FALSE
        jmp     .L45                    ; unconditionally jump
.L44:                                   
        mov     eax,[TRUE]              ; set eax to TRUE
.L45:                                   
        cmp     eax,0                   ; compare eax to 0
        je      .L46                    ; if T0 is false then jump to end of if
        mov     eax,[I6]                ; AReg = 1
        mov     [I2],eax                ; cmp = AReg
.L46:                                   ; end if
        call    ReadInt                 ; read int; value placed in eax
        mov     [I2],eax                ; store eax at cmp
        call    WriteInt                ; write int in eax to standard out
        call    Crlf                    ; write \r\n to standard out
        Exit    {0}
                    
SECTION .data                           
I5      dd      0                       ; 0
I6      dd      1                       ; 1
I7      dd      2                       ; 2
FALSE   dd      0                       ; false
TRUE    dd      -1                      ; true

SECTION .bss                            
I2      resd    1                       ; cmp
I0      resd    1                       ; m
I1      resd    1                       ; n
I3      resd    1                       ; x
I4      resd    1                       ; y
