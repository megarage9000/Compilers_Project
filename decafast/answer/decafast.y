%{
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

%}

%define parse.error verbose

%union{
    class decafAST *ast;
    std::string *sval;
    std::string np_sval;
 }

%token T_PACKAGE
%token T_LCB
%token T_RCB
// Operations
%token<np_sval> T_AND T_ASSIGN T_DIV T_DOT T_EQ T_GEQ T_GT T_LEFTSHIFT T_RIGHTSHIFT T_LEQ T_LT T_MINUS T_MOD T_MULT T_NEQ T_NOT T_OR T_PLUS 
// Special Characters
%token T_COMMA T_LPAREN T_RPAREN T_LSB T_RSB T_SEMICOLON
// Keywords
%token T_ELSE T_EXTERN T_BREAK T_CONTINUE T_BOOLTYPE T_FOR T_FUNC T_IF T_INTTYPE T_STRINGTYPE T_VAR T_VOID T_WHILE T_RETURN
// Values
%token<sval> T_CHARCONSTANT T_FALSE T_NULL T_STRINGCONSTANT T_TRUE T_INTCONSTANT 
// Types
%token<sval> T_ID

// Misc
%token T_COMMENT T_WHITESPACE

%left T_PLUS T_MINUS
%left T_MULT T_DIV
%left T_LPAREN T_RPAREN
%left UMINUS

// %type <ast> extern_list decafpackage
%type <sval>  constant expression 
%type <np_sval> binary_operator

%%

start: expression

expression: constant                          {$$ = $1;}
    | expression binary_operator expression   {std::cout << "Expression = " << ($1)* << $2 << ($3)* << '\n';}
    | T_LPAREN expression T_RPAREN            {std::cout << "Braced Expression = (" << ($2)* << ")\n";}
    ;

/* Operators */
binary_operator:  T_PLUS {$$ = "+";}
    | T_MINUS   {$$ = "-";}
    | T_MULT    {$$ = "*";}
    | T_DIV     {$$ = "/";}
    | T_GT      {$$ = ">";}
    ;


/* Constants */
constant: T_STRINGCONSTANT  {std::cout << "constant = " << *($1) << '\n'; $$ = $1;}
    | T_CHARCONSTANT {std::cout << "constant =" << *($1) << '\n'; $$ = $1;}
    | T_INTCONSTANT  {std::cout << "constant =" << $1 << '\n'; $$ = $1;}
    | T_MINUS T_INTCONSTANT %prec UMINUS {
                                            std::string unaryConst = '-' + *($2); 
                                            std::cout << "constant =" << unaryConst<< '\n'; 
                                            $$ = new std::string(unaryConst);
                                        }
    ;

%%
    // TODO remember to bring back!
// start: program
// program: extern_list decafpackage
//     { 
//         ProgramAST *prog = new ProgramAST((decafStmtList *)$1, (PackageAST *)$2); 
//         if (printAST) {
//             cout << getString(prog) << endl;
//         }
//         delete prog;
//     }


// /* Externs */
// extern_list: /* extern_list can be empty */
//     { decafStmtList *slist = new decafStmtList(); $$ = slist; }
//     ;

// decafpackage: T_PACKAGE T_ID T_LCB T_RCB
//     { $$ = new PackageAST(*$2, new decafStmtList(), new decafStmtList()); delete $2; }
//     ; 

int main() {
  // parse the input and create the abstract syntax tree
  int retval = yyparse();
  return(retval >= 1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

