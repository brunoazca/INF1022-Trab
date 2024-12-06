%{
    #include "grammar.tab.h"
%}

%%
"FACA"                  { return FACA; }
"NOVO"                  { return NOVO; }
"SER"                   { return SER; }
"MOSTRE"                { return MOSTRE; }
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

[a-zA-Z]+               { yylval.var = strdup(yytext); return var; }
0|([1-9][0-9]*)   { yylval.num = atoi(yytext); return num; }
[0-9]+\.[0-9]+          { yylval.floatnum = atof(yytext); return floatnum; }
[ \t\n]                 { /* Ignora espaços, tabulações e novas linhas */ }
[();:]                  { return yytext[0]; }
.                       { /* Ignora caracteres não reconhecidos */ }

%%



int yywrap(void) {
    return 1;
}
