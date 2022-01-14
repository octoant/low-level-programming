global sepia_four_pixels

%macro sepia 2
    movdqu xmm0, [rdi]
    movdqu xmm1, [rsi]
    movdqu xmm2, [rdx]
    shufps xmm0, xmm0, %1
    shufps xmm1, xmm1, %1
    shufps xmm2, xmm2, %1
    movdqu xmm3, [red]
    movdqu xmm4, [green]
    movdqu xmm5, [blue]
    shufps xmm3, xmm3, %2
    shufps xmm4, xmm4, %2
    shufps xmm5, xmm5, %2
    mulps  xmm0, xmm3
    mulps  xmm1, xmm4
    mulps  xmm2, xmm5
    addps  xmm0, xmm1
    addps  xmm0, xmm2
    call   store
%endmacro

section .rodata
red:   dd 0.131, 0.168, 0.189
green: dd 0.543, 0.686, 0.769
blue:  dd 0.272, 0.349, 0.393
align 16
max:   dd 255.0, 255.0, 255.0, 255.0

section .text
sepia_four_pixels:
    sepia 0b01000000, 0b00100100
    add rcx, 4
    sepia 0b10100101, 0b01001001
    add rcx, 4
    sepia 0b11111110, 0b10010010
    ret

store:
    minps    xmm0,    [max]
    cvtps2dq xmm0,    xmm0
    pextrb   [rcx],   xmm0, 0
    pextrb   [rcx+1], xmm0, 4
    pextrb   [rcx+2], xmm0, 8
    pextrb   [rcx+3], xmm0, 12
    ret
