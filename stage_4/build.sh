clear
lex explc.l
yacc -d explc.y
echo "building compiler ..."
gcc y.tab.c lex.yy.c -o explc.out
echo "compiler build complete -> 'explc.out'"

echo "building linker ..."
gcc linker.c -o linker.out
echo "linker build complete -> 'linker.out'"