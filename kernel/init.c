#include <mm.h>

void x86_32_print(char c, int col, int row, int color);
void x86_32_disp_clear();
void trace(char *str);

void init() {
  trace("\nenter kernel.\n\0");
  trace("init kernel.\n\0");

  char *ptr = NULL;
  *((void **)ptr) += 0x100000;
  *ptr = 54;
  x86_32_print(*ptr, 0, 8, 0x04);

  int ret;
  ret = init_mm();
  if (ret == 0)
    trace("init_mm() is error \n");
}
