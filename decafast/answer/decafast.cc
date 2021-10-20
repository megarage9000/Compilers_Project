
#include "default-defs.h"
#include <list>
#include <ostream>
#include <iostream>
#include <sstream>

#ifndef YYTOKENTYPE
#include "decafast.tab.h"
#endif

using namespace std;


/// decafAST - Base class for all abstract syntax tree nodes.
class decafAST {
public:
  virtual ~decafAST() {}
  virtual string str() { return string(""); }
};


string getString(decafAST *d) {
	if (d != NULL) {
		return d->str();
	} else {
		return string("None");
	}
}
/// Debugging purposes
void debugAST(decafAST * d) {
	std::cout << getString(d) << '\n';
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
};

// Identifiers to deal with strings
class Identifier : public decafAST {
	string id_name;
public:
	Identifier(string ** id) : id_name(*(*id)) {
		delete *id;
	}
	~Identifier(){}
	string str() {
		return id_name;
	}
};

class Identifier_List : public decafAST {
	list<Identifier *> identifiers;
public:
	Identifier_List() {}
	~Identifier_List() {
		for(auto id : identifiers) {
			delete id;
		}
	}
	void push_back(Identifier * id) {
		identifiers.push_back(id);
	}
	void push_front(Identifier * id) {
		identifiers.push_front(id);
	}
	string str() {
		return commaList<Identifier *>(identifiers);
	}
	list<Identifier *> get_list() {
		return identifiers;
	}
};

typedef enum {
	INTTYPE,
	BOOLTYPE,
	STRINGTYPE,
	VOIDTYPE
}	val_type;

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
			default:
				return "None";
		}
	}
};

typedef enum {
	PLUS, MINUS, MULT, DIV, 
	LEFT_SHIFT, RIGHT_SHIFT, 
	MOD,
	LT, GT, LEQ, GEQ, EQ, NEQ,
	AND, OR, NOT,
	UNARY_MINUS
} type_op;

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
				return "Eq";
			case OR:
				return "Or";
			default:
				return "None";
		}
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
};

/// Constant Expressions 
/// - For String, Int and Boolean values
class Constant_Expr : public decafAST {
	string val_rep;
	val_type const_type;
public:
	Constant_Expr(string ** val, val_type type) : val_rep(*(*val)), const_type(type){
		delete *val;
	}
	~Constant_Expr() {}
	string str() {
		switch (const_type)
		{
			case STRINGTYPE:
				return "StringConstant(" + val_rep + ")";
			case INTTYPE:
				return "NumberExpr(" + val_rep + ")";
			case BOOLTYPE:
				return "BoolExpr(" + val_rep + ")";
			default:
				return "None";
		}
	}
	string get_num() {
		if(const_type == INTTYPE) {
			return val_rep;
		}
		else {
			return "None";
		}
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
};

class Unary_Expr: public decafStmtList {
public: 
	Unary_Expr(decafAST * val, Unary_Operator * op) : decafStmtList() {
		push_back(op);
		push_back(val);
	}
	string str() {
		return "UnaryExpr(" + decafStmtList::str() + ")";
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
};

class Var_Expr: public decafAST{
	Identifier * identifier;
public:
	Var_Expr(Identifier * id) : identifier(id) {}
	~Var_Expr() { if(identifier) {delete identifier;}}
	string str() {
		return "VariableExpr(" + getString(identifier) + ")";
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
	}
	string str() {
		return "MethodCall(" + decafStmtList::str() + ")";
	}
};

// Variable declarations
class Var_Def : public decafStmtList {
public:
	Var_Def(decafAST * identifier, Type * type) : decafStmtList() {
		push_back(identifier);
		push_back(type);
	}
	Var_Def(Identifier_List ** identifiers, Type * type) : decafStmtList() {
		list<Identifier *> ids = (*identifiers)->get_list();
		for(list<Identifier *>::iterator i = ids.begin(); i != ids.end(); i++){
			Var_Def * var_def = new Var_Def(*i, type);
			push_back(var_def);
		}
		delete identifiers;
	}
	Var_Def(Type * type) : decafStmtList() {
		push_back(type);
	}
	string str() {
		return "VarDef(" + decafStmtList::str() + ")";
	}
};

class Var_Def_List: public decafStmtList {
public:
	Var_Def_List(Identifier_List ** identifiers, Type * type) : decafStmtList() {
		list<Identifier *> ids = (*identifiers)->get_list();
		for(list<Identifier *>::iterator i = ids.begin(); i != ids.end(); i++){
			Var_Def * var_def = new Var_Def(*i, type);
			push_back(var_def);
		}
		delete identifiers;
	}
	string str() {
		return decafStmtList::str();
	}
};

/// Field declarations
class Field_Size : public decafAST {
	string size;
public: 
	Field_Size() {size = "";}
	Field_Size(Constant_Expr ** arr_size) {
		size = (*arr_size)->get_num();
		if(size == "None") {
			size = "";
		}
		delete *arr_size;
	}
	string str() {
		if(size == "") {
			return "Scalar";
		}
		return "Array(" + size + ")";
	}
};

class Field_Decl : public decafStmtList{
public:
	Field_Decl(Identifier * id, Type * type, Field_Size * sz) : decafStmtList(){
		push_back(id);
		push_back(type);
		push_back(sz);
	}
	string str() {
		return "FieldDecl(" + decafStmtList::str() + ")";
	}
};

class Field_Decl_List : public decafStmtList {
public:
	Field_Decl_List(Identifier_List ** identifiers, Type * type, Field_Size * sz) : decafStmtList() {
		list<Identifier *> ids = (*identifiers)->get_list();
		for(list<Identifier *>::iterator i = ids.begin(); i != ids.end(); i++){
			Field_Decl * field_def = new Field_Decl(*i, type, sz);
			push_back(field_def);
		}
		delete identifiers;
	}
	string str() {
		return decafStmtList::str();
	}
};

class Assign_Global : public decafStmtList {
public:
	Assign_Global(Identifier * identifier, Type * type, Constant_Expr * const_expr) : decafStmtList() {
		push_back(identifier);
		push_back(type);
		push_back(const_expr);
	}
	string str() {
		return "AssignGlobalVar(" + decafStmtList::str() + ")";
	}
};

/* Blocks and Method Blocks */
class Block : public decafStmtList {
	bool if_method;
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
	string get_content() {
		return decafStmtList::str();
	}
};


/// If else, For, While
class If_Else: public decafStmtList {
public: 
	If_Else(decafAST * expr, Block * if_blk) : decafStmtList() {
		push_back(expr);
		push_back(if_blk);
	}
	If_Else(decafAST * expr, Block * if_blk, Block * else_blk) : decafStmtList() {
		push_back(expr);
		push_back(if_blk);
		push_back(else_blk);
	}
	string str() {
		return "IfSmt(" + decafStmtList::str() + ")";
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
};

class Continue: public decafAST {
public:
	Continue() {}
	~Continue() {}
	string str() {
		return "ContinueStmt";
	}
};

class Break: public decafAST {
public:
	Break() {}
	~Break() {}
	string str() {
		return "BreakStmt";
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
};

class Method_Decl: public decafStmtList {
	public:
	Method_Decl(Identifier * id, Type * return_type, 
	decafAST * param_list, Block * block)
	: decafStmtList() {
		block->set_to_method(true);
		push_back(id);
		push_back(return_type);
		push_back(param_list);
		push_back(block);
	}
	string str() {
		return "Method(" + decafStmtList::str() + ")";
	}
};