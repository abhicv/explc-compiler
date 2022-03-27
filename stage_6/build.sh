clear
lex -o source/lexer.c source/explc.l
yacc -d -o source/parser.c source/explc.y

echo "building compiler ..."
gcc -o bin/compiler/explc source/parser.c source/lexer.c
echo "compiler build finished -> bin/compiler/explc"

echo "building linker ..."
gcc -o bin/compiler/linker source/linker.c
echo "linker build finished -> bin/compiler/linker"
