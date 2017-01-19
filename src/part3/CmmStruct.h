/*
 * CmmStruct.h
 *
 *  Created on: Jan 19, 2017
 *      Author: compm
 */

#ifndef CMMSTRUCT_H_
#define CMMSTRUCT_H_

#include "definitions.h"
#include "tableOfStructs.h"
#include <string>

extern class TableOfStructs;
class CmmStruct;

using namespace std;


//
//struct CmmStructField- describes a field of a CmmStruct.
//
//note: CmmStructField can be REAL, INT or a previously defined CmmStruct
//
struct CmmStructField {

	string name;
	t_type type;

	// if the filed is a struct,
	//then that this is a pointer to its place in the TableOfStructs,
	//in order to access and verify it's fileds.
	//else, this pointer is nullptr.
	CmmStruct * structDescriptor;


	//returns true if the field is a struct
	bool isStruct() {
		return (type != INT && type != REAL);
	}
	int getNumFields(){
		if (!isStruct()) return 1;
		return structDescriptor->getNumFields();
	}

};

//
// Class CmmStruct - describes CmmStructs
//
class CmmStruct {

	string m_name; //name of the struct
	map<string, CmmStructField> m_fields; // map of struct's fields

public:
	CmmStruct();
	virtual ~CmmStruct();

	//uage notes:
	//----caller must check if field exists, and fully initiate it before calling this function.
	void addField(CmmStructField field);


	//throws an eception if it does not exists
	CmmStructField * getFieldByName(string name);


	//get the number of fields
	int getNumFields();

};

#endif /* CMMSTRUCT_H_ */
