set -e
bison -d grammar.y
flex lex.l
gcc lex.yy.c grammar.tab.c -o grammar -ll
./grammar