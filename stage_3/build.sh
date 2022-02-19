clear
echo "building compiler ..."
lex explc.l
yacc -d explc.y
gcc y.tab.c lex.yy.c -o explc.out
echo "compiler build complete -> 'explc.out'"

echo "building linker ..."
gcc linker.c -o linker.out
echo "linker build complete -> 'linker.out'"