#include <kernel/def.h>

#define MM_SIZE                       0x2000000 // 32MB
#define PAGE_NUM                      (MM_SIZE / 0x1000)
#define PAGE_DIR_NUM                  (PAGE_NUM / 1024)
#define PAGE_SIZE                     4096
#define PAGE_DIR_REG_POS              0x400000
#define PAGE_TABLE_REG_POS            0x401000

typedef struct page_info_s page_info_t;

struct page_info_s {
  uint32  used:1;
  uint32  type:5;
  uint32  other:3;
}__attribute__((packed));

int32 init_mm();
void* get_free_page();
void  free_page(void* ptr);
