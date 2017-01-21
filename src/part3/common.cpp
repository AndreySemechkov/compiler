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

extern "C" {
	int yyparse (void);
}
/**************************************************************************/
/*                           Main of parser                               */
/**************************************************************************/

int main(void)
{
    int rc;
#if YYDEBUG
    yydebug=1;
#endif
    rc = yyparse();
    if (rc == 0) { // Parsed successfully
//TODO:
    }



}
