/*
 * memHandler.h
 *
 *  Created on: Jan 20, 2017
 *      Author: compm
 */

#ifndef MEMHANDLER_H_
#define MEMHANDLER_H_

#include "definitions.h"

class MemHandler {
	int bank[2];
public:
	MemHandler();
	virtual ~MemHandler();
	int getMem(t_type type); //get next available mem of requested type
};

#endif /* MEMHANDLER_H_ */
