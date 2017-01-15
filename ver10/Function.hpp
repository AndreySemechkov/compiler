#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_
#include "Common.hpp"
#include "Symbol.hpp"
#include <vector>
#include <memory>
#include <map>

class Function {
public:
	Function(Type returnType, int startLine, pSymbolTable funcSymbolTable);
	~Function();


	std::vector<std::string> getParamNames();
	void setParamNames(std::vector<std::string> paramNames);
	std::vector<Type> getParamTypes();
	void setParamTypes(std::vector<Type> paramTypes);
	Type getReturnType() const;
	void setReturnType(Type returnType);
	int getStartLine() const;
	void setStartLine(int startLine);
	const pSymbolTable getFuncSymbolTable() const;
	void setFuncSymbolTable(const pSymbolTable funcSymbolTable);
	std::vector<int> getCallLines() ;
	void addCallLine(int line);
private:
	Type returnType;
	int startLine;
	pSymbolTable funcSymbolTable;
	std::vector<Type> paramTypes;
	std::vector<std::string> paramNames;
	std::vector<int> callLines;
};

typedef std::string FunctionName;
typedef std::shared_ptr<Function> pFunction;

extern std::map<FunctionName,pFunction> globalFunctionsMap;


#endif /* FUNCTION_HPP_ */
