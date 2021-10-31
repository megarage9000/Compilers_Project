%{ 
#include "exprdefs.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include <cstdio> 
#include <stdexcept>
#include <iostream>
#include <map>
#include <list>
#include <iterator>
#include <vector>

using namespace llvm;


/// Symbol table 
// TODO 
// -make the symbol table
// -add some llvm helpers
// -test symbol table
typedef std::map<std::string, llvm::Value*> symTable;
typedef std::list<symTable> symTableList;

static symTableList symbl_table_list;

llvm::Value * getValueFromTable(std::string name, symTable tbl) {
  symTable::iterator it;
  for(it = tbl.begin(); it != tbl.end(); it++){
    if(it->first == name) {
      return it->second;
    }
  }
  return nullptr;
}

llvm::Value * getValueFromTables(std::string name) {
  symTableList::iterator it;
  llvm::Value * result = nullptr;
  for(it = symbl_table_list.begin(); it != symbl_table_list.end(); it++) {
    result = getValueFromTable(name, *it);
    if(result != nullptr){
      return result;
    }
  }
  return result;
}

void insertToTable(std::string name, Value * val) {
  std::pair<std::string, Value *> tuple (name ,val);
  symbl_table_list.begin()->insert(tuple);
}

void pushTable() {
  symTable newtable;
  symbl_table_list.push_front(newtable);
}

void popTable() {
  symbl_table_list.pop_front();
}


// this global variable contains all the generated code
static Module *TheModule;

// this is the method used to construct the LLVM intermediate code (IR)
static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
// the calls to TheContext in the init above and in the
// following code ensures that we are incrementally generating
// instructions in the right order

static Function *TheFunction = 0;

/// ExprAST - Base class for all expression nodes.
class ExprAST {
public:
  virtual ~ExprAST() {}
  virtual Value *Codegen() = 0;
};

class NameExprAST: public ExprAST {
  std::string Name;
public:
  NameExprAST(std::string id) : Name(id) {}
  virtual Value *Codegen();
};

/// NumberExprAST - Expression class for integer numeric literals like "12".
class NumberExprAST : public ExprAST {
  int Val;
public:
  NumberExprAST(int val) : Val(val) {}
  virtual Value *Codegen();
};

/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
  char Op;
  ExprAST *LHS, *RHS;
public:
  BinaryExprAST(char op, ExprAST *lhs, ExprAST *rhs) 
    : Op(op), LHS(lhs), RHS(rhs) {}
  virtual Value *Codegen();
  ~BinaryExprAST() {
    delete LHS;
    delete RHS;
  }
};

// we also have to create a main function that contains
// all the code generated for the expression and the print_int call
Function *gen_main_def() {
  // create the top-level definition for main
  FunctionType *FT = FunctionType::get(IntegerType::get(TheContext, 32), false);
  Function *TheFunction = Function::Create(FT, Function::ExternalLinkage, "main", TheModule);
  if (TheFunction == 0) {
    throw runtime_error("empty function block"); 
  }
  // Create a new basic block which contains a sequence of LLVM instructions
  BasicBlock *BB = BasicBlock::Create(TheContext, "entry", TheFunction);
  // All subsequent calls to IRBuilder will place instructions in this location
  Builder.SetInsertPoint(BB);
  return TheFunction;
}

// CreateEntryBlockAlloca - Create an alloca instruction in the entry block of
/// the function.  This is used for mutable variables etc.
static AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, const std::string &VarName) {
  IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(IntegerType::get(TheContext, 32), 0, VarName.c_str());
}

%}

%union{
  class ExprAST *ast;
  int number;
  std::string * name;
}

%token <name> NAME
%token <number> NUMBER
%type <ast> expression

%%

statement_list: statement ';' statement_list
              | /* empty */
              ;

statement: NAME '=' expression
      {
        Value * rval = $3->Codegen();
        AllocaInst * alloca = (AllocaInst*)getValueFromTables(*$1);
        if(alloca == nullptr) {
          alloca = Builder.CreateAlloca(Builder.getInt32Ty(), 0, $1->c_str());
          insertToTable(*$1, alloca);
        }
        Builder.CreateStore(rval, alloca);
        delete($1);
        delete($3);
      }
      | NAME '(' expression ')'
      {
        Value * retVal = $3->Codegen();
        Function * CalleeF = (Function *)getValueFromTables(*$1);
        if(CalleeF == nullptr) {
          std::vector<Type *> args;
          args.push_back(Builder.getInt32Ty());
          Function * func = Function::Create(
            FunctionType::get(Builder.getInt32Ty(), args, false),
            Function::ExternalLinkage,
            *$1,
            TheModule
          );
          CalleeF = TheModule->getFunction(func->getName());
          insertToTable(*$1, CalleeF);
        }
        if(CalleeF == 0) {
          throw runtime_error("can't find function");
        }
        Value * CallF = Builder.CreateCall( 
          CalleeF,
          retVal,
          "calltmp"
        );
        delete($1);
        delete($3);
      }
      ;

expression: expression '+' NUMBER 
            { 
	      $$ = new BinaryExprAST('+', $1, new NumberExprAST($3));
	    }
          | expression '-' NUMBER 
            { 
	      $$ = new BinaryExprAST('-', $1, new NumberExprAST($3)); 
	    }
      | expression '-' NAME
          { 
      $$ = new BinaryExprAST('-', $1, new NameExprAST(*$3)); 
      delete $3;
      }
      | expression '+' NAME
          { 
      $$ = new BinaryExprAST('+', $1, new NameExprAST(*$3)); 
      delete $3;
      }
        | NUMBER 
      { 
      $$ = new NumberExprAST($1); 
      }
        | NAME  
      {
      $$ = new NameExprAST(*$1);
      delete $1;
      }
      ;
%%

Value *NameExprAST::Codegen() {
  Value * alloca = getValueFromTables(Name);
  if(alloca == 0) {
    throw runtime_error("Unrecognized variable: " + Name);
  }
  return Builder.CreateLoad(alloca, Name.c_str());

}

Value *NumberExprAST::Codegen() {
  return ConstantInt::get(TheContext, APInt(32, Val));
}

Value *BinaryExprAST::Codegen() {
  Value *L = LHS->Codegen();
  Value *R = RHS->Codegen();
  if (L == 0 || R == 0) return 0;
  
  switch (Op) {
  case '+': return Builder.CreateAdd(L, R, "addtmp");
  case '-': return Builder.CreateSub(L, R, "subtmp");
  default: throw runtime_error("what operator is this? never heard of it.");
  }
}

int main() {

  LLVMContext &Context = TheContext;
  // Make the module, which holds all the code.
  TheModule = new Module("module for very simple expressions", Context);

  TheFunction = gen_main_def();
  pushTable();
  // parse the input and create the abstract syntax tree
  int retval = yyparse();
  popTable();
  // Print out all of the generated code to stdout
  Builder.CreateRet(ConstantInt::get(TheContext, APInt(32, 0)));
  // Validate the generated code, checking for consistency.
  verifyFunction(*TheFunction);
  // Print out all of the generated code to stderr
  TheModule->print(errs(), nullptr);
  return(retval >= 1 ? 1 : 0);
}
