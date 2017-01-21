/* 046266 Compilation Methods, EE Faculty, Technion                        */
/* part2_helpers.h - Helper functions for project part 2 - API definitions */

#ifndef COMMON_H
#define COMMON_H
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include "registersBank.h"
#include "memHandler.h"
#include "buffer.h"
#include "tableOfSymbols.h"
#include <set>
#include <list>
#include <algorithm>
#include <iterator>
#include "CmmStruct.h"
#include "Function.h"


extern Buffer buffer;
extern RegistersBank bank;
extern MemHandler mem;
extern std::stack<TableOfSymbols> symbolTable;
extern std::map<std::string,CmmStruct> structsTable ;
extern std::map<std::string, Function> functionsTable;
extern std::stack<t_type> currentFunctionReturnType;
extern bool isMain;


//extern "C" {
	// int yylex();
	// char* yytext;
	// int yylineno;
//}

//no adress
#define NO_ADDR -1

//merge sets source1 and source2 to a destination set: usage: MERGE(dest,source1,source2);
#define MERGE(dest, v1,v2) do{ \
dest.insert(v1.begin(),v1.end()); \
dest.insert(v2.begin(),v2.end()); \
}	while(0)


typedef CmmStructField DCLnode;

/* common struct to use for bison and flex*/
typedef struct {
	t_type type;
	std::string value; // for keeping multiple types.
	int registerNum;
	int addr; //if the variable is stored in memory, address will represent where (the offset) , else it will be NO_ADDR


	//for declarations parsing
	std::list<std::pair<string,DCLnode> > dclNodes;

	//for control statements and backpatching , M,N;
	int quad;
	std::set< int > nextList;

	std::set< int > trueList;
	std::set< int > falseList;

	//for STREF
	int INToffsetInsideStruct;
	int REALoffsetInsideStruct;

	int INTaddr;
	int REALaddr;

	CmmStructField * oldFieldD;


	//for function calls

	std::list<std::pair<t_type,int>> paramNodes;


} yystype_t;

#define YYSTYPE yystype_t 


void assignStructs(list<CmmStructField>& left,
		int left_int_start_addr ,
		int left_real_start_addr,
		int right_int_start_addr ,
		int right_real_start_addr);



#endif //COMMON_H
