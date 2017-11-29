[bits 32]

[SECTION .bss]
stack_space		resb	2 * 1024
stack_top:

[SECTION .text]
global _enter_
extern init

_enter_:
  mov	esp, stack_top
  call init
  jmp $
