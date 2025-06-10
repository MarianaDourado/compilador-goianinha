/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_GOIANINHA_SINTATICO_H_INCLUDED
# define YY_YY_GOIANINHA_SINTATICO_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROGRAMA = 258,                /* PROGRAMA  */
    INT = 259,                     /* INT  */
    CAR = 260,                     /* CAR  */
    LEIA = 261,                    /* LEIA  */
    ESCREVA = 262,                 /* ESCREVA  */
    NOVALINHA = 263,               /* NOVALINHA  */
    RETORNE = 264,                 /* RETORNE  */
    INTCONST = 265,                /* INTCONST  */
    CARCONST = 266,                /* CARCONST  */
    ID = 267,                      /* ID  */
    CONSTSTRING = 268,             /* CONSTSTRING  */
    SE = 269,                      /* SE  */
    ENTAO = 270,                   /* ENTAO  */
    SENAO = 271,                   /* SENAO  */
    ENQUANTO = 272,                /* ENQUANTO  */
    EXECUTE = 273,                 /* EXECUTE  */
    OU = 274,                      /* OU  */
    E = 275,                       /* E  */
    NEG = 276,                     /* NEG  */
    EQ = 277,                      /* EQ  */
    NEQ = 278,                     /* NEQ  */
    LEQ = 279,                     /* LEQ  */
    GEQ = 280,                     /* GEQ  */
    MENOR = 281,                   /* MENOR  */
    MAIOR = 282,                   /* MAIOR  */
    RECEBE = 283,                  /* RECEBE  */
    MAIS = 284,                    /* MAIS  */
    MENOS = 285,                   /* MENOS  */
    VEZES = 286,                   /* VEZES  */
    DIVIDE = 287,                  /* DIVIDE  */
    PONTOVIRGULA = 288,            /* PONTOVIRGULA  */
    VIRGULA = 289,                 /* VIRGULA  */
    ABREPARENT = 290,              /* ABREPARENT  */
    FECHAPARENT = 291,             /* FECHAPARENT  */
    ABRECHAVE = 292,               /* ABRECHAVE  */
    FECHACHAVE = 293               /* FECHACHAVE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 23 "goianinha.y"

    int intval;
    char charval;
    char *string;
    ASTNode *node;

#line 109 "goianinha.sintatico.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_GOIANINHA_SINTATICO_H_INCLUDED  */
