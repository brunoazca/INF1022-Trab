%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void yyerror(const char *s);
    int yylex(void);

    // Output Rust file pointer
    extern FILE *yyin;
    FILE *outfile;
    char command[256];
    char output_file[256];
    char exec_file[256];

    // Indentation tracking
    int indent_level = 1;

    void write_indent() {
        for (int i = 0; i < indent_level; i++) {
            fprintf(outfile, "    ");
        }
    }
%}

%union {
    int ival;
    char *sval;
}

%define parse.error verbose
%debug

%token <sval> var
%token <sval> num
%token FACA SER MOSTRE SOME COM REPITA VEZES FIM EOL MOSTRANDO SE ENTAO FOR_IGUAL FOR_MAIOR FOR_MENOR OU E SENAO FIMDOSE MULTIPLIQUE

%type <sval> valor
%type <sval> operador_relacional
%type <sval> operador_numerico

%left OU
%left E
%nonassoc FOR_IGUAL FOR_MAIOR FOR_MENOR

%%

programa: cmd_list;

cmd_list:
    cmd EOL cmd_list 
    | cmd EOL;

cmd:
    atribuicao 
    | impressao 
    | operacao 
    | repeticao 
    | controle;

atribuicao:
    FACA var SER valor 
    { 
        write_indent();
        fprintf(outfile, "let mut %s: u32 = %s;\n", $2, $4); 
    };

impressao:
    MOSTRE valor 
    { 
        write_indent();
        fprintf(outfile, "println!(\"{}\", %s);\n", $2); 
    };

operacao:
    operador_numerico var COM valor
    {
        write_indent();
        fprintf(outfile, "%s %s= %s;\n", $2, $1, $4);
    };
    | operador_numerico num COM valor MOSTRANDO
    {
        write_indent();
        fprintf(outfile, "println!(\"{}\", %s %s %s);\n", $2, $1, $4);
    };

operador_numerico:
    SOME {$$ = "+";} | MULTIPLIQUE {$$ = "*";};

repeticao:
    REPITA valor VEZES 
    { 
        write_indent();
        fprintf(outfile, "for _i in 0..%s {\n", $2); 
        indent_level++;
    } 
    cmd_list
    FIM 
    { 
        indent_level--;
        write_indent();
        fprintf(outfile, "}\n"); 
    };

controle:
    SE 
    { 
        write_indent();
        fprintf(outfile, "if "); 
    } 
    expressao_booleana 
    ENTAO 
    { 
        fprintf(outfile, " {\n"); 
        indent_level++;
    }  
    cmd_list
    opt_senao
    FIMDOSE 
    { 
        indent_level--;
        write_indent();
        fprintf(outfile, "}\n"); 
    };

opt_senao:
    SENAO 
    { 
        indent_level--;
        write_indent();
        fprintf(outfile, "} else {\n"); 
        indent_level++;
    } 
    cmd_list 
    | /* empty */ 
    { 
        /* No else block */
    };

expressao_booleana:
    comparacao
    | comparacao operador_logico comparacao;


comparacao:
    valor operador_relacional valor 
    { 
        fprintf(outfile, "%s %s %s", $1, $2, $3); 
    };

operador_relacional:
    FOR_IGUAL 
    { 
        $$ = "=="; 
    }  
    | FOR_MAIOR 
    { 
        $$ = ">"; 
    }  
    | FOR_MENOR 
    { 
        $$ = "<"; 
    };

operador_logico:
    E { fprintf(outfile, " && "); }
    | OU { fprintf(outfile, " || "); };

valor: 
    var 
    | num;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        fprintf(stderr, "Uso: magc [arquivo de saida].rs [arquivo de entrada].mag\n");
        exit(1);
    }
    if (argc == 4) {
        if (strcmp(argv[3], "-d") == 0) {
            yydebug = 1;
        } else {
            fprintf(stderr, "Opcao invalida: %s\n", argv[3]);
            exit(1);
        }
    }
    strcpy(output_file, argv[1]); // Copy the first parameter to output file name
    strcpy(exec_file, argv[1]); // Copy first parameter to executable file name

    // Remove the ".rs" if it exists
    size_t len = strlen(exec_file);
    if (len > 3 && strcmp(&exec_file[len - 3], ".rs") == 0) {
        exec_file[len - 3] = '\0'; // Truncate the string
    }

    // Open input and output files
    yyin = fopen(argv[2], "rt");
    if (!yyin) {
        fprintf(stderr, "Arquivo nao encontrado: %s\n", argv[2]);
        exit(1);
    }
    outfile = fopen(output_file, "wt"); 
    if (!outfile) {
        fprintf(stderr, "Erro ao criar arquivo: %s\n", output_file);
        exit(1);
    }

    // Suppress warnings about unused mutable variables in Rust
    fprintf(outfile, "#[allow(unused_mut)]\n#[allow(unused_variables)]\nfn main() {\n");

    // Parse input and translate to Rust
    yyparse();

    // End the main function
    fprintf(outfile, "}\n");

    // Close files
    fclose(yyin);
    fclose(outfile);

    // Compile rust file
    snprintf(command, sizeof(command), "rustc %s -o %s", output_file, exec_file);
    system(command);
    return 0;
}
