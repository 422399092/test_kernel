#include <kernel/def.h>

#define MM_SIZE                       0x2000000 // 32MB
#define PAGE_NUM                      (MM_SIZE / 0x1000)
#define PAGE_DIR_NUM                  (PAGE_NUM / 1024)
#define PAGE_SIZE                     4096
#define PAGE_DIR_REG_POS              0x400000
#define PAGE_TABLE_REG_POS            0x402000
#define PAGE_INFO_POS                 0x300000
#define KENREL_USE_PAGE_NUM           2048

typedef struct page_info_s page_info_t;

struct page_info_s {
  uint32  used:1;
  uint32  type:4;
  uint32  other:3;
}__attribute__((packed));

extern int32 init_mm();
extern void* get_free_page();
extern void  free_page(void* ptr);
