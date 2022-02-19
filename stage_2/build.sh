clear
lex explc.l
yacc -d explc.y
gcc y.tab.c lex.yy.c -o explc.out