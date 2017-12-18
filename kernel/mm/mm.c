#include <mm.h>
#include <asm/asm.h>

// struct page_info page_dir[PAGE_NUM] __attribute__((aligned(PAGE_SIZE)));

void init_mm_dir()
{
  struct page_dir_info* pd = NULL;
  *((void **)pd) += 0x100000;
  int i = 0;
  for (; i < PAGE_DIR_NUM; i++)
  {
    pd->flg = 7;
    pd->avl = 0;
    pd->addr = (i + 1) * PAGE_SIZE;
    *((void **)pd) += 4;
  }
}

void init_mm_page()
{

}

int32 init_mm()
{
  init_mm_dir();
  init_mm_page();
  // set cr link register
  set_cr0(0x100000);
  set_cr3(0x80000000);

  return 0;
}
