#!/bin/bash
clear
rm lex.yy.c a.out
lex $1
gcc lex.yy.c -lfl
