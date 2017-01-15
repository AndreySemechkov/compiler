/*
 * Symbol.cpp
 *
 *  Created on: Dec 30, 2015
 *      Author: elad
 */

#include <string>
#include <iostream>
#include "Symbol.hpp"
#include "Common.hpp"

using namespace std;

Symbol::Symbol(int size, bool isArray) :
type(INTEGER),
size(size),
offset(globalCurrentScopeOffset),
isArray_(isArray)
{
	globalCurrentScopeOffset += size;
}


Symbol::Symbol(Type type,int size, bool isArray) :
type(type),
size(size),
offset(globalCurrentScopeOffset),
isArray_(isArray)
{
	globalCurrentScopeOffset += size;
}

Symbol::~Symbol() {}

Type Symbol::getType() {
	return type;
}

void Symbol::setType(Type type) {
	this->type = type;
}

int Symbol::getOffset() const {
	return offset;
}

void Symbol::setOffset(int offset) {
	this->offset = offset;
}

int Symbol::getSize() const {
	return size;
}

void Symbol::setSize(int size) {
	this->size = size;
}

void mergeSymbolTables(std::map<SymbolName, pSymbol>& tableA,
		std::map<SymbolName, pSymbol>& tableB,
		std::map<SymbolName, pSymbol>& tableC)
{
	// insert tableA:
	tableC.insert(tableA.begin(), tableA.end());

	// insert tableB - merge names:
	for(std::map<SymbolName, pSymbol>::iterator itr = tableB.begin(); itr != tableB.end(); itr++ ) {
		std::cout << "merge: " << itr->first << std::endl;
		if (tableC.find(itr->first) == tableC.end()) {
			tableC[itr->first] = itr->second;
		}
		else {
			// found conflicting types!
			std::cout << "Error" << std::endl;
		}
	}
	// erase all elements:
	tableA.erase(tableA.begin(), tableA.end());
	tableB.erase(tableB.begin(), tableB.end());

}

void copySymbolTable(std::map<SymbolName, pSymbol>& tableSrc,
		std::map<SymbolName, pSymbol>& tableDst)
{
	tableDst.insert(tableSrc.begin(), tableSrc.end());
	tableSrc.erase(tableSrc.begin(), tableSrc.end());
}

bool Symbol::isArray() const {
	return isArray_;
}

void Symbol::setIsArray(bool isArray) {
	this->isArray_ = isArray;
}
