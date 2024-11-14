%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void yyerror(const char *s);
    int yylex();
%}

%union {
    char *sval;
}

%token FACA
%token NUM
%type <sval> NUM

%%

programa:
    | programa comando
    ;

comando:
    FACA                  { printf("Comando 'FACA' encontrado.\n"); }
    | NUM                 { printf("Número encontrado: %s\n", $1); free($1); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}

int main() {
    return yyparse();
}
