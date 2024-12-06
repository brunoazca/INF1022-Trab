/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "grammar.y"

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

void exportar_if_num(int num, int ehBuffer) {
    char str_formatada[101];
    sprintf(str_formatada, "if (%d) {\n", num);
    
    if(ehBuffer){
        adicionar_ao_buffer(str_formatada);
    } else{
        exportar(str_formatada);
        exportar_buffer();
    }

}

void exportar_if_var(char* var, int ehBuffer) {
    char str_formatada[101];
    sprintf(str_formatada, "if (%s) {\n", var);

    if(ehBuffer){
        adicionar_ao_buffer(str_formatada);
    } else{
        exportar(str_formatada);
        exportar_buffer();

    }

}

void exportar_else(int ehBuffer) {
    if(ehBuffer){
        adicionar_ao_buffer("else {\n");
    } else{
        exportar("else {\n");
    }
}

void exportar_fim_condicao(int ehBuffer) {
    if(ehBuffer){
        adicionar_ao_buffer("}\n");
    } else{
        exportar("}\n");
    }
}



#line 332 "grammar.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "grammar.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_FACA = 3,                       /* FACA  */
  YYSYMBOL_NOVO = 4,                       /* NOVO  */
  YYSYMBOL_SER = 5,                        /* SER  */
  YYSYMBOL_MOSTRE = 6,                     /* MOSTRE  */
  YYSYMBOL_ENCERRAR = 7,                   /* ENCERRAR  */
  YYSYMBOL_SOME = 8,                       /* SOME  */
  YYSYMBOL_COM = 9,                        /* COM  */
  YYSYMBOL_MULTIPLIQUE = 10,               /* MULTIPLIQUE  */
  YYSYMBOL_POR = 11,                       /* POR  */
  YYSYMBOL_SUBTRAIA = 12,                  /* SUBTRAIA  */
  YYSYMBOL_DE = 13,                        /* DE  */
  YYSYMBOL_REPITA = 14,                    /* REPITA  */
  YYSYMBOL_VEZES = 15,                     /* VEZES  */
  YYSYMBOL_FIM = 16,                       /* FIM  */
  YYSYMBOL_SE = 17,                        /* SE  */
  YYSYMBOL_ENTAO = 18,                     /* ENTAO  */
  YYSYMBOL_SENAO = 19,                     /* SENAO  */
  YYSYMBOL_FIMENTAO = 20,                  /* FIMENTAO  */
  YYSYMBOL_FIMSENAO = 21,                  /* FIMSENAO  */
  YYSYMBOL_num = 22,                       /* num  */
  YYSYMBOL_var = 23,                       /* var  */
  YYSYMBOL_24_ = 24,                       /* ';'  */
  YYSYMBOL_25_ = 25,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 26,                  /* $accept  */
  YYSYMBOL_programa = 27,                  /* programa  */
  YYSYMBOL_cmds = 28,                      /* cmds  */
  YYSYMBOL_cmd = 29,                       /* cmd  */
  YYSYMBOL_atribuicao = 30,                /* atribuicao  */
  YYSYMBOL_impressao = 31,                 /* impressao  */
  YYSYMBOL_operacao = 32,                  /* operacao  */
  YYSYMBOL_repeticao = 33,                 /* repeticao  */
  YYSYMBOL_condicao = 34,                  /* condicao  */
  YYSYMBOL_encerrar = 35,                  /* encerrar  */
  YYSYMBOL_cmdsClosure = 36,               /* cmdsClosure  */
  YYSYMBOL_cmdClosure = 37,                /* cmdClosure  */
  YYSYMBOL_atribuicaoClosure = 38,         /* atribuicaoClosure  */
  YYSYMBOL_impressaoClosure = 39,          /* impressaoClosure  */
  YYSYMBOL_operacaoClosure = 40,           /* operacaoClosure  */
  YYSYMBOL_repeticaoClosure = 41,          /* repeticaoClosure  */
  YYSYMBOL_condicaoClosure = 42            /* condicaoClosure  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  28
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   109

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  26
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  42
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  121

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   278


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    25,    24,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   272,   272,   276,   277,   281,   282,   283,   284,   285,
     286,   290,   291,   292,   296,   300,   301,   302,   306,   310,
     311,   312,   313,   317,   322,   323,   327,   328,   329,   330,
     331,   335,   336,   337,   341,   345,   346,   347,   351,   355,
     356,   357,   358
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "FACA", "NOVO", "SER",
  "MOSTRE", "ENCERRAR", "SOME", "COM", "MULTIPLIQUE", "POR", "SUBTRAIA",
  "DE", "REPITA", "VEZES", "FIM", "SE", "ENTAO", "SENAO", "FIMENTAO",
  "FIMSENAO", "num", "var", "';'", "':'", "$accept", "programa", "cmds",
  "cmd", "atribuicao", "impressao", "operacao", "repeticao", "condicao",
  "encerrar", "cmdsClosure", "cmdClosure", "atribuicaoClosure",
  "impressaoClosure", "operacaoClosure", "repeticaoClosure",
  "condicaoClosure", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-39)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       7,    -3,   -21,   -19,    -5,     9,    11,    14,   -14,    30,
     -39,     7,   -39,   -39,   -39,   -39,   -39,   -39,    16,    37,
      25,   -39,    41,    40,    42,    39,    38,    43,   -39,   -39,
      -2,    35,   -39,    36,    44,    45,    33,    23,    23,    47,
     -39,    46,    48,    50,    52,    23,     0,    54,    55,    56,
      57,    49,   -11,     8,    23,   -39,   -39,   -39,   -39,   -39,
      24,    58,   -39,   -39,   -39,   -39,    65,    60,    59,    61,
      51,    73,    53,    71,    69,    70,    23,   -39,   -39,    23,
     -39,   -39,   -39,     1,    67,   -39,    68,    72,    74,    75,
      23,    23,    77,    78,    79,   -39,    66,    80,    81,    82,
      23,    26,    28,   -39,   -39,    83,   -39,   -39,   -39,   -39,
      76,    23,   -39,    23,   -39,   -39,   -39,    87,    88,   -39,
     -39
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     4,     5,     6,     7,     8,     9,    10,     0,     0,
       0,    23,     0,     0,     0,     0,     0,     0,     1,     3,
       0,     0,    14,     0,     0,     0,     0,     0,     0,     0,
      12,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    25,    26,    27,    28,    29,    30,
       0,     0,    13,    15,    17,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    19,    24,     0,
      21,    11,    18,     0,     0,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    32,     0,     0,     0,     0,
       0,     0,     0,    20,    22,     0,    33,    35,    37,    36,
       0,     0,    39,     0,    41,    31,    38,     0,     0,    40,
      42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -39,   -39,    85,   -39,   -39,   -39,   -39,   -39,   -39,   -39,
     -38,   -39,   -39,   -39,   -39,   -39,   -39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      53,    54,    55,    56,    57,    58,    59
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      60,    18,    20,    39,    67,    21,    94,    66,    26,    27,
       1,    74,    75,     2,     3,     4,    78,     5,    22,     6,
      19,     7,    40,    68,     8,    95,    46,    76,    77,    47,
      28,    48,    23,    49,    24,    50,    25,    51,    92,    30,
      52,    93,    31,    79,    80,   111,   112,   113,   114,    32,
      33,    34,   101,   102,    36,    35,    37,    41,    45,    42,
      86,    38,   110,     0,    84,     0,    88,    43,    44,    61,
      62,    73,    63,   117,    64,   118,    65,    69,    70,    71,
      72,    82,    81,    83,    87,    85,    89,    90,    91,    96,
     106,    97,   116,     0,     0,    98,    29,    99,   103,   104,
     100,   105,     0,     0,   107,   108,   109,   115,   119,   120
};

static const yytype_int8 yycheck[] =
{
      38,     4,    23,     5,     4,    24,     5,    45,    22,    23,
       3,    22,    23,     6,     7,     8,    54,    10,    23,    12,
      23,    14,    24,    23,    17,    24,     3,    19,    20,     6,
       0,     8,    23,    10,    23,    12,    22,    14,    76,    23,
      17,    79,     5,    19,    20,    19,    20,    19,    20,    24,
       9,    11,    90,    91,    15,    13,    18,    22,    25,    23,
       9,    18,   100,    -1,     5,    -1,    13,    23,    23,    22,
      24,    22,    24,   111,    24,   113,    24,    23,    23,    23,
      23,    16,    24,    23,    11,    24,    15,    18,    18,    22,
      24,    23,    16,    -1,    -1,    23,    11,    23,    21,    21,
      25,    22,    -1,    -1,    24,    24,    24,    24,    21,    21
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     6,     7,     8,    10,    12,    14,    17,    27,
      28,    29,    30,    31,    32,    33,    34,    35,     4,    23,
      23,    24,    23,    23,    23,    22,    22,    23,     0,    28,
      23,     5,    24,     9,    11,    13,    15,    18,    18,     5,
      24,    22,    23,    23,    23,    25,     3,     6,     8,    10,
      12,    14,    17,    36,    37,    38,    39,    40,    41,    42,
      36,    22,    24,    24,    24,    24,    36,     4,    23,    23,
      23,    23,    23,    22,    22,    23,    19,    20,    36,    19,
      20,    24,    16,    23,     5,    24,     9,    11,    13,    15,
      18,    18,    36,    36,     5,    24,    22,    23,    23,    23,
      25,    36,    36,    21,    21,    22,    24,    24,    24,    24,
      36,    19,    20,    19,    20,    24,    16,    36,    36,    21,
      21
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    26,    27,    28,    28,    29,    29,    29,    29,    29,
      29,    30,    30,    30,    31,    32,    32,    32,    33,    34,
      34,    34,    34,    35,    36,    36,    37,    37,    37,    37,
      37,    38,    38,    38,    39,    40,    40,    40,    41,    42,
      42,    42,    42
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     6,     4,     5,     3,     5,     5,     5,     6,     5,
       7,     5,     7,     2,     2,     1,     1,     1,     1,     1,
       1,     6,     4,     5,     3,     5,     5,     5,     6,     5,
       7,     5,     7
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: cmds  */
#line 272 "grammar.y"
         {;}
#line 1425 "grammar.tab.c"
    break;

  case 3: /* cmds: cmd cmds  */
#line 276 "grammar.y"
             {;}
#line 1431 "grammar.tab.c"
    break;

  case 4: /* cmds: cmd  */
#line 277 "grammar.y"
          {;}
#line 1437 "grammar.tab.c"
    break;

  case 5: /* cmd: atribuicao  */
#line 281 "grammar.y"
               {;}
#line 1443 "grammar.tab.c"
    break;

  case 6: /* cmd: impressao  */
#line 282 "grammar.y"
                {;}
#line 1449 "grammar.tab.c"
    break;

  case 7: /* cmd: operacao  */
#line 283 "grammar.y"
               {;}
#line 1455 "grammar.tab.c"
    break;

  case 8: /* cmd: repeticao  */
#line 284 "grammar.y"
                {;}
#line 1461 "grammar.tab.c"
    break;

  case 9: /* cmd: condicao  */
#line 285 "grammar.y"
               {;}
#line 1467 "grammar.tab.c"
    break;

  case 10: /* cmd: encerrar  */
#line 286 "grammar.y"
               {;}
#line 1473 "grammar.tab.c"
    break;

  case 11: /* atribuicao: FACA NOVO var SER num ';'  */
#line 290 "grammar.y"
                              { exportar_nova_atribuicao((yyvsp[-3].var), (yyvsp[-1].num),0); set_valor_var((yyvsp[-3].var), (yyvsp[-1].num)); }
#line 1479 "grammar.tab.c"
    break;

  case 12: /* atribuicao: FACA NOVO var ';'  */
#line 291 "grammar.y"
                        { exportar_nova_atribuicao_vazia((yyvsp[-1].var),0); set_valor_var((yyvsp[-1].var), 0);}
#line 1485 "grammar.tab.c"
    break;

  case 13: /* atribuicao: FACA var SER num ';'  */
#line 292 "grammar.y"
                           { exportar_atribuicao((yyvsp[-3].var), (yyvsp[-1].num),0); set_valor_var((yyvsp[-3].var), (yyvsp[-1].num)); }
#line 1491 "grammar.tab.c"
    break;

  case 14: /* impressao: MOSTRE var ';'  */
#line 296 "grammar.y"
                   { exportar_impressao((yyvsp[-1].var),0); }
#line 1497 "grammar.tab.c"
    break;

  case 15: /* operacao: SOME var COM var ';'  */
#line 300 "grammar.y"
                         { exportar_operacao_soma((yyvsp[-3].var), (yyvsp[-1].var),0); }
#line 1503 "grammar.tab.c"
    break;

  case 16: /* operacao: SUBTRAIA var DE var ';'  */
#line 301 "grammar.y"
                              { exportar_operacao_diferenca((yyvsp[-3].var), (yyvsp[-1].var),0); }
#line 1509 "grammar.tab.c"
    break;

  case 17: /* operacao: MULTIPLIQUE var POR var ';'  */
#line 302 "grammar.y"
                                  { exportar_operacao_multiplicacao((yyvsp[-3].var), (yyvsp[-1].var),0); }
#line 1515 "grammar.tab.c"
    break;

  case 18: /* repeticao: REPITA num VEZES ':' cmdsClosure FIM  */
#line 306 "grammar.y"
                                         { exportar_repeticao((yyvsp[-4].num),0); exportar_fim_repeticao(0); }
#line 1521 "grammar.tab.c"
    break;

  case 19: /* condicao: SE num ENTAO cmdsClosure FIMENTAO  */
#line 310 "grammar.y"
                                      { exportar_if_num((yyvsp[-3].num),0); exportar_fim_condicao(0); }
#line 1527 "grammar.tab.c"
    break;

  case 20: /* condicao: SE num ENTAO cmdsClosure SENAO cmdsClosure FIMSENAO  */
#line 311 "grammar.y"
                                                          { exportar_if_num((yyvsp[-5].num),0); exportar_else(0); exportar_fim_condicao(0); }
#line 1533 "grammar.tab.c"
    break;

  case 21: /* condicao: SE var ENTAO cmdsClosure FIMENTAO  */
#line 312 "grammar.y"
                                        { exportar_if_var((yyvsp[-3].var),0); exportar_fim_condicao(0); }
#line 1539 "grammar.tab.c"
    break;

  case 22: /* condicao: SE var ENTAO cmdsClosure SENAO cmdsClosure FIMSENAO  */
#line 313 "grammar.y"
                                                          { exportar_if_var((yyvsp[-5].var),0); exportar_else(0); exportar_fim_condicao(0); }
#line 1545 "grammar.tab.c"
    break;

  case 23: /* encerrar: ENCERRAR ';'  */
#line 317 "grammar.y"
                 { encerrar(); }
#line 1551 "grammar.tab.c"
    break;

  case 24: /* cmdsClosure: cmdClosure cmdsClosure  */
#line 322 "grammar.y"
                           {;}
#line 1557 "grammar.tab.c"
    break;

  case 25: /* cmdsClosure: cmdClosure  */
#line 323 "grammar.y"
                 {;}
#line 1563 "grammar.tab.c"
    break;

  case 26: /* cmdClosure: atribuicaoClosure  */
#line 327 "grammar.y"
                      {;}
#line 1569 "grammar.tab.c"
    break;

  case 27: /* cmdClosure: impressaoClosure  */
#line 328 "grammar.y"
                       {;}
#line 1575 "grammar.tab.c"
    break;

  case 28: /* cmdClosure: operacaoClosure  */
#line 329 "grammar.y"
                      {;}
#line 1581 "grammar.tab.c"
    break;

  case 29: /* cmdClosure: repeticaoClosure  */
#line 330 "grammar.y"
                       {;}
#line 1587 "grammar.tab.c"
    break;

  case 30: /* cmdClosure: condicaoClosure  */
#line 331 "grammar.y"
                      {;}
#line 1593 "grammar.tab.c"
    break;

  case 31: /* atribuicaoClosure: FACA NOVO var SER num ';'  */
#line 335 "grammar.y"
                              { exportar_nova_atribuicao((yyvsp[-3].var), (yyvsp[-1].num),1); set_valor_var((yyvsp[-3].var), (yyvsp[-1].num)); }
#line 1599 "grammar.tab.c"
    break;

  case 32: /* atribuicaoClosure: FACA NOVO var ';'  */
#line 336 "grammar.y"
                        { exportar_nova_atribuicao_vazia((yyvsp[-1].var),1); set_valor_var((yyvsp[-1].var), 0);}
#line 1605 "grammar.tab.c"
    break;

  case 33: /* atribuicaoClosure: FACA var SER num ';'  */
#line 337 "grammar.y"
                           { exportar_atribuicao((yyvsp[-3].var), (yyvsp[-1].num),1); set_valor_var((yyvsp[-3].var), (yyvsp[-1].num)); }
#line 1611 "grammar.tab.c"
    break;

  case 34: /* impressaoClosure: MOSTRE var ';'  */
#line 341 "grammar.y"
                   { exportar_impressao((yyvsp[-1].var),1); }
#line 1617 "grammar.tab.c"
    break;

  case 35: /* operacaoClosure: SOME var COM var ';'  */
#line 345 "grammar.y"
                         { exportar_operacao_soma((yyvsp[-3].var), (yyvsp[-1].var),1); }
#line 1623 "grammar.tab.c"
    break;

  case 36: /* operacaoClosure: SUBTRAIA var DE var ';'  */
#line 346 "grammar.y"
                              { exportar_operacao_diferenca((yyvsp[-3].var), (yyvsp[-1].var),1); }
#line 1629 "grammar.tab.c"
    break;

  case 37: /* operacaoClosure: MULTIPLIQUE var POR var ';'  */
#line 347 "grammar.y"
                                  { exportar_operacao_multiplicacao((yyvsp[-3].var), (yyvsp[-1].var),1); }
#line 1635 "grammar.tab.c"
    break;

  case 38: /* repeticaoClosure: REPITA num VEZES ':' cmdsClosure FIM  */
#line 351 "grammar.y"
                                         { exportar_repeticao((yyvsp[-4].num),1); exportar_fim_repeticao(1); }
#line 1641 "grammar.tab.c"
    break;

  case 39: /* condicaoClosure: SE num ENTAO cmdsClosure FIMENTAO  */
#line 355 "grammar.y"
                                      { exportar_if_num((yyvsp[-3].num),1); exportar_fim_condicao(1); }
#line 1647 "grammar.tab.c"
    break;

  case 40: /* condicaoClosure: SE num ENTAO cmdsClosure SENAO cmdsClosure FIMSENAO  */
#line 356 "grammar.y"
                                                          { exportar_if_num((yyvsp[-5].num),1); exportar_else(1); exportar_fim_condicao(1); }
#line 1653 "grammar.tab.c"
    break;

  case 41: /* condicaoClosure: SE var ENTAO cmdsClosure FIMENTAO  */
#line 357 "grammar.y"
                                        { exportar_if_var((yyvsp[-3].var),1); exportar_fim_condicao(1); }
#line 1659 "grammar.tab.c"
    break;

  case 42: /* condicaoClosure: SE var ENTAO cmdsClosure SENAO cmdsClosure FIMSENAO  */
#line 358 "grammar.y"
                                                          { exportar_if_var((yyvsp[-5].var),1); exportar_else(1); exportar_fim_condicao(1); }
#line 1665 "grammar.tab.c"
    break;


#line 1669 "grammar.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 361 "grammar.y"




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
