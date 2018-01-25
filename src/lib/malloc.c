#include <malloc.h>

typedef struct mm_block_s mm_block_t;
typedef struct mm_zone_s  mm_zone_t;

struct mm_block_s {
  uint32  size;
  uint32  addr;
}__attribute__((packed));

struct mm_zone_s {
  int32       type;
  mm_block_t  *bl;
};

static mm_zone_t zones[] = {
  { 16,       NULL },
  { 32,       NULL },
  { 64,       NULL },
  { 128,      NULL },
  { 256,      NULL },
  { 512,      NULL },
  { 1024,     NULL },
  { 1024*2,   NULL },
  { 1024*4,   NULL },
  { 1024*8,   NULL },
  { 1024*16,  NULL },
  { 1024*32,  NULL },
  { 1024*64,  NULL },
  { 1024*128, NULL },
};

void* malloc(uint32 size)
{

  return NULL;
}

void free(void* ptr)
{
  mm_block_t *block = (mm_block_t*)(ptr-sizeof(mm_block_t));
}
