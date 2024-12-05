%{
#include "grammar.tab.h"    
%}

%%
"FACA"                  { return FACA; }
"SER"                   { return SER; }
"MOSTRE"                { return MOSTRE; }
"ENCERRAR"              { return ENCERRAR; }
"SOME"                  { return SOME; }
"COM"                   { return COM; }
"MULTIPLIQUE"           { return MULTIPLIQUE; }
"POR"                   { return POR; }
"SUBTRAIA"              { return SUBTRAIA; }
"DE"                    { return DE; }
"REPITA"                { return REPITA; }    
"VEZES"                 { return VEZES; }
"FIM"                   { return FIM; }
"SE"                    { return SE; }
"ENTAO"                 { return ENTAO; }
"SENAO"                 { return SENAO; }
"FIMENTAO"              { return FIMENTAO; }
"FIMSENAO"              { return FIMSENAO; }

[a-zA-Z]+               { yylval.str_val = strdup(yytext); return VAR; }
[1-9][0-9]*             { yylval.int_val = atoi(yytext); return NUM; }
[ \t\n]                 { /* Ignora espaços, tabulações e novas linhas */ }
[();:]                  { return yytext[0]; }
.                       { /* Ignora caracteres não reconhecidos */ }

%%

int yywrap(void) {
    return 1;
}
