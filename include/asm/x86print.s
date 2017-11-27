[SECTION .s16]
[BITS 16]
global x86_16_print, x86_16_disp_clear
x86_16_print:;msg ptr, msg len
  push bp
  mov bp, sp
  push ax
  push bx
  push cx
  push dx
  mov ax,[bp+4]
  mov cx,[bp+6]
  mov bp,ax
  mov ax,0x1301
  mov bx,15
  mov dx,0x0101
  int 0x10
  pop dx
  pop cx
  pop bx
  pop ax
  pop bp
ret 4

x86_16_disp_clear:
	mov ax,0x0600
	mov cx,0x0000
	mov dx,0x174f
	mov bh,0x00
	int 0x10
ret
