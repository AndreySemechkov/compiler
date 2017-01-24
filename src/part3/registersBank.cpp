/*
 * RegistersBank.cpp
 *
 *  Created on: Jan 16, 2017
 *      Author: saar
 */

#include "registersBank.h"

RegistersBank::RegistersBank() {
	bank[REAL] = 0;
	bank[INT]  = NUM_RETURN_REGISTERS + NUM_STACK_REGISTERS;
}

RegistersBank::~RegistersBank() {
// we may add an assert test here later
}

int RegistersBank::getRegister(t_type type){ //get next register

if(type != REAL && type != INT){
	// our erorr!
}

if(bank[type] == 999 ){
	//operational error, but they say we can assume it will not happen
}

return bank[type]++;
}


int RegistersBank::getRegistersCount(t_type type){ //get next register
	return bank[type];
}


void RegistersBank::setRegistersCount(t_type type,int toSet){
	bank[type] = toSet;
}
