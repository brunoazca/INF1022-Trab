%{
#include "grammar.tab.h"  // Bison's generated header file
#include <string.h>
%}

%%
"FACA"|"faca"           { return FACA; }
"SER"|"ser"             { return SER; }
"MOSTRE"|"mostre"       { return MOSTRE; }
"MOSTRANDO"|"mostrando" { return MOSTRANDO; }
"SOME"|"some"           { return SOME; }
"MULTIPLIQUE"|"multiplique"           { return MULTIPLIQUE; }
"COM"|"com"             { return COM; }
"REPITA"|"repita"       { return REPITA; }
"VEZES:"|"vezes:"       { return VEZES; }
"FIM"|"fim"             { return FIM; }
"SE"                    { return SE; }
"ENTAO"                 {  return ENTAO; }
"SENAO"                 {  return SENAO; }
"FIM DO SE"             {  return FIMDOSE; }
"FOR IGUAL A"           {  return FOR_IGUAL; }
"FOR MENOR QUE"         {  return FOR_MENOR; }
"FOR MAIOR QUE"         {  return FOR_MAIOR; }
"OU"                    {  return OU; }
"E"                     {  return E; }
"."                   { return EOL; }
[ \t\n]+              { /* Ignore whitespace */ }
[0-9]+                { 
                          yylval.sval = strdup(yytext); 
                          return num; 
                        }
[a-zA-Z_][a-zA-Z0-9_]* { 
                          yylval.sval = strdup(yytext); 
                          return var; 
                        }
.                     { printf("Unknown character: %s\n", yytext); }

%%

int yywrap() { return 1; }
