#include "default-defs.h"
#include <map>
#include <string>

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
  symbl_table_list.push_front(newtable);
}

void popTable() {
  symbl_table_list.pop_front();
}

// this global variable contains all the generated code
static llvm::Module *TheModule;

// this is the method used to construct the LLVM intermediate code (IR)
static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);

typedef enum { voidTp, intTp, boolTp, stringTp } decafType;

// Getting types
llvm::Type *getLLVMType(decafType type) {
	switch(type) {
		case voidTp:
			return Builder.getVoidTy();
		case intTp:
			return Builder.getInt32Ty();
		case boolTp:
			return Builder.getInt1Ty();
		case stringTp:
			return Builder.getInt8PtrTy();
		default:
			throw runtime_error("Unknown type!");
	}
}

// Getting constants
llvm::Constant *initializeLLVMVal(decafType type, int initialVal) {
	switch(type) {
		case intTp:
			return Builder.getInt32(initialVal);
		case boolTp:
			return Builder.getInt1(initialVal);
		default:
			throw runtime_error("Invalid type to initialize!");
	}
}

// Local Variables
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

// Functions

llvm::Function * defineFunc(
	llvm::Type * returnTp, 
	std::vector<llvm::Type *> argTypes, 
	std::string funcName) {
	llvm::Function * func = llvm::Function::Create(
		llvm::FunctionType::get(returnTp, argTypes, false),
		llvm::Function::ExternalLinkage,
		funcName,
		TheModule
	);
	insertToTable(funcName, func);
	return func;
}

llvm::BasicBlock * createBasicBlock(llvm::Function * func, std::string funcName) {
	std::string blockID = funcName + "entry";
	llvm::BasicBlock * basicBlock = llvm::BasicBlock::Create(
		TheContext,
		blockID,
		func
	);
	insertToTable(blockID, basicBlock);
	return basicBlock;
}



