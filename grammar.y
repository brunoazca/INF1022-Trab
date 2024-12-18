%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PATH "output.c"


void yyerror(const char *s);

int yylex(void);

extern FILE* yyin;
FILE* output = NULL;

struct var {
    char nome[31];
    float valor;
};
typedef struct var Var;

Var variaveis[100];
int var_count = 0;
int num_ident = 0;
int num_ident_anterior = 0;

char* itoa(int num) {
    char* arr = (char*)malloc(30); 
    int index = 0;
    if (num == 0) { 
        arr[index++] = '0';
    } else {
        while (num > 0) {
            arr[index++] = (num % 10) + '0';
            num /= 10;
        }
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
        if (strcmp(nome, variaveis[i].nome) == 0) {
            return variaveis[i].valor;
        }
    }
    fprintf(stderr, "Erro: variavel '%s' nao foi encontrada\n", nome);
    exit(1);
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
    if (output == NULL) {
        fprintf(stderr, "Erro ao abrir arquivo de saída\n");
        exit(1);
    }
    fprintf(output, "#include <stdio.h>\n#include <stdlib.h>\n\nint main(void) {\n");
}

void exportar(const char* texto) {
    for(int i = num_ident; i > 0; i--){
        fprintf(output, "\t");
    }

    fprintf(output, "\t%s", texto);
}

int jaDeclarada(const char* variavel) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variavel, variaveis[i].nome) == 0) {
            return 1;
        }
    }
    return 0;
}

void exportar_atribuicao(const char* variavel, float valor) {
    char str_formatada[101];
    if (jaDeclarada(variavel)) {
        sprintf(str_formatada, "%s = %.0f;\n", variavel, valor);
        exportar(str_formatada);
    } else{
        fprintf(stderr, "Erro: variavel nao declarada\n");
        exit(1);
    }
}


void exportar_atribuicao_float(const char* variavel, float valor) {
    char str_formatada[101];
    if (jaDeclarada(variavel)) {
        sprintf(str_formatada, "%s = %f;\n", variavel, valor);
        exportar(str_formatada);
    } else{
        fprintf(stderr, "Erro: variavel nao declarada\n");
        exit(1);
    }
}


void exportar_nova_atribuicao_float(const char* variavel, float valor) {
    char str_formatada[101];
    sprintf(str_formatada, "float %s = %f;\n", variavel, valor);
    exportar(str_formatada);
}

void exportar_nova_atribuicao(const char* variavel, float valor) {
    char str_formatada[101];
    sprintf(str_formatada, "int %s = %.0f;\n", variavel, valor);
    exportar(str_formatada);
}

void exportar_nova_atribuicao_vazia(const char* variavel) {
    char str_formatada[101];
    sprintf(str_formatada, "int %s;\n", variavel);
    exportar(str_formatada);
}

void exportar_impressao(const char* variavel) {
    char str_formatada[101];
    sprintf(str_formatada, "printf(\"Mostrando %s: %%f\\n\", (double)%s);\n", variavel, variavel);
    exportar(str_formatada);
}

void exportar_impressao_num(int num) {
    char str_formatada[101];
    sprintf(str_formatada, "printf(\"Mostrando %d\\n\");\n", num);
    exportar(str_formatada);
}


void exportar_impressao_float(float num) {
    char str_formatada[101];
    sprintf(str_formatada, "printf(\"Mostrando %f\\n\");\n", num);
    exportar(str_formatada);
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


void exportar_operacao_soma_num(const char* variavel1, float num) {
    char str_formatada[101];
    sprintf(str_formatada, "%s += %.0f;\n", variavel1, num);
    exportar(str_formatada);
}

void exportar_operacao_diferenca_num(const char* variavel1, float num) {
    char str_formatada[101];
    sprintf(str_formatada, "%s -= %.0f;\n", variavel1, num);
    exportar(str_formatada);
}

void exportar_operacao_multiplicacao_num(const char* variavel1, float num) {
    char str_formatada[101];
    sprintf(str_formatada, "%s *= %.0f;\n", variavel1, num);

    exportar(str_formatada);
}

void exportar_operacao_soma_float(const char* variavel1, float num) {
    char str_formatada[101];
    sprintf(str_formatada, "%s += %f;\n", variavel1, num);
    exportar(str_formatada);
}

void exportar_operacao_diferenca_float(const char* variavel1, float num) {
    char str_formatada[101];
    sprintf(str_formatada, "%s -= %f;\n", variavel1, num);
    exportar(str_formatada);
}

void exportar_operacao_multiplicacao_float(const char* variavel1, float num) {
    char str_formatada[101];
    sprintf(str_formatada, "%s *= %f;\n", variavel1, num);

    exportar(str_formatada);
}

void exportar_repeticao(float vezes) {
    char str_formatada[101];
    sprintf(str_formatada, "for (int i = 0; i < %.0f; i++) {\n", vezes);

    exportar(str_formatada);
}

void exportar_fim_repeticao() {
    exportar("}\n");
}


void exportar_conteudo_if_var(char* var) {
    char str_formatada[101];
    sprintf(str_formatada, "%s", var);
    
    exportar(str_formatada);

}
void exportar_conteudo_if_num(float num) {
    char str_formatada[101];
    sprintf(str_formatada, "%.0f", num);
    
    exportar(str_formatada);
}

void exportar_conteudo_if_float(float num) {
    char str_formatada[101];
    sprintf(str_formatada, "%f", num);
    
    exportar(str_formatada);
}


%}

%union {float num; char* var; float floatnum;}
%start programa
%token FACA NOVO SER MOSTRE SOME COM MULTIPLIQUE POR SUBTRAIA DE REPITA VEZES FIM SE ENTAO SENAO FIMENTAO 
%token <num> num
%token <var> var
%token <floatnum> floatnum


%%

programa:
    cmds {;}
    ;

cmds:
    cmd cmds {;}
    | cmd {;}
    ;

cmd:
    atribuicao {;}
    | impressao {;}
    | operacao {;}
    | repeticao {;}
    | condicao {;}
    ;

atribuicao:
    FACA NOVO var SER num ';' { exportar_nova_atribuicao($3, $5); set_valor_var($3, $5); }
    | FACA var SER num ';' { exportar_atribuicao($2, $4); set_valor_var($2, $4); }
    | FACA NOVO var SER floatnum ';' { exportar_nova_atribuicao_float($3, $5); set_valor_var($3, $5); }
    | FACA var SER floatnum ';' { exportar_atribuicao_float($2, $4); set_valor_var($2, $4); }
    | FACA NOVO var ';' { exportar_nova_atribuicao_vazia($3); set_valor_var($3, 0);}
    ;

impressao:
    MOSTRE var ';' { exportar_impressao($2); }
    | MOSTRE num ';' { exportar_impressao_num($2); }
    | MOSTRE floatnum ';' { exportar_impressao_float($2); }
    ;

operacao:
    SOME var COM var ';' { exportar_operacao_soma($2, $4); }
    | SUBTRAIA var DE var ';' { exportar_operacao_diferenca($2, $4); }
    | MULTIPLIQUE var POR var ';' { exportar_operacao_multiplicacao($2, $4); }
    | SOME var COM num ';' { exportar_operacao_soma_num($2, $4); }
    | SUBTRAIA var DE num ';' { exportar_operacao_diferenca_num($2, $4); }
    | MULTIPLIQUE var POR num ';' { exportar_operacao_multiplicacao_num($2, $4); }
    | SOME var COM floatnum ';' { exportar_operacao_soma_float($2, $4); }
    | SUBTRAIA var DE floatnum ';' { exportar_operacao_diferenca_float($2, $4); }
    | MULTIPLIQUE var POR floatnum ';' { exportar_operacao_multiplicacao_float($2, $4); }
    ;


repeticao:
    REPITA num VEZES ':'{exportar_repeticao($2); num_ident++;}
    cmds 
    FIM { num_ident--;exportar_fim_repeticao(); }
    ;

condicao:
    SE 
    { num_ident_anterior = num_ident; ; exportar("if("); num_ident = 0;} 
    expr_bool 
    ENTAO 
    {  exportar(") {\n"); num_ident = num_ident_anterior + 1;}  
    cmds
    senao
    FIMENTAO 
    {  num_ident--; exportar("}\n");};

senao:
    SENAO { num_ident--; exportar( "} else {\n");num_ident++; }
    cmds
    | 
    {;}

expr_bool:
    var{  exportar_conteudo_if_var($1);}
    |
    num {  exportar_conteudo_if_num($1); };
    |
    floatnum {  exportar_conteudo_if_float($1); };

    

%%



void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(int argc, char* argv[]) {
    iniciar();
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    // Imprimir o conteúdo do arquivo
    printf("Conteúdo do arquivo %s:\n", argv[1]);
    char c;
    while ((c = fgetc(yyin)) != EOF) {
        putchar(c);  // Imprime o caractere lido
    }
    rewind(yyin);

    yyparse();
    
    printf("\n");
    fprintf(output, "\n\treturn 0;\n}");
    fclose(output);
    return 0;
}
