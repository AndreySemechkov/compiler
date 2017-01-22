/*
 * memHandler.h
 *
 *  Created on: Jan 20, 2017
 *      Author: compm
 */

#ifndef MEMHANDLER_H_
#define MEMHANDLER_H_

#include "definitions.h"
#include <stack>

//
// Class MemHandler : handles offset for the current BLK.
//
class MemHandler {
	int bank[2];

	std::stack<int> scopeMem[2]; //in order to forget all the temporary memory allocated in a block
public:
	MemHandler();
	virtual ~MemHandler();
	int getMem(t_type type); //get next available mem of requested simple type


	//a function to be called when inserting structs to the symbol table.
	/*
	 * parmeters are
	 * @type - type of memory we want to allocate (int or real)
	 * @numFieldsOfType - total number of fields of the requested type ,
	 * 		(which caller struct contains)
	 *
	 * behavior:
	 * the function adds numFieldsOfType to bank[type],
	 * and returns the adress before change
	 * */
	int getBulkMem(t_type type, int numFieldsOfType);


	//remember the memroy places we used, and init offsets back to 0
	void startBLK();

	//init offsets back to where they where in the father block.
	void endBLK();



};

#endif /* MEMHANDLER_H_ */
