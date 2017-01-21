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
			int lAddr = li->INToffsetInsideStruct + left_int_start_addr;
			int rAddr = li->INToffsetInsideStruct + right_int_start_addr;

			int reg = bank.getRegister(INT);

			//load to reg
			string eLoad = "LOADI I" + to_string(reg) + " " + to_string(rAddr) + " 0";

			//strore from reg to mem.
			string eStore = "STORI I" + to_string(reg) + " " + to_string(lAddr) + " 0";

			//now, emit
			buffer.emit(eLoad);
			buffer.emit(eStore);
			break;
		case REAL:
			int lAddr = li->REALoffsetInsideStruct + left_real_start_addr;
			int rAddr = li->REALoffsetInsideStruct + right_real_start_addr;

			int reg = bank.getRegister(REAL);

			//load to reg
			string eLoad = "LOADR R" + to_string(reg) + " " + to_string(rAddr) + " 0";

			//strore from reg to mem.
			string eStore = "STORR R" + to_string(reg) + " " + to_string(lAddr) + " 0";

			//now, emit
			buffer.emit(eLoad);
			buffer.emit(eStore);
			break;

		default: //struct!
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

