/*
 * tableOfSymbols.cpp
 *
 *  Created on: Jan 16, 2017
 *      Author: Andrey
 */

#include "tableOfSymbols.h"
#include <cassert>

TableOfSymbols::TableOfSymbols() {
	this->currentTableScopeID = 0;
	this->parsingDeclerations = false;
}

TableOfSymbols::~TableOfSymbols() {
}
;

int TableOfSymbols::getTableID() const {
	return this->currentTableScopeID;
}

int TableOfSymbols::getTableSize() const {
	return this->scopeMap.size();
}

// returns true if a symbol is a struct
bool TableOfSymbols::isStruct(string name) const throw (string) {
	map<string, stack<symbol>>::const_iterator it = this->scopeMap.find(name);

	if (it != this->scopeMap.end()) {
		if (it->second.empty()) {
			cerr << " stack requested empty" << endl; //TODO: change cerr to exceptions and handle above
			throw name;
			return false;
		}
		return (it->second.top().type == structType);
	}
	cerr << "error: " + name + " was not found in table" + '\n'; //TODO cerr
	throw name;
}

// tells whether a symbol is in the table in the current scope
bool TableOfSymbols::find(string name) const {
	map<string, stack<symbol>>::const_iterator it = this->scopeMap.find(name);
	return it != this->scopeMap.end() && !it->second.empty();
}

// returns the type of symbol named name from the table in the current scope
t_type TableOfSymbols::getType(string name) const throw (string) {
	map<string, stack<symbol>>::const_iterator it = this->scopeMap.find(name);
	if (it == this->scopeMap.end())
		throw name;
	//throw " symbol " + name + " does not exist";
	return it->second.top().type;
}

// returns the address of symbol named name from the table in the current scope
int TableOfSymbols::getAddr(string name) const throw (string) {
	map<string, stack<symbol>>::const_iterator it = this->scopeMap.find(name);
	if (it == this->scopeMap.end())
		throw name;
	//throw " symbol " + name + " does not exist";

	if (this->currentTableScopeID == -1) {

		return it->second.top().address;

	} else {

		t_type tt = it->second.top().type;
		int sum = getBLKoffset(tt);

		return (it->second.top().address + sum);
	}

}

int TableOfSymbols::getBLKoffset(t_type typet) const {
	int delta = (-1 - this->currentTableScopeID);
	assert(delta > 0);
	//must be positive!
	std::list<int>::const_iterator IT2;
	std::list<int>::const_iterator IT3;

	if (typet == INT) {
		IT2 = this->BLKoffsets_INT.begin();
		IT3 = this->BLKoffsets_INT.end();
	} else if (typet == REAL) {
		IT2 = this->BLKoffsets_REAL.begin();
		IT3 = this->BLKoffsets_REAL.end();

	} else {
		assert(0); //ILLIGAL CALL!!!!
	}
	++IT2;
	int sum = 0;

	for (; IT2 != IT3; ++IT2) {
		sum += *IT2;
	}
	return sum;

}

/*
 void TableOfSymbols::print() const
 {
 cout << "current Table scope id: " + to_string(this->currentTableScopeID) << '\n';
 cout << "current Table symbols: " << '\n';
 for (map<string,stack<symbol>>::const_iterator it = scopeMap.begin(); it != scopeMap.end(); it++) {
 cout << "name: " + it->first << '\n' << " top symbol: ";
 it->second.top().print();
 }
 }
 */
// adds a new symbol name name to the current scope
void TableOfSymbols::addSymbol(string name, t_type symType, int address)
		throw (string) {
	printf("called with : %s %d \n", name.c_str(), symType);
	map<string, stack<symbol>>::iterator it = this->scopeMap.find(name);
	// new symbol, not previously declared
	if (it == this->scopeMap.end()) {
		symbol sym;
		sym.scopeID = this->currentTableScopeID;
		sym.type = symType;
		sym.address = address;
		this->scopeMap[name].push(sym);

		//debug
		//map<string,stack<symbol>>::iterator it = this->scopeMap.find(name);
		//cout << "added symbol: " << '\n';
		//it->second.top().print();

		// where here so there was a symbol called name in the past
	} else if (it->second.empty()) {
		//owr internal error
		cerr << "error: symbol named " + name + "was popped from its stack"
				<< endl; //TODO : replace cerr with agreed exceptions handling
		throw name;
		// Table scope closing error: symbol named   name has scope less than current this symbol should have been deleted earlier
	} else if (it->second.top().scopeID < this->currentTableScopeID) {
		cerr
				<< "error: symbol named " + name
						+ " has scope less than current when addSymbol tried to add another symbol"
				<< endl;
		throw name;

		// error: user tried to declare the same symbol twice
	} else if (it->second.top().scopeID == this->currentTableScopeID) {
		cerr
				<< "semantic scope error: symbol named " + name
						+ " user tried to declare the same symbol twice in the same scope";
		throw name;

		// this symbol has been declared in a bigger scope before, masking
	} else { // prev.scopeID > this->currentTableScopeID
		symbol sym;
		sym.scopeID = this->currentTableScopeID;
		sym.type = symType;
		sym.address = address;
		it->second.push(sym);

		//debug
		//		    map<string,stack<symbol>>::iterator it = this->scopeMap.find(name);
		// 		    cout << "added symbol: " << '\n';
		//		    it->second.top().print();
	}
}

// opens a new  inner blokc scope with the variables from the father scope.
void TableOfSymbols::startNewScope(int spAddReal, int spAddInt) {

	this->BLKoffsets_INT.push_front(spAddInt);
	this->BLKoffsets_REAL.push_front(spAddReal);

	this->currentTableScopeID--;
}

// deletes all local scope variables, ends the current scope and updates table to father scope symbols
void TableOfSymbols::endScope(int *spAddReal, int *spAddInt) {
	for (map<string, stack<symbol>>::iterator it = this->scopeMap.begin();
			it != this->scopeMap.end(); it++) {
		if (it->second.top().scopeID <= this->currentTableScopeID) {
			// debug
			//cout << "deleted symbol: " << '\n';
			//it->second.top().print();

			it->second.pop();
			if (it->second.empty())
				this->scopeMap.erase(it++);
		}
	}

	*spAddReal = BLKoffsets_REAL.begin().operator *();
	*spAddInt = BLKoffsets_INT.begin().operator *();

	BLKoffsets_INT.pop_front();
	BLKoffsets_REAL.pop_front();

	this->currentTableScopeID++;
}

//added for supporting structs:

string TableOfSymbols::getTypeName(string name) const throw (string) {

	map<string, stack<symbol>>::const_iterator it = this->scopeMap.find(name);
	if (it == this->scopeMap.end())
		throw name;
	//throw " symbol " + name + " does not exist";
	return it->second.top().typeName;

}

int TableOfSymbols::getINTStartAddr(string name) const throw (string) {

	map<string, stack<symbol>>::const_iterator it = this->scopeMap.find(name);
	if (it == this->scopeMap.end())
		throw name;
	//throw " symbol " + name + " does not exist";

	if (this->currentTableScopeID == -1) {
		return it->second.top().m_INTstartAddr;
	} else {

		int sum = getBLKoffset(INT);
		return (it->second.top().m_INTstartAddr + sum);

	}

}

int TableOfSymbols::getREALStartAddr(string name) const throw (string) {

	map<string, stack<symbol>>::const_iterator it = this->scopeMap.find(name);
	if (it == this->scopeMap.end())
		throw name;
	//throw " symbol " + name + " does not exist";
	if (this->currentTableScopeID == -1) {

		return it->second.top().m_REALstartAddr;
	} else {
		int sum = getBLKoffset(REAL);
		return (it->second.top().m_REALstartAddr + sum);

	}

}

void TableOfSymbols::addSymbolStruct(string name, t_type symType,
		int INTaddress, int REALadress) throw (string) {

	map<string, stack<symbol>>::iterator it = this->scopeMap.find(name);
	// new symbol, not previously declared
	if (it == this->scopeMap.end()) {
		symbol sym;
		sym.scopeID = this->currentTableScopeID;
		sym.type = symType;
		sym.m_INTstartAddr = INTaddress;
		sym.m_REALstartAddr = REALadress;
		this->scopeMap[name].push(sym);

		//debug
		//map<string,stack<symbol>>::iterator it = this->scopeMap.find(name);
		//cout << "added symbol: " << '\n';
		//it->second.top().print();

		// where here so there was a symbol called name in the past
	} else if (it->second.empty()) {
		//our internal error
		cerr << "error: symbol named " + name + "was popped from its stack"
				<< endl; //TODO : replace cerr with agreed exceptions handling
		throw name;
		// Table scope closing error: symbol named   name has scope less than current this symbol should have been deleted earlier
	} else if (it->second.top().scopeID < this->currentTableScopeID) {
		cerr
				<< "error: symbol named " + name
						+ " has scope less than current when addSymbol tried to add another symbol"
				<< endl;
		throw name;

		// error: user tried to declare the same symbol twice
	} else if (it->second.top().scopeID == this->currentTableScopeID) {
		cerr
				<< "semantic scope error: symbol named " + name
						+ " user tried to declare the same symbol twice in the same scope";
		throw name;

		// this symbol has been declared in a bigger scope before, masking
	} else { // prev.scopeID > this->currentTableScopeID
		symbol sym;
		sym.scopeID = this->currentTableScopeID;
		sym.type = symType;
		sym.m_INTstartAddr = INTaddress;
		sym.m_REALstartAddr = REALadress;
		it->second.push(sym);

		//debug
		//		    map<string,stack<symbol>>::iterator it = this->scopeMap.find(name);
		// 		    cout << "added symbol: " << '\n';
		//		    it->second.top().print();
	}
}

