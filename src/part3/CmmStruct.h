/*
 * CmmStruct.h
 *
 *  Created on: Jan 19, 2017
 *      Author: compm
 */

#ifndef CMMSTRUCT_H_
#define CMMSTRUCT_H_

#include "definitions.h"
//#include "tableOfStructs.h"
#include <string>

//class TableOfStructs;
class CmmStruct;

using namespace std;


////
//// Class CmmSybmol : For the symbol s table.
////
////can represent both simple types (INT, REAL) or complex types (structs)
////
//class CmmSymbol : public CmmStructField {
////
//
//	int intStartAddr;
//	int realStartAddr;
//}


//
//Class CmmStructField- describes a field of a CmmStruct.
//
//note: CmmStructField can be REAL, INT or a previously defined CmmStruct
//
struct CmmStructField {

//public:
	string name;
	t_type type;

	// if the filed is a struct,
	//then that this is a pointer to its place in the TableOfStructs,
	//in order to access and verify it's fileds.
	//else, this pointer should be set to nullptr.
	CmmStruct * structDescriptor;


	//returns true if the field is a struct
	bool isStruct();
	int getNumFields();

	int getNumIntFields();

	int getNumRealFields();

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
	int getNumIntFields();
	int getNumRealFields();




};

#endif /* CMMSTRUCT_H_ */
