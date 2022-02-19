clear
lex expr.l
yacc -d expr.y
gcc y.tab.c lex.yy.c