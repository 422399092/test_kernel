#include <kernel/mm.h>
#include <kernel/ret.h>
#include <asm/asm.h>

page_info_t *pages = NULL;

void init_mm_dir()
{
  uint32* pd = (void*)PAGE_DIR_REG_POS;
  uint32 i = 0;
  for (; i < 1024; i++)
  {
    if (i < PAGE_DIR_NUM)
      *pd = (uint32)(PAGE_TABLE_REG_POS + i * 0x1000 + 7);
    else
      *pd = (uint32)0;

    pd += 4;
  }
}

void init_mm_page()
{
  pages = (void*)PAGE_INFO_POS;
  uint32* pt = (void*)PAGE_TABLE_REG_POS;
  uint32 i, flg;
  for (i = 0; i < PAGE_NUM; i++)
  {
    *pt = (uint32)(i * 0x1000 + 7);
    flg = (i < KENREL_USE_PAGE_NUM) ? 1 : 0;
    pages->used = flg;
    pages->type = 0;
    pages->other = 0;

    pt += 4;
    pages += 1;
  }
  pages = (void*)PAGE_INFO_POS;
}

int32 init_mm()
{
  init_mm_dir();
  init_mm_page();

  set_cr0(PAGE_DIR_REG_POS);
  set_cr3(0x80000000);

  return SUCCESS;
}

void* get_free_page()
{

  return NULL;
}

void free_page(void* ptr)
{

}
