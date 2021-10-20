/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "decafast.y"

#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>
#include "default-defs.h"

int yylex(void);
int yyerror(char *); 

// print AST?
bool printAST = true;

#include "decafast.cc"

using namespace std;

decafStmtList * initialize_recursive_list(decafAST * a, decafAST * b) {
    decafStmtList * list = new decafStmtList();
    list->push_front(a); list->push_back(b);
    return list;
}


#line 95 "decafast.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
 

#line 213 "decafast.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_DECAFAST_TAB_H_INCLUDED  */



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
typedef yytype_uint8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   401

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  118
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  226

#define YYUNDEFTOK  2
#define YYMAXUTOK   311


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    82,    82,    85,    94,   104,   109,   114,   121,   122,
     123,   125,   126,   127,   130,   131,   133,   134,   137,   140,
     144,   145,   147,   148,   153,   158,   162,   163,   166,   169,
     174,   175,   176,   177,   180,   181,   183,   184,   186,   187,
     188,   189,   190,   191,   192,   197,   198,   200,   201,   204,
     209,   214,   220,   230,   231,   233,   234,   237,   240,   244,
     245,   247,   248,   249,   251,   254,   255,   257,   258,   260,
     262,   263,   270,   274,   278,   280,   282,   285,   286,   289,
     290,   293,   294,   297,   298,   302,   303,   307,   308,   309,
     310,   311,   312,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   331,   332,   336,   337,
     338,   339,   343,   344,   347,   348,   350,   351,   353
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_PACKAGE", "T_LCB", "T_RCB", "T_AND",
  "T_ASSIGN", "T_DIV", "T_DOT", "T_EQ", "T_GEQ", "T_GT", "T_LEFTSHIFT",
  "T_RIGHTSHIFT", "T_LEQ", "T_LT", "T_MINUS", "T_MOD", "T_MULT", "T_NEQ",
  "T_NOT", "T_OR", "T_PLUS", "T_COMMA", "T_LPAREN", "T_RPAREN", "T_LSB",
  "T_RSB", "T_SEMICOLON", "T_ELSE", "T_EXTERN", "T_BREAK", "T_CONTINUE",
  "T_BOOLTYPE", "T_FOR", "T_FUNC", "T_IF", "T_INTTYPE", "T_STRINGTYPE",
  "T_VAR", "T_VOID", "T_WHILE", "T_RETURN", "T_CHARCONSTANT", "T_FALSE",
  "T_NULL", "T_STRINGCONSTANT", "T_TRUE", "T_INTCONSTANT", "T_ID",
  "T_COMMENT", "T_WHITESPACE", "IF", "IF_ELSE", "U_NOT", "U_MINUS",
  "$accept", "start", "program", "decafpackage", "keywords", "return",
  "extern_declaration", "extern_list", "extern_func", "extern_arg_group",
  "extern_func_args", "while_loop", "for_loop", "for_loop_assigns",
  "if_stmt", "block", "statement_group", "statement_list", "statement",
  "field_decl_group", "field_decl_list", "field_decl", "method_decl_group",
  "method_decl_list", "method_decl", "method_decl_args",
  "method_decl_multi_args", "method_decl_sing_arg",
  "typed_symbols_decl_group", "typed_symbols_decls", "typed_symbols_decl",
  "typed_symbols", "identifier_list", "method_call", "method_args",
  "method_arg", "assign_list", "assign", "rvalue", "expression",
  "binary_operation", "unary_operation", "constant", "method_type",
  "extern_type", "decaf_type", "identifier", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311
};
# endif

#define YYPACT_NINF (-112)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-55)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       0,   -12,    18,    41,  -112,  -112,    59,    34,    34,  -112,
      86,   -12,  -112,  -112,  -112,  -112,    -3,    76,  -112,   -12,
     -12,    78,    90,    90,   135,    78,     2,   125,   118,    26,
      68,   145,  -112,  -112,  -112,  -112,  -112,   132,   134,   -21,
     159,  -112,  -112,  -112,   146,   154,   156,  -112,   -22,   -12,
     143,   167,   -12,   158,   191,  -112,   -12,   -12,  -112,  -112,
     198,  -112,   159,   201,   201,   159,   202,  -112,   205,  -112,
    -112,   219,  -112,  -112,  -112,  -112,   221,  -112,  -112,   247,
     159,   -21,   -21,  -112,    92,  -112,   247,   224,   230,  -112,
    -112,  -112,   235,   242,   -12,   245,   253,   243,  -112,  -112,
    -112,  -112,  -112,   274,   144,   144,   112,   249,   249,   257,
     262,   268,    73,  -112,  -112,  -112,   -12,   181,    25,    75,
     181,   140,  -112,  -112,  -112,  -112,  -112,   293,  -112,  -112,
    -112,  -112,  -112,   181,    -5,   181,   276,   288,   292,    19,
     181,   181,   181,  -112,  -112,  -112,  -112,  -112,  -112,   284,
    -112,  -112,  -112,     5,  -112,  -112,   303,  -112,   322,  -112,
     360,  -112,  -112,    65,   102,   360,   246,   181,   -12,   -12,
    -112,  -112,   341,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   247,   181,   247,  -112,
     174,  -112,   174,  -112,   301,   226,  -112,  -112,  -112,   193,
    -112,   152,   152,   152,   152,   152,   104,  -112,  -112,   152,
     378,   104,   287,   265,  -112,  -112,  -112,   181,   -12,   247,
    -112,   360,   298,  -112,   247,  -112
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     2,     4,     0,    14,    15,   118,
       0,     0,     1,     3,    17,    16,     0,     0,     7,     0,
       0,     0,    45,    46,     0,    53,    61,     0,     0,     0,
       0,     0,    48,    47,     6,    56,    55,    59,    60,     0,
       0,   116,   117,   114,     0,    21,    20,   115,    61,     0,
       0,     0,     0,     0,     0,     5,     0,     0,    64,   112,
       0,   113,     0,     0,     0,     0,     0,    73,     0,    50,
      72,     0,    49,    63,    62,    19,     0,    23,    22,     0,
       0,     0,     0,    18,     0,    58,     0,     0,     0,    33,
       9,     8,     0,     0,     0,     0,    11,     0,    10,    42,
      43,    41,    44,     0,    34,    35,     0,    65,    66,     0,
       0,     0,     0,    57,    52,    51,     0,     0,     0,     0,
       0,     0,    40,    32,    37,    36,    31,     0,    68,    67,
      69,    39,    38,     0,     0,     0,     0,    27,    26,     0,
       0,     0,     0,   108,   110,   111,   109,    91,    92,     0,
      88,    89,    87,    85,    71,    70,     0,    12,     0,    30,
      83,    74,    79,     0,     0,    80,     0,     0,     0,     0,
     106,   107,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
       0,    76,     0,    75,     0,     0,    82,    81,    90,   103,
      96,   101,   100,    99,   105,    98,    94,    97,    95,   102,
     104,    93,    28,     0,    24,    78,    77,     0,     0,     0,
      86,    84,     0,    29,     0,    25
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -112,  -112,  -112,   321,  -112,  -112,  -112,  -112,    15,  -112,
    -112,  -112,  -112,   113,  -112,   -78,   229,  -112,    16,  -112,
    -112,   116,   315,  -112,   318,   302,  -112,    96,  -112,  -112,
     107,  -112,   252,   -18,  -112,   -59,  -112,  -111,  -112,  -106,
    -112,  -112,  -112,   -56,   119,    55,    -1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    97,    98,     6,     7,     8,    44,
      45,    99,   100,   136,   101,   102,   103,   104,   105,    21,
      22,    23,    24,    25,    26,    36,    37,    38,   106,   107,
     108,   109,    29,   147,   163,   164,   137,   111,   148,   165,
     150,   151,   152,    60,    46,    61,   153
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      10,    85,    18,     1,    65,   138,    76,   -54,   113,    79,
      17,   149,   140,    41,   156,   158,   141,    42,    28,    30,
     142,   161,    14,    15,    86,    39,   133,   160,     9,   166,
     134,     2,   187,    19,   170,   171,   172,    20,     9,   143,
     144,    12,   162,   145,   146,     9,   135,    39,    67,    49,
      49,    70,     9,    50,    11,    39,    39,   196,   197,    41,
      41,   195,     1,    42,    42,     2,   110,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     133,   213,    47,   112,    51,    54,   110,   110,   110,   190,
      16,   191,    52,   119,    58,    53,    84,    89,   134,    52,
     135,    27,    41,   112,   112,   112,    42,   138,   212,    41,
     214,   221,   174,    42,    19,   139,    84,   126,    47,    47,
     124,   125,   181,   182,    90,    91,   192,    92,   193,    93,
      20,   215,    94,   216,    95,    96,    87,    88,    32,    33,
      34,   223,     9,    48,    90,    91,   225,    92,    84,    93,
      55,    40,    73,    74,    95,    96,    56,   140,    57,    41,
     174,   141,     9,    42,    43,   142,   157,   139,   139,   180,
     181,   182,    62,   154,   155,   185,    90,    91,    63,    92,
      64,    93,    77,    78,   143,   144,    95,    96,   145,   146,
       9,   140,    68,    41,     9,   141,    69,    42,   140,   142,
      59,   174,   141,   175,   176,   177,   142,    71,   178,   179,
     180,   181,   182,   183,   128,   129,   185,   139,   143,   144,
      72,   162,   145,   146,     9,   143,   144,    75,    80,   145,
     146,     9,   173,    81,   174,    41,   175,   176,   177,    42,
      43,   178,   179,   180,   181,   182,   183,    82,   184,   185,
      83,    84,   173,   114,   174,   218,   175,   176,   177,   115,
     116,   178,   179,   180,   181,   182,   183,   117,   184,   185,
     120,   173,   122,   174,   194,   175,   176,   177,   121,   123,
     178,   179,   180,   181,   182,   183,   130,   184,   185,    94,
     173,   131,   174,   220,   175,   176,   177,   132,   159,   178,
     179,   180,   181,   182,   183,   167,   184,   185,   217,   173,
     186,   174,   168,   175,   176,   177,   169,   219,   178,   179,
     180,   181,   182,   183,   224,   184,   185,    13,   173,   188,
     174,   222,   175,   176,   177,   127,    31,   178,   179,   180,
     181,   182,   183,    35,   184,   185,   118,   173,   189,   174,
      66,   175,   176,   177,     0,     0,   178,   179,   180,   181,
     182,   183,     0,   184,   185,     0,   173,   198,   174,     0,
     175,   176,   177,     0,     0,   178,   179,   180,   181,   182,
     183,     0,   184,   185,   173,     0,   174,     0,   175,   176,
     177,     0,     0,   178,   179,   180,   181,   182,   183,     0,
       0,   185
};

static const yytype_int16 yycheck[] =
{
       1,    79,     5,     3,    26,   116,    62,     5,    86,    65,
      11,   117,    17,    34,   120,   121,    21,    38,    19,    20,
      25,    26,     7,     8,    80,    26,     7,   133,    50,   135,
      25,    31,    27,    36,   140,   141,   142,    40,    50,    44,
      45,     0,    47,    48,    49,    50,    27,    48,    49,    24,
      24,    52,    50,    27,    36,    56,    57,   168,   169,    34,
      34,   167,     3,    38,    38,    31,    84,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
       7,   187,    27,    84,    29,    30,   104,   105,   106,    24,
       4,    26,    24,    94,    39,    27,     4,     5,    25,    24,
      27,    25,    34,   104,   105,   106,    38,   218,   186,    34,
     188,   217,     8,    38,    36,   116,     4,     5,    63,    64,
     104,   105,    18,    19,    32,    33,    24,    35,    26,    37,
      40,   190,    40,   192,    42,    43,    81,    82,    22,    23,
       5,   219,    50,    25,    32,    33,   224,    35,     4,    37,
       5,    26,    56,    57,    42,    43,    24,    17,    24,    34,
       8,    21,    50,    38,    39,    25,    26,   168,   169,    17,
      18,    19,    26,   118,   119,    23,    32,    33,    24,    35,
      24,    37,    63,    64,    44,    45,    42,    43,    48,    49,
      50,    17,    49,    34,    50,    21,    29,    38,    17,    25,
      41,     8,    21,    10,    11,    12,    25,    49,    15,    16,
      17,    18,    19,    20,   107,   108,    23,   218,    44,    45,
      29,    47,    48,    49,    50,    44,    45,    29,    26,    48,
      49,    50,     6,    28,     8,    34,    10,    11,    12,    38,
      39,    15,    16,    17,    18,    19,    20,    28,    22,    23,
      29,     4,     6,    29,     8,    29,    10,    11,    12,    29,
      25,    15,    16,    17,    18,    19,    20,    25,    22,    23,
      25,     6,    29,     8,    28,    10,    11,    12,    25,     5,
      15,    16,    17,    18,    19,    20,    29,    22,    23,    40,
       6,    29,     8,    28,    10,    11,    12,    29,     5,    15,
      16,    17,    18,    19,    20,    29,    22,    23,     7,     6,
      26,     8,    24,    10,    11,    12,    24,    30,    15,    16,
      17,    18,    19,    20,    26,    22,    23,     6,     6,    26,
       8,   218,    10,    11,    12,   106,    21,    15,    16,    17,
      18,    19,    20,    25,    22,    23,    94,     6,    26,     8,
      48,    10,    11,    12,    -1,    -1,    15,    16,    17,    18,
      19,    20,    -1,    22,    23,    -1,     6,    26,     8,    -1,
      10,    11,    12,    -1,    -1,    15,    16,    17,    18,    19,
      20,    -1,    22,    23,     6,    -1,     8,    -1,    10,    11,
      12,    -1,    -1,    15,    16,    17,    18,    19,    20,    -1,
      -1,    23
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    31,    58,    59,    60,    63,    64,    65,    50,
     103,    36,     0,    60,    65,    65,     4,   103,     5,    36,
      40,    76,    77,    78,    79,    80,    81,    25,   103,    89,
     103,    79,    78,    78,     5,    81,    82,    83,    84,   103,
      26,    34,    38,    39,    66,    67,   101,   102,    25,    24,
      27,   102,    24,    27,   102,     5,    24,    24,   102,    41,
     100,   102,    26,    24,    24,    26,    82,   103,    49,    29,
     103,    49,    29,    84,    84,    29,   100,   101,   101,   100,
      26,    28,    28,    29,     4,    72,   100,   102,   102,     5,
      32,    33,    35,    37,    40,    42,    43,    61,    62,    68,
      69,    71,    72,    73,    74,    75,    85,    86,    87,    88,
      90,    94,   103,    72,    29,    29,    25,    25,    89,   103,
      25,    25,    29,     5,    75,    75,     5,    73,    87,    87,
      29,    29,    29,     7,    25,    27,    70,    93,    94,   103,
      17,    21,    25,    44,    45,    48,    49,    90,    95,    96,
      97,    98,    99,   103,   102,   102,    96,    26,    96,     5,
      96,    26,    47,    91,    92,    96,    96,    29,    24,    24,
      96,    96,    96,     6,     8,    10,    11,    12,    15,    16,
      17,    18,    19,    20,    22,    23,    26,    27,    26,    26,
      24,    26,    24,    26,    28,    96,    94,    94,    26,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    72,    96,    72,    92,    92,     7,    29,    30,
      28,    96,    70,    72,    26,    72
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    57,    58,    59,    59,    60,    60,    60,    61,    61,
      61,    62,    62,    62,    63,    63,    64,    64,    65,    65,
      66,    66,    67,    67,    68,    69,    70,    70,    71,    71,
      72,    72,    72,    72,    73,    73,    74,    74,    75,    75,
      75,    75,    75,    75,    75,    76,    76,    77,    77,    78,
      78,    78,    78,    79,    79,    80,    80,    81,    81,    82,
      82,    83,    83,    83,    84,    85,    85,    86,    86,    87,
      88,    88,    89,    89,    90,    90,    90,    91,    91,    92,
      92,    93,    93,    94,    94,    95,    95,    96,    96,    96,
      96,    96,    96,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    98,    98,    99,    99,
      99,    99,   100,   100,   101,   101,   102,   102,   103
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     6,     5,     4,     1,     1,
       1,     1,     3,     4,     1,     1,     2,     2,     8,     7,
       1,     1,     3,     3,     5,     9,     1,     1,     5,     7,
       4,     3,     3,     2,     1,     1,     2,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     2,     2,     4,
       4,     7,     7,     1,     1,     2,     2,     7,     6,     1,
       1,     0,     3,     3,     2,     1,     1,     2,     2,     2,
       3,     3,     3,     3,     3,     4,     4,     3,     3,     1,
       1,     3,     3,     3,     6,     1,     4,     1,     1,     1,
       3,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 3:
#line 86 "decafast.y"
    { 
        ProgramAST *prog = new ProgramAST((decafStmtList *)(yyvsp[-1].ast), (PackageAST *)(yyvsp[0].ast)); 
        if (printAST) {
            cout << getString(prog) << endl;
        }
        delete prog;
    }
#line 1598 "decafast.tab.c"
    break;

  case 4:
#line 95 "decafast.y"
    { 
        ProgramAST *prog = new ProgramAST(new decafStmtList(), (PackageAST *)(yyvsp[0].ast)); 
        if (printAST) {
            cout << getString(prog) << endl;
        }
        delete prog;
    }
#line 1610 "decafast.tab.c"
    break;

  case 5:
#line 105 "decafast.y"
    {   
        string id_name = (yyvsp[-4].ast)->str();
        (yyval.ast) = new PackageAST(id_name, dynamic_cast<decafStmtList *>((yyvsp[-2].ast)), dynamic_cast<decafStmtList *>((yyvsp[-1].ast))); 
    }
#line 1619 "decafast.tab.c"
    break;

  case 6:
#line 110 "decafast.y"
    {   
        string id_name = (yyvsp[-3].ast)->str();
        (yyval.ast) = new PackageAST(id_name, new decafStmtList() , dynamic_cast<decafStmtList *>((yyvsp[-1].ast))); 
    }
#line 1628 "decafast.tab.c"
    break;

  case 7:
#line 114 "decafast.y"
                                       {   
        string id_name = (yyvsp[-2].ast)->str();
        (yyval.ast) = new PackageAST(id_name, new decafStmtList(), new decafStmtList()); 
    }
#line 1637 "decafast.tab.c"
    break;

  case 8:
#line 121 "decafast.y"
                     {(yyval.ast) = new Continue();}
#line 1643 "decafast.tab.c"
    break;

  case 9:
#line 122 "decafast.y"
                     {(yyval.ast) = new Break();}
#line 1649 "decafast.tab.c"
    break;

  case 10:
#line 123 "decafast.y"
                     {(yyval.ast) = (yyvsp[0].ast);}
#line 1655 "decafast.tab.c"
    break;

  case 11:
#line 125 "decafast.y"
                     {(yyval.ast) = new Return();}
#line 1661 "decafast.tab.c"
    break;

  case 12:
#line 126 "decafast.y"
                                    {(yyval.ast) = new Return();}
#line 1667 "decafast.tab.c"
    break;

  case 13:
#line 127 "decafast.y"
                                               {(yyval.ast) = new Return((yyvsp[-1].ast));}
#line 1673 "decafast.tab.c"
    break;

  case 14:
#line 130 "decafast.y"
                                        {(yyval.ast) = (yyvsp[0].list);}
#line 1679 "decafast.tab.c"
    break;

  case 15:
#line 131 "decafast.y"
                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 1685 "decafast.tab.c"
    break;

  case 16:
#line 133 "decafast.y"
                                       {(yyval.list) = initialize_recursive_list((yyvsp[-1].ast), (yyvsp[0].ast));}
#line 1691 "decafast.tab.c"
    break;

  case 17:
#line 134 "decafast.y"
                                {(yyvsp[-1].list)->push_back((yyvsp[0].ast)); (yyval.list) = (yyvsp[-1].list);}
#line 1697 "decafast.tab.c"
    break;

  case 18:
#line 137 "decafast.y"
                                                                                                   {
        (yyval.ast) = new Extern_Func(dynamic_cast<Identifier *>((yyvsp[-5].ast)), dynamic_cast<Type *>((yyvsp[-1].ast)), (yyvsp[-3].ast));
    }
#line 1705 "decafast.tab.c"
    break;

  case 19:
#line 140 "decafast.y"
                                                                           {
        (yyval.ast) = new Extern_Func(dynamic_cast<Identifier *>((yyvsp[-4].ast)), dynamic_cast<Type *>((yyvsp[-1].ast)), new decafStmtList());
    }
#line 1713 "decafast.tab.c"
    break;

  case 20:
#line 144 "decafast.y"
                                {(yyval.ast) = (yyvsp[0].ast);}
#line 1719 "decafast.tab.c"
    break;

  case 21:
#line 145 "decafast.y"
                                {(yyval.ast) = (yyvsp[0].list);}
#line 1725 "decafast.tab.c"
    break;

  case 22:
#line 147 "decafast.y"
                                                    {(yyval.list) = initialize_recursive_list((yyvsp[-2].ast), (yyvsp[0].ast));}
#line 1731 "decafast.tab.c"
    break;

  case 23:
#line 148 "decafast.y"
                                                    {(yyvsp[-2].list)->push_back((yyvsp[0].ast)); (yyval.list) = (yyvsp[-2].list);}
#line 1737 "decafast.tab.c"
    break;

  case 24:
#line 153 "decafast.y"
                                                       {
    (yyval.ast) = new While_Loop((yyvsp[-2].ast), dynamic_cast<Block *>((yyvsp[0].ast)));
}
#line 1745 "decafast.tab.c"
    break;

  case 25:
#line 158 "decafast.y"
                                                                                                             {
        (yyval.ast) = new For_Loop((yyvsp[-6].ast), (yyvsp[-4].ast), (yyvsp[-2].ast), dynamic_cast<Block *>((yyvsp[0].ast)));
    }
#line 1753 "decafast.tab.c"
    break;

  case 26:
#line 162 "decafast.y"
                         {(yyval.ast) = (yyvsp[0].ast);}
#line 1759 "decafast.tab.c"
    break;

  case 27:
#line 163 "decafast.y"
                         {(yyval.ast) = (yyvsp[0].list);}
#line 1765 "decafast.tab.c"
    break;

  case 28:
#line 166 "decafast.y"
                                                 {
        (yyval.ast) = new If_Else((yyvsp[-2].ast), dynamic_cast<Block *> ((yyvsp[0].ast)));
    }
#line 1773 "decafast.tab.c"
    break;

  case 29:
#line 169 "decafast.y"
                                                           {
        (yyval.ast) = new If_Else((yyvsp[-4].ast), dynamic_cast<Block *> ((yyvsp[-2].ast)), dynamic_cast<Block *> ((yyvsp[0].ast)));
    }
#line 1781 "decafast.tab.c"
    break;

  case 30:
#line 174 "decafast.y"
                                                                          {(yyval.ast) = new Block((yyvsp[-2].ast), (yyvsp[-1].ast));}
#line 1787 "decafast.tab.c"
    break;

  case 31:
#line 175 "decafast.y"
                                                                          {(yyval.ast) = new Block((yyvsp[-1].ast), new decafStmtList());}
#line 1793 "decafast.tab.c"
    break;

  case 32:
#line 176 "decafast.y"
                                                                          {(yyval.ast) = new Block(new decafStmtList(), (yyvsp[-1].ast));}
#line 1799 "decafast.tab.c"
    break;

  case 33:
#line 177 "decafast.y"
                                                                          {(yyval.ast) = new Block(new decafStmtList(), new decafStmtList());}
#line 1805 "decafast.tab.c"
    break;

  case 34:
#line 180 "decafast.y"
                                        {(yyval.ast) = (yyvsp[0].list);}
#line 1811 "decafast.tab.c"
    break;

  case 35:
#line 181 "decafast.y"
                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 1817 "decafast.tab.c"
    break;

  case 36:
#line 183 "decafast.y"
                                        {(yyval.list) = initialize_recursive_list((yyvsp[-1].ast), (yyvsp[0].ast)); }
#line 1823 "decafast.tab.c"
    break;

  case 37:
#line 184 "decafast.y"
                                        {(yyvsp[-1].list)->push_back((yyvsp[0].ast)); (yyval.list) = (yyvsp[-1].list); }
#line 1829 "decafast.tab.c"
    break;

  case 38:
#line 186 "decafast.y"
                                        {(yyval.ast) = (yyvsp[-1].ast);}
#line 1835 "decafast.tab.c"
    break;

  case 39:
#line 187 "decafast.y"
                                        {(yyval.ast) = (yyvsp[-1].ast);}
#line 1841 "decafast.tab.c"
    break;

  case 40:
#line 188 "decafast.y"
                                        {(yyval.ast) = (yyvsp[-1].ast);}
#line 1847 "decafast.tab.c"
    break;

  case 41:
#line 189 "decafast.y"
                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 1853 "decafast.tab.c"
    break;

  case 42:
#line 190 "decafast.y"
                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 1859 "decafast.tab.c"
    break;

  case 43:
#line 191 "decafast.y"
                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 1865 "decafast.tab.c"
    break;

  case 44:
#line 192 "decafast.y"
                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 1871 "decafast.tab.c"
    break;

  case 45:
#line 197 "decafast.y"
                                           {(yyval.ast) = (yyvsp[0].list);}
#line 1877 "decafast.tab.c"
    break;

  case 46:
#line 198 "decafast.y"
                                           {(yyval.ast) = (yyvsp[0].ast);}
#line 1883 "decafast.tab.c"
    break;

  case 47:
#line 200 "decafast.y"
                                         {(yyval.list) = initialize_recursive_list((yyvsp[-1].ast), (yyvsp[0].ast));}
#line 1889 "decafast.tab.c"
    break;

  case 48:
#line 201 "decafast.y"
                                          {(yyvsp[-1].list)->push_back((yyvsp[0].ast)); (yyval.list) = (yyvsp[-1].list);}
#line 1895 "decafast.tab.c"
    break;

  case 49:
#line 204 "decafast.y"
                                                    {
        Identifier * id = dynamic_cast<Identifier *>((yyvsp[-2].ast));
        Type * type = dynamic_cast<Type *>((yyvsp[-1].ast));
        (yyval.ast)  = new Field_Decl(id, type, new Field_Size());
    }
#line 1905 "decafast.tab.c"
    break;

  case 50:
#line 209 "decafast.y"
                                                   {
        Type * type = dynamic_cast<Type *>((yyvsp[-1].ast));
        (yyvsp[-2].id_list)->to_field_decl(&type);
        (yyval.ast) = (yyvsp[-2].id_list);
    }
#line 1915 "decafast.tab.c"
    break;

  case 51:
#line 214 "decafast.y"
                                                                        {
        Identifier * id = dynamic_cast<Identifier *>((yyvsp[-5].ast));
        Type * type = dynamic_cast<Type *>((yyvsp[-1].ast));
        Constant_Expr * const_expr = new Constant_Expr(&((yyvsp[-3].sval)), INTTYPE);
        (yyval.ast)  = new Field_Decl(id, type, new Field_Size(&const_expr));   
    }
#line 1926 "decafast.tab.c"
    break;

  case 52:
#line 220 "decafast.y"
                                                                             {
        Type * type = dynamic_cast<Type *>((yyvsp[-1].ast));
        Constant_Expr * size = new Constant_Expr(&((yyvsp[-3].sval)), INTTYPE);
        Field_Size * field_sz = new Field_Size(&size);
        (yyvsp[-5].id_list)->to_field_decl(&type, &field_sz);
        (yyval.ast) = (yyvsp[-5].id_list);  
    }
#line 1938 "decafast.tab.c"
    break;

  case 53:
#line 230 "decafast.y"
                                                     {(yyval.ast) = (yyvsp[0].list);}
#line 1944 "decafast.tab.c"
    break;

  case 54:
#line 231 "decafast.y"
                                                     {(yyval.ast) = (yyvsp[0].ast);}
#line 1950 "decafast.tab.c"
    break;

  case 55:
#line 233 "decafast.y"
                                                           {(yyval.list) = initialize_recursive_list ((yyvsp[-1].ast), (yyvsp[0].ast));}
#line 1956 "decafast.tab.c"
    break;

  case 56:
#line 234 "decafast.y"
                                                           {(yyvsp[-1].list)->push_back((yyvsp[0].ast)), (yyval.list)=(yyvsp[-1].list);}
#line 1962 "decafast.tab.c"
    break;

  case 57:
#line 237 "decafast.y"
                                                                                    {
        (yyval.ast) = new Method_Decl(dynamic_cast<Identifier *>((yyvsp[-5].ast)), dynamic_cast<Type *>((yyvsp[-1].ast)), (yyvsp[-3].ast), dynamic_cast<Block *>((yyvsp[0].ast)));
    }
#line 1970 "decafast.tab.c"
    break;

  case 58:
#line 240 "decafast.y"
                                                            {
        (yyval.ast) = new Method_Decl(dynamic_cast<Identifier *>((yyvsp[-4].ast)), dynamic_cast<Type *>((yyvsp[-1].ast)), new decafStmtList(), dynamic_cast<Block *>((yyvsp[0].ast)));
    }
#line 1978 "decafast.tab.c"
    break;

  case 59:
#line 244 "decafast.y"
                                         {(yyval.ast) = (yyvsp[0].list);}
#line 1984 "decafast.tab.c"
    break;

  case 60:
#line 245 "decafast.y"
                           {(yyval.ast) = (yyvsp[0].ast);}
#line 1990 "decafast.tab.c"
    break;

  case 61:
#line 247 "decafast.y"
                                                            {(yyval.list) = new decafStmtList();}
#line 1996 "decafast.tab.c"
    break;

  case 62:
#line 248 "decafast.y"
                                                            {(yyval.list) = initialize_recursive_list((yyvsp[-2].ast), (yyvsp[0].ast));}
#line 2002 "decafast.tab.c"
    break;

  case 63:
#line 249 "decafast.y"
                                                                 {(yyvsp[-2].list)->push_back((yyvsp[0].ast)); (yyval.list)=(yyvsp[-2].list);}
#line 2008 "decafast.tab.c"
    break;

  case 64:
#line 251 "decafast.y"
                                                                 {(yyval.ast) = new Var_Def((yyvsp[0].ast), dynamic_cast<Type *>((yyvsp[-1].ast))); }
#line 2014 "decafast.tab.c"
    break;

  case 65:
#line 254 "decafast.y"
                                                        {(yyval.ast) = (yyvsp[0].list);}
#line 2020 "decafast.tab.c"
    break;

  case 66:
#line 255 "decafast.y"
                                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 2026 "decafast.tab.c"
    break;

  case 67:
#line 257 "decafast.y"
                                                           {(yyval.list) = initialize_recursive_list((yyvsp[-1].ast), (yyvsp[0].ast));}
#line 2032 "decafast.tab.c"
    break;

  case 68:
#line 258 "decafast.y"
                                                     {(yyvsp[-1].list)->push_back((yyvsp[0].ast)); (yyval.list) = (yyvsp[-1].list); }
#line 2038 "decafast.tab.c"
    break;

  case 69:
#line 260 "decafast.y"
                                                  {(yyval.ast)=(yyvsp[-1].ast);}
#line 2044 "decafast.tab.c"
    break;

  case 70:
#line 262 "decafast.y"
                                                         {(yyval.ast) = new Var_Def((yyvsp[-1].ast), dynamic_cast<Type *>((yyvsp[0].ast)));}
#line 2050 "decafast.tab.c"
    break;

  case 71:
#line 263 "decafast.y"
                                                         {
                                                            Type * type = dynamic_cast<Type *>((yyvsp[0].ast));
                                                            (yyvsp[-1].id_list)->to_var_def(&type);
                                                            (yyval.ast) = (yyvsp[-1].id_list);
                                                         }
#line 2060 "decafast.tab.c"
    break;

  case 72:
#line 270 "decafast.y"
                                                        {(yyval.id_list) = new Identifier_List(); 
                                                            (yyval.id_list)->push_back(dynamic_cast<Identifier*>((yyvsp[-2].ast))); 
                                                            (yyval.id_list)->push_back(dynamic_cast<Identifier*>((yyvsp[0].ast))); 
                                                        }
#line 2069 "decafast.tab.c"
    break;

  case 73:
#line 274 "decafast.y"
                                                        {(yyvsp[-2].id_list)->push_back(dynamic_cast<Identifier*>((yyvsp[0].ast))); (yyval.id_list) = (yyvsp[-2].id_list);}
#line 2075 "decafast.tab.c"
    break;

  case 74:
#line 278 "decafast.y"
                                          {(yyval.ast) = new Method_Call(dynamic_cast<Identifier *>((yyvsp[-2].ast))); }
#line 2081 "decafast.tab.c"
    break;

  case 75:
#line 280 "decafast.y"
                                                      {(yyval.ast) = new Method_Call(dynamic_cast<Identifier *>((yyvsp[-3].ast)), (yyvsp[-1].ast)); }
#line 2087 "decafast.tab.c"
    break;

  case 76:
#line 282 "decafast.y"
                                                      {(yyval.ast) = new Method_Call(dynamic_cast<Identifier *>((yyvsp[-3].ast)), (yyvsp[-1].list));}
#line 2093 "decafast.tab.c"
    break;

  case 77:
#line 285 "decafast.y"
                                               {(yyval.list) = initialize_recursive_list((yyvsp[-2].ast), (yyvsp[0].ast));}
#line 2099 "decafast.tab.c"
    break;

  case 78:
#line 286 "decafast.y"
                                              {(yyvsp[-2].list)->push_back((yyvsp[0].ast)); (yyval.list) = (yyvsp[-2].list); }
#line 2105 "decafast.tab.c"
    break;

  case 79:
#line 289 "decafast.y"
                              {(yyval.ast) = new Constant_Expr(&((yyvsp[0].sval)), STRINGTYPE);}
#line 2111 "decafast.tab.c"
    break;

  case 80:
#line 290 "decafast.y"
                              {(yyval.ast) = (yyvsp[0].ast);}
#line 2117 "decafast.tab.c"
    break;

  case 81:
#line 293 "decafast.y"
                                    {(yyval.list) = initialize_recursive_list((yyvsp[-2].ast), (yyvsp[0].ast));}
#line 2123 "decafast.tab.c"
    break;

  case 82:
#line 294 "decafast.y"
                                 {(yyvsp[-2].list)->push_back((yyvsp[0].ast)); (yyval.list) = (yyvsp[-2].list);}
#line 2129 "decafast.tab.c"
    break;

  case 83:
#line 297 "decafast.y"
                                       {(yyval.ast) = new Assign_Var(dynamic_cast<Identifier *>((yyvsp[-2].ast)), (yyvsp[0].ast)); }
#line 2135 "decafast.tab.c"
    break;

  case 84:
#line 298 "decafast.y"
                                                            {(yyval.ast) = new Assign_Arr_Loc(dynamic_cast<Identifier *>((yyvsp[-5].ast)), (yyvsp[-3].ast), (yyvsp[0].ast)); }
#line 2141 "decafast.tab.c"
    break;

  case 85:
#line 302 "decafast.y"
                    {(yyval.ast) = new Var_Expr(dynamic_cast<Identifier *>((yyvsp[0].ast)));}
#line 2147 "decafast.tab.c"
    break;

  case 86:
#line 303 "decafast.y"
                                        {(yyval.ast) = new Arr_Loc_Expr(dynamic_cast<Identifier *>((yyvsp[-3].ast)), (yyvsp[-1].ast));}
#line 2153 "decafast.tab.c"
    break;

  case 87:
#line 307 "decafast.y"
                                              {(yyval.ast) = (yyvsp[0].ast);}
#line 2159 "decafast.tab.c"
    break;

  case 88:
#line 308 "decafast.y"
                                              {(yyval.ast) = (yyvsp[0].ast);}
#line 2165 "decafast.tab.c"
    break;

  case 89:
#line 309 "decafast.y"
                                              {(yyval.ast) = (yyvsp[0].ast);}
#line 2171 "decafast.tab.c"
    break;

  case 90:
#line 310 "decafast.y"
                                              {(yyval.ast) = (yyvsp[-1].ast);}
#line 2177 "decafast.tab.c"
    break;

  case 91:
#line 311 "decafast.y"
                                              {(yyval.ast) = (yyvsp[0].ast);}
#line 2183 "decafast.tab.c"
    break;

  case 92:
#line 312 "decafast.y"
                                              {(yyval.ast) = (yyvsp[0].ast);}
#line 2189 "decafast.tab.c"
    break;

  case 93:
#line 316 "decafast.y"
                                                {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(PLUS));}
#line 2195 "decafast.tab.c"
    break;

  case 94:
#line 317 "decafast.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(MINUS));}
#line 2201 "decafast.tab.c"
    break;

  case 95:
#line 318 "decafast.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(MULT));}
#line 2207 "decafast.tab.c"
    break;

  case 96:
#line 319 "decafast.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(DIV));}
#line 2213 "decafast.tab.c"
    break;

  case 97:
#line 320 "decafast.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(MOD));}
#line 2219 "decafast.tab.c"
    break;

  case 98:
#line 321 "decafast.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(LT));}
#line 2225 "decafast.tab.c"
    break;

  case 99:
#line 322 "decafast.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(GT));}
#line 2231 "decafast.tab.c"
    break;

  case 100:
#line 323 "decafast.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(GEQ));}
#line 2237 "decafast.tab.c"
    break;

  case 101:
#line 324 "decafast.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(EQ));}
#line 2243 "decafast.tab.c"
    break;

  case 102:
#line 325 "decafast.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(NEQ));}
#line 2249 "decafast.tab.c"
    break;

  case 103:
#line 326 "decafast.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(AND));}
#line 2255 "decafast.tab.c"
    break;

  case 104:
#line 327 "decafast.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(OR));}
#line 2261 "decafast.tab.c"
    break;

  case 105:
#line 328 "decafast.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(LEQ));}
#line 2267 "decafast.tab.c"
    break;

  case 106:
#line 331 "decafast.y"
                                                   {(yyval.ast) = new Unary_Expr((yyvsp[0].ast), new Unary_Operator(UNARY_MINUS));}
#line 2273 "decafast.tab.c"
    break;

  case 107:
#line 332 "decafast.y"
                                   {(yyval.ast) = new Unary_Expr((yyvsp[0].ast), new Unary_Operator(NOT));}
#line 2279 "decafast.tab.c"
    break;

  case 108:
#line 336 "decafast.y"
                         {(yyval.ast) = new Constant_Expr(&((yyvsp[0].sval)), INTTYPE);}
#line 2285 "decafast.tab.c"
    break;

  case 109:
#line 337 "decafast.y"
                     {(yyval.ast) = new Constant_Expr(&((yyvsp[0].sval)), INTTYPE);}
#line 2291 "decafast.tab.c"
    break;

  case 110:
#line 338 "decafast.y"
                     {(yyval.ast) = new Constant_Expr(&((yyvsp[0].sval)), BOOLTYPE);}
#line 2297 "decafast.tab.c"
    break;

  case 111:
#line 339 "decafast.y"
                     {(yyval.ast) = new Constant_Expr(&((yyvsp[0].sval)), BOOLTYPE);}
#line 2303 "decafast.tab.c"
    break;

  case 112:
#line 343 "decafast.y"
                       {(yyval.ast) = new Type(VOIDTYPE);}
#line 2309 "decafast.tab.c"
    break;

  case 113:
#line 344 "decafast.y"
                       {(yyval.ast) = (yyvsp[0].ast);}
#line 2315 "decafast.tab.c"
    break;

  case 114:
#line 347 "decafast.y"
                              {(yyval.ast) = new Var_Def(new Type(STRINGTYPE));}
#line 2321 "decafast.tab.c"
    break;

  case 115:
#line 348 "decafast.y"
                              {(yyval.ast) = new Var_Def(dynamic_cast<Type *>((yyvsp[0].ast)));}
#line 2327 "decafast.tab.c"
    break;

  case 116:
#line 350 "decafast.y"
                       {(yyval.ast) = new Type(BOOLTYPE);}
#line 2333 "decafast.tab.c"
    break;

  case 117:
#line 351 "decafast.y"
                       {(yyval.ast) = new Type(INTTYPE);}
#line 2339 "decafast.tab.c"
    break;

  case 118:
#line 353 "decafast.y"
                       {(yyval.ast) = new Identifier(&((yyvsp[0].sval)));}
#line 2345 "decafast.tab.c"
    break;


#line 2349 "decafast.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 355 "decafast.y"

// TODO remember to bring back!

// /* Externs */
// extern_list: /* extern_list can be empty */
//     { decafStmtList *slist = new decafStmtList(); $$ = slist; }
//     ;

// decafpackage: T_PACKAGE T_ID T_LCB T_RCB
//     { $$ = new PackageAST(*$2, new decafStmtList(), new decafStmtList()); delete $2; }
//     ; 

// /* While */


// /* If-Else */
// if_else: if_stmt T_ELSE block {
//         If_Else * temp = dynamic_cast<If_Else *>($1);
//         temp->setElse(dynamic_cast<Block *>($3));
//         $$ = temp;
//     }

// if_stmt: T_IF T_LPAREN expression T_RPAREN block {
//         $$ = new If_Else($3, dynamic_cast<Block *> ($5));
//     }
// /* Blocks */
// method_block: block     {$$ = new Method_Block(&(dynamic_cast<Block *>($1)));}

// block: T_LCB typed_symbol_list_decl statement_list T_RCB {$$ = new Block($2, $3);}
//     | T_LCB typed_symbol_decl statement_list T_RCB {$$ = new Block($2, $3);}
//     | T_LCB typed_symbol_list_decl statement T_RCB {$$ = new Block($2, $3);}
//     | T_LCB typed_symbol_decl statement T_RCB      {$$ = new Block($2, $3);}
//     | T_LCB typed_symbol_decl T_RCB                {$$ = new Block($2, new decafStmtList());}
//     | T_LCB typed_symbol_list_decl T_RCB           {$$ = new Block($2, new decafStmtList());}
//     | T_LCB statement T_RCB                        {$$ = new Block(new decafStmtList(), $2);}
//     | T_LCB statement_list T_RCB                   {$$ = new Block(new decafStmtList(), $2);}
//     | T_LCB T_RCB                                  {$$ = new Block(new decafStmtList(), new decafStmtList());}

// /* Statement and Statements */
// statement_list: statement statement     {$$ = initialize_recursive_list($1, $2); }
//         | statement_list statement      {$1->push_back($2); $$ = $1; }

// statement: assign T_SEMICOLON                {$$ = $1; }
//         | method_call T_SEMICOLON            {$$ = $1; }
//         | block                              {$$ = $1; }
//         | if_stmt                            {$$ = $1; }
//         | if_else                            {$$ = $1; }

// /* Field declarations */
// field_decl_list: field_decl field_decl {
//         $$ = initialize_recursive_list($1, $2);
        
//     }
//     | field_decl_list field_decl {
//         $1->push_back($2); $$ = $1;
//     }

// field_decl: T_VAR typed_symbol_sing T_SEMICOLON{$$ = new Field_Decl($2, SCALAR); }
//     | T_VAR typed_symbol_sing T_ASSIGN constant T_SEMICOLON    {$$ = new Assign_Global($2, getString($4)); }
//     | T_VAR typed_symbol_sing T_LSB constant T_RSB T_SEMICOLON {$$ = new Field_Decl($2, ARRAY, $4->getValue()); }
//     | T_VAR typed_symbols_multi T_SEMICOLON {$$ = createFieldDeclList(dynamic_cast<decafStmtList *>($2)); }
//     | T_VAR typed_symbols_multi T_LSB constant T_RSB T_SEMICOLON {$$ = createFieldDeclListArr(dynamic_cast<decafStmtList *>($2), $4->getValue()); }

// /* For variable declarations */
// typed_symbol_list_decl: typed_symbol_decl typed_symbol_decl {
//         $$ = initialize_recursive_list($1, $2);
//     }
//     |   typed_symbol_list_decl typed_symbol_decl  {
//         $1->push_back($2); $$=$1;
//     }
//     ;

// typed_symbol_decl: T_VAR typed_symbol_sing T_SEMICOLON {$$=$2;}
//     | T_VAR typed_symbols_multi T_SEMICOLON {$$=$2;}
//     ;

// /* For function extern declarations */
// typed_symbol_extern_list: typed_symbol_extern T_COMMA typed_symbol_extern {
//     $$ = initialize_recursive_list($1,$3);
// }
//     | typed_symbol_extern_list T_COMMA typed_symbol_extern {
//         $1->push_back($3); 
//         $$ = $1;
//     }
//     ;

// typed_symbol_extern: T_BOOLTYPE  {$$=new Typed_Symbol(BOOL);}
//     | T_INTTYPE         {$$=new Typed_Symbol(INT);}
//     | T_STRINGTYPE      {$$=new Typed_Symbol(STRING);}

// /* For method declarations arguements */
// typed_symbol_list: typed_symbol_sing T_COMMA typed_symbol_sing {
//         $$ = initialize_recursive_list($1, $3);
//     }
//     |   typed_symbol_list T_COMMA typed_symbol_sing {
//         $1->push_back($3); $$=$1;
//     }

// /* Comment for now, not sure where this is needed */
// /*
// typed_symbol: T_VAR typed_symbols_multi {$$ = $2;}
//     |   T_VAR typed_symbol_sing {$$ = $2;}
// */

// /* General typed symbols, will be used in declarations, field declarations, method and extern function args */
// typed_symbols_multi: untyped_symbols T_BOOLTYPE { $$ = createTypedSymbolList(&($1), BOOL); }
//     | untyped_symbols T_STRINGTYPE { $$ = createTypedSymbolList(&($1), STRING); }
//     | untyped_symbols T_INTTYPE { $$ = createTypedSymbolList(&($1), INT); }

// typed_symbol_sing: T_ID T_BOOLTYPE {$$ = new Typed_Symbol(&($1), BOOL); }
//     | T_ID T_STRINGTYPE {$$ = new Typed_Symbol(&($1), STRING); }
//     | T_ID T_INTTYPE {$$ = new Typed_Symbol(&($1), INT); }

// untyped_symbols: T_ID T_COMMA T_ID {
//         $$ = new Untyped_Symbols();
//         $$->push_front(new Untyped_Symbol(&($1))); 
//         $$->push_back(new Untyped_Symbol(&($3))); 
//     }
//     | untyped_symbols T_COMMA T_ID          {$1->push_back(new Untyped_Symbol(&($3))); $$ = $1;}

// /* Variable Assignments */
// assign_list : assign T_COMMA assign {$$ = initialize_recursive_list($1, $3);}
//     | assign_list T_COMMA assign {$1->push_back($3);}

// assign: T_ID T_ASSIGN expression {$$ = new Assign_Var(&($1), $3); }
//     | T_ID T_LSB expression T_RSB T_ASSIGN expression {$$ = new Assign_Arr_Loc(&($1), $3, $6); }
//     ;

// /* Methods and Method args*/
// method_call: T_ID T_LPAREN T_RPAREN {$$ = new Method_Call(&($1)); }
//         /* Single arg*/
//         | T_ID T_LPAREN expression T_RPAREN     {$$ = new Method_Call(&($1), $3); }
//         /* Mutliple args*/
//         | T_ID T_LPAREN method_args T_RPAREN    {$$ = new Method_Call(&($1), $3);}

// method_args: expression T_COMMA expression     {$$ = initialize_recursive_list($1, $3);}
//     | method_args T_COMMA expression           {$1->push_back($3); $$ = $1; }
//     ;

// /* Expressions */
// expression: constant                          {$$ = $1; }
//     | binary_operation                        {$$ = $1; }
//     | unary_operation                         {$$ = $1; }
//     | rvalue                                  {$$ = $1; }
//     | method_call                             {$$ = $1; }
//     | T_LPAREN expression T_RPAREN            {$$ = $2; }
//     ;

// /* Operators */
// binary_operation:  expression T_PLUS expression {$$ = new Binary_Expr($1, $3, PLUS);}
//     | expression T_MINUS expression   {$$ = new Binary_Expr($1, $3, MINUS);}
//     | expression T_MULT expression    {$$ = new Binary_Expr($1, $3, MULT);}
//     | expression T_DIV expression     {$$ = new Binary_Expr($1, $3, DIV);}
//     | expression T_MOD expression     {$$ = new Binary_Expr($1, $3, MOD);}
//     | expression T_LT expression      {$$ = new Binary_Expr($1, $3, LT);}
//     | expression T_GT expression      {$$ = new Binary_Expr($1, $3, GT);}
//     | expression T_GEQ expression     {$$ = new Binary_Expr($1, $3, GEQ);}
//     | expression T_EQ expression      {$$ = new Binary_Expr($1, $3, EQ);}
//     | expression T_NEQ expression     {$$ = new Binary_Expr($1, $3, NEQ);}
//     | expression T_AND expression     {$$ = new Binary_Expr($1, $3, AND);}
//     | expression T_OR expression      {$$ = new Binary_Expr($1, $3, NOT);}
//     ;

// /* R Values */
// rvalue: T_ID T_LSB expression T_RSB   {$$ = new Arr_Loc_Expr(&($1), $3); } 
//     | T_ID                            {$$ = new Var_Expr(&($1)); }
//     ;

// unary_operation: T_MINUS expression %prec U_MINUS {$$ = new Unary_Expr($2, UNARY_MINUS);}
//     | T_NOT expression %prec U_NOT {$$ = new Unary_Expr($2, NOT);}

// /* Constants */
// constant: T_STRINGCONSTANT  {$$ = new Constant_Expr(&($1), STRING);}
//     | T_CHARCONSTANT {$$ = new Constant_Expr(&($1), CHAR);}
//     | T_INTCONSTANT  {$$ = new Constant_Expr(&($1), INT);}
//     | T_FALSE        {$$ = new Constant_Expr(&($1), BOOL);}
//     | T_TRUE         {$$ = new Constant_Expr(&($1), BOOL);}
//     ;


int main() {
  // parse the input and create the abstract syntax tree
  int retval = yyparse();
  return(retval >= 1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

