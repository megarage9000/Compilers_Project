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

%}

%define parse.error verbose

%union{
    class decafAST *ast;
    class decafStmtList *list;
    // For a list of identifiers, cache them in to a vector string
    class string_vector *id_list;
    std::string *sval;
    int inval;
    bool bval;
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
%token<sval> T_STRINGCONSTANT 
%token<inval> T_INTCONSTANT T_CHARCONSTANT 
%token<bval>  T_TRUE T_FALSE
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


%type<ast> program decafpackage expression constant identifier extern_func extern_declaration typed_symbol
%type<ast> binary_operation unary_operation assign statement method_call method_arg method_type decaf_type extern_type
%type<ast> typed_symbols field_decl typed_symbols_decl method_decl assign_global
%type<ast> block  if_stmt rvalue for_loop while_loop for_loop_assigns method_decl_args keywords return
%type<ast> statement_group typed_symbols_decl_group field_decl_group method_decl_group extern_arg_group
%type<list> assign_list statement_list method_args method_decl_multi_args typed_symbols_decls extern_func_args method_decl_list extern_list field_decl_list
%type<id_list> identifier_list
%%

start: program {}
|    method_decl_group { pushTable(); $1->Codegen(); delete $1;}
    ;

start_block: T_LCB {
    
}
;
end_block: T_RCB{
    popTable();
    onBlockEnd();
}

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

/* --- Packages --- */
decafpackage: T_PACKAGE identifier start_block field_decl_group method_decl_group end_block
    {   
        string id_name = $2->str();
        $$ = new PackageAST(id_name, dynamic_cast<decafStmtList *>($4), dynamic_cast<decafStmtList *>($5));   
        delete $2;     
    }
    | T_PACKAGE identifier start_block method_decl_group end_block
    {   
        string id_name = $2->str();
        $$ = new PackageAST(id_name, new decafStmtList() , dynamic_cast<decafStmtList *>($4));  
        delete $2;        
    }    
    | T_PACKAGE identifier start_block field_decl_group end_block
    {   
        string id_name = $2->str();
        $$ = new PackageAST(id_name, dynamic_cast<decafStmtList *>($4), new decafStmtList());  
        delete $2;        
    }
    | T_PACKAGE identifier start_block end_block {   
        string id_name = $2->str();
        $$ = new PackageAST(id_name, new decafStmtList(), new decafStmtList());    
        delete $2;     
    }
    ; 


/* --- Externs --- */
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

/* --- While-Loop --- */
while_loop: T_WHILE T_LPAREN expression T_RPAREN block {
    $$ = new While_Loop($3, dynamic_cast<Block *>($5));
}

/* --- For-Loop ---  */
for_loop: T_FOR T_LPAREN for_loop_assigns T_SEMICOLON expression T_SEMICOLON for_loop_assigns T_RPAREN block {
        $$ = new For_Loop($3, $5, $7, dynamic_cast<Block *>($9));
    }

for_loop_assigns: assign {$$ = $1;}
    | assign_list        {$$ = $1;}


assign_list : assign T_COMMA assign {$$ = initialize_recursive_list($1, $3);}
    | assign_list T_COMMA assign {$1->push_back($3); $$ = $1;}
    ;
/* --- If-Else ---  */
if_stmt: T_IF T_LPAREN expression T_RPAREN block {
        $$ = new If_Else($3, dynamic_cast<Block *> ($5));
    }
    | T_IF T_LPAREN expression T_RPAREN block T_ELSE block {
        $$ = new If_Else($3, dynamic_cast<Block *> ($5), dynamic_cast<Block *> ($7));
    }
    
/* --- Blocks --- */
block: start_block typed_symbols_decl_group statement_group end_block               {$$ = new Block($2, $3); } 
    | start_block typed_symbols_decl_group end_block                                {$$ = new Block($2, new decafStmtList()); }
    | start_block statement_group end_block                                         {$$ = new Block(new decafStmtList(), $2); }
    | start_block end_block                                                         {$$ = new Block(new decafStmtList(), new decafStmtList()); }

/* --- Statements ---  */
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

/* --- Keywords ---- */
keywords: T_CONTINUE {$$ = new Continue();}
    | T_BREAK        {$$ = new Break();}
    | return         {$$ = $1;}

return: T_RETURN     {$$ = new Return();}
    | T_RETURN T_LPAREN T_RPAREN    {$$ = new Return();}
    | T_RETURN T_LPAREN expression T_RPAREN    {$$ = new Return($3);}

/* --- Field Declarations --- */
field_decl_group: field_decl_list          {$$ = $1;}
    | field_decl                           {$$ = $1;}

field_decl_list: field_decl field_decl    {$$ = initialize_recursive_list($1, $2);}
    | field_decl_list  field_decl         {$1->push_back($2); $$ = $1;}


field_decl: T_VAR identifier decaf_type T_SEMICOLON {
        Identifier * id = dynamic_cast<Identifier *>($2);
        Type * type = dynamic_cast<Type *>($3);
        $$  = new Field_Decl(id, type, new Field_Size());
    }
    | T_VAR identifier_list decaf_type T_SEMICOLON {
        $$ = vector_to_field_decls($2, dynamic_cast<Type *>($3));
        delete $2; $3;
    }
    | T_VAR identifier T_LSB T_INTCONSTANT T_RSB decaf_type T_SEMICOLON {
        Identifier * id = dynamic_cast<Identifier *>($2);
        Type * type = dynamic_cast<Type *>($6);
        Int_Constant * size = new Int_Constant($4);
        $$  = new Field_Decl(id, type, new Field_Size(size));   
        delete size;
    }
    | T_VAR identifier_list T_LSB T_INTCONSTANT T_RSB decaf_type T_SEMICOLON {
        Type * type = dynamic_cast<Type *>($6);
        Int_Constant * size = new Int_Constant($4);
        Field_Size * field_sz = new Field_Size(size);
        $$ = vector_to_field_decls($2, type, field_sz);
        delete field_sz; delete type; delete size;
    }
    | assign_global         {$$ = $1;}
    ;

assign_global: T_VAR identifier decaf_type T_ASSIGN T_INTCONSTANT T_SEMICOLON {
        $$ = new Assign_Global(dynamic_cast<Identifier *>($2), dynamic_cast<Type *>($3), new Int_Constant($5));
    }
    | T_VAR identifier decaf_type T_ASSIGN T_TRUE T_SEMICOLON {
        $$ = new Assign_Global(dynamic_cast<Identifier *>($2), dynamic_cast<Type *>($3), new Bool_Constant(true));
    }
    | T_VAR identifier decaf_type T_ASSIGN T_FALSE T_SEMICOLON {
        $$ = new Assign_Global(dynamic_cast<Identifier *>($2), dynamic_cast<Type *>($3), new Bool_Constant(false));
    }

/* --- Method declaration --- */
method_decl_group: method_decl_list                  {$$ = $1; }
    | method_decl                                    {$$ = $1; }

method_decl_list: method_decl method_decl            {$$ = initialize_recursive_list ($1, $2);}
    | method_decl_list method_decl                   {$1->push_back($2), $$=$1;}

method_decl: T_FUNC identifier T_LPAREN method_decl_args T_RPAREN method_type block {
        $$ = new Method_Decl(dynamic_cast<Identifier *>($2), dynamic_cast<Type *>($6), dynamic_cast<decafStmtList *>($4), dynamic_cast<Block *>($7));
    }
    | T_FUNC identifier T_LPAREN T_RPAREN method_type block {
        $$ = new Method_Decl(dynamic_cast<Identifier *>($2), dynamic_cast<Type *>($5), new decafStmtList(), dynamic_cast<Block *>($6));
    }

method_decl_args: method_decl_multi_args {$$ = $1;}
    | typed_symbol {
        // Convert to stmtList for ease of use
        decafStmtList * list = new decafStmtList();
        list->push_back($1);
        $$ = list;
    }

method_decl_multi_args:                                     {$$ = new decafStmtList();}
    | typed_symbol T_COMMA typed_symbol                     {$$ = initialize_recursive_list($1, $3);}
    | method_decl_multi_args T_COMMA typed_symbol           {$1->push_back($3); $$=$1;}


/* --- Typed Symbols and Typed Declarations --- */
typed_symbols_decl_group: typed_symbols_decls           {$$ = $1; }
    | typed_symbols_decl                                {$$ = $1; }

typed_symbols_decls: typed_symbols_decl typed_symbols_decl {$$ = initialize_recursive_list($1, $2);}
    | typed_symbols_decls typed_symbols_decl               {$1->push_back($2); $$ = $1; }

typed_symbols_decl: typed_symbols T_SEMICOLON           {$$=$1;}

typed_symbols: T_VAR typed_symbol                       {$$ = $2;}
                                                            
    | T_VAR identifier_list decaf_type                   {
                                                            $$ = vector_to_var_defs($2, dynamic_cast<Type *>($3));
                                                            delete $3; delete $2; 
                                                         }
    ;

typed_symbol: identifier decaf_type                     {$$ = new Var_Def(dynamic_cast<Identifier *>($1), dynamic_cast<Type *>($2)); }

/* --- Methods and Method args --- */
method_call: identifier T_LPAREN T_RPAREN {$$ = new Method_Call(dynamic_cast<Identifier *>($1)); }
        /* Single arg*/
        | identifier T_LPAREN method_arg T_RPAREN     {$$ = new Method_Call(dynamic_cast<Identifier *>($1), $3); }
        /* Mutliple args*/
        | identifier T_LPAREN method_args T_RPAREN    {$$ = new Method_Call(dynamic_cast<Identifier *>($1), $3);}
        ;

method_args: method_arg T_COMMA method_arg     {$$ = initialize_recursive_list($1, $3);}
    | method_args T_COMMA method_arg          {$1->push_back($3); $$ = $1; }
    ;

method_arg: T_STRINGCONSTANT  {$$ = new String_Constant(&($1));}
    | expression              {$$ = $1;}

/* --- Assignments --- */ 
assign: identifier T_ASSIGN expression {$$ = new Assign_Var(dynamic_cast<Identifier *>($1), $3); }
    | identifier T_LSB expression T_RSB T_ASSIGN expression {$$ = new Assign_Arr_Loc(dynamic_cast<Identifier *>($1), $3, $6); }
    ;

/* --- Rvalues --- */
rvalue: identifier  {$$ = new Var_Expr(dynamic_cast<Identifier *>($1));}
    | identifier T_LSB expression T_RSB {$$ = new Arr_Loc_Expr(dynamic_cast<Identifier *>($1), $3);}


/* --- Expressions --- */
expression: constant                          {$$ = $1;}
    | binary_operation                        {$$ = $1;}
    | unary_operation                         {$$ = $1;}
    | T_LPAREN expression T_RPAREN            {$$ = $2;}
    | method_call                             {$$ = $1;}
    | rvalue                                  {$$ = $1;}
    ;

/* --- Operators --- */
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
    | expression T_LEFTSHIFT expression         {$$ = new Binary_Expr($1, $3, new Binary_Operator(LEFT_SHIFT));} 
    | expression T_RIGHTSHIFT expression        {$$ = new Binary_Expr($1, $3, new Binary_Operator(RIGHT_SHIFT));} 
    ;

unary_operation:  T_MINUS expression %prec U_MINUS {$$ = new Unary_Expr($2, new Unary_Operator(UNARY_MINUS));}
    | T_NOT expression %prec U_NOT {$$ = new Unary_Expr($2, new Unary_Operator(NOT));}
    ;

/* --- Constants ---  */
constant: T_CHARCONSTANT {$$ = new Int_Constant($1);}
    | T_INTCONSTANT  {$$ = new Int_Constant($1);}
    | T_FALSE        {$$ = new Bool_Constant(false);}
    | T_TRUE         {$$ = new Bool_Constant(true);}
    | T_NULL         {$$ = new Null_Constant();}
    ;

/* --- Value types --- */
method_type: T_VOID    {$$ = new Type(VOIDTYPE);}
    | decaf_type       {$$ = $1;}
    ;

extern_type: T_STRINGTYPE     {$$ = new Var_Def(new Type(STRINGTYPE));}
    | decaf_type              {$$ = new Var_Def(dynamic_cast<Type *>($1));}

decaf_type: T_BOOLTYPE {$$ = new Type(BOOLTYPE);}
    | T_INTTYPE        {$$ = new Type(INTTYPE);}

/* --- Identifiers --- */
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
  // initialize LLVM
  llvm::LLVMContext &Context = TheContext;
  // Make the module, which holds all the code.
  TheModule = new llvm::Module("Test", Context);
  // set up symbol table
    pushTable();
  // parse the input and create the abstract syntax tree
  int retval = yyparse();
  // remove symbol table
  // Finish off the main function. (see the WARNING above)
  // return 0 from main, which is EXIT_SUCCESS
  Builder.CreateRet(llvm::ConstantInt::get(TheContext, llvm::APInt(32, 0)));
  // Validate the generated code, checking for consistency.
  // verifyFunction(*TheFunction);
  // Print out all of the generated code to stderr
  TheModule->print(llvm::errs(), nullptr);
  popTable();
  return(retval >= 1 ? EXIT_FAILURE : EXIT_SUCCESS);
}
