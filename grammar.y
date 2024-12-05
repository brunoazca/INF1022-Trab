%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PATH "output.c"

FILE* output = NULL;

struct variable {
    char nome[31];
    int valor; 
};
typedef struct variable Variable;

struct variables_if {
    Variable vars[100];
};
typedef struct variables_if VariablesIF;

Variable variaveis[100];
VariablesIF variaveis_if[100] = {0};
int var_count = 0;
int ifs_count = 0;
int local_if_count = 0;

char* itoa_safe(int number) {
    char* arr = (char*)malloc(30); 
    int index = 0;
    if (number == 0) {
        arr[index++] = '0';
    }
    while (number > 0) {
        arr[index++] = (number % 10) + '0';
        number /= 10;
    }
    arr[index] = '\0';
    for (int i = 0; i < index / 2; i++) {
        char temp = arr[i];
        arr[i] = arr[index - i - 1];
        arr[index - i - 1] = temp;
    }
    return arr;
}

int get_variable_value(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(name, variaveis[i].nome) == 0) {
            return variaveis[i].valor;
        }
    }
    fprintf(stderr, "Erro: variável %s não foi encontrada\n", name);
    return -1;
}

int is_variable_declared_if(const char* name) {
    for (int i = 0; i < local_if_count; i++) {
        if (strcmp(name, variaveis_if[ifs_count].vars[i].nome) == 0) {
            return i;
        }
    }
    return -1;
}

int get_variable_value_if(const char* name) {
    for (int i = 0; i < local_if_count; i++) {
        if (strcmp(name, variaveis_if[ifs_count].vars[i].nome) == 0) {
            return variaveis_if[ifs_count].vars[i].valor;
        }
    }
    fprintf(stderr, "Erro: variável %s não foi encontrada\n", name);
    return -1;
}

void set_variable_value_if(const char* name, int value) {
    for (int i = 0; i < local_if_count; i++) {
        if (strcmp(name, variaveis_if[ifs_count].vars[i].nome) == 0) {
            variaveis_if[ifs_count].vars[i].valor = value;
            return;
        }
    }
    strcpy(variaveis_if[ifs_count].vars[local_if_count].nome, name);
    variaveis_if[ifs_count].vars[local_if_count].valor = value;
    local_if_count++;
}

void set_variable_value(const char* name, int value) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variaveis[i].nome, name) == 0) {
            variaveis[i].valor = value;
            return;
        }
    }
    strcpy(variaveis[var_count].nome, name);
    variaveis[var_count].valor = value;
    var_count++;
}

void start_program(void) {
    output = fopen(PATH, "w");
    if (output == NULL) {
        perror("Erro ao abrir arquivo de saída");
        exit(1);
    }
    fprintf(output, "#include <stdio.h>\n#include <stdlib.h>\n\nint main(void) {\n");
}

void export_code(const char* text) {
    fprintf(output, "\t%s", text);
}

void close_program(void) {
    export_code("\n\treturn 0;\n}");
    fclose(output);
}

int is_variable_declared(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(name, variaveis[i].nome) == 0) {
            return 1;
        }
    }
    return 0;
}

void export_assignment(const char* name, int value) {
    char formatted[101];
    if (is_variable_declared(name)) {
        sprintf(formatted, "%s = %d;\n", name, value);
    } else {
        sprintf(formatted, "int %s = %d;\n", name, value);
    }
    export_code(formatted);
}

void export_print(const char* name) {
    char formatted[101];
    sprintf(formatted, "printf(\"Mostrando %s: %%d\\n\", %s);\n", name, name);
    export_code(formatted);
}

void export_operation_add(const char* var1, const char* var2) {
    char formatted[101];
    sprintf(formatted, "%s += %s;\n", var1, var2);
    export_code(formatted);
}

void export_repetition(int times) {
    char formatted[101];
    sprintf(formatted, "for (int i = 0; i < %d; i++) {\n", times);
    export_code(formatted);
}

void export_if(int condition) {
    char formatted[101];
    sprintf(formatted, "if (%d) {\n", condition);
    export_code(formatted);
}

void export_else(void) {
    export_code("else {\n");
}

void export_end_block(void) {
    export_code("}\n");
}

void yyerror(char* s);
int yylex();
%}

%union { int int_val; char* str_val; }
%start programa
%token FACA SER MOSTRE ENCERRAR SOME COM MULTIPLIQUE POR SUBTRAIA DE REPITA VEZES FIM SE ENTAO SENAO FIMENTAO FIMSENAO
%token <int_val> NUM
%token <str_val> VAR

%%

programa: cmds;

cmds: cmd cmds | cmd;

cmd: atribuicao | impressao | operacao | repeticao | condicao | encerrar;

atribuicao: FACA VAR SER NUM ';' {
    export_assignment($2, $4);
    set_variable_value($2, $4);
};

impressao: MOSTRE VAR ';' { export_print($2); };

operacao: SOME VAR COM VAR ';' { export_operation_add($2, $4); };

repeticao: REPITA NUM VEZES ':' cmds FIM { export_end_block(); };

condicao: SE NUM ENTAO cmds FIMENTAO { export_end_block(); }
        | SE VAR ENTAO cmds FIMENTAO { export_end_block(); }
        | SE NUM ENTAO cmds SENAO cmds FIMSENAO { export_end_block(); };

encerrar: ENCERRAR ';' { close_program(); exit(0); };

%%

void yyerror(char* s) {
    fprintf(stderr, "Erro: %s\n", s);
}

int main(void) {
    start_program();
    return yyparse();
}
