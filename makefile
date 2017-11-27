asm      = nasm
cc       = gcc
ld       = ld -s
build    = bin

incs	 = include
libs	 = lib
boot_src = boot
kernel_src = kernel

cc_flg32 = -fno-builtin -fno-builtin-FUNCTION -nostdinc -m32 -c
cc_flg64 = -fno-builtin -fno-builtin-FUNCTION -nostdinc -m64 -c

all:	sys.img

sys.img:	clean boot.bin kernel.bin
	$(asm) -f bin $(boot_src)/makeboot.s -o bin/sys.img

boot.bin:
	$(asm) -f bin $(boot_src)/boot.s -o $(build)/boot.bin

kernel.bin:	
	$(cc) $(cc_flg32) $(kernel_src)/init.c -o $(build)/init.o
	$(asm) -f bin $(kernel_src)/enter.s -o $(build)/enter.bin
	# $(ld) -Ttext 0x0 -e _start -m elf_i386 -o $(build)/sys.bin $(build)/*.o

libs.bin:
	# $(cc) $(cc_flg32) -I$(incs)/base -o $(build)/libs_base.o $(libs)/base/*.c
	# $(asm) -f elf32 -o $(build)/asm_libs.bin $(incs)/asm/*.asm

clean:
	rm -rf $(build)
	mkdir $(build)
