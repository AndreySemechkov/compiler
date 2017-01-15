#include "Common.hpp"
#include "Parser.hpp"
#include "QuadBuffer.hpp"
#include "Function.hpp"
#include <sstream>
#include <fstream>

extern "C"	FILE *yyin;
extern "C"	int yylex();
extern void yylex_destroy();

using namespace std;

// global variables initilization:
QuadBuffer globalQuadBuffer;
int globalCurrentScopeRegisterCounter[TYPES_NUM] = {1,0};
int globalCurrentScopeOffset = 0;
bool globalIsMain = false;

SymbolTable globalCurrentScopeSymbolTable;
std::map<FunctionName,pFunction> globalFunctionsMap;
std::vector<std::string> globalParamInsertionOrder;

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cerr << "Operational error: invalid number of arguments" << endl;
		exit(EXIT_OPERATIONAL_FAILURE);
	}

	string inputFileName = argv[1];
	size_t lastindex;
	try {
		lastindex = inputFileName.find_last_of(".");
		if (inputFileName.substr(lastindex) != ".cmm") {
			throw std::invalid_argument("");
		}
	}
	catch (std::exception& e){
		cerr << "Operational error: invalid file type. expecting '.cmm' extension" << endl;
		exit(EXIT_OPERATIONAL_FAILURE);
	}

	string outputFileName = inputFileName.substr(0, lastindex) + ".rsk";
	std::ofstream out(outputFileName);
	std::streambuf *coutBuffer = std::cout.rdbuf(); //save old buffer
	std::cout.rdbuf(out.rdbuf()); //redirect std::cout to outputFileName

	yyin = fopen(argv[1], "r");

	yyparse();
	globalQuadBuffer.printBuffer();

	std::cout.rdbuf(coutBuffer); //reset to standard output again
	fclose(yyin);

	yylex_destroy();
	return 0;
}


void yyerror(const char* c)
{
//	printf("Syntax error: '%s' in line number %d\n", yytext, yylineno);
	exit(1);
}
