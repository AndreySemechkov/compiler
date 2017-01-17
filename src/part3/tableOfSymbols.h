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

#include "definitions.h"

namespace std {

typedef struct symbol_{

	t_type type;

	/*  scope < currentTableScopeID this symbol is from the son scope of this table
     *  scope = currentTableScopeID this symbol is from initial function scope of this table
     *  scope > currentTableScopeID this symbol is from fathers scope of this table
     * */
	int scopeID;

} symbol;

typedef shared_ptr<symbol> spSymbol;
typedef shared_ptr<TableOfSymbols> spCurrTableOfSymbols;


class TableOfSymbols {
private:
    map<string,spSymbol> scopeMap;
    int currentTableScopeID;
public:
	TableOfSymbols(int ID){
		currentTableScopeID = ID;
	}

	~TableOfSymbols(){
		//map<string,pSymbol>::
		//delete symbols
	};

	int getTableID() const{
		return currentTableScopeID;
	}

	int getTableSize() const{
		return scopeMap.size();
	}
	/*
	void addSymbol(){

	}
    */
};


} /* namespace std */



#endif /* SRC_PART3_TABLEOFSYMBOLS_H_ */
