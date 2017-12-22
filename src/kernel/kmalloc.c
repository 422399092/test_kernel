#include <kernel/kmalloc.h>
#include <kernel/mm.h>
#include <kernel/def.h>

void* kmalloc(uint32 size)
{
  static uint32 cur_kernel_mem_pos = KENREL_USE_MM_START_POS;

  if (cur_kernel_mem_pos + size < KENREL_USE_MM_END_POS) {
    void* ptr = (void*)cur_kernel_mem_pos;
    cur_kernel_mem_pos += size;
    return ptr;
  }

  return NULL;
}

void kfree(void* ptr)
{

}
