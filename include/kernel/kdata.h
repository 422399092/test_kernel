#include <kernel/def.h>

typedef struct mm_info_s mm_info_t;
typedef struct cpu_info_s cpu_info_t;
typedef struct kernel_data_s kernel_data_t;

struct mm_info_s {

};

struct cpu_info_s {

};

struct kernel_data_s {
  mm_info_t   mm_info;
  cpu_info_t  cpu_info;
};

extern int32 init_kdata();
