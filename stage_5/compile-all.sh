#!/bin/sh -x

##  xsm assembly output
# bin/compiler/explc -mode xsm -o bin/xsm/bubble_sort.labled test_programs/bubble_sort.expl
# bin/compiler/explc -mode xsm -o bin/xsm/elif.labled test_programs/elif.expl
# bin/compiler/explc -mode xsm -o bin/xsm/factorial.labled test_programs/factorial.expl
# bin/compiler/explc -mode xsm -o bin/xsm/Fibonacci.labled test_programs/Fibonacci.expl
# bin/compiler/explc -mode xsm -o bin/xsm/fizz-buzz.labled test_programs/fizz-buzz.expl
# bin/compiler/explc -mode xsm -o bin/xsm/helloworld.labled test_programs/helloworld.expl
# bin/compiler/explc -mode xsm -o bin/xsm/library.labled test_programs/library.expl
# bin/compiler/explc -mode xsm -o bin/xsm/pointer.labled test_programs/pointer.expl
# bin/compiler/explc -mode xsm -o bin/xsm/swap.labled test_programs/swap.expl
# bin/compiler/explc -mode xsm -o bin/xsm/test.labled test_programs/test.expl
# bin/compiler/explc -mode xsm -o bin/xsm/token.labled test_programs/token.expl

# bin/compiler/linker -o bin/xsm/bubble_sort.xsm bin/xsm/bubble_sort.labled
# bin/compiler/linker -o bin/xsm/elif.xsm bin/xsm/elif.labled
# bin/compiler/linker -o bin/xsm/factorial.xsm bin/xsm/factorial.labled
# bin/compiler/linker -o bin/xsm/Fibonacci.xsm bin/xsm/Fibonacci.labled
# bin/compiler/linker -o bin/xsm/fizz-buzz.xsm bin/xsm/fizz-buzz.labled
# bin/compiler/linker -o bin/xsm/helloworld.xsm bin/xsm/helloworld.labled
# bin/compiler/linker -o bin/xsm/library.xsm bin/xsm/library.labled
# bin/compiler/linker -o bin/xsm/pointer.xsm bin/xsm/pointer.labled
# bin/compiler/linker -o bin/xsm/swap.xsm bin/xsm/swap.labled
# bin/compiler/linker -o bin/xsm/test.xsm bin/xsm/test.labled
# bin/compiler/linker -o bin/xsm/token.xsm bin/xsm/token.labled

## x86 32 bit assembly output
# bin/compiler/explc -mode x86 -o bin/x86/bubble_sort.asm test_programs/bubble_sort.expl
# bin/compiler/explc -mode x86 -o bin/x86/elif.asm test_programs/elif.expl
# bin/compiler/explc -mode x86 -o bin/x86/factorial.asm test_programs/factorial.expl
# bin/compiler/explc -mode x86 -o bin/x86/Fibonacci.asm test_programs/Fibonacci.expl
# bin/compiler/explc -mode x86 -o bin/x86/fizz-buzz.asm test_programs/fizz-buzz.expl
# bin/compiler/explc -mode x86 -o bin/x86/helloworld.asm test_programs/helloworld.expl
# bin/compiler/explc -mode x86 -o bin/x86/library.asm test_programs/library.expl
# bin/compiler/explc -mode x86 -o bin/x86/pointer.asm test_programs/pointer.expl
# bin/compiler/explc -mode x86 -o bin/x86/swap.asm test_programs/swap.expl
# bin/compiler/explc -mode x86 -o bin/x86/test.asm test_programs/test.expl
# bin/compiler/explc -mode x86 -o bin/x86/token.asm test_programs/token.expl

# nasm -f elf32 -o bin/x86/bubble_sort.o bin/x86/bubble_sort.asm
# nasm -f elf32 -o bin/x86/elif.o bin/x86/elif.asm
# nasm -f elf32 -o bin/x86/factorial.o bin/x86/factorial.asm
# nasm -f elf32 -o bin/x86/Fibonacci.o bin/x86/Fibonacci.asm
# nasm -f elf32 -o bin/x86/fizz-buzz.o bin/x86/fizz-buzz.asm
# nasm -f elf32 -o bin/x86/helloworld.o bin/x86/helloworld.asm
# nasm -f elf32 -o bin/x86/library.o bin/x86/library.asm
# nasm -f elf32 -o bin/x86/pointer.o bin/x86/pointer.asm
# nasm -f elf32 -o bin/x86/swap.o bin/x86/swap.asm
# nasm -f elf32 -o bin/x86/test.o bin/x86/test.asm
# nasm -f elf32 -o bin/x86/token.o bin/x86/token.asm

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
