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
#line 1 "decafexpr.y"

#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>
#include "default-defs.h"

int yylex(void);
int yyerror(char *); 

// For freeing up left over memory
int yylex_destroy(void);

// print AST?
bool printAST = true;


using namespace std;

// the calls to TheContext in the init above and in the
// following code ensures that we are incrementally generating
// instructions in the right order

#include "decafexpr.cc"

// dummy main function
// WARNING: this is not how you should implement code generation
// for the main function!
// You should write the codegen for the main method as 
// part of the codegen for method declarations (MethodDecl)
static llvm::Function *TheFunction = 0;

// we have to create a main function 
llvm::Function *gen_main_def() {
  // create the top-level definition for main
  llvm::FunctionType *FT = llvm::FunctionType::get(llvm::IntegerType::get(TheContext, 32), false);
  llvm::Function *TheFunction = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "main", TheModule);
  if (TheFunction == 0) {
    throw runtime_error("empty function block"); 
  }
  // Create a new basic block which contains a sequence of LLVM instructions
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", TheFunction);
  // All subsequent calls to IRBuilder will place instructions in this location
  Builder.SetInsertPoint(BB);
  return TheFunction;
}

// For AST lists, starts as the base case
decafStmtList * initialize_recursive_list(decafAST * a, decafAST * b) {
    decafStmtList * list = new decafStmtList();
    list->push_front(a); list->push_back(b);
    return list;
}


#line 126 "decafexpr.tab.c"

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
#ifndef YY_YY_DECAFEXPR_TAB_H_INCLUDED
# define YY_YY_DECAFEXPR_TAB_H_INCLUDED
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
    T_STRINGCONSTANT = 301,
    T_TRUE = 302,
    T_INTCONSTANT = 303,
    T_ID = 304,
    T_COMMENT = 305,
    T_WHITESPACE = 306,
    T_NULL = 307,
    U_NOT = 308,
    U_MINUS = 309
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 59 "decafexpr.y"

    class decafAST *ast;
    class decafStmtList *list;
    // For a list of identifiers, cache them in to a vector string
    class string_vector *id_list;
    std::string *sval;
 

#line 242 "decafexpr.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_DECAFEXPR_TAB_H_INCLUDED  */



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
#define YYLAST   424

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  236

#define YYUNDEFTOK  2
#define YYMAXUTOK   309


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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   103,   103,   106,   115,   126,   132,   138,   144,   153,
     154,   156,   157,   160,   163,   167,   168,   170,   171,   174,
     179,   183,   184,   187,   188,   191,   194,   199,   200,   201,
     202,   205,   206,   208,   209,   211,   212,   213,   214,   215,
     216,   217,   221,   222,   223,   225,   226,   227,   230,   231,
     233,   234,   237,   242,   246,   252,   259,   262,   267,   268,
     270,   271,   273,   276,   280,   281,   283,   284,   285,   289,
     290,   292,   293,   295,   297,   299,   305,   308,   310,   312,
     315,   316,   319,   320,   323,   324,   328,   329,   333,   334,
     335,   336,   337,   338,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   359,
     360,   364,   365,   366,   367,   368,   372,   373,   376,   377,
     379,   380,   383,   389,   394
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
  "T_STRINGCONSTANT", "T_TRUE", "T_INTCONSTANT", "T_ID", "T_COMMENT",
  "T_WHITESPACE", "T_NULL", "U_NOT", "U_MINUS", "$accept", "start",
  "program", "decafpackage", "extern_declaration", "extern_list",
  "extern_func", "extern_arg_group", "extern_func_args", "while_loop",
  "for_loop", "for_loop_assigns", "assign_list", "if_stmt", "block",
  "statement_group", "statement_list", "statement", "keywords", "return",
  "field_decl_group", "field_decl_list", "field_decl", "assign_global",
  "method_decl_group", "method_decl_list", "method_decl",
  "method_decl_args", "method_decl_multi_args", "typed_symbols_decl_group",
  "typed_symbols_decls", "typed_symbols_decl", "typed_symbols",
  "typed_symbol", "method_call", "method_args", "method_arg", "assign",
  "rvalue", "expression", "binary_operation", "unary_operation",
  "constant", "method_type", "extern_type", "decaf_type",
  "identifier_list", "identifier", YY_NULLPTR
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
     305,   306,   307,   308,   309
};
# endif

#define YYPACT_NINF (-126)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      13,   -34,   -10,    31,  -126,  -126,    80,    22,    22,  -126,
      86,   -34,  -126,  -126,  -126,  -126,     3,    68,  -126,   -34,
      66,     6,    59,    59,  -126,   106,    87,    87,   124,   111,
     109,    94,   177,  -126,   159,  -126,  -126,  -126,  -126,  -126,
     115,  -126,  -126,  -126,   113,   151,   160,  -126,   -12,   136,
     138,   162,   185,   165,    16,  -126,  -126,   187,  -126,   115,
     161,   161,   115,   197,   200,   202,   -14,  -126,  -126,   206,
    -126,   210,   372,  -126,  -126,   201,  -126,  -126,   246,   115,
     -34,   -34,  -126,   -14,   -14,  -126,  -126,  -126,  -126,  -126,
     224,  -126,    52,  -126,   246,  -126,  -126,   225,   227,  -126,
    -126,  -126,  -126,   245,   248,    66,   250,   264,  -126,  -126,
    -126,  -126,   289,   105,   105,   263,  -126,    92,   271,   271,
     279,   286,   298,    21,  -126,  -126,  -126,   -34,   184,  -126,
      76,   184,   144,  -126,  -126,  -126,  -126,  -126,   329,  -126,
    -126,  -126,  -126,  -126,   184,   134,   184,   301,   322,   341,
      75,   184,   184,   184,  -126,  -126,   287,  -126,  -126,  -126,
      50,  -126,   306,  -126,   325,  -126,   363,  -126,  -126,    14,
      62,   363,   249,   184,   -34,   -34,  -126,  -126,   344,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   246,   184,   246,  -126,   173,  -126,
     173,  -126,   342,   229,  -126,  -126,  -126,   395,  -126,   189,
     189,   189,  -126,  -126,   189,   189,   158,  -126,  -126,   189,
     381,   158,   323,   268,  -126,  -126,  -126,   184,   -34,   246,
    -126,   363,   346,  -126,   246,  -126
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     2,     4,     0,     9,    10,   124,
       0,     0,     1,     3,    12,    11,     0,     0,     8,     0,
       0,     0,    48,    49,    56,     0,    58,    59,     0,     0,
     124,     0,     0,     7,     0,    51,    50,     6,    61,    60,
       0,   120,   121,   118,     0,    16,    15,   119,    66,     0,
       0,     0,     0,     0,     0,     5,   116,     0,   117,     0,
       0,     0,     0,     0,    64,    65,     0,   122,   123,     0,
      53,     0,     0,    52,    14,     0,    18,    17,     0,     0,
       0,     0,    76,     0,     0,   111,   113,   114,   112,   115,
       0,    13,     0,    63,     0,    68,    67,     0,     0,    57,
      30,    43,    42,     0,     0,     0,     0,    45,    39,    40,
      38,    41,     0,    31,    32,     0,    44,     0,    69,    70,
       0,     0,     0,     0,    62,    55,    54,     0,     0,    74,
       0,     0,     0,    29,    34,    33,    37,    28,     0,    72,
      71,    73,    36,    35,     0,     0,     0,     0,    22,    21,
       0,     0,     0,     0,    92,    93,     0,    89,    90,    88,
      86,    75,     0,    46,     0,    27,    84,    77,    82,     0,
       0,    83,     0,     0,     0,     0,   109,   110,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    47,     0,    79,
       0,    78,     0,     0,    24,    23,    91,   104,    97,   102,
     101,   100,   107,   108,   106,    99,    95,    98,    96,   103,
     105,    94,    25,     0,    19,    81,    80,     0,     0,     0,
      87,    85,     0,    26,     0,    20
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -126,  -126,  -126,   362,  -126,  -126,    99,  -126,  -126,  -126,
    -126,   156,  -126,  -126,   -77,   273,  -126,   -92,  -126,  -126,
    -126,  -126,   108,  -126,   367,  -126,   117,  -126,  -126,  -126,
    -126,    27,  -126,   -76,   -62,  -126,   -78,  -125,  -126,  -119,
    -126,  -126,   330,    19,   107,   -25,   316,    -1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,     8,    44,    45,   108,
     109,   147,   148,   110,   111,   112,   113,   114,   115,   116,
      21,    22,    23,    24,    25,    26,    27,    63,    64,   117,
     118,   119,   120,    65,   154,   169,   170,   122,   155,   171,
     157,   158,   159,    57,    46,    58,    31,   160
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      10,    93,   149,    47,    95,    96,    52,    54,    18,   156,
      17,    33,   162,   164,    62,     9,     1,   124,    29,    32,
      41,   134,   135,    72,    42,   166,    11,   172,   144,   129,
     121,    12,   176,   177,   178,    47,    47,     9,   198,    19,
     199,    82,    19,    20,     2,    73,   145,    66,   146,   204,
     205,   121,   121,     2,   203,   121,    92,   100,    97,    98,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   145,   223,   195,    75,    66,
      66,    78,   144,     1,   101,   102,   200,   103,   201,   104,
      16,   123,   105,    28,   106,   107,    92,   137,    94,    20,
      50,     9,   146,   149,    66,   161,    14,    15,   231,    92,
      41,    37,   123,   123,    42,    30,   123,   222,    50,   224,
     225,    51,   226,    19,   101,   102,   150,   103,    41,   104,
      35,    36,    42,    49,   106,   107,    48,   101,   102,    59,
     103,     9,   104,    38,    39,   139,   140,   106,   107,    41,
      40,   151,   233,    42,     9,   152,    56,   235,    41,   153,
     167,   151,    42,    43,    55,   152,   180,    76,    77,   153,
     163,   184,   185,   150,   150,    60,   189,   190,    85,    86,
     168,    87,    88,     9,    61,    67,    89,    68,    85,    86,
     151,    87,    88,     9,   152,    41,    89,   180,   153,    42,
      43,   151,   184,   185,    53,   152,   188,   189,   190,   153,
      69,    41,   193,    71,    70,    42,    74,    85,    86,   168,
      87,    88,     9,    79,    80,    89,    81,   150,    85,    86,
      91,    87,    88,     9,    83,   179,    89,   180,    84,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
      92,   192,   193,    99,   125,   179,   126,   180,   228,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     127,   192,   193,   128,   179,   131,   180,   202,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   132,
     192,   193,   136,   179,   133,   180,   230,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   141,   192,
     193,   105,   179,   194,   180,   142,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   143,   192,   193,
     173,   179,   196,   180,   165,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   174,   192,   193,   227,
     179,   197,   180,   229,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   175,   192,   193,    13,   179,
     206,   180,   234,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   232,   192,   193,   179,    34,   180,
     138,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,    90,   180,   193,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,    85,    86,   193,    87,
      88,   130,     0,     0,    89
};

static const yytype_int16 yycheck[] =
{
       1,    78,   127,    28,    80,    81,    31,    32,     5,   128,
      11,     5,   131,   132,    26,    49,     3,    94,    19,    20,
      34,   113,   114,     7,    38,   144,    36,   146,     7,   105,
      92,     0,   151,   152,   153,    60,    61,    49,    24,    36,
      26,    66,    36,    40,    31,    29,    25,    48,    27,   174,
     175,   113,   114,    31,   173,   117,     4,     5,    83,    84,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,    25,   195,    27,    59,    80,
      81,    62,     7,     3,    32,    33,    24,    35,    26,    37,
       4,    92,    40,    25,    42,    43,     4,     5,    79,    40,
      24,    49,    27,   228,   105,   130,     7,     8,   227,     4,
      34,     5,   113,   114,    38,    49,   117,   194,    24,   196,
     198,    27,   200,    36,    32,    33,   127,    35,    34,    37,
      22,    23,    38,    24,    42,    43,    25,    32,    33,    26,
      35,    49,    37,    26,    27,   118,   119,    42,    43,    34,
      26,    17,   229,    38,    49,    21,    41,   234,    34,    25,
      26,    17,    38,    39,     5,    21,     8,    60,    61,    25,
      26,    13,    14,   174,   175,    24,    18,    19,    44,    45,
      46,    47,    48,    49,    24,    49,    52,    49,    44,    45,
      17,    47,    48,    49,    21,    34,    52,     8,    25,    38,
      39,    17,    13,    14,    27,    21,    17,    18,    19,    25,
      48,    34,    23,    48,    29,    38,    29,    44,    45,    46,
      47,    48,    49,    26,    24,    52,    24,   228,    44,    45,
      29,    47,    48,    49,    28,     6,    52,     8,    28,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
       4,    22,    23,    29,    29,     6,    29,     8,    29,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      25,    22,    23,    25,     6,    25,     8,    28,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    25,
      22,    23,    29,     6,     5,     8,    28,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    29,    22,
      23,    40,     6,    26,     8,    29,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    29,    22,    23,
      29,     6,    26,     8,     5,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    24,    22,    23,     7,
       6,    26,     8,    30,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    24,    22,    23,     6,     6,
      26,     8,    26,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,   228,    22,    23,     6,    21,     8,
     117,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    72,     8,    23,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    44,    45,    23,    47,
      48,   105,    -1,    -1,    52
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    31,    56,    57,    58,    59,    60,    61,    49,
     102,    36,     0,    58,    61,    61,     4,   102,     5,    36,
      40,    75,    76,    77,    78,    79,    80,    81,    25,   102,
      49,   101,   102,     5,    79,    77,    77,     5,    81,    81,
      26,    34,    38,    39,    62,    63,    99,   100,    25,    24,
      24,    27,   100,    27,   100,     5,    41,    98,   100,    26,
      24,    24,    26,    82,    83,    88,   102,    49,    49,    48,
      29,    48,     7,    29,    29,    98,    99,    99,    98,    26,
      24,    24,   100,    28,    28,    44,    45,    47,    48,    52,
      97,    29,     4,    69,    98,    88,    88,   100,   100,    29,
       5,    32,    33,    35,    37,    40,    42,    43,    64,    65,
      68,    69,    70,    71,    72,    73,    74,    84,    85,    86,
      87,    89,    92,   102,    69,    29,    29,    25,    25,    88,
     101,    25,    25,     5,    72,    72,    29,     5,    70,    86,
      86,    29,    29,    29,     7,    25,    27,    66,    67,    92,
     102,    17,    21,    25,    89,    93,    94,    95,    96,    97,
     102,   100,    94,    26,    94,     5,    94,    26,    46,    90,
      91,    94,    94,    29,    24,    24,    94,    94,    94,     6,
       8,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    22,    23,    26,    27,    26,    26,    24,    26,
      24,    26,    28,    94,    92,    92,    26,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    69,    94,    69,    91,    91,     7,    29,    30,
      28,    94,    66,    69,    26,    69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    55,    56,    57,    57,    58,    58,    58,    58,    59,
      59,    60,    60,    61,    61,    62,    62,    63,    63,    64,
      65,    66,    66,    67,    67,    68,    68,    69,    69,    69,
      69,    70,    70,    71,    71,    72,    72,    72,    72,    72,
      72,    72,    73,    73,    73,    74,    74,    74,    75,    75,
      76,    76,    77,    77,    77,    77,    77,    78,    79,    79,
      80,    80,    81,    81,    82,    82,    83,    83,    83,    84,
      84,    85,    85,    86,    87,    87,    88,    89,    89,    89,
      90,    90,    91,    91,    92,    92,    93,    93,    94,    94,
      94,    94,    94,    94,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    96,
      96,    97,    97,    97,    97,    97,    98,    98,    99,    99,
     100,   100,   101,   101,   102
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     6,     5,     5,     4,     1,
       1,     2,     2,     8,     7,     1,     1,     3,     3,     5,
       9,     1,     1,     3,     3,     5,     7,     4,     3,     3,
       2,     1,     1,     2,     2,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     4,     1,     1,
       2,     2,     4,     4,     7,     7,     1,     6,     1,     1,
       2,     2,     7,     6,     1,     1,     0,     3,     3,     1,
       1,     2,     2,     2,     2,     3,     2,     3,     4,     4,
       3,     3,     1,     1,     3,     6,     1,     4,     1,     1,
       1,     3,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     1
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
#line 107 "decafexpr.y"
    { 
        ProgramAST *prog = new ProgramAST((decafStmtList *)(yyvsp[-1].ast), (PackageAST *)(yyvsp[0].ast)); 
        if (printAST) {
            cout << getString(prog) << endl;
        }
        delete prog;
    }
#line 1636 "decafexpr.tab.c"
    break;

  case 4:
#line 116 "decafexpr.y"
    { 
        ProgramAST *prog = new ProgramAST(new decafStmtList(), (PackageAST *)(yyvsp[0].ast)); 
        if (printAST) {
            cout << getString(prog) << endl;
        }
        delete prog;
    }
#line 1648 "decafexpr.tab.c"
    break;

  case 5:
#line 127 "decafexpr.y"
    {   
        string id_name = (yyvsp[-4].ast)->str();
        (yyval.ast) = new PackageAST(id_name, dynamic_cast<decafStmtList *>((yyvsp[-2].ast)), dynamic_cast<decafStmtList *>((yyvsp[-1].ast)));   
        delete (yyvsp[-4].ast);     
    }
#line 1658 "decafexpr.tab.c"
    break;

  case 6:
#line 133 "decafexpr.y"
    {   
        string id_name = (yyvsp[-3].ast)->str();
        (yyval.ast) = new PackageAST(id_name, new decafStmtList() , dynamic_cast<decafStmtList *>((yyvsp[-1].ast)));  
        delete (yyvsp[-3].ast);        
    }
#line 1668 "decafexpr.tab.c"
    break;

  case 7:
#line 139 "decafexpr.y"
    {   
        string id_name = (yyvsp[-3].ast)->str();
        (yyval.ast) = new PackageAST(id_name, dynamic_cast<decafStmtList *>((yyvsp[-1].ast)), new decafStmtList());  
        delete (yyvsp[-3].ast);        
    }
#line 1678 "decafexpr.tab.c"
    break;

  case 8:
#line 144 "decafexpr.y"
                                       {   
        string id_name = (yyvsp[-2].ast)->str();
        (yyval.ast) = new PackageAST(id_name, new decafStmtList(), new decafStmtList());    
        delete (yyvsp[-2].ast);     
    }
#line 1688 "decafexpr.tab.c"
    break;

  case 9:
#line 153 "decafexpr.y"
                                        {(yyval.ast) = (yyvsp[0].list);}
#line 1694 "decafexpr.tab.c"
    break;

  case 10:
#line 154 "decafexpr.y"
                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 1700 "decafexpr.tab.c"
    break;

  case 11:
#line 156 "decafexpr.y"
                                       {(yyval.list) = initialize_recursive_list((yyvsp[-1].ast), (yyvsp[0].ast));}
#line 1706 "decafexpr.tab.c"
    break;

  case 12:
#line 157 "decafexpr.y"
                                {(yyvsp[-1].list)->push_back((yyvsp[0].ast)); (yyval.list) = (yyvsp[-1].list);}
#line 1712 "decafexpr.tab.c"
    break;

  case 13:
#line 160 "decafexpr.y"
                                                                                                   {
        (yyval.ast) = new Extern_Func(dynamic_cast<Identifier *>((yyvsp[-5].ast)), dynamic_cast<Type *>((yyvsp[-1].ast)), (yyvsp[-3].ast));
    }
#line 1720 "decafexpr.tab.c"
    break;

  case 14:
#line 163 "decafexpr.y"
                                                                           {
        (yyval.ast) = new Extern_Func(dynamic_cast<Identifier *>((yyvsp[-4].ast)), dynamic_cast<Type *>((yyvsp[-1].ast)), new decafStmtList());
    }
#line 1728 "decafexpr.tab.c"
    break;

  case 15:
#line 167 "decafexpr.y"
                                {(yyval.ast) = (yyvsp[0].ast);}
#line 1734 "decafexpr.tab.c"
    break;

  case 16:
#line 168 "decafexpr.y"
                                {(yyval.ast) = (yyvsp[0].list);}
#line 1740 "decafexpr.tab.c"
    break;

  case 17:
#line 170 "decafexpr.y"
                                                    {(yyval.list) = initialize_recursive_list((yyvsp[-2].ast), (yyvsp[0].ast));}
#line 1746 "decafexpr.tab.c"
    break;

  case 18:
#line 171 "decafexpr.y"
                                                    {(yyvsp[-2].list)->push_back((yyvsp[0].ast)); (yyval.list) = (yyvsp[-2].list);}
#line 1752 "decafexpr.tab.c"
    break;

  case 19:
#line 174 "decafexpr.y"
                                                       {
    (yyval.ast) = new While_Loop((yyvsp[-2].ast), dynamic_cast<Block *>((yyvsp[0].ast)));
}
#line 1760 "decafexpr.tab.c"
    break;

  case 20:
#line 179 "decafexpr.y"
                                                                                                             {
        (yyval.ast) = new For_Loop((yyvsp[-6].ast), (yyvsp[-4].ast), (yyvsp[-2].ast), dynamic_cast<Block *>((yyvsp[0].ast)));
    }
#line 1768 "decafexpr.tab.c"
    break;

  case 21:
#line 183 "decafexpr.y"
                         {(yyval.ast) = (yyvsp[0].ast);}
#line 1774 "decafexpr.tab.c"
    break;

  case 22:
#line 184 "decafexpr.y"
                         {(yyval.ast) = (yyvsp[0].list);}
#line 1780 "decafexpr.tab.c"
    break;

  case 23:
#line 187 "decafexpr.y"
                                    {(yyval.list) = initialize_recursive_list((yyvsp[-2].ast), (yyvsp[0].ast));}
#line 1786 "decafexpr.tab.c"
    break;

  case 24:
#line 188 "decafexpr.y"
                                 {(yyvsp[-2].list)->push_back((yyvsp[0].ast)); (yyval.list) = (yyvsp[-2].list);}
#line 1792 "decafexpr.tab.c"
    break;

  case 25:
#line 191 "decafexpr.y"
                                                 {
        (yyval.ast) = new If_Else((yyvsp[-2].ast), dynamic_cast<Block *> ((yyvsp[0].ast)));
    }
#line 1800 "decafexpr.tab.c"
    break;

  case 26:
#line 194 "decafexpr.y"
                                                           {
        (yyval.ast) = new If_Else((yyvsp[-4].ast), dynamic_cast<Block *> ((yyvsp[-2].ast)), dynamic_cast<Block *> ((yyvsp[0].ast)));
    }
#line 1808 "decafexpr.tab.c"
    break;

  case 27:
#line 199 "decafexpr.y"
                                                                          {(yyval.ast) = new Block((yyvsp[-2].ast), (yyvsp[-1].ast)); }
#line 1814 "decafexpr.tab.c"
    break;

  case 28:
#line 200 "decafexpr.y"
                                                                          {(yyval.ast) = new Block((yyvsp[-1].ast), new decafStmtList()); }
#line 1820 "decafexpr.tab.c"
    break;

  case 29:
#line 201 "decafexpr.y"
                                                                          {(yyval.ast) = new Block(new decafStmtList(), (yyvsp[-1].ast)); }
#line 1826 "decafexpr.tab.c"
    break;

  case 30:
#line 202 "decafexpr.y"
                                                                          {(yyval.ast) = new Block(new decafStmtList(), new decafStmtList()); }
#line 1832 "decafexpr.tab.c"
    break;

  case 31:
#line 205 "decafexpr.y"
                                        {(yyval.ast) = (yyvsp[0].list);}
#line 1838 "decafexpr.tab.c"
    break;

  case 32:
#line 206 "decafexpr.y"
                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 1844 "decafexpr.tab.c"
    break;

  case 33:
#line 208 "decafexpr.y"
                                        {(yyval.list) = initialize_recursive_list((yyvsp[-1].ast), (yyvsp[0].ast)); }
#line 1850 "decafexpr.tab.c"
    break;

  case 34:
#line 209 "decafexpr.y"
                                        {(yyvsp[-1].list)->push_back((yyvsp[0].ast)); (yyval.list) = (yyvsp[-1].list); }
#line 1856 "decafexpr.tab.c"
    break;

  case 35:
#line 211 "decafexpr.y"
                                        {(yyval.ast) = (yyvsp[-1].ast);}
#line 1862 "decafexpr.tab.c"
    break;

  case 36:
#line 212 "decafexpr.y"
                                        {(yyval.ast) = (yyvsp[-1].ast);}
#line 1868 "decafexpr.tab.c"
    break;

  case 37:
#line 213 "decafexpr.y"
                                        {(yyval.ast) = (yyvsp[-1].ast);}
#line 1874 "decafexpr.tab.c"
    break;

  case 38:
#line 214 "decafexpr.y"
                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 1880 "decafexpr.tab.c"
    break;

  case 39:
#line 215 "decafexpr.y"
                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 1886 "decafexpr.tab.c"
    break;

  case 40:
#line 216 "decafexpr.y"
                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 1892 "decafexpr.tab.c"
    break;

  case 41:
#line 217 "decafexpr.y"
                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 1898 "decafexpr.tab.c"
    break;

  case 42:
#line 221 "decafexpr.y"
                     {(yyval.ast) = new Continue();}
#line 1904 "decafexpr.tab.c"
    break;

  case 43:
#line 222 "decafexpr.y"
                     {(yyval.ast) = new Break();}
#line 1910 "decafexpr.tab.c"
    break;

  case 44:
#line 223 "decafexpr.y"
                     {(yyval.ast) = (yyvsp[0].ast);}
#line 1916 "decafexpr.tab.c"
    break;

  case 45:
#line 225 "decafexpr.y"
                     {(yyval.ast) = new Return();}
#line 1922 "decafexpr.tab.c"
    break;

  case 46:
#line 226 "decafexpr.y"
                                    {(yyval.ast) = new Return();}
#line 1928 "decafexpr.tab.c"
    break;

  case 47:
#line 227 "decafexpr.y"
                                               {(yyval.ast) = new Return((yyvsp[-1].ast));}
#line 1934 "decafexpr.tab.c"
    break;

  case 48:
#line 230 "decafexpr.y"
                                           {(yyval.ast) = (yyvsp[0].list);}
#line 1940 "decafexpr.tab.c"
    break;

  case 49:
#line 231 "decafexpr.y"
                                           {(yyval.ast) = (yyvsp[0].ast);}
#line 1946 "decafexpr.tab.c"
    break;

  case 50:
#line 233 "decafexpr.y"
                                          {(yyval.list) = initialize_recursive_list((yyvsp[-1].ast), (yyvsp[0].ast));}
#line 1952 "decafexpr.tab.c"
    break;

  case 51:
#line 234 "decafexpr.y"
                                          {(yyvsp[-1].list)->push_back((yyvsp[0].ast)); (yyval.list) = (yyvsp[-1].list);}
#line 1958 "decafexpr.tab.c"
    break;

  case 52:
#line 237 "decafexpr.y"
                                                    {
        Identifier * id = dynamic_cast<Identifier *>((yyvsp[-2].ast));
        Type * type = dynamic_cast<Type *>((yyvsp[-1].ast));
        (yyval.ast)  = new Field_Decl(id, type, new Field_Size());
    }
#line 1968 "decafexpr.tab.c"
    break;

  case 53:
#line 242 "decafexpr.y"
                                                   {
        (yyval.ast) = vector_to_field_decls((yyvsp[-2].id_list), dynamic_cast<Type *>((yyvsp[-1].ast)));
        delete (yyvsp[-2].id_list); (yyvsp[-1].ast);
    }
#line 1977 "decafexpr.tab.c"
    break;

  case 54:
#line 246 "decafexpr.y"
                                                                        {
        Identifier * id = dynamic_cast<Identifier *>((yyvsp[-5].ast));
        Type * type = dynamic_cast<Type *>((yyvsp[-1].ast));
        Constant_Expr * const_expr = new Constant_Expr(&((yyvsp[-3].sval)), INTTYPE);
        (yyval.ast)  = new Field_Decl(id, type, new Field_Size(&const_expr));   
    }
#line 1988 "decafexpr.tab.c"
    break;

  case 55:
#line 252 "decafexpr.y"
                                                                             {
        Type * type = dynamic_cast<Type *>((yyvsp[-1].ast));
        Constant_Expr * size = new Constant_Expr(&((yyvsp[-3].sval)), INTTYPE);
        Field_Size * field_sz = new Field_Size(&size);
        (yyval.ast) = vector_to_field_decls((yyvsp[-5].id_list), type, field_sz);
        delete field_sz; delete type;
    }
#line 2000 "decafexpr.tab.c"
    break;

  case 56:
#line 259 "decafexpr.y"
                            {(yyval.ast) = (yyvsp[0].ast);}
#line 2006 "decafexpr.tab.c"
    break;

  case 57:
#line 262 "decafexpr.y"
                                                                         {
    (yyval.ast) = new Assign_Global(dynamic_cast<Identifier *>((yyvsp[-4].ast)), dynamic_cast<Type *>((yyvsp[-3].ast)), dynamic_cast<Constant_Expr *>((yyvsp[-1].ast)));
}
#line 2014 "decafexpr.tab.c"
    break;

  case 58:
#line 267 "decafexpr.y"
                                                     {(yyval.ast) = (yyvsp[0].list); }
#line 2020 "decafexpr.tab.c"
    break;

  case 59:
#line 268 "decafexpr.y"
                                                     {(yyval.ast) = (yyvsp[0].ast); }
#line 2026 "decafexpr.tab.c"
    break;

  case 60:
#line 270 "decafexpr.y"
                                                     {(yyval.list) = initialize_recursive_list ((yyvsp[-1].ast), (yyvsp[0].ast));}
#line 2032 "decafexpr.tab.c"
    break;

  case 61:
#line 271 "decafexpr.y"
                                                     {(yyvsp[-1].list)->push_back((yyvsp[0].ast)), (yyval.list)=(yyvsp[-1].list);}
#line 2038 "decafexpr.tab.c"
    break;

  case 62:
#line 273 "decafexpr.y"
                                                                                    {
        (yyval.ast) = new Method_Decl(dynamic_cast<Identifier *>((yyvsp[-5].ast)), dynamic_cast<Type *>((yyvsp[-1].ast)), (yyvsp[-3].ast), dynamic_cast<Block *>((yyvsp[0].ast)));
    }
#line 2046 "decafexpr.tab.c"
    break;

  case 63:
#line 276 "decafexpr.y"
                                                            {
        (yyval.ast) = new Method_Decl(dynamic_cast<Identifier *>((yyvsp[-4].ast)), dynamic_cast<Type *>((yyvsp[-1].ast)), new decafStmtList(), dynamic_cast<Block *>((yyvsp[0].ast)));
    }
#line 2054 "decafexpr.tab.c"
    break;

  case 64:
#line 280 "decafexpr.y"
                                         {(yyval.ast) = (yyvsp[0].list);}
#line 2060 "decafexpr.tab.c"
    break;

  case 65:
#line 281 "decafexpr.y"
                   {(yyval.ast) = (yyvsp[0].ast);}
#line 2066 "decafexpr.tab.c"
    break;

  case 66:
#line 283 "decafexpr.y"
                                                            {(yyval.list) = new decafStmtList();}
#line 2072 "decafexpr.tab.c"
    break;

  case 67:
#line 284 "decafexpr.y"
                                                            {(yyval.list) = initialize_recursive_list((yyvsp[-2].ast), (yyvsp[0].ast));}
#line 2078 "decafexpr.tab.c"
    break;

  case 68:
#line 285 "decafexpr.y"
                                                            {(yyvsp[-2].list)->push_back((yyvsp[0].ast)); (yyval.list)=(yyvsp[-2].list);}
#line 2084 "decafexpr.tab.c"
    break;

  case 69:
#line 289 "decafexpr.y"
                                                        {(yyval.ast) = (yyvsp[0].list); }
#line 2090 "decafexpr.tab.c"
    break;

  case 70:
#line 290 "decafexpr.y"
                                                        {(yyval.ast) = (yyvsp[0].ast); }
#line 2096 "decafexpr.tab.c"
    break;

  case 71:
#line 292 "decafexpr.y"
                                                           {(yyval.list) = initialize_recursive_list((yyvsp[-1].ast), (yyvsp[0].ast));}
#line 2102 "decafexpr.tab.c"
    break;

  case 72:
#line 293 "decafexpr.y"
                                                           {(yyvsp[-1].list)->push_back((yyvsp[0].ast)); (yyval.list) = (yyvsp[-1].list); }
#line 2108 "decafexpr.tab.c"
    break;

  case 73:
#line 295 "decafexpr.y"
                                                        {(yyval.ast)=(yyvsp[-1].ast);}
#line 2114 "decafexpr.tab.c"
    break;

  case 74:
#line 297 "decafexpr.y"
                                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 2120 "decafexpr.tab.c"
    break;

  case 75:
#line 299 "decafexpr.y"
                                                         {
                                                            (yyval.ast) = vector_to_var_defs((yyvsp[-1].id_list), dynamic_cast<Type *>((yyvsp[0].ast)));
                                                            delete (yyvsp[0].ast); delete (yyvsp[-1].id_list); 
                                                         }
#line 2129 "decafexpr.tab.c"
    break;

  case 76:
#line 305 "decafexpr.y"
                                                        {(yyval.ast) = new Var_Def((yyvsp[-1].ast), dynamic_cast<Type *>((yyvsp[0].ast))); }
#line 2135 "decafexpr.tab.c"
    break;

  case 77:
#line 308 "decafexpr.y"
                                          {(yyval.ast) = new Method_Call(dynamic_cast<Identifier *>((yyvsp[-2].ast))); }
#line 2141 "decafexpr.tab.c"
    break;

  case 78:
#line 310 "decafexpr.y"
                                                      {(yyval.ast) = new Method_Call(dynamic_cast<Identifier *>((yyvsp[-3].ast)), (yyvsp[-1].ast)); }
#line 2147 "decafexpr.tab.c"
    break;

  case 79:
#line 312 "decafexpr.y"
                                                      {(yyval.ast) = new Method_Call(dynamic_cast<Identifier *>((yyvsp[-3].ast)), (yyvsp[-1].list));}
#line 2153 "decafexpr.tab.c"
    break;

  case 80:
#line 315 "decafexpr.y"
                                               {(yyval.list) = initialize_recursive_list((yyvsp[-2].ast), (yyvsp[0].ast));}
#line 2159 "decafexpr.tab.c"
    break;

  case 81:
#line 316 "decafexpr.y"
                                              {(yyvsp[-2].list)->push_back((yyvsp[0].ast)); (yyval.list) = (yyvsp[-2].list); }
#line 2165 "decafexpr.tab.c"
    break;

  case 82:
#line 319 "decafexpr.y"
                              {(yyval.ast) = new Constant_Expr(&((yyvsp[0].sval)), STRINGTYPE);}
#line 2171 "decafexpr.tab.c"
    break;

  case 83:
#line 320 "decafexpr.y"
                              {(yyval.ast) = (yyvsp[0].ast);}
#line 2177 "decafexpr.tab.c"
    break;

  case 84:
#line 323 "decafexpr.y"
                                       {(yyval.ast) = new Assign_Var(dynamic_cast<Identifier *>((yyvsp[-2].ast)), (yyvsp[0].ast)); }
#line 2183 "decafexpr.tab.c"
    break;

  case 85:
#line 324 "decafexpr.y"
                                                            {(yyval.ast) = new Assign_Arr_Loc(dynamic_cast<Identifier *>((yyvsp[-5].ast)), (yyvsp[-3].ast), (yyvsp[0].ast)); }
#line 2189 "decafexpr.tab.c"
    break;

  case 86:
#line 328 "decafexpr.y"
                    {(yyval.ast) = new Var_Expr(dynamic_cast<Identifier *>((yyvsp[0].ast)));}
#line 2195 "decafexpr.tab.c"
    break;

  case 87:
#line 329 "decafexpr.y"
                                        {(yyval.ast) = new Arr_Loc_Expr(dynamic_cast<Identifier *>((yyvsp[-3].ast)), (yyvsp[-1].ast));}
#line 2201 "decafexpr.tab.c"
    break;

  case 88:
#line 333 "decafexpr.y"
                                              {(yyval.ast) = (yyvsp[0].ast);}
#line 2207 "decafexpr.tab.c"
    break;

  case 89:
#line 334 "decafexpr.y"
                                              {(yyval.ast) = (yyvsp[0].ast);}
#line 2213 "decafexpr.tab.c"
    break;

  case 90:
#line 335 "decafexpr.y"
                                              {(yyval.ast) = (yyvsp[0].ast);}
#line 2219 "decafexpr.tab.c"
    break;

  case 91:
#line 336 "decafexpr.y"
                                              {(yyval.ast) = (yyvsp[-1].ast);}
#line 2225 "decafexpr.tab.c"
    break;

  case 92:
#line 337 "decafexpr.y"
                                              {(yyval.ast) = (yyvsp[0].ast);}
#line 2231 "decafexpr.tab.c"
    break;

  case 93:
#line 338 "decafexpr.y"
                                              {(yyval.ast) = (yyvsp[0].ast);}
#line 2237 "decafexpr.tab.c"
    break;

  case 94:
#line 342 "decafexpr.y"
                                                {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(PLUS));}
#line 2243 "decafexpr.tab.c"
    break;

  case 95:
#line 343 "decafexpr.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(MINUS));}
#line 2249 "decafexpr.tab.c"
    break;

  case 96:
#line 344 "decafexpr.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(MULT));}
#line 2255 "decafexpr.tab.c"
    break;

  case 97:
#line 345 "decafexpr.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(DIV));}
#line 2261 "decafexpr.tab.c"
    break;

  case 98:
#line 346 "decafexpr.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(MOD));}
#line 2267 "decafexpr.tab.c"
    break;

  case 99:
#line 347 "decafexpr.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(LT));}
#line 2273 "decafexpr.tab.c"
    break;

  case 100:
#line 348 "decafexpr.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(GT));}
#line 2279 "decafexpr.tab.c"
    break;

  case 101:
#line 349 "decafexpr.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(GEQ));}
#line 2285 "decafexpr.tab.c"
    break;

  case 102:
#line 350 "decafexpr.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(EQ));}
#line 2291 "decafexpr.tab.c"
    break;

  case 103:
#line 351 "decafexpr.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(NEQ));}
#line 2297 "decafexpr.tab.c"
    break;

  case 104:
#line 352 "decafexpr.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(AND));}
#line 2303 "decafexpr.tab.c"
    break;

  case 105:
#line 353 "decafexpr.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(OR));}
#line 2309 "decafexpr.tab.c"
    break;

  case 106:
#line 354 "decafexpr.y"
                                      {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(LEQ));}
#line 2315 "decafexpr.tab.c"
    break;

  case 107:
#line 355 "decafexpr.y"
                                                {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(LEFT_SHIFT));}
#line 2321 "decafexpr.tab.c"
    break;

  case 108:
#line 356 "decafexpr.y"
                                                {(yyval.ast) = new Binary_Expr((yyvsp[-2].ast), (yyvsp[0].ast), new Binary_Operator(RIGHT_SHIFT));}
#line 2327 "decafexpr.tab.c"
    break;

  case 109:
#line 359 "decafexpr.y"
                                                   {(yyval.ast) = new Unary_Expr((yyvsp[0].ast), new Unary_Operator(UNARY_MINUS));}
#line 2333 "decafexpr.tab.c"
    break;

  case 110:
#line 360 "decafexpr.y"
                                   {(yyval.ast) = new Unary_Expr((yyvsp[0].ast), new Unary_Operator(NOT));}
#line 2339 "decafexpr.tab.c"
    break;

  case 111:
#line 364 "decafexpr.y"
                         {(yyval.ast) = new Constant_Expr(&((yyvsp[0].sval)), INTTYPE);}
#line 2345 "decafexpr.tab.c"
    break;

  case 112:
#line 365 "decafexpr.y"
                     {(yyval.ast) = new Constant_Expr(&((yyvsp[0].sval)), INTTYPE);}
#line 2351 "decafexpr.tab.c"
    break;

  case 113:
#line 366 "decafexpr.y"
                     {(yyval.ast) = new Constant_Expr(&((yyvsp[0].sval)), BOOLTYPE);}
#line 2357 "decafexpr.tab.c"
    break;

  case 114:
#line 367 "decafexpr.y"
                     {(yyval.ast) = new Constant_Expr(&((yyvsp[0].sval)), BOOLTYPE);}
#line 2363 "decafexpr.tab.c"
    break;

  case 115:
#line 368 "decafexpr.y"
                     {(yyval.ast) = new Constant_Expr();}
#line 2369 "decafexpr.tab.c"
    break;

  case 116:
#line 372 "decafexpr.y"
                       {(yyval.ast) = new Type(VOIDTYPE);}
#line 2375 "decafexpr.tab.c"
    break;

  case 117:
#line 373 "decafexpr.y"
                       {(yyval.ast) = (yyvsp[0].ast);}
#line 2381 "decafexpr.tab.c"
    break;

  case 118:
#line 376 "decafexpr.y"
                              {(yyval.ast) = new Var_Def(new Type(STRINGTYPE));}
#line 2387 "decafexpr.tab.c"
    break;

  case 119:
#line 377 "decafexpr.y"
                              {(yyval.ast) = new Var_Def(dynamic_cast<Type *>((yyvsp[0].ast)));}
#line 2393 "decafexpr.tab.c"
    break;

  case 120:
#line 379 "decafexpr.y"
                       {(yyval.ast) = new Type(BOOLTYPE);}
#line 2399 "decafexpr.tab.c"
    break;

  case 121:
#line 380 "decafexpr.y"
                       {(yyval.ast) = new Type(INTTYPE);}
#line 2405 "decafexpr.tab.c"
    break;

  case 122:
#line 383 "decafexpr.y"
                                     {
    (yyval.id_list) = new string_vector();
    (yyval.id_list)->push_back(*((yyvsp[-2].sval))); 
    (yyval.id_list)->push_back(*((yyvsp[0].sval))); 
    delete (yyvsp[-2].sval); delete (yyvsp[0].sval);
}
#line 2416 "decafexpr.tab.c"
    break;

  case 123:
#line 389 "decafexpr.y"
                                     {
    (yyvsp[-2].id_list)->push_back(*((yyvsp[0].sval))); (yyval.id_list) = (yyvsp[-2].id_list); delete (yyvsp[0].sval);
}
#line 2424 "decafexpr.tab.c"
    break;

  case 124:
#line 394 "decafexpr.y"
                       {(yyval.ast) = new Identifier(&((yyvsp[0].sval)));}
#line 2430 "decafexpr.tab.c"
    break;


#line 2434 "decafexpr.tab.c"

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
#line 396 "decafexpr.y"


int main() {
  // initialize LLVM
  llvm::LLVMContext &Context = TheContext;
  // Make the module, which holds all the code.
  TheModule = new llvm::Module("Test", Context);
  // set up symbol table
  // set up dummy main function
  TheFunction = gen_main_def();
  // parse the input and create the abstract syntax tree
  int retval = yyparse();
  // remove symbol table
  // Finish off the main function. (see the WARNING above)
  // return 0 from main, which is EXIT_SUCCESS
  Builder.CreateRet(llvm::ConstantInt::get(TheContext, llvm::APInt(32, 0)));
  // Validate the generated code, checking for consistency.
  verifyFunction(*TheFunction);
  // Print out all of the generated code to stderr
  TheModule->print(llvm::errs(), nullptr);
  return(retval >= 1 ? EXIT_FAILURE : EXIT_SUCCESS);
}
