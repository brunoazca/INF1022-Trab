# set -e
# bison -d grammar.y -Wconflicts-sr -Wconflicts-rr -Wcounterexamples
# flex lex.l
# gcc lex.yy.c grammar.tab.c -o grammar -ll
# ./grammar
#!/bin/bash

# Verificar se o arquivo grammar.y existe
if [ ! -f "grammar.y" ]; then
    echo "Erro: grammar.y não encontrado."
    # exit 1
fi
# Verificar se o arquivo lex.l existe
if [ ! -f "lex.l" ]; then
    echo "Erro: lex.l não encontrado."
    # exit 1
fi
# Rodar o bison
bison -d grammar.y -Wconflicts-sr -Wconflicts-rr -Wcounterexamples
if [ $? -ne 0 ]; then
    echo "Erro ao rodar o bison."
    # exit 1
fi
# Rodar o lex
lex lex.l
if [ $? -ne 0 ]; then
    echo "Erro ao rodar o lex."
    # exit 1
fi

gcc -o grammar grammar.tab.c lex.yy.c -ll
if [ $? -ne 0 ]; then
    echo "Erro ao compilar com gcc."
    # exit 1
fi
# Rodar o executável
./grammar entrada.mag
if [ $? -ne 0 ]; then
    echo "Erro ao rodar o executável grammar."
    # exit 1
fi