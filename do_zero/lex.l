%{
#include "grammar.tab.h"    
%}

%%
"FACA"                  {return FACA;}
"SER"                   {return SER;}
"MOSTRE"                {return MOSTRE;}
"ENCERRAR"              {return ENCERRAR;}
"SOME"                  {return SOME;}
"COM"                   {return COM;}
"MULTIPLIQUE"           {return MULTIPLIQUE;}
"POR"                   {return POR;}
"SUBTRAIA"              {return SUBTRAIA;}
"DE"                    {return DE;}
"REPITA"                {return REPITA;}    
"VEZES"                 {return VEZES;}
"FIM"                   {return FIM;}
"SE"                    {return SE;}
"ENTAO"                 {return ENTAO;}
"SENAO"                 {return SENAO;}
"FIMENTAO"              {return FIMENTAO;}
"FIMSENAO"              {return FIMSENAO;}

[a-zA-Z]+               {yylval.var = strdup(yytext); return var;}
[1-9][0-9]*             {yylval.num = atoi(yytext); return num;}
[ \t\n]                 ;
[();:]                  {return yytext[0];}
.                       ;

%%

int yywrap(void) {
    return 1;
}