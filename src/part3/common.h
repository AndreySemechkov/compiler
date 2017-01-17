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

extern Buffer buffer;
extern RegistersBank bank;
extern TableOfSymbols symbolTable;

//no adress
#define NO_ADDR -1


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

} yystype_t;

#define YYSTYPE yystype_t 









#endif //COMMON_H
