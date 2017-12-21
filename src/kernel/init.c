#include <kernel/mm.h>
#include <kernel/kdata.h>
#include <asm/asm.h>

void x86_32_print(char c, int col, int row, int color);
void x86_32_disp_clear();
void trace(char *str);

void test() {
  page_info_t *ptr = (void*)(0x100000+2046);
  x86_32_print(*(char*)(&ptr[0]), 0, 14, 0xA0);
  x86_32_print(*(char*)(&ptr[1]), 0, 15, 0x0A);
  x86_32_print(*(char*)(&ptr[2]), 0, 16, 0x0A);
  x86_32_print(*(char*)(&ptr[3]), 0, 16, 0xA0);
}

void init() {
  trace("\nenter kernel.\n\0");
  trace("init kernel.\n\0");

  int ret;
  ret = init_kdata();
  if (ret) trace("init_kdata() is error. \n");
  ret = init_mm();
  if (ret) trace("init_mm() is error. \n");
  test();
  // set_sti();
}
