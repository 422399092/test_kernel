[bits 32]

[SECTION .bss]
stack_space		resb	8 * 1024
stack_top:

[SECTION .text]
extern init, x86_32_print, trace
global _enter_
_enter_:
  mov ax, 0x10
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov ax, 0x28
  mov gs, ax
  mov	esp, stack_top
  call init
sleep:
  nop
  nop
  jmp sleep
