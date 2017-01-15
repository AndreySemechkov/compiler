#ifndef RX_H_
#define RX_H_

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "QuadBuffer.hpp"
#include "Symbol.hpp"

#define EXIT_LEXICAL_FAILURE 1
#define EXIT_SYNTAX_FAILURE 2
#define EXIT_SEMANTIC_FAILURE 3
#define EXIT_OPERATIONAL_FAILURE 9



const unsigned int TYPES_NUM = 2;

typedef struct
{
	Type type;
	std::string content;
	int registerNum;
	int offset;
	int quad;// quad - the line number of the line which comes after the
			//		  code of the variable.

	// BEXP attributes:
	std::vector<int> trueList;
	std::vector<int> falseList;

	// statements attributes:
	std::vector<int> nextList;

	// parameters lists for function calls:
	std::vector<int> paramRegisters;
	std::vector<Type> paramTypes;
} yystype;

#define YYSTYPE yystype

template <typename T>
std::vector<T> merge(std::vector<T>& vecA, std::vector<T>& vecB) {
	std::vector<T> result;
	result.reserve(vecA.size() + vecB.size()); // preallocate memory
	result.insert(result.end(), vecA.begin(), vecA.end());
	result.insert(result.end(), vecB.begin(), vecB.end());
	return result;
}

// global variables declarations:
extern QuadBuffer globalQuadBuffer;
extern int globalCurrentScopeRegisterCounter[TYPES_NUM];
extern int globalCurrentScopeOffset; // offset compared to I1.
extern Type globalCurrentReturnType;
extern std::vector<std::string> globalParamInsertionOrder;
extern bool globalIsMain; // is main being parsed?












































#endif /* RX_H_ */
