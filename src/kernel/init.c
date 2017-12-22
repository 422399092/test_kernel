#include <asm/asm.h>
#include <kernel/mm.h>
#include <kernel/kdata.h>
#include <kernel/trace.h>

extern void tracek(char* fmt, ...);

void test()
{
  int32 i;
  for (i = 2; i < 30; i++) {
    tracek("init_mm(%d) is error. \n", i);
  }
}

void init() {
  clear_screen();
  int ret;
  ret = init_kdata();
  if (ret) tracek("init_kdata() is error. \n");
  ret = init_mm();
  if (ret) tracek("init_mm(%d) is error. \n", 9);

  test();
  // set_sti();
}
