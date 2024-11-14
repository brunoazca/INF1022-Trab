%{
    #include "grammar.tab.h"
    #include <string.h>
%}

%%
"FACA" {return FACA;}
[1-9][0-9]+ {yylval.sval = strdup(yytext); return NUM;}
[ \t\n]+            { /* Ignora espaços, tabs e novas linhas */ }
.                   { /* Ignora caracteres não reconhecidos */ }

%%


int yywrap() {
    return 1;
}
