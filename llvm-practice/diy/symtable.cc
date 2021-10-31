#include "exprdefs.h"
#include <iostream>
#include <map>
#include <list>
/// Symbol table 
// TODO 
// -make the symbol table
// -add some llvm helpers
// -test symbol table
typedef std::map<std::string, llvm::Value*> symTable;
typedef std::list<symTable> symTableList;

static symTableList symbl_table_list;
static symTable main_sym_table;





