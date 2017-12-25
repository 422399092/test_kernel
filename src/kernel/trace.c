#include <asm/asm.h>
#include <kernel/kdata.h>
#include <kernel/kmalloc.h>
#include <string.h>

#define TRACE_MAX_ROW  25
#define TRACE_MAX_COL  80
#define TRACE_MAX_CHCAR TRACE_MAX_ROW * TRACE_MAX_COL
#define TRACE_MAX_NUM  TRACE_MAX_CHCAR * 2

/* VGA is a memory mapping interface, you may view it as an 80x25 array
 * vga mem pos at 0xB8000.
 * */
static uint16 px = 0;
static uint16 py = 0;
// static char **buf;
static char buf[TRACE_MAX_ROW][TRACE_MAX_COL];

static inline void up_csr()
{
    uint16 pos = (py * 80 + px);
    outb(0x3D4, 14);
    outb(0x3D5, pos>>8);
    outb(0x3D4, 15);
    outb(0x3D5, pos);
}

static inline void up_row()
{
  if (py == TRACE_MAX_ROW)
  {
      memcpy(buf, &buf[1][0], (TRACE_MAX_ROW-1) * TRACE_MAX_COL);
      memset(&buf[TRACE_MAX_ROW-1][0], 0, TRACE_MAX_COL);
      py = TRACE_MAX_ROW - 1;
  }
}

/* clear screen */
void clear_screen()
{
  uint32 row,col,idx=0;
  for (row = 0; row < 25; row++)
  {
    for (col = 0; col < 80; col++)
      set_vga_edi_val((80 * row + col) * 2, 0x0000);
  }
}

static inline void printc(uint16 row, uint16 col, char c)
{
  if (row < TRACE_MAX_ROW && col < TRACE_MAX_COL)
    buf[row][col] = c;
}

void print_buf()
{
  int32 row, col;
  for (row = 0; row < TRACE_MAX_ROW; row++) {
    for (col = 0; col < TRACE_MAX_COL; col++)
      set_vga_edi_val((80 * row + col) * 2, buf[row][col]|0x0200);
  }
  up_csr();
}

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

  up_row();
  up_csr();
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
  putc(ntab[m]);
}

/* a simpler printk
 * refer to unix v6
 * */
void tracek(char *fmt, ...)
{
  char c;
  int n;
  int *adx = (int*)(void*)&fmt + 1;

  // if (buf == NULL) {
  //   buf = (char **)kmalloc(TRACE_MAX_ROW);
  //   int32 row, col;
  //   for (row = 0; row < TRACE_MAX_ROW; row++) {
  //     buf[row] = (char *)kmalloc(TRACE_MAX_COL);
  //     memset((char*)buf[row], 0, TRACE_MAX_COL);
  //   }
  // }

_loop:
  while((c = *fmt++) != '%'){
    if (c == '\0') {
      print_buf();
      return;
    }
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
