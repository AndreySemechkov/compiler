/*
 * difinitions.h
 *
 *  Created on: Jan 17, 2017
 *      Author: andrey
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

// TYPES
typedef enum { REAL, INT, NONE } t_type ;

#define NUM_STACK_REGISTERS 4
#define NUM_RETURN_REGISTERS 1

#define EXIT_LEXICAL_FAILURE 1
#define EXIT_SYNTAX_FAILURE 2
#define EXIT_SEMANTIC_FAILURE 3
#define EXIT_OPERATIONAL_FAILURE 9


typedef NONE structType;


#endif /* DEFINITIONS_H_ */
