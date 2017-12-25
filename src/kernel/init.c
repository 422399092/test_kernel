#include <asm/asm.h>
#include <kernel/mm.h>
#include <kernel/kdata.h>
#include <kernel/kmalloc.h>
#include <kernel/trace.h>

extern void tracek(char* fmt, ...);

void test()
{
  int32 i;
  for (i=0; i < 10; i++) {
    uint32 pos = (80 * 0 + i) * 2;
    uint16 val = get_vga_edi_val(pos);
    tracek("vga 0x%x: 0x%x. %d\n", (0xB8000+pos), val, i);
  }

  // tracek("\n==============test char:\n\n");
  // char *buf = (char*)kmalloc(4096);
  // for (i = 0; i < 4096; i++) {
  //   buf[i] = i;
  // }
  // char *ptr = buf;
  // for (i = 0; i < 4096; i++) {
  //   tracek("%c ", *ptr++);
  // }
  // tracek("\n\n==============test char end.\n");

  tracek("\n==============memory:\n\n");
  uint32 *ptr1 = (uint32*)PAGE_TABLE_REG_POS;
  for (i = 0; i < 32; i++) {
    tracek("0x%x,", *ptr1++);
  }
}

void init() {
  clear_screen();
  int ret;
  ret = init_kdata();
  if (ret) tracek("init_kdata(%d) is error. \n", ret);
  ret = init_mm();
  if (ret) tracek("init_mm(%d) is error. \n", ret);
  test();
  // set_sti();
}
