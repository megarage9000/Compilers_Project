
#include "default-defs.h"
#include "llvm-helpers.cc"
#include <list>
#include <ostream>
#include <iostream>
#include <sstream>

#ifndef YYTOKENTYPE
#include "decafcomp.tab.h"
#endif

using namespace std;


/// decafAST - Base class for all abstract syntax tree nodes.
class decafAST {
public:
  virtual ~decafAST() {}
  virtual string str() { return string(""); }
  virtual llvm::Value *Codegen() = 0;
};

// For identifier lists
class string_vector {
	std::vector<string> list_of_vectors;
public:
	string_vector(){}
	void push_back(string str) {list_of_vectors.push_back(str);}
	std::vector<string> get_vector() {return list_of_vectors;}
};

string getString(decafAST *d) {
	if (d != NULL) {
		return d->str();
	} else {
		return string("None");
	}
}

template <class T>
string commaList(list<T> vec) {
    string s("");
    for (typename list<T>::iterator i = vec.begin(); i != vec.end(); i++) { 
        s = s + (s.empty() ? string("") : string(",")) + (*i)->str(); 
    }   
    if (s.empty()) {
        s = string("None");
    }   
    return s;
}

template <class T>
llvm::Value *listCodegen(list<T> vec) {
	llvm::Value *val = NULL;
	for (typename list<T>::iterator i = vec.begin(); i != vec.end(); i++) { 
		llvm::Value *j = (*i)->Codegen();
		if (j != NULL) { val = j; }
	}	
	return val;
}

/// decafStmtList - List of Decaf statements
class decafStmtList : public decafAST {
	list<decafAST *> stmts;
public:
	decafStmtList() {}
	~decafStmtList() {
		for (list<decafAST *>::iterator i = stmts.begin(); i != stmts.end(); i++) { 
			delete *i;
		}
	}
	int size() { return stmts.size(); }
	void push_front(decafAST *e) { stmts.push_front(e); }
	void push_back(decafAST *e) { stmts.push_back(e); }
	string str() { return commaList<class decafAST *>(stmts); }
	list<decafAST *>::iterator begin() {return stmts.begin();}
	list<decafAST *>::iterator end() {return stmts.end();}
	bool isEmpty() { return stmts.empty(); }
	llvm::Value *Codegen() { 
		return listCodegen<decafAST *>(stmts); 
	}
};



// Identifiers to deal with strings
class Identifier : public decafAST {
	string id_name;
public:
	Identifier(string ** id) : id_name(*(*id)) {
		delete *id;
	}
	Identifier(string id) : id_name(id) {}
	~Identifier(){}
	string str() {
		return id_name;
	}
	llvm::Value *Codegen() {
		return nullptr;
	}
};

class Type: public decafAST {
	val_type type;
public:
	Type(val_type tp) : type(tp){}
	~Type() {}
	string str() {
		switch(type) {
			case INTTYPE:
				return "IntType";
			case BOOLTYPE:
				return "BoolType";
			case STRINGTYPE:
				return "StringType";
			case VOIDTYPE:
				return "VoidType";
			case NULLTYPE:
				return "NullType";
			default:
				return "None";
		}
	}
	val_type get_type() {return type;}

	llvm::Value *Codegen() {
		return nullptr;
	}
};

class Binary_Operator : public decafAST {
	type_op type;
public:
	Binary_Operator(type_op tp) : type(tp) {}
	~Binary_Operator() {}
	string str() {
		switch(type) {
			case PLUS:
				return "Plus";
			case MINUS:
				return "Minus";
			case MULT:
				return "Mult";
			case DIV:
				return "Div";
			case LEFT_SHIFT:
				return "Leftshift";
			case RIGHT_SHIFT:
				return "Rightshift";
			case MOD:
				return "Mod";
			case LT:
				return "Lt";
			case GT:
				return "Gt";
			case LEQ:
				return "Leq";
			case GEQ:
				return "Geq";
			case EQ:
				return "Eq";
			case NEQ:
				return "Neq";
			case AND:
				return "And";
			case OR:
				return "Or";
			default:
				return "None";
		}
	}
	type_op get_operator() {
		return type;
	}
	llvm::Value *Codegen() {
		return nullptr;
	}
};

class Unary_Operator : public decafAST {
	type_op type;
public:
	Unary_Operator(type_op tp) : type(tp) {}
	~Unary_Operator() {}
	string str() {
		switch (type) {
			case UNARY_MINUS:
				return "UnaryMinus";
			case NOT:
				return "Not";
			default:
				return "None";
		}
	}
	type_op get_operator() {
		return type;
	}
	llvm::Value *Codegen() {
		return nullptr;
	}
};

/// Refactor to IntConstant, BoolConstant
class Int_Constant : public decafAST {
	int value;
public:
	Int_Constant(int val) : value(val) {}
	~Int_Constant() {}
	string str() {
		return "NumberExpr(" + std::to_string(value) + ")";
	} 
	int get_val() {
		return value;
	}
	llvm::Value *Codegen() {
		return initializeLLVMVal(INTTYPE,  value);
	}
};

class Bool_Constant : public decafAST {
	bool value;
public:
	Bool_Constant(bool val) : value(val) {}
	~Bool_Constant() {}
	string str() {
		if(value) {
			return "BoolExpr(True)";
		}
		return "BoolExpr(False)";
	}
	bool get_val() {
		return value;
	}
	llvm::Value *Codegen() {
		return initializeLLVMVal(BOOLTYPE,  value);
	}
};

/// Create StringConstant
class String_Constant : public decafAST {
	string strVal;
public:
	String_Constant(string ** val) : strVal(*(*val)) {
		delete *val;
	}
	~String_Constant() {}
	string str() {
		return "StringConstant(" + strVal + ")";
	}
	llvm::Value *Codegen() {
		return getStringConst(strVal);
	}
};

class Null_Constant : public decafAST {
public:
	Null_Constant() {}
	~Null_Constant() {}
	string str() {
		return "NullConstant";
	}
	llvm::Value *Codegen() {
		return nullptr;
	}
};

/// Expressions
class Binary_Expr : public decafStmtList {
	type_op operation;
	decafAST * lvalexpr, *rvalexpr;
public:
	Binary_Expr(decafAST * l_val, decafAST * r_val, Binary_Operator * op) : decafStmtList() {
		lvalexpr = l_val;
		rvalexpr = r_val;
		operation = op->get_operator();
		push_back(op);
		push_back(l_val);
		push_back(r_val);
	}
	string str() {
		return "BinaryExpr(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		if(operation == AND || operation == OR) {
			llvm::Function * func = Builder.GetInsertBlock()->getParent();
			if(func == nullptr) {
				throw runtime_error("Cannot fetch parent function, is the if statement outside of a function?\n");
			}
			
			llvm::Value * lval = lvalexpr->Codegen();
			llvm::BasicBlock * phiBB = createPhiBlock(func);
			llvm::BasicBlock * curBB = Builder.GetInsertBlock();
			llvm::BasicBlock * scBB = createShortCircBlock(func);
			
			// Set default block
			Builder.SetInsertPoint(scBB);
			llvm::AllocaInst * defVal = defineVar(Builder.getInt1Ty(), "defVal");
			assignVal(defVal, lval);
			llvm::Value * scVal = Builder.CreateLoad(defVal, "scVal");
			Builder.CreateBr(phiBB);
			
			// Set bool block
			llvm::BasicBlock * opBB;
			llvm::Value * opVal;		
			llvm::BasicBlock * resultingBB;	
			if(operation == OR) {
				opBB = createOrBlock(func);
				Builder.SetInsertPoint(opBB);
				llvm::Value * rval = rvalexpr->Codegen();
				opVal = Builder.CreateOr(lval, rval);

				// Fetch the resulting block from the operation to match phinode
				resultingBB = Builder.GetInsertBlock();
				Builder.CreateBr(phiBB);
				Builder.SetInsertPoint(curBB);
				Builder.CreateCondBr(lval, scBB, opBB);
			}
			else {
				opBB = createAndBlock(func);
				Builder.SetInsertPoint(opBB);
				llvm::Value * rval = rvalexpr->Codegen();
				opVal = Builder.CreateAnd(lval, rval);

				// Fetch the resulting block from the operation to match phinode
				resultingBB = Builder.GetInsertBlock();
				Builder.CreateBr(phiBB);
				Builder.SetInsertPoint(curBB);
				Builder.CreateCondBr(lval, opBB, scBB);
			}

			// Set up phi block
			Builder.SetInsertPoint(phiBB);
			llvm::PHINode * val = Builder.CreatePHI(Builder.getInt1Ty(), 2, "phival");
			val->addIncoming(scVal, scBB);
			val->addIncoming(opVal, resultingBB);
			return val;
		}
		else {
			llvm::Value * lval = lvalexpr->Codegen();
			llvm::Value * rval = rvalexpr->Codegen();
			if(lval == rval && lval == nullptr) {
				return nullptr;
			}
			return getBinaryExp(lval, rval, operation);
		}
	}
};

class Unary_Expr: public decafStmtList {
	type_op operation;
	decafAST * valexpr;
public: 
	Unary_Expr(decafAST * val, Unary_Operator * op) : decafStmtList() {
		operation = op->get_operator();
		valexpr = val;
		push_back(op);
		push_back(val);
	}
	string str() {
		return "UnaryExpr(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		llvm::Value * val = valexpr->Codegen();
		if(val == nullptr) {
			return nullptr;
		}
		return getUnaryExp(val, operation);
	}
};

/// Variable / Array Assignments and Expressions
class Assign_Var: public decafStmtList {
	decafAST * varId, * rvalexpr;
public:
	Assign_Var(Identifier * id, decafAST * expression) : decafStmtList() {
		varId = id;
		rvalexpr = expression;
		push_back(id);
		push_back(expression);
	}
	string str() {
		return "AssignVar(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		llvm::AllocaInst * variable = (llvm::AllocaInst *)getValueFromTables(varId->str());
		llvm::Value * value = rvalexpr->Codegen();
		if(value == nullptr) {
			return nullptr;
		}
		assignVal(variable, value);
		return nullptr;
	}	
};

class Assign_Arr_Loc: public decafStmtList {
	string name;
	decafAST * idx, * val;
public:
	Assign_Arr_Loc(Identifier * id, decafAST * index, decafAST * expression) : decafStmtList() {
		name = id->str();
		idx = index;
		val = expression;
		push_back(id);
		push_back(index);
		push_back(expression);
	}
	string str() {
		return "AssignArrayLoc(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		llvm::Value * arrayLocation = useArrLoc(name, idx->Codegen());
		llvm::Value * rval = val->Codegen();
		if(arrayLocation->getType()->getPointerElementType() == rval->getType()) {
			return Builder.CreateStore(rval, arrayLocation);
		}
		else{
			throw runtime_error("invalid type\n");
		}
	
		return nullptr;
	}
};

class Var_Expr: public decafAST{
	Identifier * identifier;
public:
	Var_Expr(Identifier * id) : identifier(id) {}
	~Var_Expr() { if(identifier) {delete identifier;}}
	string str() {
		return "VariableExpr(" + getString(identifier) + ")";
	}
	llvm::Value *Codegen() {
		return useVar(identifier->str());
	}
};

class Arr_Loc_Expr: public decafStmtList{
	string name;
	decafAST * exp;
public:
	Arr_Loc_Expr(Identifier * id, decafAST * expression) : decafStmtList(){
		name = id->str();
		exp = expression;
		push_back(id);
		push_back(expression);
	}
	string str() {
		return "ArrayLocExpr(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		return Builder.CreateLoad(useArrLoc(name, exp->Codegen()), name + "tmp");
	}
};

// /// Methods
class Method_Call: public decafStmtList {
	decafStmtList * args;
	std::vector<llvm::Value *> values;
	std::string funcName;
public:
	Method_Call(Identifier * name, decafStmtList * method_args): decafStmtList()  {
		args = method_args;
		funcName = name->str();
		push_back(name);
		push_back(method_args);
	}
	Method_Call(Identifier * name): decafStmtList() {
		args = nullptr;
		funcName = name->str();
		push_back(name);
		push_back(new decafStmtList());
	}
	string str() {
		return "MethodCall(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		// Get function pointer
		llvm::Function * func = (llvm::Function *)getValueFromTables(funcName);
		if(!func) {
			return nullptr;
		}
		if(args != nullptr) {
			// Retrieve values from arguments 
			if(args->size() == (int)func->arg_size()) {
				auto it = args->begin();
				auto end = args->end();
				auto funcArgIt = func->arg_begin();
				for(;it != end; it++) {
					llvm::Value * val = (*it)->Codegen();
					// Checking arg types and val types to see if there needs
					// to be an int1 -> int32 conversion
					const llvm::Type * valType = val->getType();
					const llvm::Type * argType = funcArgIt->getType();
					if(argType == Builder.getInt32Ty() && valType == Builder.getInt1Ty()) { 
						val = promoteBoolToInt(&val);
						const llvm::Type * newType = val->getType();
					}
					values.push_back(val);
					funcArgIt++;
				}
			}
		}
		return getFuncCall(func, values);
	}
};

// Variable declarations
class Var_Def : public decafStmtList {
	string id;
	val_type tp;
public:
	Var_Def(Identifier * identifier, Type * type) : decafStmtList() {
		id = identifier->str();
		tp = type->get_type();
		push_back(identifier);
		push_back(type);
	}
	Var_Def(Type * type) : decafStmtList() {
		id = "";
		tp = type->get_type();
		push_back(type);
	}
	string str() {
		return "VarDef(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		// Check if the variable is already stored in the table, if not, define it
		if(getValueFromTopTable(id) != nullptr) {
			throw runtime_error("variable " + id + " is already defined\n");
		} 

		return defineVar(getLLVMType(tp), id);
	}
	string getId() {
		return id;
	}
	val_type getType() {
		return tp;
	}
};

decafStmtList * vector_to_var_defs(string_vector * str_vector, Type * type) {
	decafStmtList * var_defs = new decafStmtList();
	std::vector<string> ids = str_vector->get_vector();
	for(string id: ids) {
		var_defs->push_back(
			new Var_Def(
				new Identifier(id), 
				new Type(type->get_type())
		));
	}
	return var_defs;
}


/// Field declarations
const int SCALAR_VAL = -1;
class Field_Size : public decafAST {
	string size;
	// Temporary fix
	int val;
public: 
	Field_Size() {
		size = "Scalar";
		val = SCALAR_VAL;
	}
	Field_Size(int value) {
		if(value == SCALAR_VAL) {
			size = "Scalar";
		}
		else {
			size = "Array(" + std::to_string(val) + ")";
		}
		val = value;
	}
	Field_Size(Int_Constant * arrsize) {
		size = "Array(" + std::to_string(arrsize->get_val()) + ")";
		val = arrsize->get_val();
	}
	string str() {
		return size;
	} 
	int get_val() {
		return val;
	}
	llvm::Value *Codegen() {
		return nullptr;
	}
};

class Field_Decl : public decafStmtList{
	int size;
	string name;
	llvm::Type * tp;
public:
	Field_Decl(Identifier * id, Type * type, Field_Size * sz) : decafStmtList(){
		size = sz->get_val();
		name = id->str();
		tp = getLLVMType(type->get_type());
		push_back(id);
		push_back(type);
		push_back(sz);
	}
	Field_Decl(Identifier * id, Type * type) : decafStmtList() {
		size = SCALAR_VAL;
		name = id->str();
		tp = getLLVMType(type->get_type());
		push_back(id);
		push_back(type);
		push_back(new Field_Size());
	}
	string str() {
		return "FieldDecl(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		if(size == SCALAR_VAL){
			return declareGlobal(name, tp);
		}
		else {
			return declareGlobalArr(name, tp, size);
		}
	}
};

decafStmtList * vector_to_field_decls(string_vector * str_vector, Type * type, Field_Size * sz) {
	decafStmtList * field_decls = new decafStmtList();
	std::vector<string> ids = str_vector->get_vector();
	for(string id: ids) {
		field_decls->push_back(new Field_Decl(
			new Identifier(id),
			new Type(type->get_type()),
			new Field_Size(sz->get_val())
		));
	}
	return field_decls;
}

decafStmtList * vector_to_field_decls(string_vector * str_vector, Type * type) {
	decafStmtList * field_decls = new decafStmtList();
	std::vector<string> ids = str_vector->get_vector();
	for(string id: ids) {
		field_decls->push_back(new Field_Decl(
			new Identifier(id),
			new Type(type->get_type())
		));
	}
	return field_decls;
}


class Assign_Global : public decafStmtList {
	string name;
	llvm::Type * tp;
	decafAST * const_val;
public:
	Assign_Global(Identifier * identifier, Type * type, Int_Constant * const_expr) : decafStmtList() {
		name = identifier->str();
		tp = getLLVMType(type->get_type());
		const_val = const_expr;
		push_back(identifier);
		push_back(type);
		push_back(const_expr);
	}
	Assign_Global(Identifier * identifier, Type * type, Bool_Constant * const_expr) : decafStmtList() {
		name = identifier->str();
		tp = getLLVMType(type->get_type());
		const_val = const_expr;
		push_back(identifier);
		push_back(type);
		push_back(const_expr);
	}
	string str() {
		return "AssignGlobalVar(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		llvm::Constant * value = (llvm::Constant *)const_val->Codegen();
		return declareGlobalWithValue(name, tp, value);
	}
};

// Blocks and Method Blocks 
class Block : public decafStmtList {
	bool if_method = false;
public:
	Block(decafAST * declarations, decafAST * statements) : decafStmtList() {
		push_back(declarations);
		push_back(statements);
	}
	void set_to_method(bool val) {
		if_method = val;
	}
	string str() {
		if(if_method){
			return "MethodBlock(" + decafStmtList::str() + ")";
		}
		return "Block(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		if(if_method) {
			decafStmtList::Codegen();
		}
		else {
			pushTable();
			decafStmtList::Codegen();
			popTable();
		}
		return nullptr;
	}
};


/// If else, For, While
class If_Else: public decafStmtList {
	Block * if_block, * else_block;
	decafAST * val;
public: 
	If_Else(decafAST * expr, Block * if_blk) : decafStmtList() {
		push_back(expr);
		push_back(if_blk);
		push_back(new decafStmtList());
		if_block = if_blk;
		else_block = nullptr;
		val = expr;
	}
	If_Else(decafAST * expr, Block * if_blk, Block * else_blk) : decafStmtList() {
		push_back(expr);
		push_back(if_blk);
		push_back(else_blk);
		if_block = if_blk;
		else_block = else_blk;
		val = expr;
	}
	string str() {
		return "IfStmt(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		
		// Get parent function
		llvm::Function * func = Builder.GetInsertBlock()->getParent();
		if(func == nullptr) {
			throw runtime_error("Cannot fetch parent function, is the if statement outside of a function?\n");
		}

		// Create Blocks
		llvm::BasicBlock * ifStatementBB = createIfBlock(func);
		Builder.CreateBr(ifStatementBB);
		llvm::BasicBlock * trueBB = createTrueBlock(func);
		llvm::BasicBlock * endBB = createEndBlock(func);

		Builder.SetInsertPoint(ifStatementBB);
		// Get the conditional value of expr
		llvm::Value * value = val->Codegen();
		if(value == nullptr) {
			throw runtime_error("Cannot evaluate value\n");
		}

		// Generate True block statment
		Builder.SetInsertPoint(trueBB);
		if_block->Codegen();
		if(trueBB->getTerminator() == nullptr) {
			Builder.CreateBr(endBB);
		}

		// Create conditional branch
		if(else_block != nullptr) {
			// Generate Else block statement
			llvm::BasicBlock * elseBB = createElseBlock(func);
			Builder.SetInsertPoint(elseBB);
			else_block->Codegen();
			if(elseBB->getTerminator() == nullptr) {
				Builder.CreateBr(endBB);
			}

			// Creates a conditional branch between else and true
			Builder.SetInsertPoint(ifStatementBB);
			Builder.CreateCondBr(value, trueBB, elseBB);
		}
		else {
			// Creates a conditional branch between true and end
			Builder.SetInsertPoint(ifStatementBB);
			Builder.CreateCondBr(value, trueBB, endBB);
		}
		Builder.SetInsertPoint(endBB);

		return endBB;
	}
};

/// At this point, most loops are decafstmtlists
class For_Loop: public decafStmtList {
	decafAST * init, * exp, *increm;
	Block * loop;
public:
	For_Loop(decafAST * assign, decafAST * expression, decafAST * after_assign, Block * block) : decafStmtList(){
		init = assign;
		exp = expression;
		increm = after_assign;
		loop = block;
		push_back(assign);
		push_back(expression);
		push_back(after_assign);
		push_back(block);
	}
	string str() {
		return "ForStmt(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		llvm::Function * func = Builder.GetInsertBlock()->getParent();	
		if(func == nullptr) {
			throw runtime_error("Cannot fetch parent function, is the if statement outside of a function?\n");
		}

		// Create blocks for labels
		llvm::BasicBlock * forEntry = createForEntryBlock(func);
		llvm::BasicBlock * loopBlock = createLoopBlock(func);
		llvm::BasicBlock * nextBlock = createNextBlock(func);
		llvm::BasicBlock * endBlock = createEndLoopBlock(func);
		init->Codegen();
		Builder.CreateBr(forEntry);

		// Set up cond branch on for expression
		Builder.SetInsertPoint(forEntry);
		llvm::Value * expVal = exp->Codegen();
		if(expVal->getType() != Builder.getInt1Ty()) {
			throw runtime_error("Invalid terminating condition for the for-loop\n");
		}
		Builder.CreateCondBr(expVal, loopBlock, endBlock);

		// Set up loop block
		Builder.SetInsertPoint(loopBlock);
		loop->Codegen();
		Builder.CreateBr(nextBlock);

		// Set up increment block
		Builder.SetInsertPoint(nextBlock);
		increm->Codegen();
		Builder.CreateBr(forEntry);

		// Set everything back to end block
		Builder.SetInsertPoint(endBlock);
		return endBlock;
	}
};

class While_Loop: public decafStmtList {
	decafAST * exprAST;
	Block * loop;
public:
	While_Loop(decafAST * expression, Block * block) : decafStmtList(){
		exprAST = expression;
		loop = block;
		push_back(expression);
		push_back(block);
	}
	string str() {
		return "WhileStmt(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		llvm::Function * func = Builder.GetInsertBlock()->getParent();	
		if(func == nullptr) {
			throw runtime_error("Cannot fetch parent function, is the if statement outside of a function?\n");
		}

		llvm::BasicBlock * whileEntry = createWhileEntryBlock(func);
		llvm::BasicBlock * loopBlock = createLoopBlock(func);
		llvm::BasicBlock * nextBlock = createNextBlock(func);
		llvm::BasicBlock * endBlock = createEndLoopBlock(func);
		Builder.CreateBr(whileEntry);

		Builder.SetInsertPoint(whileEntry);
		llvm::Value * expVal = exprAST->Codegen();
		if(expVal->getType() != Builder.getInt1Ty()) {
			throw runtime_error("Invalid terminating condition for the for-loop\n");
		}
		Builder.CreateCondBr(expVal, loopBlock, endBlock);

		// Set up loop block
		Builder.SetInsertPoint(loopBlock);
		loop->Codegen();
		Builder.CreateBr(whileEntry);

		Builder.SetInsertPoint(endBlock);
		return endBlock;

	}
};

/// Keywords
class Return: public decafStmtList {
	decafAST * value;
public:
	Return() : decafStmtList(){
		value = nullptr;
	}
	Return(decafAST * returnVal) : decafStmtList() {
		value = returnVal;
		push_back(returnVal);
	}
	string str() {
		return "ReturnStmt(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		if(!value) {
			return nullptr;
		}
		return Builder.CreateRet(value->Codegen());
	}
};

class Continue: public decafAST {
public:
	Continue() {}
	~Continue() {}
	string str() {
		return "ContinueStmt";
	}
	llvm::Value *Codegen() {
		llvm::BasicBlock * label = getNextEntryBlock();
		if(label == nullptr) {
			throw runtime_error("Could not find a loop entry label, are you inside a while / for loop?\n");
		}
		return Builder.CreateBr(label);
	}
};

class Break: public decafAST {
public:
	Break() {}
	~Break() {}
	string str() {
		return "BreakStmt";
	}
	llvm::Value *Codegen() {
		llvm::BasicBlock * label = getEndLoopBlock();
		if(label == nullptr) {
			throw runtime_error("Could not find a end entry label, are you inside a while / for loop?\n");
		}
		return Builder.CreateBr(label);
	}
};

/// Extern and method declarations
class Extern_Func: public decafStmtList {
	vector<llvm::Type*> argTypes;
	vector<string> argNames;
	llvm::Type * returnType;
	string funcName;
public:
	Extern_Func(Identifier * id, Type * return_type, decafStmtList * typeList)
	 : decafStmtList(){
		push_back(id);
		push_back(return_type);
		push_back(typeList);
		// Extract name and return type
		funcName = id->str();
		returnType = getLLVMType(return_type->get_type());
		// Extract arg names and types
		list<decafAST *>::iterator it;
		for(it = typeList->begin(); it != typeList->end(); it++){
			Var_Def * arg = dynamic_cast<Var_Def *>(*it);
			argNames.push_back(arg->getId());
			argTypes.push_back(
				getLLVMType(arg->getType())
			);
		}
	 }
	string str() {
		return "ExternFunction(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		// For now we assume we don't store / allocate extern parameters
		return defineExtern(returnType, argTypes, funcName);
	}
};

class Method_Decl: public decafStmtList {
	vector<llvm::Type*> argTypes;
	vector<string> argNames;
	llvm::Type * returnType;
	string funcName;
	Block * funcBlock;

	public:
	Method_Decl(Identifier * id, Type * return_type, 
	decafStmtList* param_list, Block * block)
	: decafStmtList() {
		block->set_to_method(true);
		push_back(id);
		push_back(return_type);
		push_back(param_list);
		push_back(block);
		/*
			Extract necessities for codegen()
			- parameter pairs and types
			- function name and return type
		*/
		funcBlock = block;
		list<decafAST *>::iterator it;
		for(it = param_list->begin(); it != param_list->end(); it++){
			Var_Def * arg = dynamic_cast<Var_Def *>(*it);
			argNames.push_back(arg->getId());
			argTypes.push_back(
				getLLVMType(arg->getType())
			);
		}
		funcName = id->str();
		returnType = getLLVMType(return_type->get_type());
	}
	string str() {
		return "Method(" + decafStmtList::str() + ")";
	}

	string getFuncName() {
		return funcName;
	}
	llvm::Value *Codegen() {
		// Defines the function, creates a block and arguments
		llvm::Function * funcVal = defineMethod(returnType, argTypes, funcName);
		return funcVal;
	}

	llvm::Value *CodegenFuncBlock() {
		llvm::Function * funcVal = (llvm::Function *)getValueFromTables(funcName);
		// New symbol table
		pushTable();
		// Prepare the arguments and block
		setupFunc(funcVal, argNames);
		// Define the block statements
		funcBlock->Codegen();
		checkFxn(funcVal);
		// Check function if it has a valid return value, if not add a default value
		popTable();
		llvm::raw_ostream &output = llvm::outs();
		
		if(llvm::verifyFunction(*funcVal, &output)) {
			//throw runtime_error("Function " + funcName + " is invalid\n");
			std::cout << "Function " << funcName << " is not valid\n";
			
		}
		return funcVal;
	}
};

class PackageAST : public decafAST {
	string Name;
	decafStmtList *FieldDeclList;
	decafStmtList *MethodDeclList;
public:
	PackageAST(string name, decafStmtList *fieldlist, decafStmtList *methodlist) 
		: Name(name), FieldDeclList(fieldlist), MethodDeclList(methodlist) {}
	~PackageAST() { 
		if (FieldDeclList != NULL) { delete FieldDeclList; }
		if (MethodDeclList != NULL) { delete MethodDeclList; }
	}
	string str() { 
		return string("Package") + "(" + Name + "," + getString(FieldDeclList) + "," + getString(MethodDeclList) + ")";
	}
	llvm::Value *Codegen() { 
		llvm::Value *val = NULL;
		TheModule->setModuleIdentifier(llvm::StringRef(Name)); 
		if (NULL != FieldDeclList) {
			val = FieldDeclList->Codegen();
		}
		if (NULL != MethodDeclList) {
			val = MethodDeclList->Codegen();
			// Also do the method block declarations
			auto it = MethodDeclList->begin();
			auto end = MethodDeclList->end();
			for(;it != end; it++) {
				Method_Decl * declaration = dynamic_cast<Method_Decl *>(*it);
				declaration->CodegenFuncBlock();
			}
		} 
		// Q: should we enter the class name into the symbol table?
		return val; 
	}
};

/// ProgramAST - the decaf program
class ProgramAST : public decafAST {
	decafStmtList *ExternList;
	PackageAST *PackageDef;
public:
	ProgramAST(decafStmtList *externs, PackageAST *c) : ExternList(externs), PackageDef(c) {}
	~ProgramAST() { 
		if (ExternList != NULL) { delete ExternList; } 
		if (PackageDef != NULL) { delete PackageDef; }
	}
	string str() { return string("Program") + "(" + getString(ExternList) + "," + getString(PackageDef) + ")"; }
	llvm::Value *Codegen() { 
		llvm::Value *val = NULL;
		if (NULL != ExternList) {
			val = ExternList->Codegen();
		}
		if (NULL != PackageDef) {
			val = PackageDef->Codegen();
		} else {
			throw runtime_error("no package definition in decaf program");
		}
		return val; 
	}
};


