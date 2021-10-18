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

decafStmtList * initialize_recursive_list(decafAST * a, decafAST * b) {
    decafStmtList * list = new decafStmtList();
    list->push_front(a); list->push_back(b);
    return list;
}


%}

%define parse.error verbose

%union{
    class decafAST *ast;
    class decafStmtList *list;
    class Typed_Symbol * typed_sym;
    class Constant_Expr * constant_type;
    class Untyped_Symbols * untyped_list;
    std::string *sval;
    
 }

%token T_PACKAGE
%token T_LCB
%token T_RCB
// Operations
%token<sval> T_AND T_ASSIGN T_DIV T_DOT T_EQ T_GEQ T_GT T_LEFTSHIFT T_RIGHTSHIFT T_LEQ T_LT T_MINUS T_MOD T_MULT T_NEQ T_NOT T_OR T_PLUS 
// Special Characters
%token T_COMMA T_LPAREN T_RPAREN T_LSB T_RSB T_SEMICOLON
// Keywords
%token T_ELSE T_EXTERN T_BREAK T_CONTINUE T_BOOLTYPE T_FOR T_FUNC T_IF T_INTTYPE T_STRINGTYPE T_VAR T_VOID T_WHILE T_RETURN
// Values
%token<sval> T_CHARCONSTANT T_FALSE T_NULL T_STRINGCONSTANT T_TRUE T_INTCONSTANT 
// Types
%token<sval> T_ID

%token T_COMMENT T_WHITESPACE

// Precedence
%left VAR_DECL
%left FIELD_DECL
%left T_OR
%left T_AND
%left T_EQ T_NEQ T_GT T_LT T_GEQ T_LEQ 
%left T_PLUS T_MINUS
%left T_MULT T_DIV T_RIGHTSHIFT T_LEFTSHIFT T_MOD
%left T_LPAREN T_RPAREN
%left U_NOT
%left U_MINUS

// %type <ast> extern_list decafpackage
%type<ast> unary_operation binary_operation expression statement 
%type<ast> assign rvalue method_call field_decl typed_symbols_multi typed_symbol
%type<list> method_args statement_list typed_symbol_list field_decl_list
%type<typed_sym> typed_symbol_sing
%type<constant_type> constant
%type<untyped_list> untyped_symbols

%%

start: field_decl T_SEMICOLON
    | field_decl_list 
    ;

statement_list: statement statement     {$$ = initialize_recursive_list($1, $2); debugAST($$);}
        | statement_list statement      {$1->push_back($2); $$ = $1; debugAST($$);}

/* statement */
statement: assign T_SEMICOLON                {$$ = $1; debugAST($$);}
        | method_call T_SEMICOLON            {$$ = $1; debugAST($$);}

/* Field, Variable declarations */
field_decl_list: field_decl T_SEMICOLON field_decl T_SEMICOLON {
        $$ = initialize_recursive_list($1, $3);
        debugAST($$);
    }
    | field_decl_list field_decl T_SEMICOLON {
        $1->push_back($2); $$ = $1;
        debugAST($$);
    }

field_decl: typed_symbol_sing {$$ = new Field_Decl($1, SCALAR); debugAST($$);}
    | typed_symbol_sing T_ASSIGN constant    {$$ = new Assign_Global($1, getString($3)); debugAST($$);}
    | typed_symbol_sing T_LSB constant T_RSB {$$ = new Field_Decl($1, ARRAY, $3->getValue()); debugAST($$);}
    | typed_symbols_multi {$$ = createFieldDeclList(dynamic_cast<decafStmtList *>($1)); debugAST($$);}
    | typed_symbols_multi T_LSB constant T_RSB {$$ = createFieldDeclListArr(dynamic_cast<decafStmtList *>($1), $3->getValue()); debugAST($$);}

typed_symbol_list: typed_symbol T_SEMICOLON typed_symbol T_SEMICOLON {
        $$ = initialize_recursive_list($1, $3);
    }
    |   typed_symbol_list typed_symbol T_SEMICOLON  {
        $1->push_back($2); $$=$1;
    }

typed_symbol: typed_symbols_multi {$$ = $1;}
    |   typed_symbol {$$ = 1;}

typed_symbols_multi: T_VAR untyped_symbols T_BOOLTYPE { $$ = createTypedSymbolList($2, BOOL); debugAST($$);}
    | T_VAR untyped_symbols T_STRINGTYPE { $$ = createTypedSymbolList($2, STRING); debugAST($$);}
    | T_VAR untyped_symbols T_INTTYPE { $$ = createTypedSymbolList($2, INT); debugAST($$);}

typed_symbol_sing: T_VAR T_ID T_BOOLTYPE {$$ = new Typed_Symbol($2, BOOL); debugAST($$);}
    | T_VAR T_ID T_STRINGTYPE {$$ = new Typed_Symbol($2, STRING); debugAST($$); }
    | T_VAR T_ID T_INTTYPE {$$ = new Typed_Symbol($2, INT); debugAST($$);}

untyped_symbols: T_ID T_COMMA T_ID {
        $$ = new Untyped_Symbols();
        $$->push_front(new Untyped_Symbol($1)); 
        $$->push_back(new Untyped_Symbol($3)); 
    }
    | untyped_symbols T_COMMA T_ID          {$1->push_back(new Untyped_Symbol($3)); $$ = $1;}



/* Variable Assignments */
assign: T_ID T_ASSIGN expression {$$ = new Assign_Var($1, $3); debugAST($$);}
    | T_ID T_LSB expression T_RSB T_ASSIGN expression {$$ = new Assign_Arr_Loc($1, $3, $6); debugAST($$);}
    ;

/* Methods and Method args*/
method_call: T_ID T_LPAREN T_RPAREN {$$ = new Method_Call($1); debugAST($$);}
        /* Single arg*/
        | T_ID T_LPAREN expression T_RPAREN     {$$ = new Method_Call($1, $3); debugAST($$);}
        /* Mutliple args*/
        | T_ID T_LPAREN method_args T_RPAREN    {$$ = new Method_Call($1, $3);}

method_args: expression T_COMMA expression     {$$ = initialize_recursive_list($1, $3)}
    | method_args T_COMMA expression           {$1->push_back($3); $$ = $1; }
    ;

/* Expressions */
expression: constant                          {$$ = $1; debugAST($$);}
    | binary_operation                        {$$ = $1; debugAST($$);}
    | unary_operation                         {$$ = $1; debugAST($$);}
    | rvalue                                  {$$ = $1; debugAST($$);}
    | method_call                             {$$ = $1; debugAST($$);}
    | T_LPAREN expression T_RPAREN            {$$ = $2; debugAST($$);}
    ;

/* Operators */
binary_operation:  expression T_PLUS expression {$$ = new Binary_Expr($1, $3, PLUS);}
    | expression T_MINUS expression   {$$ = new Binary_Expr($1, $3, MINUS);}
    | expression T_MULT expression    {$$ = new Binary_Expr($1, $3, MULT);}
    | expression T_DIV expression     {$$ = new Binary_Expr($1, $3, DIV);}
    | expression T_MOD expression     {$$ = new Binary_Expr($1, $3, MOD);}
    | expression T_LT expression      {$$ = new Binary_Expr($1, $3, LT);}
    | expression T_GT expression      {$$ = new Binary_Expr($1, $3, GT);}
    | expression T_GEQ expression     {$$ = new Binary_Expr($1, $3, GEQ);}
    | expression T_EQ expression      {$$ = new Binary_Expr($1, $3, EQ);}
    | expression T_NEQ expression     {$$ = new Binary_Expr($1, $3, NEQ);}
    | expression T_AND expression     {$$ = new Binary_Expr($1, $3, AND);}
    | expression T_OR expression      {$$ = new Binary_Expr($1, $3, NOT);}
    ;

/* R Values */
rvalue: T_ID T_LSB expression T_RSB   {$$ = new Arr_Loc_Expr($1, $3); debugAST($$);} 
    | T_ID                            {$$ = new Var_Expr($1); debugAST($$);}
    ;

unary_operation: T_MINUS expression %prec U_MINUS {$$ = new Unary_Expr($2, UNARY_MINUS);}
    | T_NOT expression %prec U_NOT {$$ = new Unary_Expr($2, NOT);}

/* Constants */
constant: T_STRINGCONSTANT  {$$ = new Constant_Expr($1, STRING);}
    | T_CHARCONSTANT {$$ = new Constant_Expr($1, CHAR);}
    | T_INTCONSTANT  {$$ = new Constant_Expr($1, INT);}
    | T_FALSE        {$$ = new Constant_Expr($1, BOOL);}
    | T_TRUE         {$$ = new Constant_Expr($1, BOOL);}
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

