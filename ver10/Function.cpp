#include "Function.hpp"
#include <iostream>
#include <string>

Function::Function(Type returnType, int startLine, pSymbolTable funcSymbolTable) :
returnType(returnType),
startLine(startLine),
funcSymbolTable(funcSymbolTable)
{
	//std::cout << "start line = " << std::to_string(startLine) << std::endl;
}

Function::~Function() {
}

std::vector<std::string> Function::getParamNames() {
	return paramNames;
}

void Function::setParamNames(std::vector<std::string> paramNames) {
	this->paramNames = paramNames;
}

std::vector<Type> Function::getParamTypes()  {
	return paramTypes;
}

void Function::setParamTypes(const std::vector<Type> paramTypes) {
	this->paramTypes = paramTypes;
}



Type Function::getReturnType() const {
	return returnType;
}

void Function::setReturnType(Type returnType) {
	this->returnType = returnType;
}

int Function::getStartLine() const {
	return startLine;
}

void Function::setStartLine(int startLine) {
	this->startLine = startLine;
}

const pSymbolTable Function::getFuncSymbolTable() const {
	return funcSymbolTable;
}

void Function::setFuncSymbolTable(pSymbolTable funcSymbolTable) {
	this->funcSymbolTable = funcSymbolTable;
}

std::vector<int> Function::getCallLines()  {
	return callLines;
}

void Function::addCallLine(int line) {
	callLines.push_back(line);
}
