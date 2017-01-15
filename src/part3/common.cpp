/* 046266 Compilation Methods, EE Faculty, Technion                        */
/* part2_helpers.c - Helper functions for project part 2 - implementation  */
#include "common.hpp"

#include <stdio.h>


extern int yyparse (void);


/**************************************************************************/
/*                           Globals                                      */
/**************************************************************************/

Buffer buffer;


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
