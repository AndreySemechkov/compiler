/*
 * tableOfSymbols.hpp
 *
 *  Created on: Jan 16, 2017
 *      Author: Andrey
 *
 * TableOfSymbols contains the symbols of the current scope.
 * Symbols are structs that hold all symbol data.
 * TableOfSymbols is the scope container that maps string names to symbols.
 *
 * Scope identification is by using
 * the member int currentTableScopeID :
 * this is the member that all scope symbols scopeID are compared to.
 * currentTableScopeID will be set each time a new scope is initialised or when scope closed.
 *
 *
 *
 */

#ifndef TABLEOFSYMBOLS_H_
#define TABLEOFSYMBOLS_H_

#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <vector>

#include "definitions.h"

namespace std {

typedef struct symbol_{

	t_type type;

	/*  scope < currentTableScopeID this symbol is from the son scope of this table
     *  scope = currentTableScopeID this symbol is from initial function scope of this table
     *  scope > currentTableScopeID this symbol is from fathers scope of this table
     * */
	int scopeID;
    int address;
    //&vector<t_type>;
} symbol,*pSymbol;

//typedef shared_ptr<symbol> spSymbol;
//typedef shared_ptr<TableOfSymbols> spTableOfSymbols;


class TableOfSymbols {

private:
    /*map:  symbol name -> stack of symbols named: symbol name .
     * each node in the stack is a symbol with diffrent scope.
     * head of the stack->scopeID is equal to the current currentTableScopeID.
     *
     * */
	map<string,stack<symbol>> scopeMap;
	int currentTableScopeID;
/*
	// removes a symbol and destroys
	void removeSymbol (string name, int symbolScopeID,);
*/
public:

    TableOfSymbols();

	~TableOfSymbols();

	int getTableID() const;

	int getTableSize() const;

	// adds a new symbol named name to the current scope stack of this variable.
	void addSymbol(string name, t_type symType,int address);

	// opens a new scope with the variables from the father scope.
	void startNewScope();

	// deletes all local scope variables, ends the current scope and updates table.
	void endScope();

	// returns true if a symbol is a struct
	bool isStruct(string name);

	// tells whether a symbol is in the table in the current scope
	bool find(string name);

	// returns the type of symbol named name from the table in the current scope
	t_type getType(string name);

	// returns the address of symbol named name from the table in the current scope
	int getAddr(string name);
};


} /* namespace std */



#endif /* TABLEOFSYMBOLS_H_ */
