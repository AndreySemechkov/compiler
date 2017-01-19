/*
 * CmmStruct.cpp
 *
 *  Created on: Jan 19, 2017
 *      Author: compm
 */

#include "CmmStruct.h"

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
		throw(" error in struct " + m_name + ": field " + field.name + " defined more then once.");
	}
}


int CmmStruct::getNumFields() {
	int sum = 0;
	for (auto& it : m_fields) {
		sum += it.second.getNumFields();
	}
	return sum;
}


CmmStructField * CmmStruct::getFieldByName(string name){
	CmmStructField* f = NULL;
	try{
		f = &(m_fields.at(name));
	}catch(...){
		throw("error in struct " + m_name + ": field " + name + " does not exist.");
	}
	return f;
}
