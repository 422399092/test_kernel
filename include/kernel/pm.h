#include <kernel/def.h>

typedef struct tss_s  tss_t;
typedef struct proc_s proc_t;

struct tss_s {
  int32 pid;
  int32 cr0, cr1, cr2, cr3;
  int32 eax, ebx, ecx, edx;
  int32 esp, ebp, edi, esi, eip;
  int32 cs, ds, es, ss, gs,fs;
};

struct proc_s {
  int32 state;
  int32 exit_code;
  tss_t tss;
};
