
#define set_cli() \
  asm volatile("cli")

#define set_sti() \
  asm volatile("sti")

#define set_cr0(val) \
  asm("movl %%eax,%%cr0"::"a" (val))

#define set_cr3(val) \
  asm("movl %%eax,%%cr3"::"a" (val))
