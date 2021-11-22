
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


static llvm::Function * mainFunction = nullptr;

/*
	CODE STYLE:
	variables: snake_case/camelCase
	functions: camelCase
	classes: CamelCase
*/

/// decafAST - Base class for all abstract syntax tree nodes.
class decafAST {
	int line_pos;
	int token_pos;
public:
	decafAST() {
		line_pos = lineno;
		token_pos = tokenpos;
	}
  virtual ~decafAST() {}
  virtual string str() { 
	  return string(""); }
  virtual llvm::Value *Codegen() = 0;
  int get_line_pos() { return line_pos; }
  int get_token_pos() { return token_pos; }
  void set_line_pos(int pos) { line_pos = pos;}
  void set_token_pos(int pos) { token_pos = pos;} 	
  string get_location(){ 
	  return "\nAt line position = " + std::to_string(line_pos) + "\nAt token position = " + std::to_string(token_pos); 
	}
	void throw_semantic_error(std::string message) {
		std::string error_message = "SEMANTIC ERROR: " + message + get_location();
		throw std::runtime_error(error_message.c_str());
	}
	void throw_semantic_error(const char * message) {
		throw_semantic_error(std::string(message));
	}
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
	decafStmtList() : decafAST() {}
	~decafStmtList() {
		for (list<decafAST *>::iterator i = stmts.begin(); i != stmts.end(); i++) { 
			delete *i;
		}
	}
	int size() { return stmts.size(); }
	void push_front(decafAST *e) { stmts.push_front(e); }
	void push_back(decafAST *e) { stmts.push_back(e); }
	string str() {
		return commaList<class decafAST *>(stmts); }
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
	Identifier(string ** id) : decafAST(), id_name(*(*id)) {
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
	ValueType type;
public:
	Type(ValueType tp) : decafAST(), type(tp){}
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
	ValueType get_type() {return type;}

	llvm::Value *Codegen() {
		return nullptr;
	}
};

class Binary_Operator : public decafAST {
	OperationType type;
public:
	Binary_Operator(OperationType tp) : decafAST(), type(tp) {}
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
	OperationType getOperator() {
		return type;
	}
	llvm::Value *Codegen() {
		return nullptr;
	}
};

class Unary_Operator : public decafAST {
	OperationType type;
public:
	Unary_Operator(OperationType tp) : decafAST(), type(tp) {}
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
	OperationType getOperator() {
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
	Int_Constant(int val) : decafAST(), value(val) {}
	~Int_Constant() {}
	string str() {
		return "NumberExpr(" + std::to_string(value) + ")";
	} 
	int get_val() {
		return value;
	}
	llvm::Value *Codegen() {
		try {
			return initializeLLVMVal(INTTYPE,  value);
		} catch (std::exception& e) {
			throw_semantic_error(e.what());
			return nullptr;
		}
	}
};

class Bool_Constant : public decafAST {
	bool value;
public:
	Bool_Constant(bool val) : decafAST(), value(val) {}
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
		try {
			return initializeLLVMVal(BOOLTYPE,  value);
		} catch (std::exception& e) {
			throw_semantic_error(e.what());
			return nullptr;
		}
	}
};

/// Create StringConstant
class String_Constant : public decafAST {
	string str_value;
public:
	String_Constant(string ** val) : decafAST(), str_value(*(*val)) {
		delete *val;
	}
	~String_Constant() {}
	string str() {
		return "StringConstant(" + str_value + ")";
	}
	llvm::Value *Codegen() {
		return getStringConst(str_value);
	}
};

class Null_Constant : public decafAST {
public:
	Null_Constant(): decafAST() {}
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
	OperationType operation;
	decafAST * lval_expr, *rval_expr;
public:
	Binary_Expr(decafAST * l_val, decafAST * r_val, Binary_Operator * op) : decafStmtList() {
		lval_expr = l_val;
		rval_expr = r_val;
		operation = op->getOperator();
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
				throw_semantic_error("binary expression cannot find parent function.");
				return nullptr;
			}
			

			llvm::BasicBlock * phiBB = createPhiBlock(func);
			llvm::BasicBlock * scStartBB = createShortCircStart(func);
			llvm::BasicBlock * scBB = createShortCircBlock(func);
			llvm::BasicBlock * opBB = createOpBlock(func);
	
			Builder.CreateBr(scStartBB);
			
			// Set start of short circuit
			Builder.SetInsertPoint(scStartBB);
			llvm::Value * lval = lval_expr->Codegen();
			
			if(operation == AND) {
				Builder.CreateCondBr(lval, opBB, scBB);
			}
			else {
				Builder.CreateCondBr(lval, scBB, opBB);
			}
			
			// Set default block
			Builder.SetInsertPoint(scBB);
			Builder.CreateBr(phiBB);
			
			// Set bool block
			Builder.SetInsertPoint(opBB);
			llvm::Value * rval = rval_expr->Codegen();
			llvm::Value * op_value;
			try {
				op_value = getBinaryExp(lval, rval, operation);
			} catch (std::exception &e) {
				throw_semantic_error(e.what());
				return nullptr;
			}
			llvm::BasicBlock * resultingBB = Builder.GetInsertBlock();
			Builder.CreateBr(phiBB);
	
			// Set up phi block
			Builder.SetInsertPoint(phiBB);
			llvm::PHINode * val = Builder.CreatePHI(Builder.getInt1Ty(), 2, "phi");
			val->addIncoming(lval, scBB);
			val->addIncoming(op_value, resultingBB);
			return val;
		}
		else {
			llvm::Value * lval = lval_expr->Codegen();
			llvm::Value * rval = rval_expr->Codegen();
			if(lval == rval && lval == nullptr) {
				throw_semantic_error("cannot evaluate lval and rval expressions.");
				return nullptr;
			}
			try {
				return getBinaryExp(lval, rval, operation);
			} catch (std::exception &e) {
				throw_semantic_error(e.what());
				return nullptr;
			}
		}
	}
};

class Unary_Expr: public decafStmtList {
	OperationType operation;
	decafAST * val_expr;
public: 
	Unary_Expr(decafAST * val, Unary_Operator * op) : decafStmtList() { 
		operation = op->getOperator();
		val_expr = val;
		push_back(op);
		push_back(val);
	}
	string str() {
		return "UnaryExpr(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		llvm::Value * val = val_expr->Codegen();
		if(val == nullptr) {
			throw_semantic_error("cannot evaluate unary expression.");
			return nullptr;
		}
		return getUnaryExp(val, operation);
	}
};

/// Variable / Array Assignments and Expressions
class Assign_Var: public decafStmtList {
	decafAST * rval_expr;
	std::string var_id;
public:
	Assign_Var(Identifier * id, decafAST * expression) : decafStmtList() {
		var_id = id->str();
		rval_expr = expression;
		push_back(id);
		push_back(expression);
	}
	string str() {
		return "AssignVar(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		llvm::AllocaInst * variable = (llvm::AllocaInst *)getValueFromTables(var_id);
		if(variable == nullptr) {
			throw_semantic_error("variable " + var_id + " is not within scope.");
			return nullptr;
		}
		llvm::Value * value = rval_expr->Codegen();
		if(value == nullptr) {
			rval_expr->throw_semantic_error("could not evaluate rval expression.");
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
		llvm::Value * index = idx->Codegen();
		if(index->getType() != Builder.getInt32Ty()) {
			idx->throw_semantic_error("index does not evaluate to integer.");
			return nullptr;
		}

		llvm::Value * arrayLocation;
		try {
			arrayLocation = useArrLoc(name, index);
		} catch(std::exception &e) {
			throw_semantic_error(e.what());
		}
		llvm::Value * rval = val->Codegen();
		if(arrayLocation->getType()->getPointerElementType() == rval->getType()) {
			return Builder.CreateStore(rval, arrayLocation);
		}
		else{
			throw_semantic_error("cannot assign array of type " 
								+ LLVMTypeToString(arrayLocation->getType()->getPointerElementType()) 
								+ " with value of type " + LLVMTypeToString(rval->getType()));
			return nullptr;
		}
	}
};

class Var_Expr: public decafAST{
	Identifier * id_ast;
public:
	Var_Expr(Identifier * id) : decafAST(), id_ast(id) {}
	~Var_Expr() { if(id_ast) {delete id_ast;}}
	string str() {
		return "VariableExpr(" + getString(id_ast) + ")";
	}
	llvm::Value *Codegen() {
		llvm::Value * var = useVar(id_ast->str());
		if(!var) {
			throw_semantic_error("variable " + id_ast->str() + " is not within scope.");
			return nullptr;
		}
		return var;
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
		llvm::Value * arr_loc;
		try {
			arr_loc = useArrLoc(name, exp->Codegen());
		} catch (std::exception& e) {
			throw_semantic_error(e.what());
			return nullptr;
		}
		return Builder.CreateLoad(arr_loc, name + "tmp");
	}
};

// /// Methods
class Method_Call: public decafStmtList {
	decafStmtList * args;
	std::vector<llvm::Value *> values;
	std::string func_name;
public:
	Method_Call(Identifier * name, decafStmtList * method_args): decafStmtList()  {
		args = method_args;
		func_name = name->str();
		push_back(name);
		push_back(method_args);
	}
	Method_Call(Identifier * name): decafStmtList() {
		args = nullptr;
		func_name = name->str();
		push_back(name);
		push_back(new decafStmtList());
	}
	string str() {
		return "MethodCall(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		// Get function pointer
		llvm::Function * func = (llvm::Function *)getValueFromTables(func_name);
		if(!func) {
			throw_semantic_error("function " + func_name + " is not defined within this scope.");
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
					llvm::Type * valType = val->getType();
					llvm::Type * argType = funcArgIt->getType();
					if(argType == Builder.getInt32Ty() && valType == Builder.getInt1Ty()) { 
						try {
							val = promoteBoolToInt(&val);
						} catch (std::exception &e) {
							(*it)->throw_semantic_error(e.what());
							return nullptr;
						}
					}
					else if(valType != argType) {
						(*it)->throw_semantic_error("arguement type " 
													+ LLVMTypeToString(argType)
													+ " cannot accept parameter of type " 
													+ LLVMTypeToString(valType));
						return nullptr;
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
	ValueType tp;
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
			throw_semantic_error("variable " + id + " is already defined within scope.");
			return nullptr;
		} 

		return defineVar(getLLVMType(tp), id);
	}
	string getId() {
		return id;
	}
	ValueType getType() {
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
	Field_Size(): decafAST() {
		size = "Scalar";
		val = SCALAR_VAL;
	}
	Field_Size(int value): decafAST() {
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
		set_line_pos(arrsize->get_line_pos());
		set_token_pos(arrsize->get_token_pos());
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
			try{
				return declareGlobal(name, tp);
			} catch(std::exception &e) {
				throw_semantic_error(e.what());
				return nullptr;
			}
		}
		else {
			try {
				return declareGlobalArr(name, tp, size);
			} catch (std::exception &e) {
				throw_semantic_error(e.what());
				return nullptr;
			}
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
		try {
			return declareGlobalWithValue(name, tp, value);
		} catch(std::exception &e) {
			throw_semantic_error(e.what());
			return nullptr;
		}
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
			throw_semantic_error("if statement cannot find parent function.");
			return nullptr;
		}
		pushTable();
		// Create Blocks
		llvm::BasicBlock * ifStatementBB = createIfBlock(func);
		Builder.CreateBr(ifStatementBB);
		llvm::BasicBlock * trueBB = createTrueBlock(func);
		llvm::BasicBlock * endBB = createEndBlock(func);

		Builder.SetInsertPoint(ifStatementBB);
		
		// Generate True block statment
		Builder.SetInsertPoint(trueBB);
		if_block->Codegen();
		// if(trueBB->getTerminator() == nullptr) {
		// }
		Builder.CreateBr(endBB);

		// Create conditional branch
		if(else_block != nullptr) {
			// Generate Else block statement
			llvm::BasicBlock * elseBB = createElseBlock(func);
			Builder.SetInsertPoint(elseBB);
			else_block->Codegen();
			// if(elseBB->getTerminator() == nullptr) {
			// }
			Builder.CreateBr(endBB);

			// Creates a conditional branch between else and true
			Builder.SetInsertPoint(ifStatementBB);
			// Get the conditional value of expr
			llvm::Value * value = val->Codegen();
			if(value == nullptr) {
				val->throw_semantic_error("cannot evaluate if expression.");
				return nullptr;
			}
			else if(value->getType() != Builder.getInt1Ty()) {
				val->throw_semantic_error("if expression is not a boolean.");
				return nullptr;
			}

			Builder.CreateCondBr(value, trueBB, elseBB);
		}
		else {
			// Creates a conditional branch between true and end
			Builder.SetInsertPoint(ifStatementBB);
			// Get the conditional value of expr
			llvm::Value * value = val->Codegen();
			if(value == nullptr) {
				val->throw_semantic_error("cannot evaluate if expression.");
				return nullptr;
			}
			else if(value->getType() != Builder.getInt1Ty()) {
				val->throw_semantic_error("if expression is not a boolean.");
				return nullptr;
			}
			Builder.CreateCondBr(value, trueBB, endBB);
		}
		Builder.SetInsertPoint(endBB);
		popTable();
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

		pushTable();

		llvm::Function * func = Builder.GetInsertBlock()->getParent();	
		if(func == nullptr) {
			throw_semantic_error("for loop cannot find parent function.");
			return nullptr;
		}

		// Create blocks for labels
		llvm::BasicBlock * forEntry = createLoopEntryBlock(func);
		llvm::BasicBlock * loopBlock = createLoopBlock(func);
		llvm::BasicBlock * nextBlock = createNextBlock(func);
		llvm::BasicBlock * endBlock = createEndLoopBlock(func);
		init->Codegen();
		Builder.CreateBr(forEntry);

		// Set up cond branch on for expression
		Builder.SetInsertPoint(forEntry);
		llvm::Value * expVal = exp->Codegen();
		if(expVal->getType() != Builder.getInt1Ty()) {
			exp->throw_semantic_error("for loop condition is not of type boolean");
			return nullptr;
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
		popTable();
		return endBlock;
	}
};

class While_Loop: public decafStmtList {
	decafAST * exp;
	Block * loop;
public:
	While_Loop(decafAST * expression, Block * block) : decafStmtList(){
		exp = expression;
		loop = block;
		push_back(expression);
		push_back(block);
	}
	string str() {
		return "WhileStmt(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		pushTable();
		llvm::Function * func = Builder.GetInsertBlock()->getParent();	
		if(func == nullptr) {
			throw_semantic_error("while loop cannot find parent function.");
			return nullptr;
		}

		llvm::BasicBlock * whileEntry = createLoopEntryBlock(func);
		llvm::BasicBlock * loopBlock = createLoopBlock(func);
		llvm::BasicBlock * endBlock = createEndLoopBlock(func);
		llvm::BasicBlock * nextBlock = createNextBlock(func);
		Builder.CreateBr(whileEntry);

		Builder.SetInsertPoint(whileEntry);
		llvm::Value * expVal = exp->Codegen();
		if(expVal->getType() != Builder.getInt1Ty()) {
			exp->throw_semantic_error("while loop condition is not of type boolean.");
			return nullptr;
		}
		Builder.CreateCondBr(expVal, loopBlock, endBlock);

		// Set up loop block
		Builder.SetInsertPoint(loopBlock);
		loop->Codegen();
		Builder.CreateBr(nextBlock);

		Builder.SetInsertPoint(nextBlock);
		Builder.CreateBr(whileEntry);

		Builder.SetInsertPoint(endBlock);
		popTable();
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
		llvm::Function * func = Builder.GetInsertBlock()->getParent();	
		if(func == nullptr) {
			throw_semantic_error("return cannot find parent function.");
			return nullptr;
		}
		if(!value) {
			return Builder.CreateRetVoid();
		}
		else {
			llvm::Value * returnValue = value->Codegen();
			if(returnValue->getType() != func->getReturnType()) {
				throw_semantic_error("return statment yields value of type " 
									+ LLVMTypeToString(returnValue->getType()) 
									+ " in a function that expects a return type of " 
									+ LLVMTypeToString(func->getReturnType()));
			}
			return Builder.CreateRet(returnValue);
		}
	}
};

class Continue: public decafAST {
public:
	Continue() : decafAST() {}
	~Continue() {}
	string str() {
		return "ContinueStmt";
	}
	llvm::Value *Codegen() {
		llvm::BasicBlock * label = getNextEntryBlock();
		if(label == nullptr) {
			throw_semantic_error("continue statement is invalid in this block.");
			return nullptr;
		}
		return Builder.CreateBr(label);
	}
};

class Break: public decafAST {
public:
	Break() : decafAST() {}
	~Break() {}
	string str() {
		return "BreakStmt";
	}
	llvm::Value *Codegen() {
		llvm::BasicBlock * label = getEndLoopBlock();
		if(label == nullptr) {
			throw_semantic_error("break statement is invalid in this block.");
			return nullptr;
		}
		return Builder.CreateBr(label);
	}
};

/// Extern and method declarations
class Extern_Func: public decafStmtList {
	vector<llvm::Type*> argTypes;
	vector<string> argNames;
	llvm::Type * returnType;
	string func_name;
public:
	Extern_Func(Identifier * id, Type * return_type, decafStmtList * typeList)
	 : decafStmtList(){
		push_back(id);
		push_back(return_type);
		push_back(typeList);
		// Extract name and return type
		func_name = id->str();
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
		try {
			return defineExtern(returnType, argTypes, func_name);
		} catch (std::exception &e) {
			throw_semantic_error(e.what());
			return nullptr;
		}
	}
};

class Method_Decl: public decafStmtList {
	vector<llvm::Type*> argTypes;
	vector<string> argNames;
	llvm::Type * returnType;
	string func_name;
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
		func_name = id->str();
		returnType = getLLVMType(return_type->get_type());
	}
	string str() {
		return "Method(" + decafStmtList::str() + ")" ;
	}

	string getFuncName() {
		return func_name;
	}
	llvm::Value *Codegen() {
		// Defines the function, creates a block and arguments
		llvm::Function * funcVal = (llvm::Function *)getValueFromTables(func_name);
		if(funcVal != nullptr) {
			throw_semantic_error("function " + func_name + " is already defined");
			return nullptr;
		}
		try {
			return defineMethod(returnType, argTypes, func_name);
		} catch (std::exception &e) {
			throw_semantic_error(e.what());
			return nullptr;
		}
	}

	llvm::Value *CodegenFuncBlock() {
		llvm::Function * funcVal = (llvm::Function *)getValueFromTables(func_name);
		if(funcVal == nullptr) {
			throw_semantic_error(func_name + " is not yet defined.");
			return nullptr;
		}
		// New symbol table
		pushTable();
		// Prepare the arguments and block
		setupFunc(funcVal, argNames);
		// Define the block statements
		funcBlock->Codegen();
		// Check function if it has a valid return value, if not add a default value
		checkFxn(funcVal);
		// If it's a main function
		if(func_name == "main" && mainFunction == nullptr) {
			mainFunction = funcVal;
		}
		// is this a semantic error?
		// else if(func_name == "main" && mainFunction != nullptr) {
		// 	throw_semantic_error("main function is already defined.")
		// }
		popTable();
		
		// llvm::raw_ostream &output = llvm::outs();
		// if(llvm::verifyFunction(*funcVal, &output)) {
		// 	//throw runtime_error("Function " + func_name + " is invalid\n");
		// 	std::cout << "Function " << func_name << " is not valid\n";
			
		// }
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


