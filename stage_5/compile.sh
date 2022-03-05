nasm -f elf32 -o out_x86.o out_x86.asm
ld.lld -m elf_i386 -o out_x86 out_x86.o bin/x86/library.a
printf 'running executable out_x86:\n'
./out_x86
printf '\nprogram exited with code %d\n' $?
