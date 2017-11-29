%include	"const.s"

[BITS 32]
global x86_32_print, x86_32_disp_clear

x86_32_disp_clear:

ret

x86_32_print:;x86_32_print(char *c, int row, short col, short color);
  push ebp
  mov ebp, esp
  mov eax, 0x18
  mov gs, ax
  mov eax, STACK_PARAM_3
  imul eax, eax, 80
  add eax, STACK_PARAM_2
  imul eax, eax, 2
  mov edi, eax
  mov ah, STACK_PARAM_4
  mov al, STACK_PARAM_1
  mov [gs:edi], ax
  pop ebp
ret
