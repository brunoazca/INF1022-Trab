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
    int valor; 
};
typedef struct var Var;

Var variaveis[100];
int var_count = 0;
char buffer_cmds[1024];
int buffer_pos = 0;


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

void limpar_buffer() {
    memset(buffer_cmds, 0, sizeof(buffer_cmds));
    buffer_pos = 0;
}

void adicionar_ao_buffer(const char* texto) {
   
    int len = strlen(texto);
    if (buffer_pos + len < sizeof(buffer_cmds)) {
        strcpy(buffer_cmds + buffer_pos, texto);
        buffer_pos += len;
    } else {
        fprintf(stderr, "Erro: buffer de comandos excedido\n");
        exit(1);
    }
}

void exportar_buffer() {
    exportar(buffer_cmds);
    limpar_buffer();  // Limpa o buffer após exportar
}

void encerrar(void) {
    exportar_buffer();
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

void exportar_atribuicao(const char* variavel, int valor, int ehBuffer) {
    char str_formatada[101];
    if (jaDeclarada(variavel)) {
        sprintf(str_formatada, "%s = %d;\n", variavel, valor);
        if(ehBuffer){
            adicionar_ao_buffer(str_formatada);
        } else{
            exportar(str_formatada);
        }
    } else{
        fprintf(stderr, "Erro: variavel nao declarada\n");
        exit(1);
    }
}


void exportar_nova_atribuicao(const char* variavel, int valor, int ehBuffer) {
    char str_formatada[101];
    sprintf(str_formatada, "int %s = %d;\n", variavel, valor);
    if(ehBuffer){
        adicionar_ao_buffer(str_formatada);
    } else{
        exportar(str_formatada);
    }
}



void exportar_nova_atribuicao_vazia(const char* variavel, int ehBuffer) {
    char str_formatada[101];
    sprintf(str_formatada, "int %s;\n", variavel);
    if(ehBuffer){
        adicionar_ao_buffer(str_formatada);
    } else{
        exportar(str_formatada);
    }}

void exportar_impressao(const char* variavel, int ehBuffer) {
    char str_formatada[101];
    sprintf(str_formatada, "printf(\"Mostrando %s: %%d\\n\", %s);\n", variavel, variavel);
    if(ehBuffer){
        adicionar_ao_buffer(str_formatada);
    } else{
        exportar(str_formatada);
    }}

void exportar_operacao_soma(const char* variavel1, const char* variavel2, int ehBuffer) {
    char str_formatada[101];
    sprintf(str_formatada, "%s += %s;\n", variavel1, variavel2);
    if(ehBuffer){
        adicionar_ao_buffer(str_formatada);
    } else{
        exportar(str_formatada);
    }}

void exportar_operacao_diferenca(const char* variavel1, const char* variavel2, int ehBuffer) {
    char str_formatada[101];
    sprintf(str_formatada, "%s -= %s;\n", variavel1, variavel2);
    if(ehBuffer){
        adicionar_ao_buffer(str_formatada);
    } else{
        exportar(str_formatada);
    }}

void exportar_operacao_multiplicacao(const char* variavel1, const char* variavel2, int ehBuffer) {
    char str_formatada[101];
    sprintf(str_formatada, "%s *= %s;\n", variavel1, variavel2);
    if(ehBuffer){
        adicionar_ao_buffer(str_formatada);
    } else{
        exportar(str_formatada);
    }
}

void exportar_repeticao(int vezes, int ehBuffer) {
    char str_formatada[101];
    sprintf(str_formatada, "for (int i = 0; i < %d; i++) {\n", vezes);

    if(ehBuffer){
        adicionar_ao_buffer(str_formatada);
    } else{
        exportar(str_formatada);
        exportar_buffer();

    }

}

void exportar_fim_repeticao(int ehBuffer) {
    if(ehBuffer){
        adicionar_ao_buffer("}\n");
    } else{
        exportar("}\n");
    }
}


void exportar_conteudo_if_var(char* var) {
    char str_formatada[101];
    sprintf(str_formatada, "%s", var);
    
    exportar(str_formatada);

}
void exportar_conteudo_if_num(int num) {
    char str_formatada[101];
    sprintf(str_formatada, "%d", num);
    
    exportar(str_formatada);

}



%}

%union {int num; char* var;}
%start programa
%token FACA NOVO SER MOSTRE ENCERRAR SOME COM MULTIPLIQUE POR SUBTRAIA DE REPITA VEZES FIM SE ENTAO SENAO FIMENTAO FIMSENAO
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
    FACA NOVO var SER num ';' { exportar_nova_atribuicao($3, $5,0); set_valor_var($3, $5); }
    | FACA NOVO var ';' { exportar_nova_atribuicao_vazia($3,0); set_valor_var($3, 0);}
    | FACA var SER num ';' { exportar_atribuicao($2, $4,0); set_valor_var($2, $4); }
    ;

impressao:
    MOSTRE var ';' { exportar_impressao($2,0); }
    ;

operacao:
    SOME var COM var ';' { exportar_operacao_soma($2, $4,0); }
    | SUBTRAIA var DE var ';' { exportar_operacao_diferenca($2, $4,0); }
    | MULTIPLIQUE var POR var ';' { exportar_operacao_multiplicacao($2, $4,0); }
    ;

repeticao:
    REPITA num VEZES ':' {exportar_repeticao($2,0);}
    cmds 
    FIM { exportar_fim_repeticao(0); }
    ;

condicao:
    SE 
    { exportar("if("); } 
    expr_bool 
    ENTAO 
    { exportar(") {\n\t"); }  
    cmds
    senao
    FIMENTAO 
    { exportar("}\n"); };

senao:
    SENAO { exportar( "} else {\n\t"); }
    cmds
    | 
    {;}

expr_bool:
    var{  exportar_conteudo_if_var($1);}
    |
    num {  exportar_conteudo_if_num($1); };
    
encerrar:
    ENCERRAR ';' { encerrar(); }
    ;

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
    printf("\n");
    return yyparse();
}
