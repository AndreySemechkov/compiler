/* 046266 Compilation Methods, EE Faculty, Technion                        */
/* part2_helpers.h - Helper functions for project part 2 - API definitions */

#ifndef COMMON_H
#define COMMON_H
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
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


extern Buffer buffer;
extern RegistersBank bank;
extern MemHandler mem;
extern TableOfSymbols symbolTable;

//no adress
#define NO_ADDR -1

//merge sets source1 and source2 to a destination set: usage: MERGE(dest,source1,source2);
#define MERGE(dest, v1,v2) do{ \
std::set_union(v1.begin(), v1.end(),v2.begin(), v2.end(), std::back_inserter(dest)); \
	while(0)


/*
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} // extern "C"
#endif
*/


typedef CmmStructField DCLnode;

/* common struct to use for bison and flex*/
typedef struct {
	t_type type;
	std::string value; // for keeping multiple types.
	int registerNum;
	int addr; //if the variable is stored in memory, address will represent where (the offset) , else it will be NO_ADDR


	//for declarations parsing
	std::list<DCLnode> dclNodes;

	//for control struts , M,N;
	int quad;
	std::set< int > nextList;

	std::set< int > trueList;
	std::set< int > falseList;



} yystype_t;

#define YYSTYPE yystype_t 







#endif //COMMON_H
