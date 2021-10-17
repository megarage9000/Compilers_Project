
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

/// Constant Expressions 
/// - For String, Int and Boolean values
typedef enum {
	STRING, INT, BOOL, CHAR
} const_type;

class Constant_Expr : public decafAST {
	string val_rep;
	const_type val_type;
public:
	Constant_Expr(string * val, const_type val_type) : val_rep(*val), val_type(val_type){}
	~Constant_Expr(){}
	string str() {
		string return_val;
		switch (val_type){
			case STRING:
				return_val = "StringConstant(";
				break;
			case INT:
				return_val = "NumberExpr(";
				break;
			case BOOL:
				return_val = "BoolExpr(";
				break;
			case CHAR:
				return_val = "CharExpr(";
				break;
			default:
				// TODO, handle error
				return_val = "(";
				break;
		}
		return return_val + val_rep + ")";
	}
};

/// Operator Expressions
typedef enum {
	PLUS, MINUS, MULT, DIV, 
	LEFT_SHIFT, RIGHT_SHIFT, 
	MOD,
	LT, GT, LEQ, GEQ, EQ, NEQ,
	AND, OR, NOT,
	UNARY_MINUS
} type_op;

class Binary_Expr : public decafAST {
	type_op operator_type;
	decafAST * left_val;
	decafAST * right_val;
public:
	Binary_Expr(decafAST * l_val, decafAST * r_val, type_op op) : left_val(l_val), right_val(r_val), operator_type(op) {}
	~Binary_Expr() {
		if (left_val) {delete left_val;}
		if (right_val) {delete right_val;}
	}
	string str() {
		string return_val = "BinaryExpr(";
		switch(operator_type) {
			case PLUS:
				return_val += "Plus,";
				break;
			case MINUS:
				return_val += "Minus,";
				break;
			case MULT:
				return_val += "Mult,";
				break;
			case DIV:
				return_val += "Div,";
				break;
			case LEFT_SHIFT:
				return_val += "Leftshift,";
				break;
			case RIGHT_SHIFT:
				return_val += "Rightshift,";
				break;
			case MOD:
				return_val += "Mod,";
				break;
			case LT:
				return_val += "Lt,";
				break;
			case GT:
				return_val += "Gt,";
				break;
			case LEQ:
				return_val += "Leq,";
				break;
			case GEQ:
				return_val += "Geq,";
				break;
			case EQ:
				return_val += "Eq,";
				break;
			case NEQ:
				return_val += "Neq,";
				break;
			case AND:
				return_val += "Eq,";
				break;
			case OR:
				return_val += "Or,";
				break;
			default:
				// TODO handle error
				return_val += "None,";
				break;
		}
		return return_val + getString(left_val) + "," + getString(right_val) + ")";
	}
};

class Unary_Expr: public decafAST {
	decafAST * value;
	type_op operator_type;
public:
	Unary_Expr(decafAST * val, type_op op) : value(val), operator_type(op) {}
	~Unary_Expr() {
		if (value) {delete value;}
	}
	string str() {
		string return_val = "UnaryExpr(";
		switch (operator_type) {
			case UNARY_MINUS:
				return_val += "UnaryMinus,";
				break;
			case NOT:
				return_val += "Not,";
				break;
			default:
				// TODO handle error
				return_val += "None,";
				break;
		}
		return return_val + getString(value) + ")";
	}
};

/// Variable / Array Assignments and Expressions
class Assign_Var: public decafAST {
	decafAST * value;
	string identifier;
public:
	Assign_Var(string * id, decafAST * val) : value(val), identifier(*id) {}
	~Assign_Var() {
		if(value) { delete value; }
	}
	string str() {
		return "AssignVar(" + identifier + "," + getString(value) + ")";
	}	
};

class Assign_Arr_Loc: public decafAST {
	decafAST * value;
	decafAST * index;
	string identifier;
public:
	Assign_Arr_Loc(string * id, decafAST * loc, decafAST * val) : identifier(*id), index(loc), value(val) {}
	~Assign_Arr_Loc() {
		if(value) { delete value; }
		if(index) { delete index; }
	}
	string str() {
		return "AssignArrayLoc(" + identifier + "," + getString(index) + "," + getString(value) + ")";
	}
};

class Var_Expr: public decafAST {
	string identifier;
public:
	Var_Expr(string * id) : identifier(*id) {}
	~Var_Expr() {}
	string str() {
		return "VariableExpr(" + identifier + ")";
	}	
};

class Arr_Loc_Expr: public decafAST {
	decafAST * index;
	string identifier;
public:
	Arr_Loc_Expr(string * id, decafAST * loc) : identifier(*id), index(loc){}
	~Arr_Loc_Expr() {
		if(index) { delete index; }
	}
	string str() {
		return "ArrayLocExpr(" + identifier + "," + getString(index) + ")";
	}
};

/// Methods
class Method_Call: public decafAST {
	// Use statement list for method_args
	decafStmtList * method_args;
	string identifier;
public:
	Method_Call(string * id, decafStmtList * args_list): identifier(*id), method_args(args_list) {}
	Method_Call(string * id, decafAST * single_arg): identifier(*id) {
		method_args = new decafStmtList();
		method_args->push_back(single_arg);
	}
	Method_Call(string * id) : identifier(*id), method_args(NULL) {}
	~Method_Call(){
		if(method_args) { delete method_args; }
	}
	string str() {
		if(!method_args) {
			return "MethodCall(" + identifier + ")";
		}
		return "MethodCall(" + identifier +"," + getString(method_args) + ")";
	}
};