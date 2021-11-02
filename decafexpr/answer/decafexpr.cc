
#include "default-defs.h"
#include "llvm-helpers.cc"
#include <list>
#include <ostream>
#include <iostream>
#include <sstream>

#ifndef YYTOKENTYPE
#include "decafexpr.tab.h"
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
		return nullptr;
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
		return nullptr;
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
		return nullptr;
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
public:
	Binary_Expr(decafAST * l_val, decafAST * r_val, Binary_Operator * op) : decafStmtList() {
		push_back(op);
		push_back(l_val);
		push_back(r_val);
	}
	string str() {
		return "BinaryExpr(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		return nullptr;
	}
};

class Unary_Expr: public decafStmtList {
	int value;
public: 
	Unary_Expr(decafAST * val, Unary_Operator * op) : decafStmtList() {
		push_back(op);
		push_back(val);
	}
	string str() {
		return "UnaryExpr(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		return nullptr;
	}
};

/// Variable / Array Assignments and Expressions
class Assign_Var: public decafStmtList {
public:
	Assign_Var(Identifier * id, decafAST * expression) : decafStmtList() {
		push_back(id);
		push_back(expression);
	}
	string str() {
		return "AssignVar(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		return nullptr;
	}	
};

class Assign_Arr_Loc: public decafStmtList {
public:
	Assign_Arr_Loc(Identifier * id, decafAST * index, decafAST * expression) : decafStmtList() {
		push_back(id);
		push_back(index);
		push_back(expression);
	}
	string str() {
		return "AssignArrayLoc(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
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
		return nullptr;
	}
};

class Arr_Loc_Expr: public decafStmtList{;
public:
	Arr_Loc_Expr(Identifier * id, decafAST * expression) : decafStmtList(){
		push_back(id);
		push_back(expression);
	}
	string str() {
		return "ArrayLocExpr(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		return nullptr;
	}
};

// /// Methods
class Method_Call: public decafStmtList {
public:
	Method_Call(Identifier * name, decafAST * method_args): decafStmtList()  {
		push_back(name);
		push_back(method_args);
	}
	Method_Call(Identifier * name): decafStmtList() {
		push_back(name);
		push_back(new decafStmtList());
	}
	string str() {
		return "MethodCall(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		return nullptr;
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
	// Local variable declarations only! Be careful and don't try to call this
	// in a function def
	llvm::Value *Codegen() {
		return nullptr;
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
class Field_Size : public decafAST {
	string size;
public: 
	Field_Size() {size = "Scalar";}
	Field_Size(string sz) {
		size = sz;
	}
	Field_Size(Int_Constant * arrsize) {
		size = "Array(" + std::to_string(arrsize->get_val()) + ")";
	}
	string str() {
		return size;
	} 
	llvm::Value *Codegen() {
		return nullptr;
	}
};

class Field_Decl : public decafStmtList{
public:
	Field_Decl(Identifier * id, Type * type, Field_Size * sz) : decafStmtList(){
		push_back(id);
		push_back(type);
		push_back(sz);
	}
	Field_Decl(Identifier * id, Type * type) : decafStmtList() {
		push_back(id);
		push_back(type);
		push_back(new Field_Size());
	}
	string str() {
		return "FieldDecl(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		return nullptr;
	}
};

decafStmtList * vector_to_field_decls(string_vector * str_vector, Type * type, Field_Size * sz) {
	decafStmtList * field_decls = new decafStmtList();
	std::vector<string> ids = str_vector->get_vector();
	for(string id: ids) {
		field_decls->push_back(new Field_Decl(
			new Identifier(id),
			new Type(type->get_type()),
			new Field_Size(sz->str())
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
public:
	Assign_Global(Identifier * identifier, Type * type, Int_Constant * const_expr) : decafStmtList() {
		push_back(identifier);
		push_back(type);
		push_back(const_expr);
	}
	Assign_Global(Identifier * identifier, Type * type, Bool_Constant * const_expr) : decafStmtList() {
		push_back(identifier);
		push_back(type);
		push_back(const_expr);
	}
	string str() {
		return "AssignGlobalVar(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		return nullptr;
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
		return nullptr;
	}
};


/// If else, For, While
class If_Else: public decafStmtList {
public: 
	If_Else(decafAST * expr, Block * if_blk) : decafStmtList() {
		push_back(expr);
		push_back(if_blk);
		push_back(new decafStmtList());
	}
	If_Else(decafAST * expr, Block * if_blk, Block * else_blk) : decafStmtList() {
		push_back(expr);
		push_back(if_blk);
		push_back(else_blk);
	}
	string str() {
		return "IfStmt(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		return nullptr;
	}
};

/// At this point, most loops are decafstmtlists
class For_Loop: public decafStmtList {
public:
	For_Loop(decafAST * assign, decafAST * expression, decafAST * after_assign, Block * block) : decafStmtList(){
		push_back(assign);
		push_back(expression);
		push_back(after_assign);
		push_back(block);
	}
	string str() {
		return "ForStmt(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		return nullptr;
	}
};

class While_Loop: public decafStmtList {
public:
	While_Loop(decafAST * expression, Block * block) : decafStmtList(){
		push_back(expression);
		push_back(block);
	}
	string str() {
		return "WhileStmt(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		return nullptr;
	}
};

/// Keywords
class Return: public decafStmtList {
public:
	Return() : decafStmtList(){}
	Return(decafAST * returnVal) : decafStmtList() {
		push_back(returnVal);
	}
	string str() {
		return "ReturnStmt(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		return nullptr;
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
		return nullptr;
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
		return nullptr;
	}
};

/// Extern and method declarations
class Extern_Func: public decafStmtList {
public:
	Extern_Func(Identifier * id, Type * return_type, decafAST * typeList)
	 : decafStmtList(){
		push_back(id);
		push_back(return_type);
		push_back(typeList);
	 }
	string str() {
		return "ExternFunction(" + decafStmtList::str() + ")";
	}
	llvm::Value *Codegen() {
		return nullptr;
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
	llvm::Value *Codegen() {
		// Defines the function, creates a block and arguments
		llvm::Value * funcVal = defineFunc(returnType, argTypes, funcName, argNames);
		// Also define the block statements
		funcBlock->Codegen();
		return funcVal;
	}
};

