clear
lex explc.l
yacc -d explc.y
echo "building compiler ..."
gcc -g y.tab.c lex.yy.c -o explc
echo "compiler build complete -> 'explc'"

echo "building linker ..."
gcc -g linker.c -o linker
echo "linker build complete -> 'linker'"