#include <kernel/mm.h>

typedef struct mem_info_s mem_info_t;

struct mem_info_s {
  uint32 page_num:16;
  uint32 page_start_addr:32;
}__attribute__((packed));

void* malloc(uint32 size);
void  free(void* ptr);
