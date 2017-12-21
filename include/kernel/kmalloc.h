#include <kernel/def.h>

#define KENREL_USE_MM_START_POS       0x100000
#define KENREL_USE_MM_END_POS         0x400000
#define KENREL_USE_PAGE_NUM           2048

extern void* kmalloc(uint32 size);
extern void  kfree(void* ptr);
