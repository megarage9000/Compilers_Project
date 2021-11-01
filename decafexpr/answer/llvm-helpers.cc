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

void insertToTable(std::string name, llvm::Value * val) {
  std::pair<std::string, llvm::Value *> tuple (name ,val);
  symbl_table_list.begin()->insert(tuple);
}

void pushTable() {
  symTable newtable;
  symbl_table_list.push_back(newtable);
}

void popTable() {
  symbl_table_list.pop_back();
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
	llvm::PointerType * rvalType = rval->getType()->getPointerTo();
	llvm::PointerType * lvalType = lval->getType();
	if(lvalType == rvalType) {
		Builder.CreateStore(rval, lval);
	}
	else {
		throw runtime_error("Invalid assign");
	}
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
	setupFuncArgs(func, argNames);
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