/*
 * memHandler.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: compm
 */

#include "memHandler.h"

MemHandler::MemHandler() {
	// TODO Auto-generated constructor stub
	bank[REAL] = 0;
	bank[INT]  = 0;

}

MemHandler::~MemHandler() {
	// TODO Auto-generated destructor stub
}

int MemHandler::getMem(t_type type){ //get next register

if(type != REAL && type != INT){
	// our erorr!
}

if(bank[type] == 999 ){
	//operational error, but they say we can assume it will not happen
}

return bank[type]++;
}
