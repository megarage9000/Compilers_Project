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
  std::cout << "-------------------------------------\n";
  for(it = tbl.begin(); it != tbl.end(); it++){
	  std::cout << "symbl table list entry = " << it->first << '\n';
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

llvm::Value * getValueFromTopTable(std::string name) {
	return getValueFromTable(name, *(symbl_table_list.begin()));
}

llvm::Value * getValueFromSecondTopTable(std::string name) {
	return getValueFromTable(name, *(++symbl_table_list.begin()));
}

void insertToTable(std::string name, llvm::Value * val) {
  std::pair<std::string, llvm::Value *> tuple (name ,val);
  symbl_table_list.begin()->insert(tuple);
}

void pushTable() {
  symTable newtable;
 std::cout << "symbol table list size before push: " << symbl_table_list.size() << '\n';	
  symbl_table_list.push_front(newtable);

}

void popTable() {
	if(!symbl_table_list.empty()) {
		std::cout << "symbol table list size before pop: " << symbl_table_list.size() << '\n';	
		symbl_table_list.pop_front();
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

// -- Checking specific types (decaf, method, externs)
bool isDecafType(llvm::Type * type) {
	return (type == Builder.getInt32Ty() || type == Builder.getInt1Ty());
}

bool isMethodType(llvm::Type * type) {
	return (type == Builder.getVoidTy() || isDecafType(type));
}

bool isExternType(llvm::Type * type) {
	return (type == Builder.getInt8PtrTy() || isDecafType(type));
}

llvm::Type * getMainType() {
	return llvm::FunctionType::get(llvm::IntegerType::get(TheContext, 32), false);
}

bool isMainReturnType(llvm::Type * type) {
	return (type == getMainType());
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

llvm::Value * getStringConst(std::string sval) {
	llvm::GlobalVariable * globalString = Builder.CreateGlobalString(sval.c_str(), "globalstring");
	return Builder.CreateConstGEP2_32(globalString->getValueType(), globalString, 0, 0, "cast");
}

// -- Promoting bools to int32s
llvm::Value * promoteBoolToInt(llvm::Value ** val) {
	if((*val)->getType() == Builder.getInt1Ty()) {
		return Builder.CreateZExt(*val, Builder.getInt32Ty(), "zexttmp");
	}
	return nullptr;
}

// -- Assignments
void assignVal(llvm::AllocaInst* lval, llvm::Value * rval) {
	const llvm::PointerType * rvalType = rval->getType()->getPointerTo();
	const llvm::PointerType * lvalType = lval->getType();
	if(rvalType == lvalType) {
		Builder.CreateStore(rval, lval);
	}
}


// -- Local Variables
llvm::AllocaInst * defineVar(llvm::Type * tp, std::string id) {
	llvm::AllocaInst * allocation = Builder.CreateAlloca(tp, 0, id.c_str());
	insertToTable(std::string(id), allocation);
	// Zero initialization
	if(tp == Builder.getInt1Ty()) {
		assignVal(allocation, initializeLLVMVal(tp, 1));
	}
	else {
		assignVal(allocation, initializeLLVMVal(tp, 0));
	}
	return allocation;

}
llvm::Value * useVar(std::string id) {
	llvm::Value * val = getValueFromTables(id);
	if(val == nullptr) {
		throw runtime_error("variable " + id + " not found in any table.");
	}
	return Builder.CreateLoad(val, id.c_str());
}

llvm::Value * useArrLoc(std::string id, llvm::Value * index) {
	llvm::GlobalVariable * val = (llvm::GlobalVariable *)getValueFromTables(id);
	if(val == nullptr) {
		throw runtime_error("variable " + id + " not found in any table.");
	}

	llvm::ArrayType * arrayTp = (llvm::ArrayType *)val->getValueType();
	llvm::Value * arrayLoc = Builder.CreateStructGEP(arrayTp, val, 0, "arrayloc");
	llvm::Value * arrayIndex = Builder.CreateGEP(arrayTp->getElementType(), arrayLoc, index, "arrayIndex");
	return arrayIndex;
}

// -- Global Variables
llvm::GlobalVariable * declareGlobalWithValue(std::string id, llvm::Type * tp, llvm::Constant* val) {
	if(isDecafType(tp)) {
		llvm::GlobalVariable * globalVar = new llvm::GlobalVariable(
			*TheModule,
			tp,
			false,
			llvm::GlobalVariable::InternalLinkage,
			val,
			id
		);
		insertToTable(id, globalVar);
		return globalVar;
	}
	else{
		return nullptr;
	}
}

llvm::GlobalVariable * declareGlobal(std::string id, llvm::Type * tp) {
	llvm::Constant * zeroInit;
	// Zero initialization
	if(tp == Builder.getInt1Ty()) {
		zeroInit = initializeLLVMVal(tp, 1);
	}
	else if(tp == Builder.getInt32Ty()) {
		zeroInit = initializeLLVMVal(tp, 0);
	}
	else{
		return nullptr;
	}
	return declareGlobalWithValue(id, tp, zeroInit);
}

llvm::GlobalVariable * declareGlobalArr(std::string id, llvm::Type * tp, int size) {
	if(isDecafType(tp)) {
		llvm::ArrayType * array = llvm::ArrayType::get(tp, size);
		llvm::Constant * zeroInit = llvm::Constant::getNullValue(array);
		llvm::GlobalVariable * globalVar = new llvm::GlobalVariable(
			*TheModule,
			array,
			false,
			llvm::GlobalVariable::ExternalLinkage,
			zeroInit,
			id
		);
		insertToTable(id, globalVar);
		return globalVar;
	}
	else{
		return nullptr;
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

// For blocks with custom entries
llvm::BasicBlock * createBasicBlockWithLabel(llvm::Function * func, std::string label) {
	llvm::BasicBlock * basicBlock = llvm::BasicBlock::Create(
		TheContext,
		label,
		func
	);
	insertToTable(label, basicBlock);
	return basicBlock;
}

// -- Method declaration

// From sexpr-codegen.y
// - For functions, we are expecting booleans, integers and chars as types of the argument
static llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *TheFunction, llvm::Type * type, const std::string &VarName) {
  llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(type, 0, VarName.c_str());
}

void setupFuncArgs(llvm::Function * func, std::vector<std::string> argNames) {
	std::vector<string>::iterator argNameIter = argNames.begin();
	for(auto &arg: func->args()) {
		arg.setName((*argNameIter).c_str());
		llvm::AllocaInst * allocation = CreateEntryBlockAlloca(func, arg.getType(), arg.getName().str());
		Builder.CreateStore(&arg, allocation);
		insertToTable(arg.getName().str(), allocation);
		argNameIter++;
	}	
}
llvm::Function * defineFunc(
	llvm::Type * returnTp, 
	std::vector<llvm::Type *> argTypes, 
	std::string funcName) 
{
	llvm::Function * func = llvm::Function::Create(
		llvm::FunctionType::get(returnTp, argTypes, false),
		llvm::Function::ExternalLinkage,
		funcName,
		TheModule
	);
	insertToTable(funcName, func);
	return func;
}

llvm::Function * defineMethod(
	llvm::Type * returnTp, 
	std::vector<llvm::Type *> argTypes, 
	std::string funcName) 
{
	// Check if return type is valid
	if(!isMethodType(returnTp) && !isMainReturnType(returnTp)) {
		throw runtime_error("Invalid return type for method");
	}
	// Validate arguments to make sure they are correct type
	for(llvm::Type * argType : argTypes) {
		if(!isDecafType(argType)){
			throw runtime_error("Invalid arg type for method");
		}
	}
	// One it passes the tests, define function
	return defineFunc(returnTp, argTypes, funcName);
}

llvm::Function * defineExtern(
	llvm::Type * returnTp, 
	std::vector<llvm::Type *> argTypes, 
	std::string funcName) 
{
	// Check if return type is valid
	if(!isMethodType(returnTp)) {
		throw runtime_error("Invalid return type for extern");
	}
	// Validate arguments to make sure they are correct type
	for(llvm::Type * argType : argTypes) {
		if(!isExternType(argType)){
			throw runtime_error("Invalid arg type for extern");
		}
	}
	// One it passes the tests, define function
	return defineFunc(returnTp, argTypes, funcName);
}



void setupFunc(llvm::Function * func, std::vector<std::string> argNames) {
	llvm::BasicBlock * funcBlock = createBasicBlock(func);
	Builder.SetInsertPoint(funcBlock);
	setupFuncArgs(func, argNames);
}

// helper to check if the function block(s) are valid
// Stackoverflow link: https://stackoverflow.com/questions/53632131/compiler-how-to-check-a-user-function-returns-properly
void checkFxn(llvm::Function * func) {
	for(llvm::BasicBlock &block : *func) {
		llvm::Instruction * terminator = block.getTerminator();
		if(terminator != nullptr) continue;
		if(func->getReturnType()->isVoidTy()) {
			Builder.SetInsertPoint(&block);
			Builder.CreateRetVoid();
		}
		else if(isMethodType(func->getReturnType())) {
			Builder.SetInsertPoint(&block);
			llvm::Type * returnTp = func->getReturnType();
			if(returnTp == Builder.getInt32Ty()) {
				Builder.CreateRet(initializeLLVMVal(returnTp, 0));
			}
			else {
				Builder.CreateRet(initializeLLVMVal(returnTp, 1));
			}
		}
	}
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
	// TODO: handle correct types (int32s for arithmetic, int1s for booleans)
	// - Currently we are gonna check if lval and rval are either int1s or int32s
	llvm::Type * lvalType = lval->getType();
	llvm::Type * rvalType = rval->getType();

	if(lvalType == Builder.getInt32Ty() && rvalType == Builder.getInt32Ty()) {
		switch(operation_tp) {
			case PLUS:
				return Builder.CreateAdd(lval, rval, "addtmp");
			case MINUS:
				return Builder.CreateSub(lval, rval, "minustmp");
			case MULT:
				return Builder.CreateMul(lval, rval, "multmp");
			case DIV:
				return Builder.CreateSDiv(lval, rval, "divtmp");
			case LEFT_SHIFT:
				return Builder.CreateShl(lval, rval, "l_shifttmp");
			case RIGHT_SHIFT:
				return Builder.CreateLShr(lval, rval, "r_shifttmp");
			case MOD:
				return Builder.CreateSRem(lval, rval, "modtmp");
			case LT:
				return Builder.CreateICmpSLT(lval, rval, "lttmp");
			case GT:
				return Builder.CreateICmpSGT(lval, rval, "gttmp");
			case LEQ:
				return Builder.CreateICmpSLE(lval, rval, "leqtmp");
			case GEQ:
				return Builder.CreateICmpSGE(lval, rval, "geqtmp");
			case EQ:
				return Builder.CreateICmpEQ(lval, rval, "eqtmp");
			case NEQ:
				return Builder.CreateICmpNE(lval, rval, "neqtmp");
			default:
				throw runtime_error("Invalid binary operation for integers!");
		}
	}
	else{
		return nullptr;
	}
}


llvm::Value * getUnaryExp(llvm::Value * value, type_op operation_tp) {
	switch(operation_tp) {
		case NOT:
			return Builder.CreateNot(value, "nottmp");
		case UNARY_MINUS:
			return Builder.CreateNeg(value, "negtmp");
		default:
			throw runtime_error("Invalid unary operation");
	}
}

// Create custom basic blocks for control flow
const std::string IF_ENTRY = "if";
const std::string FOR_ENTRY = "for";
const std::string WHILE_ENTRY = "while";
const std::string LOOP_ENTRY = "loop_entry";
const std::string LOOP_BODY = "loop";
const std::string TRUE_ENTRY = "true";
const std::string ELSE_ENTRY = "else";
const std::string NEXT_ENTRY = "next";
const std::string END_ENTRY = "end";
const std::string END_LOOP_ENTRY = "end_loop";

llvm::BasicBlock * createIfBlock(llvm::Function * func) {
	return createBasicBlockWithLabel(func, IF_ENTRY);
}

llvm::BasicBlock * createLoopEntryBlock(llvm::Function * func) {
	return createBasicBlockWithLabel(func, LOOP_ENTRY);
}

llvm::BasicBlock * createLoopBlock(llvm::Function * func) {
	return createBasicBlockWithLabel(func, LOOP_BODY);
}

llvm::BasicBlock * createTrueBlock(llvm::Function * func) {
	return createBasicBlockWithLabel(func, TRUE_ENTRY);
}

llvm::BasicBlock * createElseBlock(llvm::Function * func) {
	return createBasicBlockWithLabel(func, ELSE_ENTRY);
}

llvm::BasicBlock * createNextBlock(llvm::Function * func) {
	return createBasicBlockWithLabel(func, NEXT_ENTRY);
}

llvm::BasicBlock *  createEndBlock(llvm::Function * func) {
	return createBasicBlockWithLabel(func, END_ENTRY);
}

llvm::BasicBlock *  createEndLoopBlock(llvm::Function * func) {
	return createBasicBlockWithLabel(func, END_LOOP_ENTRY);
}


llvm::BasicBlock * getNextEntryBlock() {
	symTableList::iterator it = ++symbl_table_list.begin();
	if(it != symbl_table_list.end()) {
		return (llvm::BasicBlock *)getValueFromTable(NEXT_ENTRY, *(it));
	}
	return nullptr;
}

llvm::BasicBlock * getEndLoopBlock() {
	symTableList::iterator it = ++symbl_table_list.begin();
	if(it != symbl_table_list.end()) {
		return (llvm::BasicBlock *)getValueFromTable(END_LOOP_ENTRY, *(it));
	}
	return nullptr;
}

// Create custom basic blocks for short-circuit
const std::string SC_START = "scstart";
const std::string SC_ENTRY = "scblk";
const std::string PHI_ENTRY = "phiblk";
const std::string OR_ENTRY = "orblk";
const std::string AND_ENTRY = "andblk";

llvm::BasicBlock * createShortCircStart(llvm::Function * func) {
	return createBasicBlockWithLabel(func, SC_START);
}

llvm::BasicBlock * createShortCircBlock(llvm::Function * func) {
	return createBasicBlockWithLabel(func, SC_ENTRY);
}

llvm::BasicBlock * createPhiBlock(llvm::Function * func) {
	return createBasicBlockWithLabel(func, PHI_ENTRY);
}

llvm::BasicBlock * createOrBlock(llvm::Function * func) {
	return createBasicBlockWithLabel(func, OR_ENTRY);
}

llvm::BasicBlock * createAndBlock(llvm::Function * func) {
	return createBasicBlockWithLabel(func, AND_ENTRY);
}