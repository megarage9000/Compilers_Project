
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

typedef enum {
	INTTYPE,
	BOOLTYPE,
	STRINGTYPE
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
	Var_Def(decafAST * identifiers, Type * type) : decafStmtList() {
		push_back(identifiers);
		push_back(type);
	}
	string str() {
		return "VarDef(" + decafStmtList::str() + ")";
	}
	// For Field delarations, since FieldDecl and VarDef are similar
	string get_structure() {
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

class Field_Decl : public decafAST{
	Field_Size * size;
	Var_Def * symbols;
public:
	Field_Decl(Var_Def * syms, Field_Size * sz) : symbols(syms), size(sz){}
	~Field_Decl() {
		if(size) {delete size;}
		if(symbols) {delete symbols;}
	}
	string str() {
		return "FieldDecl(" + symbols->get_structure() + "," + size->str() + ")";
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
public:
	Block(decafAST * declarations, decafAST * statements) : decafStmtList() {
		push_back(declarations);
		push_back(statements);
	}
	string str() {
		return "Block(" + decafStmtList::str() + ")";
	}
	string get_content() {
		return decafStmtList::str();
	}
};

class Method_Block : public decafAST {
	Block * content;
public:
	Method_Block(Block * block) {
		content = block;
	}
	~Method_Block() {
		if(content) {delete content;}
	}
	string str() {
		return "MethodBlock(" + content->get_content() + ")";
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
class Return_Stmt: public decafStmtList {
public:
	Return_Stmt() : decafStmtList(){}
	Return_Stmt(decafAST * returnVal) : decafStmtList() {
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
// class Extern_Func: public  decafAST {
// 	decafStmtList * structure;
// public:
// 	Extern_Func(decafAST * ID, decafAST * return_type, decafAST * typeList){}
// 	~Extern_Func() {
// 		if(structure) {delete structure;}
// 	}
// 	string str() {
// 		return "ExternFunction(" + getString(structure) + ")";
// 	}
// };