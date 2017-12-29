[bits 32]

; 0x60000 ~ 0xA0000
[SECTION .bss]
stack_space		resb	64 * 1024 ; 0x60000 ~ 0x70000
stack_top:

[SECTION .text]
extern init, trace
global _enter_
_enter_:
  mov ax, 0x10
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov gs, ax
  mov fs, ax
  mov	esp, stack_top
  call init
sleep:
  nop
  nop
  jmp sleep
