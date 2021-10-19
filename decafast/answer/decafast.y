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
%left IF
%left IF_ELSE
%left T_OR
%left T_AND
%left T_EQ T_NEQ T_GT T_LT T_GEQ T_LEQ 
%left T_PLUS T_MINUS
%left T_MULT T_DIV T_RIGHTSHIFT T_LEFTSHIFT T_MOD
%left T_LPAREN T_RPAREN
%left U_NOT
%left U_MINUS
/*
%type<ast> unary_operation binary_operation expression statement extern_list decafpackage
%type<ast> assign rvalue method_call field_decl typed_symbols_multi typed_symbol typed_symbol_decl
%type<ast> method_block block if_else if_stmt
%type<list> method_args statement_list typed_symbol_list typed_symbol_list_decl field_decl_list typed_symbol_extern_list assign_list
%type<typed_sym> typed_symbol_sing typed_symbol_extern
%type<constant_type> constant
%type<untyped_list> untyped_symbols
*/

%type<ast> program extern_list decafpackage expression constant value_type identifier
%type<ast> binary_operation unary_operation assign statement method_call method_arg
%type<ast> typed_symbols field_decls typed_symbol
%type<list> assign_list statement_list method_args identifier_list method_decl_args

%%

start: typed_symbols {debugAST($1); delete $1;}
    | typed_symbol   {debugAST($1); delete $1;}
    | method_decl_args  {debugAST($1); delete $1;}
    ;

program: extern_list decafpackage
    { 
        ProgramAST *prog = new ProgramAST((decafStmtList *)$1, (PackageAST *)$2); 
        if (printAST) {
            cout << getString(prog) << endl;
        }
        delete prog;
    }
    ;
/* Externs */
extern_list: /* extern_list can be empty */
    { decafStmtList *slist = new decafStmtList(); $$ = slist; }
    ;

decafpackage: T_PACKAGE T_ID T_LCB T_RCB
    { $$ = new PackageAST(*$2, new decafStmtList(), new decafStmtList()); delete $2; }
    ; 

/* Statements */
statement_list: statement statement     {$$ = initialize_recursive_list($1, $2); }
        | statement_list statement      {$1->push_back($2); $$ = $1; }

statement: assign T_SEMICOLON           {$$ = $1;}
    ;

/* Field Declarations */
field_decls: typed_symbols T_SEMICOLON {
        $$ = new Field_Decl(dynamic_cast<Var_Def *>($1), new Field_Size());
    }
    | typed_symbols T_LSB T_INTCONSTANT T_RSB T_SEMICOLON {
        Constant_Expr * arrSize = new Constant_Expr(&($3), INTTYPE);
        $$ = new Field_Decl(dynamic_cast<Var_Def *>($1), 
                            new Field_Size(&arrSize));
    }
    | typed_symbol T_SEMICOLON {
        $$ = new Field_Decl(dynamic_cast<Var_Def *>($1), new Field_Size());
    }
    | typed_symbol T_LSB T_INTCONSTANT T_RSB T_SEMICOLON {
        Constant_Expr * arrSize = new Constant_Expr(&($3), INTTYPE);
        $$ = new Field_Decl(dynamic_cast<Var_Def *>($1), 
                            new Field_Size(&arrSize));
    }
    ;

/* Method declaration */
method_decl_args: typed_symbol T_COMMA typed_symbol   {$$ = initialize_recursive_list($1, $3);}
    | method_decl_args T_COMMA typed_symbol           {$1->push_back($3);}

/* Typed Symbols */
typed_symbols: T_VAR identifier_list value_type         {$$ = new Var_Def($2, dynamic_cast<Type *>($3));}
    ;
typed_symbol: T_VAR identifier value_type               {$$ = new Var_Def($2, dynamic_cast<Type *>($3));}

identifier_list: identifier T_COMMA identifier          {$$ = initialize_recursive_list($1, $3);}
    | identifier_list T_COMMA identifier                {$1->push_back($3); $$ = $1;}
    ;

/* Methods and Method args*/
method_call: identifier T_LPAREN T_RPAREN {$$ = new Method_Call(dynamic_cast<Identifier *>($1)); }
        /* Single arg*/
        | identifier T_LPAREN expression T_RPAREN     {$$ = new Method_Call(dynamic_cast<Identifier *>($1), $3); }
        /* Mutliple args*/
        | identifier T_LPAREN method_args T_RPAREN    {$$ = new Method_Call(dynamic_cast<Identifier *>($1), $3);}
        ;

method_args: method_arg T_COMMA method_arg     {$$ = initialize_recursive_list($1, $3);}
    | method_args T_COMMA method_arg          {$1->push_back($3); $$ = $1; }
    ;

method_arg: T_STRINGCONSTANT  {$$ = new Constant_Expr(&($1), STRINGTYPE);}
    | expression              {$$ = $1;}

/* Assignments */ 
assign_list : assign T_COMMA assign {$$ = initialize_recursive_list($1, $3);}
    | assign_list T_COMMA assign {$1->push_back($3); $$ = $1;}
    ;

assign: identifier T_ASSIGN expression {$$ = new Assign_Var(dynamic_cast<Identifier *>($1), $3); }
    | identifier T_LSB expression T_RSB T_ASSIGN expression {$$ = new Assign_Arr_Loc(dynamic_cast<Identifier *>($1), $3, $6); }
    ;

/* Expressions */
expression: constant                          {$$ = $1;}
    | binary_operation                        {$$ = $1;}
    | unary_operation                         {$$ = $1;}
    | T_LPAREN expression T_RPAREN            {$$ = $2;}
    | method_call                             {$$ = $1;}
    ;

/* Operators */
binary_operation:  expression T_PLUS expression {$$ = new Binary_Expr($1, $3, new Binary_Operator(PLUS));}
    | expression T_MINUS expression   {$$ = new Binary_Expr($1, $3, new Binary_Operator(MINUS));}
    | expression T_MULT expression    {$$ = new Binary_Expr($1, $3, new Binary_Operator(MULT));}
    | expression T_DIV expression     {$$ = new Binary_Expr($1, $3, new Binary_Operator(DIV));}
    | expression T_MOD expression     {$$ = new Binary_Expr($1, $3, new Binary_Operator(MOD));}
    | expression T_LT expression      {$$ = new Binary_Expr($1, $3, new Binary_Operator(LT));}
    | expression T_GT expression      {$$ = new Binary_Expr($1, $3, new Binary_Operator(GT));}
    | expression T_GEQ expression     {$$ = new Binary_Expr($1, $3, new Binary_Operator(GEQ));}
    | expression T_EQ expression      {$$ = new Binary_Expr($1, $3, new Binary_Operator(EQ));}
    | expression T_NEQ expression     {$$ = new Binary_Expr($1, $3, new Binary_Operator(NEQ));}
    | expression T_AND expression     {$$ = new Binary_Expr($1, $3, new Binary_Operator(AND));}
    | expression T_OR expression      {$$ = new Binary_Expr($1, $3, new Binary_Operator(NOT));}
    ;

unary_operation:  T_MINUS expression %prec U_MINUS {$$ = new Unary_Expr($2, new Unary_Operator(UNARY_MINUS));}
    | T_NOT expression %prec U_NOT {$$ = new Unary_Expr($2, new Unary_Operator(NOT));}
    ;

/* Constants */
constant: T_CHARCONSTANT {$$ = new Constant_Expr(&($1), INTTYPE);}
    | T_INTCONSTANT  {$$ = new Constant_Expr(&($1), INTTYPE);}
    | T_FALSE        {$$ = new Constant_Expr(&($1), BOOLTYPE);}
    | T_TRUE         {$$ = new Constant_Expr(&($1), BOOLTYPE);}
    ;

/* Value types */
value_type: T_BOOLTYPE {$$ = new Type(BOOLTYPE);}
    | T_INTTYPE        {$$ = new Type(INTTYPE);}
    | T_STRINGTYPE     {$$ = new Type(STRINGTYPE);}
    ;

identifier: T_ID       {$$ = new Identifier(&($1));}
    ;
%%
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

