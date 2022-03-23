#!/bin/sh -x

##  xsm assembly output
bin/compiler/explc -mode xsm -o bin/xsm/bubble_sort.labled test_programs/bubble_sort.expl
bin/compiler/explc -mode xsm -o bin/xsm/elif.labled test_programs/elif.expl
bin/compiler/explc -mode xsm -o bin/xsm/factorial.labled test_programs/factorial.expl
bin/compiler/explc -mode xsm -o bin/xsm/Fibonacci.labled test_programs/Fibonacci.expl
bin/compiler/explc -mode xsm -o bin/xsm/fizz-buzz.labled test_programs/fizz-buzz.expl
bin/compiler/explc -mode xsm -o bin/xsm/helloworld.labled test_programs/helloworld.expl
bin/compiler/explc -mode xsm -o bin/xsm/library.labled test_programs/library.expl
bin/compiler/explc -mode xsm -o bin/xsm/pointer.labled test_programs/pointer.expl
bin/compiler/explc -mode xsm -o bin/xsm/quick_sort.labled test_programs/quick_sort.expl
bin/compiler/explc -mode xsm -o bin/xsm/swap.labled test_programs/swap.expl
bin/compiler/explc -mode xsm -o bin/xsm/test.labled test_programs/test.expl
bin/compiler/explc -mode xsm -o bin/xsm/token.labled test_programs/token.expl

bin/compiler/linker -o bin/xsm/bubble_sort.xsm bin/xsm/bubble_sort.labled
bin/compiler/linker -o bin/xsm/elif.xsm bin/xsm/elif.labled
bin/compiler/linker -o bin/xsm/factorial.xsm bin/xsm/factorial.labled
bin/compiler/linker -o bin/xsm/Fibonacci.xsm bin/xsm/Fibonacci.labled
bin/compiler/linker -o bin/xsm/fizz-buzz.xsm bin/xsm/fizz-buzz.labled
bin/compiler/linker -o bin/xsm/helloworld.xsm bin/xsm/helloworld.labled
bin/compiler/linker -o bin/xsm/library.xsm bin/xsm/library.labled
bin/compiler/linker -o bin/xsm/pointer.xsm bin/xsm/pointer.labled
bin/compiler/linker -o bin/xsm/quick_sort.xsm bin/xsm/quick_sort.labled
bin/compiler/linker -o bin/xsm/swap.xsm bin/xsm/swap.labled
bin/compiler/linker -o bin/xsm/test.xsm bin/xsm/test.labled
bin/compiler/linker -o bin/xsm/token.xsm bin/xsm/token.labled

## x86 32 bit assembly output
# bin/compiler/explc -mode x86 -o bin/x86/array.asm test_programs/x86_programs/array.expl
# bin/compiler/explc -mode x86 -o bin/x86/helloworld.asm test_programs/x86_programs/helloworld.expl
# bin/compiler/explc -mode x86 -o bin/x86/pointer.asm test_programs/x86_programs/pointer.expl
# bin/compiler/explc -mode x86 -o bin/x86/test.asm test_programs/x86_programs/test.expl
# bin/compiler/explc -mode x86 -o bin/x86/token.asm test_programs/x86_programs/token.expl
# bin/compiler/explc -mode x86 -o bin/x86/multi_array.asm test_programs/x86_programs/multi_array.expl

# nasm -f elf32 -o bin/x86/array.o bin/x86/array.asm
# nasm -f elf32 -o bin/x86/helloworld.o bin/x86/helloworld.asm
# nasm -f elf32 -o bin/x86/pointer.o bin/x86/pointer.asm
# nasm -f elf32 -o bin/x86/test.o bin/x86/test.asm
# nasm -f elf32 -o bin/x86/token.o bin/x86/token.asm
# nasm -f elf32 -o bin/x86/multi_array.o bin/x86/multi_array.asm

# ld.lld -nostdlib -m elf_i386 -o bin/x86/array bin/x86/array.o bin/lib/library.a
# ld.lld -nostdlib -m elf_i386 -o bin/x86/helloworld bin/x86/helloworld.o bin/lib/library.a
# ld.lld -nostdlib -m elf_i386 -o bin/x86/pointer bin/x86/pointer.o bin/lib/library.a
# ld.lld -nostdlib -m elf_i386 -o bin/x86/test bin/x86/test.o bin/lib/library.a
# ld.lld -nostdlib -m elf_i386 -o bin/x86/token bin/x86/token.o bin/lib/library.a
# ld.lld -nostdlib -m elf_i386 -o bin/x86/multi_array bin/x86/multi_array.o bin/lib/library.a

## c code output x86 programs
# bin/compiler/explc -mode c -o bin/c/array.c test_programs/x86_programs/array.expl
# bin/compiler/explc -mode c -o bin/c/helloworld.c test_programs/x86_programs/helloworld.expl
# bin/compiler/explc -mode c -o bin/c/pointer.c test_programs/x86_programs/pointer.expl
# bin/compiler/explc -mode c -o bin/c/test.c test_programs/x86_programs/test.expl
# bin/compiler/explc -mode c -o bin/c/token.c test_programs/x86_programs/token.expl

# clang -nostdlib -m32 -O3 -c -o bin/c/array.o bin/c/array.c
# clang -nostdlib -m32 -O3 -c -o bin/c/helloworld.o bin/c/helloworld.c
# clang -nostdlib -m32 -O3 -c -o bin/c/pointer.o bin/c/pointer.c
# clang -nostdlib -m32 -O3 -c -o bin/c/test.o bin/c/test.c
# clang -nostdlib -m32 -O3 -c -o bin/c/token.o bin/c/token.c

# ld.lld -e main -nostdlib -m elf_i386 -o bin/c/array bin/c/array.o bin/lib/library.a
# ld.lld -e main -nostdlib -m elf_i386 -o bin/c/helloworld bin/c/helloworld.o bin/lib/library.a
# ld.lld -e main -nostdlib -m elf_i386 -o bin/c/pointer bin/c/pointer.o bin/lib/library.a
# ld.lld -e main -nostdlib -m elf_i386 -o bin/c/test bin/c/test.o bin/lib/library.a
# ld.lld -e main -nostdlib -m elf_i386 -o bin/c/token bin/c/token.o bin/lib/library.a

## c code output
# bin/compiler/explc -mode c -o bin/c/bubble_sort.c test_programs/bubble_sort.expl
# bin/compiler/explc -mode c -o bin/c/elif.c test_programs/elif.expl
# bin/compiler/explc -mode c -o bin/c/factorial.c test_programs/factorial.expl
# bin/compiler/explc -mode c -o bin/c/Fibonacci.c test_programs/Fibonacci.expl
# bin/compiler/explc -mode c -o bin/c/fizz-buzz.c test_programs/fizz-buzz.expl
# bin/compiler/explc -mode c -o bin/c/helloworld.c test_programs/helloworld.expl
# bin/compiler/explc -mode c -o bin/c/library.c test_programs/library.expl
# bin/compiler/explc -mode c -o bin/c/pointer.c test_programs/pointer.expl
# bin/compiler/explc -mode c -o bin/c/swap.c test_programs/swap.expl
# bin/compiler/explc -mode c -o bin/c/test.c test_programs/test.expl
# bin/compiler/explc -mode c -o bin/c/token.c test_programs/token.expl

# gcc -O3 -o bin/c/bubble_sort bin/c/bubble_sort.c
# gcc -O3 -o bin/c/elif bin/c/elif.c
# gcc -O3 -o bin/c/factorial bin/c/factorial.c
# gcc -O3 -o bin/c/Fibonacci bin/c/Fibonacci.c
# gcc -O3 -o bin/c/fizz-buzz bin/c/fizz-buzz.c
# gcc -O3 -o bin/c/helloworld bin/c/helloworld.c
# gcc -O3 -o bin/c/library bin/c/library.c
# gcc -O3 -o bin/c/pointer bin/c/pointer.c
# gcc -O3 -o bin/c/swap bin/c/swap.c
# gcc -O3 -o bin/c/test bin/c/test.c
# gcc -O3 -o bin/c/token bin/c/token.c