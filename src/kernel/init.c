#include <kernel/mm.h>
#include <kernel/kdata.h>
#include <asm/asm.h>

void x86_32_print(char c, int col, int row, int color);
void x86_32_disp_clear();
void trace(char *str);

void test() {
  char *ptr = NULL;
  *((void **)ptr) += 0x100000;
  *ptr = 54;
  x86_32_print(*ptr, 0, 15, 0xA0);
}

void init() {
  trace("\nenter kernel.\n\0");
  trace("init kernel.\n\0");

  test();

  int ret;
  ret = init_kdata();
  if (ret) trace("init_kdata() is error \n");
  ret = init_mm();
  if (ret) trace("init_mm() is error \n");

  // set_sti();
}
