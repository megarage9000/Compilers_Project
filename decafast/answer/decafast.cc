
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

// /// Variable / Array Assignments and Expressions
// class Assign_Var: public decafAST {
// 	decafAST * value;
// 	string identifier;
// public:
// 	Assign_Var(string ** id, decafAST * val) : value(val), identifier(*(*id)) {
// 		delete *id;
// 	}
// 	~Assign_Var() {
// 		if(value) { delete value; }
// 	}
// 	string str() {
// 		return "AssignVar(" + identifier + "," + getString(value) + ")";
// 	}	
// };

// class Assign_Arr_Loc: public decafAST {
// 	decafAST * value;
// 	decafAST * index;
// 	string identifier;
// public:
// 	Assign_Arr_Loc(string ** id, decafAST * loc, decafAST * val) : identifier(*(*id)), index(loc), value(val) {
// 		delete *id;
// 	}
// 	~Assign_Arr_Loc() {
// 		if(value) { delete value; }
// 		if(index) { delete index; }
// 	}
// 	string str() {
// 		return "AssignArrayLoc(" + identifier + "," + getString(index) + "," + getString(value) + ")";
// 	}
// };

// class Var_Expr: public decafAST {
// 	string identifier;
// public:
// 	Var_Expr(string ** id) : identifier(*(*id)) {
// 		delete *id;
// 	}
// 	~Var_Expr() {}
// 	string str() {
// 		return "VariableExpr(" + identifier + ")";
// 	}	
// };

// class Arr_Loc_Expr: public decafAST {
// 	decafAST * index;
// 	string identifier;
// public:
// 	Arr_Loc_Expr(string ** id, decafAST * loc) : identifier(*(*id)), index(loc){
// 		delete *id;
// 	}
// 	~Arr_Loc_Expr() {
// 		if(index) { delete index; }
// 	}
// 	string str() {
// 		return "ArrayLocExpr(" + identifier + "," + getString(index) + ")";
// 	}
// };

// /// Methods
// class Method_Call: public decafAST {
// 	// Use statement list for method_args
// 	decafStmtList * method_args;
// 	string identifier;
// public:
// 	Method_Call(string ** id, decafStmtList * args_list): identifier(*(*id)), method_args(args_list) {
// 		delete *id;
// 	}
// 	Method_Call(string ** id, decafAST * single_arg): identifier(*(*id)) {
// 		method_args = new decafStmtList();
// 		method_args->push_back(single_arg);
// 		delete *id;
// 	}
// 	Method_Call(string ** id) : identifier(*(*id)), method_args(NULL) {
// 		delete *id;
// 	}
// 	~Method_Call(){
// 		if(method_args) { delete method_args; }
// 	}
// 	string str() {
// 		if(!method_args) {
// 			return "MethodCall(" + identifier + ")";
// 		}
// 		return "MethodCall(" + identifier +"," + getString(method_args) + ")";
// 	}
// };

// // Variable declarations
// class Typed_Symbol : public decafAST {
// 	string identifier;
// 	const_type sym_type;
// public:
// 	Typed_Symbol(string ** id, const_type type) : identifier(*(*id)), sym_type(type) {
// 		delete *id;
// 	}
// 	Typed_Symbol(string id , const_type type) : identifier(id), sym_type(type) {}
// 	Typed_Symbol(const_type type) : identifier(""), sym_type(type) {}
// 	~Typed_Symbol() {}
// 	string str() {
// 		string returnVal = "VarDef(";
// 		if(identifier != "") {
// 			returnVal += identifier + ",";
// 		}
// 		switch (sym_type) {
// 			case INT:
// 				return returnVal + "IntType)";
// 				break;
// 			case STRING:
// 				return returnVal + "StringType)";
// 				break;
// 			case BOOL:
// 				return returnVal + "BoolType)";
// 				break;
// 			default:
// 				break;
// 		}
// 		return returnVal;
// 	}
// 	string getIdentifier() { return identifier; }
// 	const_type getType()   { return sym_type; }
// }; 

// // Special case of multiple statements
// class Untyped_Symbol {
// 	string identifier;
// public:
// 	Untyped_Symbol(string ** id) : identifier(*(*id)) {
// 		delete *id;
// 	}
// 	~Untyped_Symbol() {}
// 	string getId() { return identifier; }
// };

// class Untyped_Symbols {
// 	list<Untyped_Symbol*> values;
// public:
// 	Untyped_Symbols() {}
// 	~Untyped_Symbols() {
// 		for(Untyped_Symbol * sym: values) {
// 			delete sym;
// 		}
// 	}
// 	void push_back(Untyped_Symbol * symbol) { values.push_back(symbol);}
// 	void push_front(Untyped_Symbol * symbol) { values.push_front(symbol);}
// 	list<Untyped_Symbol*> getSymbols() { return values; }
// };

// decafStmtList * createTypedSymbolList(Untyped_Symbols ** untyped_syms_ptr, const_type type) {
// 	decafStmtList * typed_syms = new decafStmtList();
// 	Untyped_Symbols * untyped_syms = *untyped_syms_ptr;
// 	list<Untyped_Symbol *> untyped_vals = untyped_syms->getSymbols();
// 	for(list<Untyped_Symbol *>::iterator it = untyped_vals.begin(); it != untyped_vals.end(); ++it) {
// 		typed_syms->push_back(new Typed_Symbol(
// 			(*it)->getId(),
// 			type
// 		));
// 	}
// 	delete *(untyped_syms_ptr);
// 	return typed_syms;
// }

// typedef enum {SCALAR, ARRAY} field_size;

// class Field_Decl : public decafAST{
// 	field_size size;
// 	string identifier;
// 	const_type sym_type;
// 	string val_size;
// public:
// 	Field_Decl(Typed_Symbol * declaration, field_size sz) 
// 	: identifier(declaration->getIdentifier()), sym_type(declaration->getType()), size(sz) {val_size="";}
// 	Field_Decl(string ** id, const_type type, field_size sz) 
// 	: identifier(*(*id)), sym_type(type), size(sz) {val_size=""; delete *id;}
// 	Field_Decl(Typed_Symbol * declaration, field_size sz, string v_size) 
// 	: identifier(declaration->getIdentifier()), sym_type(declaration->getType()), size(sz), val_size(v_size) {}
// 	Field_Decl(string ** id, const_type type, field_size sz, string v_size) 
// 	: identifier(*(*id)), sym_type(type), size(sz), val_size(v_size) { delete *id;}	
// 	~Field_Decl() {}
// 	string str() {
// 		string returnVal = "FieldDecl(";
// 		if(identifier != "") {
// 			returnVal += identifier + ",";
// 		}
// 		switch (sym_type) {
// 			case INT:
// 				returnVal += "IntType";
// 				break;
// 			case STRING:
// 				returnVal += "StringType";
// 				break;
// 			case BOOL:
// 				returnVal += "BoolType";
// 				break;
// 			default:
// 				break;
// 		}
// 		if(size == SCALAR) {
// 			returnVal += ",Scalar)";
// 		}
// 		else if (val_size != ""){
// 			returnVal += ",Array(" + val_size + "))";
// 		}
// 		return returnVal;
// 	}
// };

// decafStmtList * createFieldDeclList(decafStmtList * typed_syms) {
// 	decafStmtList * field_decls = new decafStmtList();
// 	list<decafAST *> typed_vals = typed_syms->values();

// 	for(list<decafAST *>::iterator it = typed_vals.begin(); it != typed_vals.end(); ++it) {
// 		Typed_Symbol * symbol = dynamic_cast<Typed_Symbol *>(*it);
// 		field_decls->push_back(new Field_Decl(symbol, SCALAR));
// 	}
// 	delete typed_syms;
// 	return field_decls;
// }

// decafStmtList * createFieldDeclListArr(decafStmtList * typed_syms, string size) {
// 	decafStmtList * field_decls = new decafStmtList();
// 	list<decafAST *> typed_vals = typed_syms->values();

// 	for(list<decafAST *>::iterator it = typed_vals.begin(); it != typed_vals.end(); ++it) {
// 		Typed_Symbol * symbol = dynamic_cast<Typed_Symbol *>(*it);
// 		field_decls->push_back(new Field_Decl(symbol, ARRAY, size));
// 	}
// 	delete typed_syms;
// 	return field_decls;
// }

// class Assign_Global : public decafAST {
// 	string identifier;
// 	string value;
// 	const_type sym_type;
// public:
// 	Assign_Global(Typed_Symbol * declaration, string val):
// 	identifier(declaration->getIdentifier()), sym_type(declaration->getType()), value(val) {}
// 	Assign_Global(string id, const_type type, string val):
// 	identifier(id), sym_type(type), value(val) {}
// 	~Assign_Global() {}
// 	string str() {
// 		string returnVal = "AssignGlobalVar(" + identifier + ",";
// 		switch (sym_type) {
// 			case INT:
// 				returnVal += "IntType";
// 				break;
// 			case STRING:
// 				returnVal += "StringType";
// 				break;
// 			case BOOL:
// 				returnVal += "BoolType";
// 				break;
// 			default:
// 				break;
// 		}
// 		returnVal += "," + value + ")";
// 		return returnVal;
// 	}
// };

// /* Blocks and Method Blocks */
// class Block : public decafAST {
// public:
// 	decafStmtList * variable_decls;
// 	decafStmtList * statement_list;
// 	Block(decafStmtList * decls, decafStmtList * stmts) : variable_decls(decls), statement_list(stmts) {}
// 	// Handle cases where there is either one declaration or one statement in the block only
// 	Block(decafAST * declaration, decafStmtList * stmts) {
// 		statement_list = stmts;
// 		variable_decls = new decafStmtList();
// 		if(declaration) {variable_decls->push_front(declaration);}
		
// 	}
// 	Block(decafStmtList * decls, decafAST * statement) {
// 		variable_decls = decls;
// 		statement_list = new decafStmtList();
// 		if(statement) {statement_list->push_front(statement);}
// 	}
// 	// If only one statement and one declaration
// 	Block(decafAST * declaration, decafAST * statement) {
// 		variable_decls = new decafStmtList();
// 		if(declaration) {variable_decls->push_front(declaration);}
// 		statement_list = new decafStmtList();
// 		if(statement) {statement_list->push_front(statement);}
// 	}
// 	~Block() {
// 		if(variable_decls) { delete variable_decls; }
// 		if(statement_list) { delete statement_list; }
// 	}
// 	string str() {
// 		return "Block(" + getString(variable_decls) + "," + getString(statement_list) + ")";
// 	}
// };

// class Method_Block : public decafAST {
// 	decafStmtList * variable_decls;
// 	decafStmtList * statement_list;
// public:
// 	Method_Block(Block ** block) {
// 		variable_decls = (*block)->variable_decls;
// 		statement_list = (*block)->statement_list;
// 		delete (*block);
// 	}
// 	~Method_Block() {
// 		if(variable_decls) { delete variable_decls; }
// 		if(statement_list) { delete statement_list; }
// 	}
// 	string str() {
// 		return "MethodBlock(" + getString(variable_decls) + "," + getString(statement_list) + ")";
// 	}
// };


// /// If else, For, While
// class If_Else: public decafAST {
// 	decafAST * expression;
// 	Block * if_block;
// 	Block * else_block;
// public: 
// 	If_Else(decafAST * expr, Block * if_blk) 
// 	: expression(expr), if_block(if_blk) {}
// 	~If_Else() {
// 		if(expression) {delete expression;}
// 		if(if_block) {delete if_block;}
// 		if(else_block) {delete else_block;}
// 	}
// 	void setElse(Block * else_blk) {
// 		else_block = else_blk;
// 	}
// 	string str() {
// 		if(else_block){
// 			return "IfSmt(" + getString(expression) + "," + getString(if_block) + "," + getString(else_block) + ")";
// 		}
// 		return "IfSmt(" + getString(expression) + "," + getString(if_block) + ")";
// 	}
// };

// /// At this point, most loops are decafstmtlists
// class For_Loop: public decafAST {
// 	decafStmtList * data;
// public:
// 	For_Loop(decafAST * assign, decafAST * expression, decafAST * after_assign, Block * block) {
// 		data = new decafStmtList();
// 		data->push_back(assign);
// 		data->push_back(expression);
// 		data->push_back(after_assign);
// 		data->push_back(block);
// 	}
// 	~For_Loop() {
// 		if(data) { delete data; }
// 	}
// 	string str() {
// 		return "ForStmt(" + getString(data) + ")";
// 	}
// };

// class While_Loop: public decafAST {
// 	decafStmtList * data;
// public:
// 	While_Loop(decafAST * expression, Block * block) {
// 		data = new decafStmtList();
// 		data->push_back(expression);
// 		data->push_back(block);
// 	}
// 	~While_Loop() {
// 		delete data;
// 	}
// 	string str() {
// 		return "WhileStmt(" + getString(data) + ")";
// 	}
// };

// /// Keywords
// class Return_Stmt: public decafAST {
// 	decafStmtList * structure;
// public:
// 	Return_Stmt() {
// 		structure = new decafStmtList();
// 	}
// 	Return_Stmt(decafAST * returnVal) {
// 		structure = new decafStmtList();
// 		structure->push_back(returnVal);
// 	}
// 	~Return_Stmt() {
// 		if(structure) {delete structure;}
// 	}
// 	string str() {
// 		return "ReturnStmt(" + getString(structure) + ")";
// 	}
// };

// class Continue: public decafAST {
// public:
// 	Continue() {}
// 	~Continue() {}
// 	string str() {
// 		return "ContinueStmt";
// 	}
// };

// class Break: public decafAST {
// public:
// 	Break() {}
// 	~Break() {}
// 	string str() {
// 		return "BreakStmt";
// 	}
// };

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