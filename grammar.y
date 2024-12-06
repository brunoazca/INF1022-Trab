%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PATH "output.c"


void yyerror(const char *s);

int yylex();

extern FILE* yyin;
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
    fprintf(output, "\t%s", texto);
}

void encerrar(void) {
    exportar("\n\treturn 0;\n}");
    fclose(output);
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
    } else {
        sprintf(str_formatada, "int %s = %d;\n", variavel, valor);
        exportar(str_formatada);
    }
}

void exportar_impressao(const char* variavel) {
    char str_formatada[101];
    sprintf(str_formatada, "printf(\"Mostrando %s: %%d\\n\", %s);\n", variavel, variavel);
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

void exportar_repeticao(int vezes) {
    char str_formatada[101];
    sprintf(str_formatada, "for (int i = 0; i < %d; i++) {\n", vezes);
    exportar(str_formatada);
}

void exportar_fim_repeticao(void) {
    exportar("}\n");
}

void exportar_if_num(int num) {
    char str_formatada[101];
    sprintf(str_formatada, "if (%d) {\n", num);
    exportar(str_formatada);
}

void exportar_if_var(char* var) {
    char str_formatada[101];
    sprintf(str_formatada, "if (%s) {\n", var);
    exportar(str_formatada);
}

void exportar_else(void) {
    exportar("else {\n");
}

void exportar_fim_condicao(void) {
    exportar("}\n");
}

void avanca_count_blocos_if(void) {
    ifs_count++;
    local_if_count = 0;
}




%}

%union {int num; char* var;}
%start programa
%token FACA SER MOSTRE ENCERRAR SOME COM MULTIPLIQUE POR SUBTRAIA DE REPITA VEZES FIM SE ENTAO SENAO FIMENTAO FIMSENAO
%token <num> num
%token <var> var

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
    | encerrar {;}
    ;

atribuicao:
    FACA var SER num ';' { exportar_atribuicao($2, $4); set_valor_var($2, $4); }
    ;

impressao:
    MOSTRE var ';' { exportar_impressao($2); }
    ;

operacao:
    SOME var COM var ';' { exportar_operacao_soma($2, $4); }
    | SUBTRAIA var DE var ';' { exportar_operacao_diferenca($2, $4); }
    | MULTIPLIQUE var POR var ';' { exportar_operacao_multiplicacao($2, $4); }
    ;

repeticao:
    REPITA num VEZES ':' cmds FIM { exportar_repeticao($2); exportar_fim_repeticao(); }
    ;

condicao:
    SE num ENTAO cmds FIMENTAO { exportar_if_num($2); exportar_fim_condicao(); }
    | SE num ENTAO cmds SENAO cmds FIMSENAO { exportar_if_num($2); exportar_else(); exportar_fim_condicao(); }
    | SE var ENTAO cmds FIMENTAO { exportar_if_var($2); exportar_else(); exportar_fim_condicao(); }
    | SE var ENTAO cmds SENAO cmds FIMSENAO { exportar_if_var($2); exportar_else(); exportar_fim_condicao(); }
    ;

encerrar:
    ENCERRAR ';' { encerrar(); }
    ;

%%



void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    // Abrir o arquivo especificado
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
    printf("\n");

    // Iniciar o parsing
    if (yyparse() != 0) {
        fprintf(stderr, "Erro durante o parsing.\n");
        fclose(yyin);
        return 1;
    } 

    return 0;
}
