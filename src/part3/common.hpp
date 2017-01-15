/* 046266 Compilation Methods, EE Faculty, Technion                        */
/* part2_helpers.h - Helper functions for project part 2 - API definitions */

#ifndef COMMON_H
#define COMMON_H
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <stdio.h>


#define EXIT_LEXICAL_FAILURE 1
#define EXIT_SYNTAX_FAILURE 2
#define EXIT_SEMANTIC_FAILURE 3
#define EXIT_OPERATIONAL_FAILURE 9

typedef enum { REAL, INT, NONE } t_type ;


#ifdef __cplusplus
extern "C" {
#endif

/* common struct to use for bison and flex*/
typedef struct {
	t_type type;
	std::string value; // for keeping multiple types.

} yystype_t;

#define YYSTYPE yystype_t 


#ifdef __cplusplus
} // extern "C"
#endif



#endif //COMMON_H
