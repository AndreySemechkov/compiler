/*
 * Function.h
 *
 *  Created on: Jan 21, 2017
 *      Author: compm
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <vector>
#include <list>
#include "definitions.h"
#include <string>
#include <map>

using namespace std;

//this is in minus...
//Fixme: TODO:
#define INITIAL_OFFSET 2
#define UNDEFINED_START_LINE 99


typedef struct {
	string name;
	t_type type;
    int offset;
} FunctionSymbol;

class Function {
public:
	t_type returnType;
	string name;


	map<string,FunctionSymbol> m_symbols;
	std::list<FunctionSymbol> m_symbols_list;
	std::list<t_type> m_types;

	int startLine; // for implemeneted functions
    int offset;

    std::vector<int> calledFromLines; // for unimplemented functions
    bool implemented; // true of the function was implemented in the file

	void addSymbol(FunctionSymbol s) throw(string){

		if(m_symbols.find(s.name) != m_symbols.end() ){
			throw "Bad function declaration: multiple definitions of arg '" + s.name + "'";
		}
		//insert
		m_symbols.insert(std::make_pair(s.name,s));
		m_symbols_list.push_back(s);
		m_types.push_back(s.type);
	}

};

#endif /* FUNCTION_H_ */
