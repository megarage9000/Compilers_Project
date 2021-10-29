%{
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

#include "decafexpr.cc"

using namespace std;

// For AST lists, starts as the base case
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
    // For a list of identifiers, cache them in to a vector string
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
%token<sval> T_CHARCONSTANT T_FALSE T_STRINGCONSTANT T_TRUE T_INTCONSTANT 
// Types
%token<sval> T_ID

%token T_COMMENT T_WHITESPACE T_NULL 

// Precedence
%left T_OR
%left T_AND
%left T_EQ T_NEQ T_GT T_LT T_GEQ T_LEQ 
%left T_PLUS T_MINUS
%left T_MULT T_DIV T_RIGHTSHIFT T_LEFTSHIFT T_MOD
%left T_LPAREN T_RPAREN
%left U_NOT
%left U_MINUS


%%

start: program
    ;

program: extern_declaration decafpackage
    { 

    }
    ;
    | decafpackage
    { 

    }
    ;

/* --- Packages --- */
decafpackage: T_PACKAGE identifier T_LCB field_decl_group method_decl_group T_RCB
    {   
    
    }
    | T_PACKAGE identifier T_LCB method_decl_group T_RCB
    {   
     
    }    
    | T_PACKAGE identifier T_LCB field_decl_group T_RCB
    {   
        
    }
    | T_PACKAGE identifier T_LCB T_RCB {   
  
    }
    ; 


/* --- Externs --- */
extern_declaration: extern_list         {}
    | extern_func                       {}

extern_list: extern_func extern_func   {}
    | extern_list extern_func   {}
    ;

extern_func: T_EXTERN T_FUNC identifier T_LPAREN extern_arg_group T_RPAREN method_type T_SEMICOLON 
    {
        
    }
    | T_EXTERN T_FUNC identifier T_LPAREN T_RPAREN method_type T_SEMICOLON 
    {
        
    }

extern_arg_group: extern_type   {}
    | extern_func_args          {}

extern_func_args: extern_type T_COMMA extern_type   {}
    | extern_func_args T_COMMA extern_type          {}

/* --- While-Loop --- */
while_loop: T_WHILE T_LPAREN expression T_RPAREN block {
    
}

/* --- For-Loop ---  */
for_loop: T_FOR T_LPAREN for_loop_assigns T_SEMICOLON expression T_SEMICOLON for_loop_assigns T_RPAREN block {
        
    }

for_loop_assigns: assign {}
    | assign_list        {}


assign_list : assign T_COMMA assign {}
    | assign_list T_COMMA assign {}
    ;
/* --- If-Else ---  */
if_stmt: T_IF T_LPAREN expression T_RPAREN block {

    }
    | T_IF T_LPAREN expression T_RPAREN block T_ELSE block {

    }
    
/* --- Blocks --- */
block: T_LCB typed_symbols_decl_group statement_group T_RCB               {} 
    | T_LCB typed_symbols_decl_group T_RCB                                {}
    | T_LCB statement_group T_RCB                                         {}
    | T_LCB T_RCB                                                         {}

/* --- Statements ---  */
statement_group: statement_list         {}
    | statement                         {}

statement_list: statement statement     {}
        | statement_list statement      {}

statement: assign T_SEMICOLON           {}
    | method_call T_SEMICOLON           {}
    | keywords  T_SEMICOLON             {}
    | if_stmt                           {}
    | while_loop                        {}
    | for_loop                          {}
    | block                             {}
    ;

/* --- Keywords ---- */
keywords: T_CONTINUE {}
    | T_BREAK        {}
    | return         {}

return: T_RETURN     {}
    | T_RETURN T_LPAREN T_RPAREN    {}
    | T_RETURN T_LPAREN expression T_RPAREN    {}

/* --- Field Declarations --- */
field_decl_group: field_decl_list          {}
    | field_decl                           {}

field_decl_list: field_decl field_decl    {}
    | field_decl_list  field_decl         {}


field_decl: T_VAR identifier decaf_type T_SEMICOLON {

    }
    | T_VAR identifier_list decaf_type T_SEMICOLON {

    }
    | T_VAR identifier T_LSB T_INTCONSTANT T_RSB decaf_type T_SEMICOLON {

    }
    | T_VAR identifier_list T_LSB T_INTCONSTANT T_RSB decaf_type T_SEMICOLON {

    }
    | assign_global         {}
    ;

assign_global: T_VAR identifier decaf_type T_ASSIGN constant T_SEMICOLON {

}

/* --- Method declaration --- */
method_decl_group: method_decl_list                  {}
    | method_decl                                    {}

method_decl_list: method_decl method_decl            {}
    | method_decl_list method_decl                   {}

method_decl: T_FUNC identifier T_LPAREN method_decl_args T_RPAREN method_type block {

    }
    | T_FUNC identifier T_LPAREN T_RPAREN method_type block {

    }

method_decl_args: method_decl_multi_args {}
    | typed_symbol {}

method_decl_multi_args:                                     {}
    | typed_symbol T_COMMA typed_symbol                     {}
    | method_decl_multi_args T_COMMA typed_symbol           {}


/* --- Typed Symbols and Typed Declarations --- */
typed_symbols_decl_group: typed_symbols_decls           {}
    | typed_symbols_decl                                {}

typed_symbols_decls: typed_symbols_decl typed_symbols_decl {}
    | typed_symbols_decls typed_symbols_decl               {}

typed_symbols_decl: typed_symbols T_SEMICOLON           {}

typed_symbols: T_VAR typed_symbol                       {}
                                                            
    | T_VAR identifier_list decaf_type                   {

                                                         }
    ;

typed_symbol: identifier decaf_type                     {}

/* --- Methods and Method args --- */
method_call: identifier T_LPAREN T_RPAREN {}
        /* Single arg*/
        | identifier T_LPAREN method_arg T_RPAREN     {}
        /* Mutliple args*/
        | identifier T_LPAREN method_args T_RPAREN    {}
        ;

method_args: method_arg T_COMMA method_arg     {}
    | method_args T_COMMA method_arg          {}
    ;

method_arg: T_STRINGCONSTANT  {}
    | expression              {}

/* --- Assignments --- */ 
assign: identifier T_ASSIGN expression {}
    | identifier T_LSB expression T_RSB T_ASSIGN expression {}
    ;

/* --- Rvalues --- */
rvalue: identifier  {}
    | identifier T_LSB expression T_RSB {}


/* --- Expressions --- */
expression: constant                          {}
    | binary_operation                        {}
    | unary_operation                         {}
    | T_LPAREN expression T_RPAREN            {}
    | method_call                             {}
    | rvalue                                  {}
    ;

/* --- Operators --- */
binary_operation:  expression T_PLUS expression {}
    | expression T_MINUS expression   {}
    | expression T_MULT expression    {}
    | expression T_DIV expression     {}
    | expression T_MOD expression     {}
    | expression T_LT expression      {}
    | expression T_GT expression      {}
    | expression T_GEQ expression     {}
    | expression T_EQ expression      {}
    | expression T_NEQ expression     {}
    | expression T_AND expression     {}
    | expression T_OR expression      {}
    | expression T_LEQ expression     {}
    | expression T_LEFTSHIFT expression         {} 
    | expression T_RIGHTSHIFT expression        {} 
    ;

unary_operation:  T_MINUS expression %prec U_MINUS {}
    | T_NOT expression %prec U_NOT {}
    ;

/* --- Constants ---  */
constant: T_CHARCONSTANT {}
    | T_INTCONSTANT  {}
    | T_FALSE        {}
    | T_TRUE         {}
    | T_NULL         {}
    ;

/* --- Value types --- */
method_type: T_VOID    {}
    | decaf_type       {}
    ;

extern_type: T_STRINGTYPE     {}
    | decaf_type              {}

decaf_type: T_BOOLTYPE {}
    | T_INTTYPE        {}

/* --- Identifiers --- */
identifier_list: T_ID T_COMMA T_ID   {

    }
    | identifier_list T_COMMA T_ID   {

    }
    ;

identifier: T_ID       {}
    ;
%%

int main() {
  // parse the input and create the abstract syntax tree
  int retval = yyparse();
  yylex_destroy();
  return(retval >= 1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

