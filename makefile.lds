ENTRY(_enter_)
SECTIONS {
  .text 0x200 : {
      __kbegin__ = .;
      __code__ = .;
      *(.text);
      . = ALIGN(4096);
  }
  .data : {
      __data__ = .;
      *(.rodata);
      *(.data);
      . = ALIGN(4096);
  }
  .bss : {
      __bss__ = .;
      *(.bss);
      . = ALIGN(4096);
  }
  __kend__ = .;
}
