asm      = nasm
c        = gcc
ld       = ld -s
build    = bin

incs	     = include
asm_incs   = include/asm
libs	     = src/lib
boot_src   = src/boot
kernel_src = src/kernel

c_flg32 = -I$(incs) -fno-builtin -fno-builtin-FUNCTION -nostdinc -m32 -c

all: sys.img

sys.img: clean boot.bin libs.bin kernel.bin
	$(asm) -f bin $(boot_src)/makeboot.s -o bin/sys.img

boot.bin:
	$(asm) -f bin $(boot_src)/boot.s -o $(build)/boot.bin

kernel.bin:
	$(c) $(c_flg32) $(kernel_src)/kmalloc.c -o $(build)/kmalloc.o
	$(c) $(c_flg32) $(kernel_src)/trace.c -o $(build)/trace.o
	$(c) $(c_flg32) $(kernel_src)/kdata.c -o $(build)/kdata.o
	$(c) $(c_flg32) $(kernel_src)/mm/mm.c -o $(build)/mm.o
	$(c) $(c_flg32) $(kernel_src)/idt.c -o $(build)/idt.o
	$(c) $(c_flg32) $(kernel_src)/pm.c -o $(build)/pm.o
	$(c) $(c_flg32) $(kernel_src)/init.c -o $(build)/init.o
	$(asm) -f elf32 $(kernel_src)/enter.s -o $(build)/enter.o
	$(ld) -T makefile.lds -m elf_i386 -o $(build)/kernel.bin $(build)/*.o

libs.bin:
	$(c) $(c_flg32) $(libs)/malloc.c -o $(build)/malloc.o
	$(c) $(c_flg32) $(libs)/string.c -o $(build)/string.o

clean:
	rm -rf $(build)
	mkdir $(build)
