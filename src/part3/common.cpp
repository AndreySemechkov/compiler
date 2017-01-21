/* 046266 Compilation Methods, EE Faculty, Technion                        */
/* part2_helpers.c - Helper functions for project part 2 - implementation  */
#include "common.h"


/**************************************************************************/
/*                           Globals                                      */
/**************************************************************************/

Buffer buffer;
RegistersBank bank;
TableOfSymbols symbolTable;
MemHandler mem;
std::map<std::string,CmmStruct> structsTable;


extern int yyparse ();
extern void yylex_destroy();
extern	FILE *yyin;
extern 	int yylex();
extern int yydebug;
/**************************************************************************/
/*                           Main of parser                               */
/**************************************************************************/

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		cerr << "Operational error: ";
		cerr << "Invalid number of arguments!" << endl;
	    exit(EXIT_OPERATIONAL_FAILURE);
	}
    string inputCodeName = argv[1];

    if(inputCodeName.substr(inputCodeName.find_last_of("."),4) != ".cmm")
    {
    	  cerr << "Operational error: ";
    	  cerr << "Invalid argument!" << endl;
    	  exit(EXIT_OPERATIONAL_FAILURE);
    }

//#if YYDEBUG
    yydebug=1;
//#endif
    yyin = fopen(argv[1],"r");
    int rs;
    rs = yyparse();
    if (rs == 0) { // Parsed successfully
      buffer.printRiski(inputCodeName);
    }
    fclose(yyin);
    yylex_destroy();

return 0;
}
