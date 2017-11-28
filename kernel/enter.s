[bits 32]
_enter_:
  ; mov ax, cs
  ; mov ds, ax
  ; mov es, ax
  ;
  ; mov ax,0x0600
	; mov cx,0x0000
	; mov dx,0x174f
	; mov bh,0x00
	; int 0x10
  ;
  ; mov ax,info
  ; mov cx,17
  ; mov bp,ax
  ; mov ax,0x1301
  ; mov bx,15
  ; mov dx,0x0101
  ; int 0x10
  mov eax, 0x18
	mov gs, ax
	mov edi, (80 * 6 + 1) * 2
	mov ah, 0x0A
	mov al, 'o'
	mov [gs:edi], ax

  jmp $

info        db "kernel be laoded!"
