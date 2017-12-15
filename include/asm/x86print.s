%include	"const.s"

[SECTION .data]
disp_pos	dd	0

[SECTION .text]
global x86_32_print, x86_32_disp_clear, trace

x86_32_disp_clear:

ret

x86_32_print:;x86_32_print(char c, int col, int row, int color);
  push ebp
  mov ebp, esp
  mov eax, STACK_PARAM_3
  imul eax, eax, 80
  add eax, STACK_PARAM_2
  imul eax, eax, 2
  mov edi, eax
  mov ah, STACK_PARAM_4
  mov al, byte STACK_PARAM_1
  mov [gs:edi], ax
  pop ebp
ret

trace:
	push ebp
	mov	ebp, esp
	mov	esi, [ebp + 8]	; pszInfo
	mov	edi, [disp_pos]
	mov	ah, 0Fh
.1:
	lodsb
	test al, al
	jz	.2
	cmp	al, 0Ah	; 是回车吗?
	jnz	.3
	push eax
	mov	eax, edi
	mov	bl, 160
	div	bl
	and	eax, 0FFh
	inc	eax
	mov	bl, 160
	mul	bl
	mov	edi, eax
	pop	eax
	jmp	.1
.3:
	mov	[gs:edi], ax
	add	edi, 2
	jmp	.1
.2:
	mov	[disp_pos], edi
	pop	ebp
	ret
