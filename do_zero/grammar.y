%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PATH "output.c"

FILE* output = NULL;

struct var {
    char nome[31];
    int valor; 
};
typedef struct var Var;

struct vars_if {
    Var vars[100];
};
typedef struct vars_if VarsIF;

Var variaveis[100];
VarsIF variaveis_if[100] = {0};
int var_count = 0;
int ifs_count = 0;
int local_if_count = 0;

char* itoa(int num) {
    char* arr = (char*)malloc(30); 
    int index = 0;
    while (num > 0) {
        arr[index++] = (num % 10) + '0';
        num /= 10;
    }
    arr[index] = '\0';

    for (int i = 0; i < index / 2; i++) {
        char temp = arr[i];
        arr[i] = arr[index - i - 1];
        arr[index - i - 1] = temp;
    }
    return arr;
}

int get_valor_var(const char* nome) {
    for (int i = 0; i < var_count; i++) {
        printf("nome: %s valor: %d\n", variaveis[i].nome, variaveis[i].valor);
        if (strcmp(nome, variaveis[i].nome) == 0) {
            return variaveis[i].valor;
        }
    }
    printf("Erro: variavel %s nao foi encontrada\n", nome);
}

int var_ja_declarada_if(const char* var) {
    for (int i = 0; i < local_if_count; i++) {
        if (strcmp(var, variaveis_if[ifs_count].vars[i].nome) == 0) {
            return i;
        }
    }
    return -1;
}

int get_valor_var_if(const char* nome) {
    for (int i = 0; i < local_if_count; i++) {
        if (strcmp(nome, variaveis_if[ifs_count].vars[i].nome) == 0) {
            return variaveis_if[ifs_count].vars[i].valor;
        }
    }
    printf("Erro: variavel %s nao foi encontrada\n", nome);
}

void set_valor_var_if(char* varnome, int val) {
    for (int i = 0; i < local_if_count; i++) {
        if (strcmp(varnome, variaveis_if[ifs_count].vars[i].nome) == 0) {
            variaveis_if[ifs_count].vars[i].valor = val;
            return;
        }
    }
    strcpy(variaveis_if[ifs_count].vars[local_if_count].nome, varnome);
    variaveis_if[ifs_count].vars[local_if_count].valor = val;
    local_if_count++;
}

void set_valor_var(const char* nome, int valor) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variaveis[i].nome, nome) == 0) {
            variaveis[i].valor = valor;
            return;
        }
    }
    strcpy(variaveis[var_count].nome, nome);
    variaveis[var_count].valor = valor;
    var_count++;
}

void iniciar(void) {
    output = fopen(PATH, "w");
    fseek(output, 0, SEEK_SET);
    if (output == NULL) exit(1);
    fprintf(output, "#include <stdio.h>\n#include <stdlib.h>\n\nint main(void) {\n");
}


void exportar(const char* texto) {
    fprintf(output, "\t%s", texto);
    return;
}

void encerrar(void) {
    exportar("\n\treturn 0;\n}");
    exit(0);
}

int jaDeclarada(const char* variavel) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variavel, variaveis[i].nome) == 0) {
            return 1;
        }
    }
    return 0;
}

void exportar_atribuicao(const char* variavel, int valor) {
    char str_formatada[101];
    if (jaDeclarada(variavel)) {
        sprintf(str_formatada, "%s = %d;\n", variavel, valor);
        exportar(str_formatada);
    }
    else {
        sprintf(str_formatada, "int %s = %d;\n", variavel, valor);
        exportar(str_formatada);
    }
    return;
}

void exportar_atribuicao_if(const char* variavel, int valor) {
    char str_formatada[101];
    if (var_ja_declarada_if(variavel) >= 0) {
        sprintf(str_formatada, "%s = %d;\n", variavel, valor);
        exportar(str_formatada);
    }
    else {
        sprintf(str_formatada, "int %s = %d;\n", variavel, valor);
        exportar(str_formatada);
    }
    return;
}

void avanca_count_blocos_if(void) {
    int separacao = var_ja_declarada_if("else");
}

void exportar_impressao(const char* variavel) {
    char str_formatada[101];
    sprintf(str_formatada, "printf(\"Mostrando %s: %%d\\n\", %s);\n", variavel, variavel);
    exportar(str_formatada);
    return;
}

void exportar_operacao_soma(const char* variavel1, const char* variavel2) {
    char str_formatada[101];
    sprintf(str_formatada, "%s += %s;\n", variavel1, variavel2);
    exportar(str_formatada);
}

void exportar_operacao_diferenca(const char* variavel1, const char* variavel2) {
    char str_formatada[101];
    sprintf(str_formatada, "%s -= %s;\n", variavel1, variavel2);
    exportar(str_formatada);
}

void exportar_operacao_multiplicacao(const char* variavel1, const char* variavel2) {
    char str_formatada[101];
    sprintf(str_formatada, "%s *= %s;\n", variavel1, variavel2);
    exportar(str_formatada);
}

void exportar_repeticao(int vezes) {
    char str_formatada[101];
    sprintf(str_formatada, "for (int i = 0; i < %d; i++) {\n", vezes);
    exportar(str_formatada);
}

void exportar_identacao(void) {
    exportar("\t");
}

void exportar_fim_repeticao(void) {
    exportar("}\n");
}

void exportar_if(int num) {
    char str_formatada[101];
    sprintf(str_formatada, "if (%d) {\n", num);
    exportar(str_formatada);
}

void exportar_else(void) {
    exportar("else {\n");
}

void exportar_fim_condicao(void) {
    exportar("}\n");
}

void yyerror(char* s);
int yylex();
%}

%union{int num; char* var;}
%start programa
%token FACA
%token SER
%token MOSTRE
%token ENCERRAR
%token SOME
%token COM
%token MULTIPLIQUE
%token POR
%token SUBTRAIA
%token DE
%token REPITA
%token VEZES
%token FIM
%token SE
%token ENTAO
%token SENAO
%token FIMENTAO
%token FIMSENAO
%token <num> num
%token <var> var

%%

programa:
    cmds        {;}
    ;

cmds:
    cmd cmds    {;}
    | cmd       {;}
    ;

cmd         : 
                atribuicao                  {;}
                | impressao                 {;}
                | operacao                  {;}
                | repeticao                 {;}
                | condicao                  {}
                | encerrar                  {;}
            ;

atribuicao  :
                FACA var SER num ';'        { exportar_atribuicao($2, $4); set_valor_var($2, $4); }
            ;

impressao   :
                MOSTRE var ';'              { exportar_impressao($2); }       

operacao    :
                SOME var COM var ';'          { exportar_operacao_soma($2, $4); }
                | SOME var COM num ';'        { exportar_operacao_soma($2, itoa($4)); }
                | SUBTRAIA var DE num ';'     { exportar_operacao_diferenca($2, itoa($4)); }
                | SUBTRAIA var DE var ';'     { exportar_operacao_diferenca($2, $4); }
                | MULTIPLIQUE var POR num ';' { exportar_operacao_multiplicacao($2, itoa($4)); }
                | MULTIPLIQUE var POR var ';' { exportar_operacao_multiplicacao($2, $4); }
            ;

repeticao   :
                cabecalho cmds FIM      { exportar_fim_repeticao(); }
            ;

cabecalho   :
                REPITA num VEZES ':'    { exportar_repeticao($2); }
                | REPITA var VEZES ':'  { exportar_repeticao(get_valor_var($2)); }
            ;

condicao    :
                condicao_el     { avanca_count_blocos_if(); }
                | condicao_if   { avanca_count_blocos_if(); }

condicao_el :
                condicao_if condicional_senao cmds_if FIMSENAO  { exportar_fim_condicao(); }
            ;

condicao_if :
                condicional_se cmds_if FIMENTAO     { exportar_fim_condicao(); }
            ;

condicional_se:
                SE num ENTAO        { exportar_if($2); }
                | SE var ENTAO      { exportar_if(get_valor_var($2)); }
              ;

condicional_senao :
                        SENAO       { exportar_else(); } 
                  ;

cmds_if :
            cmd_if           {;}
            | cmd_if cmds_if {;}
        ;

cmd_if : 
            atribuicao_if               {;}
            | impressao                 {;}
            | operacao                  {;}
            | repeticao                 {;}
            | condicao                  {;}
            | encerrar                  {;}
       ;

atribuicao_if :
                    FACA var SER num ';'        { exportar_atribuicao_if($2, $4); set_valor_var_if($2, $4); }
              ;

encerrar    :
                ENCERRAR ';'        { encerrar(); exit(0); }    
            ;

%%

void yyerror(char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}

int main(void) {
    iniciar();
    return yyparse();
}