// #include <kernel/trace.h>
// #include <kernel/kmalloc.h>
// #include <string.h>
//
// #define TRACE_MAX_ROW  24
// #define TRACE_MAX_COL  64
// #define TRACE_MAX_NUM  TRACE_MAX_ROW * TRACE_MAX_COL * 2
//
// void x86_32_print(char c, int col, int row, int color);
//
// static uint32 cur_pos = 0;
// static uint32 cur_col = 0;
// static uint32 cur_row = 0;
// static char *strs = NULL;
//
// void up_device()
// {
//   x86_32_print('0', cur_col, cur_row, 0x0A);
// }
//
// void putc(char c)
// {
//   *(strs + cur_pos) = c;
//   if (++cur_pos == TRACE_MAX_NUM)
//     cur_pos = 0;
// }
//
// void puts(char *str)
// {
//   int32 i;
//   for(i = 0; i < strlen(str); i++)
//     putc(str[i]);
// }
//
// void putn(uint32 n, uint32 b)
// {
//   static char *ntab = "0123456789ABCDEF";
//   uint32 a, m;
//   if (a = n / b)
//       putn(a, b);
//   m = n % b;
//   putc(ntab[m]);
// }
//
// void tracek(char* fmt, ...)
// {
//   if (!strs) {
//     strs = (char*)kmalloc(TRACE_MAX_NUM);
//   }
//
//   char c;
//   int n;
//   int *adx = (int*)(void*)&fmt + 1;
//
// _loop:
//   while((c = *fmt++) != '%'){
//       if (c == '\0') return;
//       putc(c);
//   }
//   c = *fmt++;
//   if (c == 'd' || c == 'l'){
//       n = *adx;
//       if (n<0) {
//           putc('-');
//           n *= -1;
//       }
//       putn(n, 10);
//   }
//   if (c == 'o' || c == 'x'){
//       putn(*adx, c=='o'? 8:16 );
//   }
//   if (c == 'c') {
//       putc(*adx);
//   }
//   if (c == 's'){
//       puts((char*)*adx);
//   }
//   adx++;
//   goto _loop;
//
//   up_device();
// }
#include <asm/asm.h>
#include <kernel/kdata.h>
#include <string.h>

#define VGA_WHITE 0x07
#define VGA_BLACK 0x00

#define VC_BLANK (' '|VGA_WHITE<<8)

#define printc(row, col, c) \
  set_gs_edi((80 * row + col) * 2); \
  set_gs_edi_val(c|0x0A00)

/* VGA is a memory mapping interface, you may view it as an 80x25 array
 * which located at 0x8b000 (defined in main.ld).
 * */
static uint16 px = 0;
static uint16 py = 0;
/* clear screen */
void clear_screen()
{
  uint32 row,col,idx=0;
  for (row = 0; row < 25; row++)
  {
    for (col = 0; col < 80; col++)
      printc(row, col, 0x0000);
  }
}

/* ----------------------------------------------------- */
void putc(char c)
{
  if(c == '\b') {
    if(px > 0) {
      px--;
      printc(py, px, ' ');
    }
    else {
      if (py>0) py--;
      px = 79;
      printc(py, px, ' ');
    }
  }
  else if(c == '\t') {
    px = (px + 4) & ~3;
  }
  else if(c == '\r') {
    px = 0;
  }
  else if(c == '\n') {
    px = 0;
    py++;
  }
  else if(c >= ' ') {
    printc(py, px, c);
    px++;
  }
  if(px >= 80) {
    px = 0;
    py++;
  }
}

void puts(char *str)
{
  int i;
  for(i=0; i<strlen(str); i++) {
    putc(str[i]);
  }
}

// print an unsigned integer in base b
void putn(uint32 n, uint32 b)
{
  static char *ntab = "0123456789ABCDEF";
  uint32 a, m;
  if ((a = n / b)) {
    putn(a, b);
  }
  m = n % b;
  putc( ntab[m] );
}

/* a simpler printk
 * refer to unix v6
 * */
void tracek(char *fmt, ...)
{
  char c;
  int n;
  int *adx = (int*)(void*)&fmt + 1;

_loop:
  while((c = *fmt++) != '%'){
    if (c == '\0') return;
    putc(c);
  }
  c = *fmt++;
  if (c == 'd' || c == 'l'){
    n = *adx;
    if (n<0) {
      putc('-');
      n *= -1;
    }
    putn(n, 10);
  }
  if (c == 'o' || c == 'x'){
    putn(*adx, c=='o'? 8:16);
  }
  if (c == 'c') {
    putc(*adx);
  }
  if (c == 's'){
    puts((char*)*adx);
  }
  adx++;
  goto _loop;
}
