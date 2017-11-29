void x86_32_print(char c, short row, short col, short color);
void x86_32_disp_clear();

void trace(char *str, int len, int row) {
  char *ptr = str;
  int pos = 1;
  while (len-- > 0) {
    x86_32_print((char)ptr, pos++, row, 0x0A);
    ptr++;
  }
}

void init() {
  x86_32_print('o', 1, 2, 0x0A);
  x86_32_print('k', 2, 2, 0x0A);
  x86_32_print('.', 3, 2, 0x0A);
  trace("kernel be laoded!", 16, 3);
  for (;;) {}
}
