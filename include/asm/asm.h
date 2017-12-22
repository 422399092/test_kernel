#include <kernel/def.h>

#define set_cli() \
  asm volatile("cli"::)

#define set_sti() \
  asm volatile("sti"::)

#define set_gs_edi(val) \
  asm("movl %%eax,%%edi"::"a" (val))

#define set_gs_edi_val(val) \
  asm("mov %%ax,%%gs:(%%edi)"::"a" (val))

#define set_cr0(val) \
  asm("movl %%eax,%%cr0"::"a" (val))

#define set_cr3(val) \
  asm("movl %%eax,%%cr3"::"a" (val))

static inline void io_delay(){
    asm volatile (
        "jmp 1f; 1: jmp 1f; 1:"
        );
}

/* inb & outb */
static inline uint8 inb(uint16 port){
    uint8 ret;
    asm volatile( "inb %1, %0" : "=a" (ret) : "dN" (port));
    io_delay();
    return ret;
}

static inline void outb(uint16 port, uint8 data){
    asm volatile( "outb %1, %0" :: "dN" (port), "a" (data));
    io_delay();
}
