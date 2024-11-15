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
%token SER
%token NUM
%token VAR
%type <sval> NUM
%type <sval> VAR


%%

programa:
    | programa comando
    ;

comando:
    FACA VAR SER NUM              { printf("%s = %s;\n", $2, $4);  free($2); free($4);}
    | NUM                 { printf("Número encontrado: %s\n", $1); free($1); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}

int main() {
    return yyparse();
}
