/* 046266 Compilation Methods, EE Faculty, Technion                        */
/* part2_helpers.c - Helper functions for project part 2 - implementation  */
#include "common.h"
#include <stack>

/**************************************************************************/
/*                           Globals                                      */
/**************************************************************************/

Buffer buffer;
RegistersBank bank;
std::stack<TableOfSymbols> symbolTable;
MemHandler mem;
std::map<std::string,CmmStruct> structsTable;
std::map<std::string, Function> functionsTable;
std::stack<t_type> currentFunctionReturnType;
bool isMain;
int rs;


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

    yyin = fopen(argv[1],"r");
    if(yyin==NULL)
    {
    	  cerr << "Operational error: ";
    	  cerr << "Invalid argument!" << endl;
    	  exit(EXIT_OPERATIONAL_FAILURE);
    }
    if(inputCodeName.substr(inputCodeName.find_last_of("."),4) != ".cmm")
    {
    	  cerr << "Operational error: ";
    	  cerr << "Invalid argument!" << endl;
    	  exit(EXIT_OPERATIONAL_FAILURE);
    }

//#if YYDEBUG
//    yydebug=1;
//#endif
    
    //int rs;
    yyparse();
    //cout << rs << endl;
    if (rs == 0) { // Parsed successfully
      buffer.printRiski(inputCodeName);
    }
    fclose(yyin);
    yylex_destroy();

return 0;
}





/**************************************************************************/
/*                           assignStructs                               */
/**************************************************************************/

//ALG : structs assinment
		//input : 2 lists - structs fields lists, for every struct: 2 start addrs : real and int

		//go over both structs fields list:
			//for every field:
				//if its a simple type - transfer
				//if its a struct type, call the algorithm recursively with the lists.


void assignStructs(list<CmmStructField>& left,
		int left_int_start_addr ,
		int left_real_start_addr,
		int right_int_start_addr ,
		int right_real_start_addr)
{
	for ( list<CmmStructField>::iterator li = left.begin(); li !=left.end(); ++li){

		switch(li->type){
		case INT:
			{
			int lAddr = li->INToffsetInsideStruct + left_int_start_addr;
			int rAddr = li->INToffsetInsideStruct + right_int_start_addr;

			int reg = bank.getRegister(INT);

			//load to reg
			string eLoad = "LOADI I" + to_string(reg) + " " + to_string(rAddr) + " I1";

			//strore from reg to mem.
			string eStore = "STORI I" + to_string(reg) + " " + to_string(lAddr) + " I1";

			//now, emit
			buffer.emit(eLoad);
			buffer.emit(eStore);
			break;
			}
		case REAL:
			{
			int lAddrR = li->REALoffsetInsideStruct + left_real_start_addr;
			int rAddrR = li->REALoffsetInsideStruct + right_real_start_addr;

			int reg = bank.getRegister(REAL);

			//load to reg
			string eLoadR = "LOADR R" + to_string(reg) + " " + to_string(rAddrR) + " I3";

			//strore from reg to mem.
			string eStoreR = "STORR R" + to_string(reg) + " " + to_string(lAddrR) + " I3";

			//now, emit
			buffer.emit(eLoadR);
			buffer.emit(eStoreR);
			break;
			}
		default: //struct!
			{
			//call recusivly!

			//prep addrs

			int l_int_start_Addr = li->INToffsetInsideStruct + left_int_start_addr;
			int r_int_start_Addr = li->INToffsetInsideStruct + right_int_start_addr;

			int l_real_start_Addr = li->REALoffsetInsideStruct + left_real_start_addr;
			int r_real_start_Addr = li->REALoffsetInsideStruct + right_real_start_addr;

			//now do the job
			assignStructs(li->structDescriptor->m_fields_list,
					l_int_start_Addr,l_real_start_Addr,r_int_start_Addr,r_real_start_Addr);
			}
		}

	}

}

