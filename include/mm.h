#include <def.h>
#define MM_SIZE                       0x4000000 // 64MB
#define PAGE_TABLE_NUM                (MM_SIZE / 0x1000)
#define PAGE_DIR_NUM                  (PAGE_TABLE_NUM / 1024)
#define PAGE_SIZE                     4096
#define PAPGE_DIR_REG_POS             0x100000
#define PAPGE_TABLE_REG_POS           0x102000

typedef struct page_dir_s   page_dir_t;
typedef struct page_table_s page_table_t;

struct page_dir_s {
  uint32 flg:9;
  uint32 avl:3;
  uint32 addr:20;
};

struct page_s {
  struct page   *next;
};

struct s_ptr_t {

};

extern int32 init_mm();
extern void* get_free_page();
extern void  free_page(void* ptr);
