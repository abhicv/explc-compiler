nasm -f elf32 -o out_x86.o out_x86.asm
ld -m elf_i386 -o out_x86 out_x86.o
echo "elf32 executable output:"
./out_x86
