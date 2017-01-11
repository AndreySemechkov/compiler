%{
/* Project part 2 - Bison file */

/**********************************************************************************
*                                   Includes
***********************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "part2_helpers.h"
#include "part2_bison.tab.h"
ParserNode* parseTree;
/**********************************************************************************
*                                   Header
***********************************************************************************/
//We create the parser nodes for each token in the lexical analyser. 
//Using yylval common data structure we transfer the nodes to the parser unit. 
//In the parser we only create the father node, connect the nodes and build the tree.




/**********************************************************************************
*                                   Function Declarations
***********************************************************************************/
extern int yylex();
extern char* yytext;
extern int yylineno;
void yyerror(const char* msg);
%}



/**********************************************************************************
*                                   Tokens
***********************************************************************************/

%token TK_id
%token TK_real
%token TK_integer
%token TK_write
%token TK_read
%token TK_while
%token TK_do
%token TK_if
%token TK_then
%token TK_else
%token TK_main
%token TK_var
%token TK_call
%token TK_return
%token TK_defstruct
%token TK_extern
%token TK_num
%token TK_str
%token ':'
%token ';'
%token '{'
%token '}'
%token '('
%token ')'
%token ','
%token '['
%token ']'

/**********************************************************************************
*                         Operators: Associativity 
***********************************************************************************/

%right  TK_assign
%left   TK_or
%left   TK_and
%left   TK_relop
%left   TK_addop
%left   TK_mulop
%right  TK_not
%left   '[' ']'
%left   '{' '}'
%left   '(' ')'
/**********************************************************************************
*                         Operators: Precedence  
***********************************************************************************/

%precedence TK_then
%precedence TK_else

%%


/**********************************************************************************
*                         Reduction rules - (and actions)
*There are comments for the first few rules and all of the other are done the same way according 
*to each reduction rule  
***********************************************************************************/

PROGRAM: TDEFS FDEFS MAIN_FUNCTION 
{
        /*concatenate all children to a list*/
        $1.node = concatList($1.node,$2.node);
        $1.node = concatList($1.node,$3.node);
        /*Now, make the father node*/
        $$.node = makeNode("PROGRAM",NULL,$1.node);
        /*Update the global pointer for dumping the parse tree*/
        parseTree = $$.node;
}

;

TDEFS: TDEFS TK_defstruct '{' DECLARLIST '}' TK_id ';' 
{        
        /*concatenate all children to a list*/
        $1.node = concatList($1.node,$2.node);
        $1.node = concatList($1.node,$3.node);
        $1.node = concatList($1.node,$4.node);
        $1.node = concatList($1.node,$5.node);
        $1.node = concatList($1.node,$6.node);
        $1.node = concatList($1.node,$7.node);
        /*Now, make the father node*/
        $$.node = makeNode("TDEFS",NULL,$1.node);


}
| /*epsilon*/ { $$.node = makeNode("TDEFS",NULL, makeNode("EPSILON",NULL,NULL));}
;


FDEFS: FDEFS TYPE TK_id '(' FUNC_ARGLIST_FULL ')' BLK {

        /*concatenate all children to a list*/
        $1.node = concatList($1.node,$2.node);
        $1.node = concatList($1.node,$3.node);
        $1.node = concatList($1.node,$4.node);
        $1.node = concatList($1.node,$5.node);
        $1.node = concatList($1.node,$6.node);
        $1.node = concatList($1.node,$7.node);
        /*Now, make the father node*/
        $$.node = makeNode("FDEFS",NULL,$1.node);
        

}
| FDEFS TK_extern TYPE TK_id '(' FUNC_ARGLIST_FULL ')' ';' {
        /*concatenate all children to a list*/
        $1.node = concatList($1.node,$2.node);
        $1.node = concatList($1.node,$3.node);
        $1.node = concatList($1.node,$4.node);
        $1.node = concatList($1.node,$5.node);
        $1.node = concatList($1.node,$6.node);
        $1.node = concatList($1.node,$7.node);
        $1.node = concatList($1.node,$8.node);
        /*Now, make the father node*/
        $$.node = makeNode("FDEFS",NULL,$1.node);
}
| /*epsilon*/ { $$.node = makeNode("FDEFS",NULL, makeNode("EPSILON",NULL,NULL));}
;

FUNC_ARGLIST_FULL: FUNC_ARGLIST { $$.node = makeNode("FUNC_ARGLIST_FULL",NULL, $1.node); }
| /*epsilon*/ { $$.node = makeNode("FUNC_ARGLIST_FULL",NULL, makeNode("EPSILON",NULL,NULL)) ;}
;

FUNC_ARGLIST: FUNC_ARGLIST ',' DCL {
        /*concatenate all children to a list*/
        $1.node = concatList($1.node,$2.node);
        $1.node = concatList($1.node,$3.node);
        /*Now, make the father node*/
        $$.node = makeNode("FUNC_ARGLIST",NULL, $1.node);

}
| DCL {
        $$.node = makeNode("FUNC_ARGLIST",NULL, $1.node);
}
;

MAIN_FUNCTION: TK_main BLK {
        $1.node = concatList($1.node,$2.node);
        $$.node = makeNode("MAIN_FUNCTION",NULL,$1.node);
}
| /*epsilon*/ { $$.node = makeNode("MAIN_FUNCTION",NULL, makeNode("EPSILON",NULL,NULL));}
;

BLK: DECLARATIONS '{' LIST '}' {

        $1.node = concatList($1.node,$2.node);
        $1.node = concatList($1.node,$3.node);
        $1.node = concatList($1.node,$4.node);
        $$.node = makeNode("BLK",NULL,$1.node);
}
;

DECLARATIONS: TK_var DECLARLIST {

  $1.node = concatList($1.node,$2.node);
  $$.node = makeNode("DECLARATIONS",NULL,$1.node);

}
| /*epsilon*/ { $$.node = makeNode("DECLARATIONS",NULL, makeNode("EPSILON",NULL,NULL)) ;}
;

DECLARLIST: DECLARLIST DCL ';' { 

  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $$.node = makeNode("DECLARLIST",NULL,$1.node);
}

| DCL ';' { 

  $1.node = concatList($1.node,$2.node);
  $$.node = makeNode("DECLARLIST",NULL,$1.node);
}
;

DCL: TK_id ':' TYPE { 

  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $$.node = makeNode("DCL",NULL,$1.node);

}
| TK_id ':' TK_id   { 

  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $$.node = makeNode("DCL",NULL,$1.node);
}
| TK_id ',' DCL     { 
        $1.node = concatList($1.node,$2.node); 
        $1.node = concatList($1.node,$3.node);
        $$.node = makeNode("DCL",NULL,$1.node);
}
;

TYPE: TK_integer { $$.node = makeNode("TYPE",NULL, $1.node);  }
| TK_real        { $$.node = makeNode("TYPE",NULL, $1.node);  }
;

LIST: LIST STMT {  $1.node = concatList($1.node,$2.node);
                   $$.node = makeNode("LIST",NULL, $1.node);  }
| /*epsilon*/ { $$.node = makeNode("LIST",NULL, makeNode("EPSILON",NULL,NULL)) ;}
;

STMT: ASSN    {$$.node = makeNode("STMT",NULL, $1.node);}
| CNTRL       {$$.node = makeNode("STMT",NULL, $1.node);}
| READ        {$$.node = makeNode("STMT",NULL, $1.node);}
| WRITE       {$$.node = makeNode("STMT",NULL, $1.node);}
| STMT_RETURN {$$.node = makeNode("STMT",NULL, $1.node);}
| BLK         {$$.node = makeNode("STMT",NULL, $1.node);}
;

STMT_RETURN: TK_return '(' EXP ')' ';' { 
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $1.node = concatList($1.node,$4.node);
  $1.node = concatList($1.node,$5.node);
  $$.node = makeNode("STMT_RETURN",NULL,$1.node);
}
;

WRITE: TK_write '(' EXP ')' ';' { 
  
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $1.node = concatList($1.node,$4.node);
  $1.node = concatList($1.node,$5.node);
  $$.node = makeNode("WRITE",NULL,$1.node);
}
| TK_write '(' TK_str ')' ';'   { 
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $1.node = concatList($1.node,$4.node);
  $1.node = concatList($1.node,$5.node);
  $$.node = makeNode("WRITE",NULL,$1.node);
}
;

READ: TK_read '(' LVAL ')' ';'   { 

  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $1.node = concatList($1.node,$4.node);
  $1.node = concatList($1.node,$5.node);
  $$.node = makeNode("READ",NULL,$1.node);
}
;

ASSN: LVAL TK_assign EXP ';' { 

  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $1.node = concatList($1.node,$4.node);
  $$.node = makeNode("ASSN",NULL,$1.node);

}
;

LVAL: TK_id { $$.node = makeNode("LVAL",NULL, $1.node);  }
| STREF     { $$.node = makeNode("LVAL",NULL, $1.node);  }
;

CNTRL: TK_if BEXP TK_then STMT TK_else STMT{ 

  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $1.node = concatList($1.node,$4.node);
  $1.node = concatList($1.node,$5.node);
  $1.node = concatList($1.node,$6.node);
  $$.node = makeNode("CNTRL",NULL,$1.node);

}
| TK_if BEXP TK_then STMT{ 

  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $1.node = concatList($1.node,$4.node);
  $$.node = makeNode("CNTRL",NULL,$1.node);

}
| TK_while BEXP TK_do STMT { 
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $1.node = concatList($1.node,$4.node);
  $$.node = makeNode("CNTRL",NULL,$1.node);
}
;

BEXP: BEXP TK_or BEXP {  
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $$.node = makeNode("BEXP",NULL,$1.node);
}
| BEXP TK_and BEXP    {  
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $$.node = makeNode("BEXP",NULL,$1.node);
}
| TK_not BEXP         {  
  $1.node = concatList($1.node,$2.node);
  $$.node = makeNode("BEXP",NULL,$1.node);
}
| EXP TK_relop EXP    {  
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $$.node = makeNode("BEXP",NULL,$1.node);
}
| '(' BEXP ')'        {  
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $$.node = makeNode("BEXP",NULL,$1.node);
}
;

EXP: EXP TK_addop EXP { 
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $$.node = makeNode("EXP",NULL,$1.node);
}
| EXP TK_mulop EXP { 
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $$.node = makeNode("EXP",NULL,$1.node);
}
| '(' EXP ')' { 
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $$.node = makeNode("EXP",NULL,$1.node);
}
| '(' TYPE ')' EXP { 
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $1.node = concatList($1.node,$4.node);
  $$.node = makeNode("EXP",NULL,$1.node);
}
| TK_id {
  $$.node = makeNode("EXP",NULL,$1.node);
}
| STREF {
  $$.node = makeNode("EXP",NULL,$1.node);
}
| TK_num {
  $$.node = makeNode("EXP",NULL,$1.node);
}
| CALL {
  $$.node = makeNode("EXP",NULL,$1.node);
}
;

STREF: TK_id '[' TK_id ']' {
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $1.node = concatList($1.node,$4.node);
  $$.node = makeNode("STREF",NULL,$1.node);

}  
| STREF '[' TK_id ']' {
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $1.node = concatList($1.node,$4.node);
  $$.node = makeNode("STREF",NULL,$1.node);
} 
;

CALL: TK_call TK_id '(' CALL_ARGS_FULL ')' {
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $1.node = concatList($1.node,$4.node);
  $1.node = concatList($1.node,$5.node);
  $$.node = makeNode("CALL",NULL,$1.node);
}
;

CALL_ARGS_FULL: CALL_ARGS {
              $$.node = makeNode("CALL_ARGS_FULL",NULL, $1.node);
} 
|  /*epsilon*/ { $$.node = makeNode("CALL_ARGS_FULL",NULL, makeNode("EPSILON",NULL,NULL));}
;

CALL_ARGS: EXP { $$.node = makeNode("CALL_ARGS",NULL, $1.node);}
| CALL_ARGS ',' EXP { 
  $1.node = concatList($1.node,$2.node);
  $1.node = concatList($1.node,$3.node);
  $$.node = makeNode("CALL_ARGS",NULL, $1.node);
}
;

%%

// printig an error when no reduction rule can be applied.code 2 of error as requested showind the syntax error details
void yyerror(const char* msg)
{
  printf("Syntax error: '%s' in line number %d\n", yytext, yylineno);
  exit(2);
}

