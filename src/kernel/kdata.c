#include <kernel/kdata.h>
#include <kernel/ret.h>
#include <kernel/kmalloc.h>

int32 init_kdata()
{
  kernel_data = (kernel_data_t*)kmalloc(sizeof(kernel_data_t));
  kernel_data->vga_text_addr = (uint16*)(VGA_TEXT_MODE_ADDR);

  return SUCCESS;
}
