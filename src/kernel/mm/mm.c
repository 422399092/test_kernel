#include <kernel/mm.h>
#include <kernel/ret.h>
#include <asm/asm.h>
#include <kernel/kmalloc.h>

page_info_t *page_infos = NULL;

void init_mm_dir()
{
  uint32* pd = (void*)PAGE_DIR_REG_POS;
  uint32 i = 0;
  for (; i < 1024; i++)
  {
    if (i < PAGE_DIR_NUM)
      *pd = (uint32)(PAGE_TABLE_REG_POS + (i << 12) + 7);
    else
      *pd = (uint32)0;

    pd += 4;
  }
}

void init_mm_page()
{
  page_infos = kmalloc(sizeof(page_info_t) * PAGE_NUM);
  page_info_t *pi = page_infos;
  uint32* pt = (void*)PAGE_TABLE_REG_POS;
  uint32 i, flg;
  for (i = 0; i < PAGE_NUM; i++)
  {
    *pt = (uint32)(i * 0x1000 + 7);
    flg = (i < KENREL_USE_PAGE_NUM) ? 1 : 0;
    pi->used = flg;
    pi->type = 0;
    pi->other = 0;

    pt += 4;
    pi += 1;
  }
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
  void *fp = NULL;
  page_info_t *pi;

  set_cli();
  uint32 i;
  for (i = 0; i < PAGE_NUM; i++)
  {
    pi = &page_infos[i];
    if (!pi->used) {
      fp = (void*)(i * PAGE_SIZE);
      break;
    }
  }
  set_sti();

  return fp;
}

void free_page(void* ptr)
{
  if (!ptr) return;

  uint32 val = (uint32)ptr;
  val >>= 12;
  if (val < PAGE_NUM)
  {
    set_cli();
    page_info_t *pi = &page_infos[val];
    pi->used = 0;
    set_sti();
  }
}
