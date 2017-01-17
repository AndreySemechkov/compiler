/*
 * registersBank.hpp
 *
 *  Created on: Jan 16, 2017
 *      Author: saar
 */

#ifndef REGISTERSBANK_H_
#define REGISTERSBANK_H_
#include "definitions.h"

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

#endif /* REGISTERSBANK_H_ */
