#include <kernel/def.h>

typedef struct mm_info_s mm_info_t;
typedef struct cpu_info_s cpu_info_t;
typedef struct vgamem_s vgamem_t;
typedef struct kernel_data_s kernel_data_t;

struct mm_info_s {

}__attribute__((packed));

struct cpu_info_s {

}__attribute__((packed));

struct vgamem_s {
    char    vga_char:8;
    char    vga_color:4;
    char    vga_bgcolor:4;
}__attribute__((packed));

struct kernel_data_s {
  mm_info_t   mm_info;
  cpu_info_t  cpu_info;
  vgamem_t    **vgamem;
};

kernel_data_t *kernel_data;
int32 init_kdata();
