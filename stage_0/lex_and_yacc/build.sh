clear
lex $1
yacc -d $2
gcc y.tab.c lex.yy.c