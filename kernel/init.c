void x86_32_print(char c, int col, int row, int color);
void x86_32_disp_clear();
void trace(char *str);

void test(char *str) {
  int pos = 0;
  while (*str != '\n') {
    x86_32_print(*str++, pos++, 9, 0x02);
  }
}

void init(char *enter_kernel_info, char *loaded_info) {
  trace("\n\n\nGCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609\n\0");
  trace("enter kernel.\n\0");
  trace("init kernel.\n\0");
  test("11111111\n");
}
