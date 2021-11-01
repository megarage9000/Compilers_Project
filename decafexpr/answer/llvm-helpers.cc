
#include <iostream>
#include <map>

// this global variable contains all the generated code
static llvm::Module *TheModule;

// this is the method used to construct the LLVM intermediate code (IR)
static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);

typedef enum { voidTp, intTp, boolTp, stringTp } decafType;

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

/// Symbol table 
// TODO 
// -make the symbol table
// -add some llvm helpers
// -test symbol table
typedef std::map<std::string, llvm::value> symTable;