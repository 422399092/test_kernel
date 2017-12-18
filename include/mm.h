#include <def.h>

#define PAGE_DIR_NUM                  1024
#define PAGE_NUM                      1024
#define PAGE_SIZE                     4096
#define PAPGE_DIR_REG_POS             0x100000
#define PAPGE_TABLE_REG_POS           0x102000

struct page_dir_info {
  uint32 flg:9;
  uint32 avl:3;
  uint32 addr:20;
};

struct page_table_info {
  uint32 flg:9;
  uint32 avl:3;
  uint32 addr:20;
};

struct page {
  uint8          flg;
  uint8          used;/*0 ~ 1*/
  uint16         num;
  struct page   *next;
};

extern struct page_dir_info   *pd_arr;
extern struct page_table_info *pt_arr;
extern int32 init_mm();
