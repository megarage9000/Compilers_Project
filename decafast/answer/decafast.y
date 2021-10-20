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
    class string_vector *id_list;
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
%type<ast>  block if_else if_stmt
%type<list> method_args statement_list typed_symbol_list typed_symbol_list_decl field_decl_list typed_symbol_extern_list assign_list
%type<typed_sym> typed_symbol_sing typed_symbol_extern
%type<constant_type> constant
%type<untyped_list> untyped_symbols
*/

%type<ast> program decafpackage expression constant identifier extern_func extern_declaration
%type<ast> binary_operation unary_operation assign statement method_call method_arg method_type decaf_type extern_type
%type<ast> typed_symbols field_decl method_decl_sing_arg typed_symbols_decl method_decl assign_global
%type<ast> block  if_stmt rvalue for_loop while_loop for_loop_assigns method_decl_args keywords return
%type<ast> statement_group typed_symbols_decl_group field_decl_group method_decl_group extern_arg_group
%type<list> assign_list statement_list method_args method_decl_multi_args typed_symbols_decls extern_func_args method_decl_list extern_list field_decl_list
%type<id_list> identifier_list
%%

start: program
    ;

program: extern_declaration decafpackage
    { 
        ProgramAST *prog = new ProgramAST((decafStmtList *)$1, (PackageAST *)$2); 
        if (printAST) {
            cout << getString(prog) << endl;
        }
        delete prog;
    }
    ;
    | decafpackage
    { 
        ProgramAST *prog = new ProgramAST(new decafStmtList(), (PackageAST *)$1); 
        if (printAST) {
            cout << getString(prog) << endl;
        }
        delete prog;
    }
    ;

decafpackage: T_PACKAGE identifier T_LCB field_decl_group method_decl_group T_RCB
    {   
        string id_name = $2->str();
        $$ = new PackageAST(id_name, dynamic_cast<decafStmtList *>($4), dynamic_cast<decafStmtList *>($5));   
        delete $2;     
    }
    | T_PACKAGE identifier T_LCB method_decl_group T_RCB
    {   
        string id_name = $2->str();
        $$ = new PackageAST(id_name, new decafStmtList() , dynamic_cast<decafStmtList *>($4));  
        delete $2;        
    }
    | T_PACKAGE identifier T_LCB T_RCB {   
        string id_name = $2->str();
        $$ = new PackageAST(id_name, new decafStmtList(), new decafStmtList());    
        delete $2;     
    }
    ; 

/* Keywords */
keywords: T_CONTINUE {$$ = new Continue();}
    | T_BREAK        {$$ = new Break();}
    | return         {$$ = $1;}

return: T_RETURN     {$$ = new Return();}
    | T_RETURN T_LPAREN T_RPAREN    {$$ = new Return();}
    | T_RETURN T_LPAREN expression T_RPAREN    {$$ = new Return($3);}

/* Externs */
extern_declaration: extern_list         {$$ = $1;}
    | extern_func                       {$$ = $1;}

extern_list: extern_func extern_func   {$$ = initialize_recursive_list($1, $2);}
    | extern_list extern_func   {$1->push_back($2); $$ = $1;}
    ;

extern_func: T_EXTERN T_FUNC identifier T_LPAREN extern_arg_group T_RPAREN method_type T_SEMICOLON {
        $$ = new Extern_Func(dynamic_cast<Identifier *>($3), dynamic_cast<Type *>($7), $5);
    }
    | T_EXTERN T_FUNC identifier T_LPAREN T_RPAREN method_type T_SEMICOLON {
        $$ = new Extern_Func(dynamic_cast<Identifier *>($3), dynamic_cast<Type *>($6), new decafStmtList());
    }

extern_arg_group: extern_type   {$$ = $1;}
    | extern_func_args          {$$ = $1;}

extern_func_args: extern_type T_COMMA extern_type   {$$ = initialize_recursive_list($1, $3);}
    | extern_func_args T_COMMA extern_type          {$1->push_back($3); $$ = $1;}



/* While-Loop */
while_loop: T_WHILE T_LPAREN expression T_RPAREN block {
    $$ = new While_Loop($3, dynamic_cast<Block *>($5));
}

/* For-Loop */
for_loop: T_FOR T_LPAREN for_loop_assigns T_SEMICOLON expression T_SEMICOLON for_loop_assigns T_RPAREN block {
        $$ = new For_Loop($3, $5, $7, dynamic_cast<Block *>($9));
    }

for_loop_assigns: assign {$$ = $1;}
    | assign_list        {$$ = $1;}

/* If-Else */
if_stmt: T_IF T_LPAREN expression T_RPAREN block {
        $$ = new If_Else($3, dynamic_cast<Block *> ($5));
    }
    | T_IF T_LPAREN expression T_RPAREN block T_ELSE block {
        $$ = new If_Else($3, dynamic_cast<Block *> ($5), dynamic_cast<Block *> ($7));
    }
    
/* Blocks */
block: T_LCB typed_symbols_decl_group statement_group T_RCB               {$$ = new Block($2, $3); } 
    | T_LCB typed_symbols_decl_group T_RCB                                {$$ = new Block($2, new decafStmtList()); }
    | T_LCB statement_group T_RCB                                         {$$ = new Block(new decafStmtList(), $2); }
    | T_LCB T_RCB                                                         {$$ = new Block(new decafStmtList(), new decafStmtList()); }

/* Statements */
statement_group: statement_list         {$$ = $1;}
    | statement                         {$$ = $1;}

statement_list: statement statement     {$$ = initialize_recursive_list($1, $2); }
        | statement_list statement      {$1->push_back($2); $$ = $1; }

statement: assign T_SEMICOLON           {$$ = $1;}
    | method_call T_SEMICOLON           {$$ = $1;}
    | keywords  T_SEMICOLON             {$$ = $1;}
    | if_stmt                           {$$ = $1;}
    | while_loop                        {$$ = $1;}
    | for_loop                          {$$ = $1;}
    | block                             {$$ = $1;}
    ;

/* Field Declarations */

field_decl_group: field_decl_list          {$$ = $1;}
    | field_decl                           {$$ = $1;}

field_decl_list: field_decl field_decl   {$$ = initialize_recursive_list($1, $2);}
    | field_decl_list  field_decl         {$1->push_back($2); $$ = $1;}


field_decl: T_VAR identifier decaf_type T_SEMICOLON {
        Identifier * id = dynamic_cast<Identifier *>($2);
        Type * type = dynamic_cast<Type *>($3);
        $$  = new Field_Decl(id, type, new Field_Size());
    }
    | T_VAR identifier_list decaf_type T_SEMICOLON {
        $$ = vector_to_field_decls($2, dynamic_cast<Type *>($3));
        delete $2; delete $3;
    }
    | T_VAR identifier T_LSB T_INTCONSTANT T_RSB decaf_type T_SEMICOLON {
        Identifier * id = dynamic_cast<Identifier *>($2);
        Type * type = dynamic_cast<Type *>($6);
        Constant_Expr * const_expr = new Constant_Expr(&($4), INTTYPE);
        $$  = new Field_Decl(id, type, new Field_Size(&const_expr));   
    }
    | T_VAR identifier_list T_LSB T_INTCONSTANT T_RSB decaf_type T_SEMICOLON {
        Type * type = dynamic_cast<Type *>($6);
        Constant_Expr * size = new Constant_Expr(&($4), INTTYPE);
        Field_Size * field_sz = new Field_Size(&size);
        $$ = vector_to_field_decls($2, type, field_sz);
        delete field_sz; delete type;
    }
    | assign_global         {$$ = $1;}
    ;

assign_global: T_VAR identifier decaf_type T_ASSIGN constant T_SEMICOLON {
    $$ = new Assign_Global(dynamic_cast<Identifier *>($2), dynamic_cast<Type *>($3), dynamic_cast<Constant_Expr *>($5));
}

/* Method declaration */
method_decl_group: method_decl_list                  {$$ = $1; }
    | method_decl                                    {$$ = $1; }

method_decl_list: method_decl method_decl            {$$ = initialize_recursive_list ($1, $2);}
    | method_decl_list method_decl                   {$1->push_back($2), $$=$1;}

method_decl: T_FUNC identifier T_LPAREN method_decl_args T_RPAREN method_type block {
        $$ = new Method_Decl(dynamic_cast<Identifier *>($2), dynamic_cast<Type *>($6), $4, dynamic_cast<Block *>($7));
    }
    | T_FUNC identifier T_LPAREN T_RPAREN method_type block {
        $$ = new Method_Decl(dynamic_cast<Identifier *>($2), dynamic_cast<Type *>($5), new decafStmtList(), dynamic_cast<Block *>($6));
    }

method_decl_args: method_decl_multi_args {$$ = $1;}
    | method_decl_sing_arg {$$ = $1;}

method_decl_multi_args:                                     {$$ = new decafStmtList();}
    | method_decl_sing_arg T_COMMA method_decl_sing_arg     {$$ = initialize_recursive_list($1, $3);}
    | method_decl_multi_args T_COMMA method_decl_sing_arg        {$1->push_back($3); $$=$1;}

method_decl_sing_arg: identifier decaf_type             {$$ = new Var_Def($1, dynamic_cast<Type *>($2)); }

/* Typed Symbols and Typed Declarations */
typed_symbols_decl_group: typed_symbols_decls           {$$ = $1; }
    | typed_symbols_decl                                {$$ = $1; }

typed_symbols_decls: typed_symbols_decl typed_symbols_decl {$$ = initialize_recursive_list($1, $2);}
    | typed_symbols_decls typed_symbols_decl               {$1->push_back($2); $$ = $1; }

typed_symbols_decl: typed_symbols T_SEMICOLON           {$$=$1;}

typed_symbols: T_VAR identifier decaf_type               {$$ = new Var_Def($2, dynamic_cast<Type *>($3));
                                                            
                                                        }
    | T_VAR identifier_list decaf_type                   {
                                                            $$ = vector_to_var_defs($2, dynamic_cast<Type *>($3));
                                                            delete $3; delete $2; 
                                                         }
    ;

/* Methods and Method args*/
method_call: identifier T_LPAREN T_RPAREN {$$ = new Method_Call(dynamic_cast<Identifier *>($1)); }
        /* Single arg*/
        | identifier T_LPAREN method_arg T_RPAREN     {$$ = new Method_Call(dynamic_cast<Identifier *>($1), $3); }
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

/* Rvalues */
rvalue: identifier  {$$ = new Var_Expr(dynamic_cast<Identifier *>($1));}
    | identifier T_LSB expression T_RSB {$$ = new Arr_Loc_Expr(dynamic_cast<Identifier *>($1), $3);}


/* Expressions */
expression: constant                          {$$ = $1;}
    | binary_operation                        {$$ = $1;}
    | unary_operation                         {$$ = $1;}
    | T_LPAREN expression T_RPAREN            {$$ = $2;}
    | method_call                             {$$ = $1;}
    | rvalue                                  {$$ = $1;}
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
    | expression T_OR expression      {$$ = new Binary_Expr($1, $3, new Binary_Operator(OR));}
    | expression T_LEQ expression     {$$ = new Binary_Expr($1, $3, new Binary_Operator(LEQ));}
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
method_type: T_VOID    {$$ = new Type(VOIDTYPE);}
    | decaf_type       {$$ = $1;}
    ;

extern_type: T_STRINGTYPE     {$$ = new Var_Def(new Type(STRINGTYPE));}
    | decaf_type              {$$ = new Var_Def(dynamic_cast<Type *>($1));}

decaf_type: T_BOOLTYPE {$$ = new Type(BOOLTYPE);}
    | T_INTTYPE        {$$ = new Type(INTTYPE);}

/* Identifiers */
identifier_list: T_ID T_COMMA T_ID   {
    $$ = new string_vector();
    $$->push_back(*($1)); 
    $$->push_back(*($3)); 
    delete $1; delete $3;
}
    | identifier_list T_COMMA T_ID   {
    $1->push_back(*($3)); $$ = $1; delete $3;
}
    ;

identifier: T_ID       {$$ = new Identifier(&($1));}
    ;
%%

int main() {
  // parse the input and create the abstract syntax tree
  int retval = yyparse();
  return(retval >= 1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

