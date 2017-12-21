#include <kernel/mm.h>
#include <kernel/kdata.h>
#include <asm/asm.h>

void x86_32_print(char c, int col, int row, int color);
void x86_32_disp_clear();
void trace(char *str);

void test() {
  page_info_t *ptr = (void*)(PAGE_INFO_POS+2048);
  x86_32_print(*(char*)ptr, 0, 14, 0xA0);
  x86_32_print(*(char*)(ptr-1), 0, 15, 0x0A);
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
