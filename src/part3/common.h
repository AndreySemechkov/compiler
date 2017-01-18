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
#include "buffer.h"
#include <set>
#include <algorithm>
#include <iterator>



extern Buffer buffer;
extern RegistersBank bank;
extern TableOfSymbols symbolTable;

//no adress
#define NO_ADDR -1

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


/* common struct to use for bison and flex*/
typedef struct {
	t_type type;
	std::string value; // for keeping multiple types.
	int registerNum;
	int addr; //if the variable is stored in memory, address will represent where (the offset) , else it will be NO_ADDR



	//for control struts , M,N;
	int quad;
	std::set< int > nextList;

	std::set< int > trueList;
	std::set< int > falseList;


} yystype_t;

#define YYSTYPE yystype_t 







#endif //COMMON_H
