#include <asm/asm.h>
#include <kernel/kdata.h>
#include <kernel/kmalloc.h>
#include <string.h>

#define TRACE_MAX_ROW  25
#define TRACE_MAX_COL  80
#define TRACE_MAX_CHCAR TRACE_MAX_ROW * TRACE_MAX_COL
#define TRACE_COLOR    0x0200

static uint16 col = 0;
static uint16 row = 0;
static uint16 (*vga_addr)[TRACE_MAX_COL] = NULL;

void up_csr()
{
    uint16 pos = (row * TRACE_MAX_COL + col);
    outb(0x3D4, 14);
    outb(0x3D5, pos >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, pos);
}

void up_row()
{
  if (row == TRACE_MAX_ROW) {
    memcpy(vga_addr, &vga_addr[1][0], (TRACE_MAX_ROW-1) * TRACE_MAX_COL * 2);
    memsetw(&vga_addr[TRACE_MAX_ROW-1][0], 0, TRACE_MAX_COL);
    row = TRACE_MAX_ROW - 1;
  }
}

static inline void put_buf(uint16 row, uint16 col, char c)
{
  if (row < TRACE_MAX_ROW && col < TRACE_MAX_COL)
    vga_addr[row][col] = c|TRACE_COLOR;
}

void putc(char c)
{
  if(c == '\b') {
    if(col > 0) {
      col--;
      put_buf(row, col, ' ');
    }
    else {
      if (row>0) row--;
      col = TRACE_MAX_COL - 1;
      put_buf(row, col, ' ');
    }
  }
  else if(c == '\t') {
    col = (col + 4) & ~3;
  }
  else if(c == '\r') {
    col = 0;
  }
  else if(c == '\n') {
    col = 0;
    row++;
  }
  else if(c >= ' ') {
    put_buf(row, col, c);
    col++;
  }
  if(col >= TRACE_MAX_COL) {
    col = 0;
    row++;
  }

  up_row();
  up_csr();
}

void puts(char *str)
{
  int32 i;
  for(i = 0; i < strlen(str); i++)
    putc(str[i]);
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

/** easy clear tracek */
void clear_tracek()
{
  memset((char*)VGA_TEXT_MODE_ADDR, 0, VGA_TEXT_MODE_ADDR_END);
}

/** for reference unix v6 */
void tracek(char *fmt, ...)
{
  char c;
  int32 n;
  int32 *adx = (int32*)(void*)&fmt + 1;

  if (vga_addr == NULL) {
    vga_addr = (uint16 (*)[TRACE_MAX_COL])(kernel_data->vga_text_addr);
  }

_loop:
  while((c = *fmt++) != '%'){
    if (c == '\0') {
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
