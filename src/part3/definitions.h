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

#define NUM_STACK_REGISTERS 6 //I1, I2 - fp, I3,I4 - sp,  + I5,I6 - for save
#define NUM_RETURN_REGISTERS 1 //I0

#define EXIT_LEXICAL_FAILURE 1
#define EXIT_SYNTAX_FAILURE 2
#define EXIT_SEMANTIC_FAILURE 3
#define EXIT_OPERATIONAL_FAILURE 9


#define structType NONE


#endif /* DEFINITIONS_H_ */
