set -e
bison -d grammar.y
lex lex.l
gcc grammar.tab.c lex.yy.c -o grammar -ll
./grammar