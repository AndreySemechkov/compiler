/*
 * Function.h
 *
 *  Created on: Jan 21, 2017
 *      Author: compm
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <vector>
#include "definitions.h"
#include <string>
#include <map>

using namespace std;



typedef struct {
	string name;
	t_type type;
    int offset;
} FunctionSymbol;

struct Function {
	string name;
	map<string,FunctionSymbol> m_symbols;
	std::vector<FunctionSymbol> m_symbols_list;
	std::vector<t_type> m_types;

	t_type returnType;
	int startLine;
	std::vector<int> calledFromLines;

	void addSymbol(FunctionSymbol s) throw(string){

		if(m_symbols.find(s.name) != m_symbols.end() ){
			throw "Illigal function multiple definitions of arg  " + s.name;
		}
		//insert
		m_symbols.insert(std::make_pair(s.name,s));
		m_symbols_list.push_back(s);
		m_types.push_back(s.type);
	}

};

#endif /* FUNCTION_H_ */
