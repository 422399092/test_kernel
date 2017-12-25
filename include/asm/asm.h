#include <kernel/def.h>

static inline void set_cli() {
  asm volatile("cli"::);
}

static inline void set_sti() {
  asm volatile("sti"::);
}

static inline void set_vga_edi_val(uint32 addr, uint16 val) {
  asm("movl %%eax,%%edi"::"a" (addr));
  asm("mov %%ax,%%fs:(%%edi)"::"a" (val));
}

static inline uint16 get_vga_edi_val(uint32 addr) {
  int val = 0;
  asm("movl %%eax,%%edi"::"a" (addr));
  asm("mov %%fs:(%%edi),%0":"=r" (val));
  return val;
}

static inline void set_cr0(uint32 val) {
  asm("movl %%eax,%%cr0"::"a" (val));
}

static inline void set_cr3(uint32 val) {
  asm("movl %%eax,%%cr3"::"a" (val));
}

static inline void io_delay() {
  asm("jmp 1f; 1: jmp 1f; 1:");
}

static inline uint8 inb(uint16 port) {
  uint8 inb_ret;
  asm("inb %%dx,%%al":"=a" (inb_ret):"d" (port));
  io_delay();
  return inb_ret;
}

static inline void outb(uint16 port, uint8 value) {
  asm("outb %%al,%%dx"::"a" (value),"d" (port));
  io_delay();
}
