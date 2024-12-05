/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     FACA = 258,
     SER = 259,
     MOSTRE = 260,
     ENCERRAR = 261,
     SOME = 262,
     COM = 263,
     MULTIPLIQUE = 264,
     POR = 265,
     SUBTRAIA = 266,
     DE = 267,
     REPITA = 268,
     VEZES = 269,
     FIM = 270,
     SE = 271,
     ENTAO = 272,
     SENAO = 273,
     FIMENTAO = 274,
     FIMSENAO = 275,
     NUMBER = 276,
     VAR = 277
   };
#endif
/* Tokens.  */
#define FACA 258
#define SER 259
#define MOSTRE 260
#define ENCERRAR 261
#define SOME 262
#define COM 263
#define MULTIPLIQUE 264
#define POR 265
#define SUBTRAIA 266
#define DE 267
#define REPITA 268
#define VEZES 269
#define FIM 270
#define SE 271
#define ENTAO 272
#define SENAO 273
#define FIMENTAO 274
#define FIMSENAO 275
#define NUMBER 276
#define VAR 277




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 171 "grammar.y"
{ int int_val; char* str_val; }
/* Line 1529 of yacc.c.  */
#line 95 "grammar.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

