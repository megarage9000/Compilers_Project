#include "default-defs.h"
#include <map>
#include <string>
#include <stack>


/*
	Functions here will throw runtime errors.
	- decafcomp.cc will deal with these
	- exceptions though are symbol table functions
*/

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

llvm::Value * getValWithStart(std::string name, symTableList::iterator it) {
	llvm::Value * result = nullptr;
	if(symbl_table_list.empty()) {
	  return result;
	}
	for(; it != symbl_table_list.end(); it++) {
		result = getValueFromTable(name, *it);
		if(result != nullptr){
			return result;
		}
	}
	return result;
}

llvm::Value * getValueFromTables(std::string name) {
  return getValWithStart(name, symbl_table_list.begin());
}
llvm::Value * getValueFromTopTable(std::string name) {
	return getValueFromTable(name, *(symbl_table_list.begin()));
}

llvm::Value * getValueFromSecondTopTable(std::string name) {
	return getValueFromTable(name, *(++symbl_table_list.begin()));
}

void insertToTable(std::string name, llvm::Value * val) {
	symTable topTable = (*symbl_table_list.begin());
	auto it = topTable.find(name);
	if(it != topTable.end()) {
		it->second = val;
	}
	else{
		std::pair<std::string, llvm::Value *> tuple (name ,val);
		symbl_table_list.begin()->insert(tuple);
	}
}

void pushTable() {
  symTable newtable;;	
  symbl_table_list.push_front(newtable);

}

void popTable() {
	if(!symbl_table_list.empty()) {	
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
}	ValueType;

// Getting types
llvm::Type *getLLVMType(ValueType type) {
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
			throw runtime_error("Invalid type");
	}
}

std::string LLVMTypeToString(llvm::Type * type) {
	if(type == Builder.getVoidTy()) {
		return "void";
	}
	else if(type == Builder.getInt32Ty()) {
		return "int";
	}
	else if(type == Builder.getInt1Ty()) {
		return "bool";
	}
	else if(type == Builder.getInt8PtrTy()) {
		return "string";
	}
	else {
		return "";
	}
}

// -- Checking specific types (decaf, method, externs, bool, int, string, etc.)

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
llvm::Constant *initializeLLVMVal(ValueType type, int initialVal) {
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
		std::string typeStr = LLVMTypeToString(type);
		throw runtime_error("constant of type " + typeStr + " cannot be initialized.");
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
	throw runtime_error("value cannot be promoted to integer.");
}

// -- Assignments
void assignVal(llvm::AllocaInst* lval, llvm::Value * rval) {
	const llvm::PointerType * rvalType = rval->getType()->getPointerTo();
	const llvm::PointerType * lvalType = lval->getType();
	if(rvalType == lvalType) {
		Builder.CreateStore(rval, lval);
	}
	else {
		std::string rvalstr = LLVMTypeToString(rvalType->getElementType());
		std::string lvalstr = LLVMTypeToString(lvalType->getElementType());
		throw std::logic_error("Cannot assign lvalue of type " + lvalstr + " with rvalue of type " + rvalstr + '.');
	}
}


// -- Local Variables
llvm::AllocaInst * defineVar(llvm::Type * tp, std::string id) {
	llvm::AllocaInst * allocation = Builder.CreateAlloca(tp, 0, id.c_str());
	// Zero initialization
	if(tp == Builder.getInt1Ty()) {
		assignVal(allocation, initializeLLVMVal(tp, 1));
	}
	else {
		assignVal(allocation, initializeLLVMVal(tp, 0));
	}
	insertToTable(std::string(id), allocation);
	return allocation;

}
llvm::Value * useVar(std::string id) {
	llvm::Value * val = getValueFromTables(id);
	if(val == nullptr) {
		throw runtime_error("variable " + id + " cannot be found. Either it is not within scope or is not defined.");
	}
	return Builder.CreateLoad(val, id.c_str());
}

llvm::Value * useArrLoc(std::string id, llvm::Value * index) {
	llvm::GlobalVariable * val = (llvm::GlobalVariable *)getValueFromTables(id);
	if(val == nullptr) {
		throw runtime_error("array " + id + " cannot be found. Either it is not within scope or is not defined.");
	}
	llvm::Type * indexType = index->getType();
	if(indexType != Builder.getInt32Ty()) {
		std::string typeToStr = LLVMTypeToString(indexType);
		throw logic_error("array " + id + " cannot be indexed with value of type " + typeToStr + '.');
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
		std::string globalType = LLVMTypeToString(tp);
		throw logic_error("global variable " + id + " of type " + globalType + " cannot be initialized with a value.");
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
		std::string globalType = LLVMTypeToString(tp);
		throw logic_error("global variable " + id + " of type " + globalType + " cannot be initialized with a value.");
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
		std::string globalType = LLVMTypeToString(tp);
		throw logic_error("global array " + id + " of type " + globalType + " is not valid.");
	}
}



// -- Blocks

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
llvm::BasicBlock * createLabelBlock(llvm::Function * func, std::string label) {
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
		throw logic_error("method can not be defined with a return type of " + LLVMTypeToString(returnTp) + '.');
	}
	// Validate arguments to make sure they are correct type
	for(llvm::Type * argType : argTypes) {
		if(!isDecafType(argType)){
			throw runtime_error("method argument cannot be of type " + LLVMTypeToString(argType) + '.');
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
		throw logic_error("extern method can not be defined with a return type of " + LLVMTypeToString(returnTp) + '.');
	}
	// Validate arguments to make sure they are correct type
	for(llvm::Type * argType : argTypes) {
		if(!isExternType(argType)){
			throw runtime_error("extern method argument cannot be of type " + LLVMTypeToString(argType) + '.');
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
} OperationType;

std::string operationToString(OperationType opType) {
	switch(opType) {
			case PLUS:
				return "plus(+)";
			case MINUS:
				return "minus(-)";
			case MULT:
				return "multiply(*)";
			case DIV:
				return "divide(/)";
			case LEFT_SHIFT:
				return "left shift(<<)";
			case RIGHT_SHIFT:
				return "right shift(>>)";
			case MOD:
				return "modulus(%)";
			case LT:
				return "less than(<)";
			case GT:
				return "greater than(>)";
			case LEQ:
				return "less than/equal to(<=)";
			case GEQ:
				return "greater than/equal to(>=)";
			case EQ:
				return "equal to(==)";
			case NEQ:
				return "not equal to(!=)";
			case OR:
				return "or(||)";
			case AND:
				return "and(&&)";	
			case NOT:
				return "not(!)";
			case UNARY_MINUS:
				return "negative(-)";
			default:
				return "";
		
	}
}

llvm::Value * getBinaryExp(llvm::Value * lval, llvm::Value * rval, OperationType operation_tp) {
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
				throw logic_error("cannot apply operation " + operationToString(operation_tp) + " on integers.");
		}
	}
	else if(lvalType == Builder.getInt1Ty() && rvalType == Builder.getInt1Ty()) {
		switch (operation_tp)
		{
			case OR:
				return Builder.CreateOr(lval, rval, "ortmp");
			case AND:
				return Builder.CreateAnd(lval, rval, "andtmp");	
			case EQ:
				return Builder.CreateICmpEQ(lval, rval, "eqtmp");
			case NEQ:
				return Builder.CreateICmpNE(lval, rval, "neqtmp");		
			default:
				throw logic_error("cannot apply operation " + operationToString(operation_tp) + " on booleans.");
		}
	}
	else {
		return nullptr;
	}
}


llvm::Value * getUnaryExp(llvm::Value * value, OperationType operation_tp) {
	switch(operation_tp) {
		case NOT:
			if(value->getType() != Builder.getInt1Ty()) {
				throw logic_error("cannot apply unary not operation on type " + LLVMTypeToString(value->getType()) + '.');
			}
			return Builder.CreateNot(value, "nottmp");
		case UNARY_MINUS:
			if(value->getType() != Builder.getInt32Ty()) {
				throw logic_error("cannot apply unary minus operation on type " + LLVMTypeToString(value->getType()) + '.');
			}
			return Builder.CreateNeg(value, "negtmp");
		default:
			throw logic_error("cannot apply operation " + operationToString(operation_tp) + " on unary");
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
	return createLabelBlock(func, IF_ENTRY);
}

llvm::BasicBlock * createLoopEntryBlock(llvm::Function * func) {
	return createLabelBlock(func, LOOP_ENTRY);
}

llvm::BasicBlock * createLoopBlock(llvm::Function * func) {
	return createLabelBlock(func, LOOP_BODY);
}

llvm::BasicBlock * createTrueBlock(llvm::Function * func) {
	return createLabelBlock(func, TRUE_ENTRY);
}

llvm::BasicBlock * createElseBlock(llvm::Function * func) {
	return createLabelBlock(func, ELSE_ENTRY);
}

llvm::BasicBlock * createNextBlock(llvm::Function * func) {
	return createLabelBlock(func, NEXT_ENTRY);
}

llvm::BasicBlock *  createEndBlock(llvm::Function * func) {
	return createLabelBlock(func, END_ENTRY);
}

llvm::BasicBlock *  createEndLoopBlock(llvm::Function * func) {
	return createLabelBlock(func, END_LOOP_ENTRY);
}


llvm::BasicBlock * getNextEntryBlock() {
	symTableList::iterator it = ++symbl_table_list.begin();
	if(it != symbl_table_list.end()) {
		return (llvm::BasicBlock *)getValWithStart(NEXT_ENTRY, it);  
	}
	return nullptr;
	//return (llvm::BasicBlock *)getValueFromTopTable(NEXT_ENTRY);
}

llvm::BasicBlock * getEndLoopBlock() {
	symTableList::iterator it = ++symbl_table_list.begin();
	if(it != symbl_table_list.end()) {
		return (llvm::BasicBlock *)getValWithStart(END_LOOP_ENTRY, it);
	}
	return nullptr;
	//return (llvm::BasicBlock *)getValueFromTopTable(END_LOOP_ENTRY);
	
}

// Create custom basic blocks for short-circuit
const std::string SC_START = "scstart";
const std::string SC_ENTRY = "scblk";
const std::string PHI_ENTRY = "phiblk";
const std::string OP_ENTRY = "opblk";

llvm::BasicBlock * createShortCircStart(llvm::Function * func) {
	return createLabelBlock(func, SC_START);
}

llvm::BasicBlock * createShortCircBlock(llvm::Function * func) {
	return createLabelBlock(func, SC_ENTRY);
}

llvm::BasicBlock * createPhiBlock(llvm::Function * func) {
	return createLabelBlock(func, PHI_ENTRY);
}

llvm::BasicBlock * createOpBlock(llvm::Function * func) {
	return createLabelBlock(func, OP_ENTRY);
}

