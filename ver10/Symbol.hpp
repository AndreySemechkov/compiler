#ifndef SYMBOL_HPP_
#define SYMBOL_HPP_
#include <string>
#include <map>
#include <memory>

typedef enum {INTEGER, REAL} Type;


class Symbol   {
public:
	Symbol(int size, bool isArray);
	Symbol(Type type, int size, bool isArray);
	 ~Symbol();

	Type getType();
	void setType(Type type);

	int getOffset() const;
	void setOffset(int offset);

	int getSize() const;
	void setSize(int size);
	bool isArray() const;
	void setIsArray(bool isArray);
protected:
	Type type;
	int size;
	int offset;
	bool isArray_;
};

typedef std::string SymbolName;
typedef std::shared_ptr<Symbol> pSymbol;
typedef std::map<SymbolName,pSymbol> SymbolTable;
typedef std::shared_ptr<std::map<SymbolName,pSymbol>> pSymbolTable;

void copySymbolTable(
		std::map<SymbolName,pSymbol>& tableSrc,
		std::map<SymbolName, pSymbol>& tableDst
		);

void mergeSymbolTables(
		std::map<SymbolName,pSymbol>& tableA,
		std::map<SymbolName, pSymbol>& tableB,
		std::map<SymbolName, pSymbol>& tableC
		);

extern SymbolTable globalCurrentScopeSymbolTable;


#endif /* SYMBOL_HPP_ */
