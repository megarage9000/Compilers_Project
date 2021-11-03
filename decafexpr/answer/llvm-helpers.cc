#include "default-defs.h"
#include <map>
#include <string>
#include <stack>

/// Symbol table 
typedef std::map<std::string, llvm::Value*> symTable;
typedef std::list<symTable> symTableList;

static symTableList symbl_table_list;

llvm::Value * getValueFromTable(std::string name, symTable tbl) {
  symTable::iterator it;
  if(tbl.empty()) {
	  return nullptr;
  }
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
  if(symbl_table_list.empty()) {
	  return result;
  }
  for(it = symbl_table_list.begin(); it != symbl_table_list.end(); it++) {
    result = getValueFromTable(name, *it);
    if(result != nullptr){
      return result;
    }
  }
  return result;
}

void insertToTable(std::string name, llvm::Value * val) {
  std::pair<std::string, llvm::Value *> tuple (name ,val);
  symbl_table_list.begin()->insert(tuple);
}

void pushTable() {
  symTable newtable;
  symbl_table_list.push_back(newtable);
}

void popTable() {
	if(!symbl_table_list.empty()) {
	  symbl_table_list.pop_back();
	}
}

// this global variable contains all the generated code
static llvm::Module *TheModule;

// this is the method used to construct the LLVM intermediate code (IR)
static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);

typedef enum {
	INTTYPE,
	BOOLTYPE,
	STRINGTYPE,
	VOIDTYPE,
	NULLTYPE
}	val_type;

// Getting types
llvm::Type *getLLVMType(val_type type) {
	switch(type) {
		case VOIDTYPE:
			return Builder.getVoidTy();
		case INTTYPE:
			return Builder.getInt32Ty();
		case BOOLTYPE:
			return Builder.getInt1Ty();
		case STRINGTYPE:
			return Builder.getInt8PtrTy();
		default:
			throw runtime_error("Unknown type!");
	}
}

// -- Getting constants
llvm::Constant *initializeLLVMVal(val_type type, int initialVal) {
	switch(type) {
		case INTTYPE:
			return Builder.getInt32(initialVal);
		case BOOLTYPE:
			return Builder.getInt1(initialVal);
		default:
			throw runtime_error("Invalid type to initialize!");
	}
}

llvm::Constant *initializeLLVMVal(llvm::Type * type, int initialVal) {
	if(type == Builder.getInt32Ty()) {
		return Builder.getInt32(initialVal);
	}
	else if(type == Builder.getInt1Ty()) {
		return Builder.getInt1(initialVal);
	}
	else {
		throw runtime_error("invalid type!");
	}
}

// -- Promoting bools to int32s
llvm::Value * promoteBoolToInt(llvm::Value ** val) {
	if((*val)->getType() == Builder.getInt1Ty()) {
		return Builder.CreateZExt(*val, Builder.getInt32Ty(), "zexttmp");
	}
	return nullptr;
}

// -- Local Variables
llvm::AllocaInst * defineVar(llvm::Type * tp, std::string id) {
	llvm::AllocaInst * allocation = Builder.CreateAlloca(tp, 0, id.c_str());
	insertToTable(id, allocation);
	return allocation;

}
llvm::Value * useVar(std::string id) {
	llvm::Value * val = getValueFromTables(id);
	if(val == nullptr) {
		throw runtime_error("variable " + id + " not found in any table.");
	}
	return Builder.CreateLoad(val, id.c_str());
}

void assignVal(llvm::AllocaInst* lval, llvm::Value * rval) {
	Builder.CreateStore(rval, lval);
}

// -- Blocks
std::stack<llvm::BasicBlock *> blockStack;

void onInsertBlock(llvm::BasicBlock * block) {
	blockStack.push(block);
	Builder.SetInsertPoint(block);
}

void onBlockEnd() {
	if(!blockStack.empty()) {
		blockStack.pop();
		Builder.SetInsertPoint(blockStack.top());
	}
}

const std::string BLOCK_ENTRY_ID = "entry";
llvm::BasicBlock * createBasicBlock(llvm::Function * func) {
	llvm::BasicBlock * basicBlock = llvm::BasicBlock::Create(
		TheContext,
		BLOCK_ENTRY_ID,
		func
	);
	insertToTable(BLOCK_ENTRY_ID, basicBlock);
	return basicBlock;
}

// Non-function blocks
llvm::BasicBlock * createBasicBlockDefault() {
	llvm::BasicBlock * basicBlock = llvm::BasicBlock::Create(
		TheContext,
		BLOCK_ENTRY_ID,
		nullptr
	);
	insertToTable(BLOCK_ENTRY_ID, basicBlock);
	return basicBlock;
}

// -- Method declaration

// From sexpr-codegen.y
// - For functions, we are expecting booleans, integers and chars as types of the argument
static llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction, const std::string &VarName) {
  llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(llvm::IntegerType::get(TheContext, 32), 0, VarName.c_str());
}

void setupFuncArgs(llvm::Function * func, std::vector<std::string> argNames) {
	std::vector<string>::iterator argNameIter = argNames.begin();
	for(auto &arg: func->args()) {
		arg.setName((*argNameIter).c_str());
		llvm::AllocaInst * allocation = CreateEntryBlockAlloca(func, arg.getName().str());
		Builder.CreateStore(&arg, allocation);
		insertToTable(arg.getName().str(), allocation);
		argNameIter++;
	}	
}

llvm::Function * defineFunc(
	llvm::Type * returnTp, 
	std::vector<llvm::Type *> argTypes, 
	std::string funcName,
	std::vector<std::string> argNames) {
	llvm::Function * func = llvm::Function::Create(
		llvm::FunctionType::get(returnTp, argTypes, false),
		llvm::Function::ExternalLinkage,
		funcName,
		TheModule
	);
	insertToTable(funcName, func);
	llvm::BasicBlock * funcBlock = createBasicBlock(func);
	onInsertBlock(funcBlock);
	pushTable();
	setupFuncArgs(func, argNames);
	// Default return statement
	Builder.CreateRet(
		initializeLLVMVal(returnTp, 0)
	);
	return func;
}


// -- Method calls
llvm::Value * getFuncCall(llvm::Function * funcCall, std::vector<llvm::Value *> args) {
	std::string twine = (funcCall->getReturnType()->isVoidTy()) ? "" : "calltmp";
	return Builder.CreateCall(
		funcCall,
		args,
		twine
	);
}	

// Expressions
typedef enum {
	PLUS, MINUS, MULT, DIV, 
	LEFT_SHIFT, RIGHT_SHIFT, 
	MOD,
	LT, GT, LEQ, GEQ, EQ, NEQ,
	AND, OR, NOT,
	UNARY_MINUS
} type_op;

llvm::Value * getBinaryExp(llvm::Value * lval, llvm::Value * rval, type_op operation_tp) {
	switch(operation_tp) {
		case PLUS:
			return Builder.CreateAdd(lval, rval);
		case MINUS:
			return Builder.CreateSub(lval, rval);
		case MULT:
			return Builder.CreateMul(lval, rval);
		case DIV:
			return Builder.CreateSDiv(lval, rval);
		case LEFT_SHIFT:
			return Builder.CreateShl(lval, rval);
		case RIGHT_SHIFT:
			return Builder.CreateLShr(lval, rval);
		case MOD:
			return Builder.CreateSRem(lval, rval);
		case LT:
			return Builder.CreateICmpSLT(lval, rval);
		case GT:
			return Builder.CreateICmpSGT(lval, rval);
		case LEQ:
			return Builder.CreateICmpSLE(lval, rval);
		case GEQ:
			return Builder.CreateICmpSGE(lval, rval);
		case EQ:
			return Builder.CreateICmpEQ(lval, rval);
		case NEQ:
			return Builder.CreateICmpNE(lval, rval);
		case AND:
			return Builder.CreateAnd(lval, rval);
		case OR:
			return Builder.CreateOr(lval, rval);
		default:
			throw runtime_error("Invalid binary operation!");
	}
}

llvm::Value * getUnaryExp(llvm::Value * value, type_op operation_tp) {
	switch(operation_tp) {
		case NOT:
			return Builder.CreateNot(value);
		case UNARY_MINUS:
			return Builder.CreateNeg(value);
		default:
			throw runtime_error("Invalid unary operation");
	}
}