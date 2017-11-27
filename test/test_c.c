void trace_by_c(const char* str, int len);

void test_c(int loop) {
  int i = 0;
  const char* out_str = "test_c.\n";
  for (; i < loop; i++) {
    trace_by_c(out_str, 8);
  }
}

void wait_c() {
  while (1) {
    ;
  }
}
