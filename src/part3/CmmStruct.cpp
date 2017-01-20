/*
 * CmmStruct.cpp
 *
 *  Created on: Jan 19, 2017
 *      Author: compm
 */

#include "CmmStruct.h"

//
//Class CMM struct field


	bool CmmStructField::isStruct() {
		return (type != INT && type != REAL);
	}
	int CmmStructField::getNumFields(){
		if (!isStruct()) return 1;
		return structDescriptor->getNumFields();
	}
	int CmmStructField::getNumIntFields(){
		if (!isStruct()){
			if (type == INT) return 1;
			if (type == REAL) return 0;
		}
		return structDescriptor->getNumIntFields();

	}

	int CmmStructField::getNumRealFields(){

		if (!isStruct()){
			if (type == REAL) return 1;
			if (type == INT) return 0;
		}
		return structDescriptor->getNumRealFields();
	}

//





//
//Class CMM struct
//
CmmStruct::CmmStruct() {
	// TODO Auto-generated constructor stub

}

CmmStruct::~CmmStruct() {
	// TODO Auto-generated destructor stub
}

void CmmStruct::addField(CmmStructField field){
	try{
		m_fields.insert(std::pair<string,CmmStructField>(field.name, field));
	}catch(...){
		throw(" struct " + m_name + ": field " + field.name + " defined more then once.");
	}
}


int CmmStruct::getNumFields() {
	int sum = 0;
	for (auto& it : m_fields) {
		sum += it.second.getNumFields();
	}
	return sum;
}

int CmmStruct::getNumIntFields() {
	int sum = 0;
	for (auto& it : m_fields) {
		sum += it.second.getNumIntFields();
	}
	return sum;
}


int CmmStruct::getNumRealFields() {
	int sum = 0;
	for (auto& it : m_fields) {
		sum += it.second.getNumRealFields();
	}
	return sum;
}



CmmStructField * CmmStruct::getFieldByName(string name){
	CmmStructField* f = NULL;
	try{
		f = &(m_fields.at(name));
	}catch(...){
		throw("struct " + m_name + ": field " + name + " does not exist.");
	}
	return f;
}
