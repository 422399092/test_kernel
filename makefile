asm      = nasm
cc       = gcc
ld       = ld -s
build    = bin

incs	     = include
asm_incs   = include/asm
libs	     = lib
boot_src   = boot
kernel_src = kernel

cc_flg32 = -I$(incs) -fno-builtin -fno-builtin-FUNCTION -nostdinc -m32 -c

all: sys.img

sys.img: clean boot.bin libs.bin kernel.bin
	$(asm) -f bin $(boot_src)/makeboot.s -o bin/sys.img

boot.bin:
	$(asm) -f bin $(boot_src)/boot.s -o $(build)/boot.bin

kernel.bin:
	$(cc) $(cc_flg32) $(kernel_src)/mm/mm.c -o $(build)/mm.o
	$(cc) $(cc_flg32) $(kernel_src)/init.c -o $(build)/init.o
	$(asm) -f elf32 $(kernel_src)/enter.s -o $(build)/enter.o
	$(ld) -T makefile.lds -m elf_i386 -o $(build)/kernel.bin $(build)/*.o

libs.bin: $(asm_incs)/const.s
	$(asm) -f elf32 -I $(asm_incs)/ -o $(build)/x86print.o $(asm_incs)/x86print.s
	$(asm) -f elf32 -I $(asm_incs)/ -o $(build)/x86mem.o $(asm_incs)/x86mem.s

clean:
	rm -rf $(build)
	mkdir $(build)
