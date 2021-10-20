/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_DECAFAST_TAB_H_INCLUDED
# define YY_YY_DECAFAST_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_PACKAGE = 258,
    T_LCB = 259,
    T_RCB = 260,
    T_AND = 261,
    T_ASSIGN = 262,
    T_DIV = 263,
    T_DOT = 264,
    T_EQ = 265,
    T_GEQ = 266,
    T_GT = 267,
    T_LEFTSHIFT = 268,
    T_RIGHTSHIFT = 269,
    T_LEQ = 270,
    T_LT = 271,
    T_MINUS = 272,
    T_MOD = 273,
    T_MULT = 274,
    T_NEQ = 275,
    T_NOT = 276,
    T_OR = 277,
    T_PLUS = 278,
    T_COMMA = 279,
    T_LPAREN = 280,
    T_RPAREN = 281,
    T_LSB = 282,
    T_RSB = 283,
    T_SEMICOLON = 284,
    T_ELSE = 285,
    T_EXTERN = 286,
    T_BREAK = 287,
    T_CONTINUE = 288,
    T_BOOLTYPE = 289,
    T_FOR = 290,
    T_FUNC = 291,
    T_IF = 292,
    T_INTTYPE = 293,
    T_STRINGTYPE = 294,
    T_VAR = 295,
    T_VOID = 296,
    T_WHILE = 297,
    T_RETURN = 298,
    T_CHARCONSTANT = 299,
    T_FALSE = 300,
    T_NULL = 301,
    T_STRINGCONSTANT = 302,
    T_TRUE = 303,
    T_INTCONSTANT = 304,
    T_ID = 305,
    T_COMMENT = 306,
    T_WHITESPACE = 307,
    IF = 308,
    IF_ELSE = 309,
    U_NOT = 310,
    U_MINUS = 311
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "decafast.y"

    std::vector<string> new_id_list;
    class decafAST *ast;
    class decafStmtList *list;
    class Identifier_List *id_list;
    std::string *sval;
 

#line 123 "decafast.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_DECAFAST_TAB_H_INCLUDED  */
