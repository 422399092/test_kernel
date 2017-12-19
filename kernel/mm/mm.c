#include <mm.h>
#include <asm/asm.h>

// struct page_info page_dir[PAGE_NUM] __attribute__((aligned(PAGE_SIZE)));

void init_mm_dir()
{
  uint32* pd = NULL;
  *((void **)pd) += PAPGE_DIR_REG_POS;
  uint32 i = 0;
  for (; i < 1024; i++)
  {
    if (i < PAGE_DIR_NUM)
      *pd = (uint32)(PAPGE_TABLE_REG_POS + i * 0x1000 + 7);
    else
      *pd = (uint32)0;

    *((void **)pd) += 4;
  }
}

void init_mm_page()
{
  uint32* pt = NULL;
  *((void **)pt) += PAPGE_TABLE_REG_POS;
  uint32 i = 0;
  for (; i < PAGE_TABLE_NUM * 1024; i++)
  {
    *pt = (uint32)(i * 0x1000 + 7);
    *((void **)pt) += 4;
  }
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
