
nasm -f elf32 test.asm
nasm -f elf32 misc.asm
gcc -m32 -c *.c
ld -m elf_i386 -s -o test test.o misc.o test_c.o

echo ""
echo "=============run==============="
./test
