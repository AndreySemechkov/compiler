/*
 * tableOfSymbols.cpp
 *
 *  Created on: Jan 16, 2017
 *      Author: Andrey
 */

#include "tableOfSymbols.h"

namespace std {

    TableOfSymbols::TableOfSymbols(){
		currentTableScopeID = 0;
	}

    TableOfSymbols::~TableOfSymbols(){
		/*
    	std::map<string,pSymbol>::iterator it;
		for (it = scopeMap.begin(); it != scopeMap.end(); it++) {
			//when using shared_ptr to hold each symbol , releasing each symbol safely
			//it->second.reset();
			delete it->second;
		}
		*/
	};

	int TableOfSymbols::getTableID() const{
		return currentTableScopeID;
	}

	int TableOfSymbols::getTableSize() const{
		return scopeMap.size();
	}

	// returns true if a symbol is a struct
	bool TableOfSymbols::isStruct(string name){
		map<string,stack<symbol>>::iterator it = this->scopeMap.find(name);

		if(it != this->scopeMap.end()){
			if(it->second.empty()){
				cerr << " stack requested empty"<< endl;
			    return false;
			}
			return (it->second.top().type==structType);
		}

		throw "this symbol is not in table";
		return false;
	}
//TODO :add a end() iterator defence
		// tells whether a symbol is in the table in the current scope
	bool TableOfSymbols::find(string name){
		map<string,stack<symbol>>::iterator it = this->scopeMap.find(name);
		return !it->second.empty();
	}

		// returns the type of symbol named name from the table in the current scope
	t_type TableOfSymbols::getType(string name){
		map<string,stack<symbol>>::iterator it = this->scopeMap.find(name);
		return !it->second.top().type;
	}

		// returns the address of symbol named name from the table in the current scope
	int TableOfSymbols::getAddr(string name){
		map<string,stack<symbol>>::iterator it = this->scopeMap.find(name);
		return !it->second.top().address;
	}

	// adds a new symbol name name to the current scope
	void TableOfSymbols::addSymbol (string name, t_type symType,int address) {

		map<string,stack<symbol>>::iterator it = this->scopeMap.find(name);
		// new symbol, not previously declared
		if( it == this->scopeMap.end() ) {
			symbol sym;
			sym.scopeID = currentTableScopeID;
			sym.type = symType;
		    sym.address = address;
		    scopeMap[name].push(sym);

		    // where here so there was a symbol called name in the past
		}else if (it->second.empty()){
			cerr << "error: symbol named " + name + "was popped from its stack" << endl;

			// Table scope closing error: symbol named   name has scope less than current this symbol should have been deleted earlier
		}else if (it->second.top().scopeID < currentTableScopeID){
		    cerr << "error: symbol named " + name + " has scope less than current when addSymbol tried to add another symbol" <<endl;
			//throw "error: symbol named " + name + " has scope less than current when addSymbol tried to add another symbol";

		    // error: user tried to declare the same symbol twice
		}else if (it->second.top().scopeID == currentTableScopeID){
			throw "semantic scope error: symbol named " + name + " user tried to declare the same symbol twice in the same scope";

			// this symbol has been declared in a bigger scope before, masking
		}else{ // prev.scopeID > currentTableScopeID
			symbol sym;
			sym.scopeID = currentTableScopeID;
			sym.type = symType;
		    sym.address = address;
		    it->second.push(sym);
		}
	}

	/*
	// removes a symbol and destroys
	void TableOfSymbols::removeSymbol (string name, int symbolScopeID){

	}
    */

	// opens a new  inner blokc scope with the variables from the father scope.
	void TableOfSymbols::startNewScope(){
        currentTableScopeID--;
	}

		// deletes all local scope variables, ends the current scope and updates table to father scope symbols
	void TableOfSymbols::endScope(){
	    for(map<string,stack<symbol>>::iterator it = this->scopeMap.begin(); it != this->scopeMap.end(); it++){
            if( it->second.top().scopeID <= this->currentTableScopeID ){
            	it->second.pop();
            	if(it->second.empty())
                    this->scopeMap.erase(it);
            }
	    }
		currentTableScopeID++;
	}

} /* namespace std */
