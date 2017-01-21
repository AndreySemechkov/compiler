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



int MemHandler::getBulkMem(t_type type, int numFieldsOfType){


	if(type != REAL && type != INT){
		// our error!
	}
	if(numFieldsOfType <= 0){
		//our error!

	}

	if(bank[type] +  numFieldsOfType > 999 ){
		//operational error, but they say we can assume it will not happen
	}

	int tmp = bank[type];


	bank[type] = bank[type] + numFieldsOfType;

	return tmp;

}


void MemHandler::startBLK(){

	//remember the memroy places we used
	for(int i =0 ; i< 2 ; i++){
		scopeMem[i] = bank[i];
	}
}

void MemHandler::endBLK(){
	//resotre the memory places
	for(int i =0 ; i< 2 ; i++){
		bank[i] = scopeMem[i];
	}
}
