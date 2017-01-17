/*
 * registersBank.hpp
 *
 *  Created on: Jan 16, 2017
 *      Author: compm
 */

#ifndef REGISTERSBANK_HPP_
#define REGISTERSBANK_HPP_

#define NUM_STACK_REGISTERS 4
#define NUM_RETURN_REGISTERS 1


typedef enum { REAL, INT, NONE } t_type ;

//
// Class :  Registers Bank : handles registers allocation
//
class RegistersBank {
int bank[2];

public:
	RegistersBank();
	virtual ~RegistersBank();
	int getRegister(t_type type); //get next available register of requested type

};

#endif /* REGISTERSBANK_HPP_ */
