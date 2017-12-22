#include <kernel/kdata.h>
#include <kernel/ret.h>
#include <kernel/kmalloc.h>

int32 init_kdata()
{
  kernel_data = (kernel_data_t*)kmalloc(sizeof(kernel_data_t));

  // kernel_data->vgamem = (vgamem_t**)((void*)0x8b000);

  return SUCCESS;
}
