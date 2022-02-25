clear
lex explc.l
yacc -d explc.y
echo "building compiler ..."
gcc y.tab.c lex.yy.c -o explc
echo "compiler build complete -> 'explc'"

echo "building linker ..."
gcc linker.c -o linker
echo "linker build complete -> 'linker'"