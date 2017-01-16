%{
#include <stdio.h>
#include <string.h>
#include <string>
#include "common.hpp"
#include "parser.tab.hpp"

//Helper Functions
//Debug functions to print values
void showToken(char*);
void showStr();
//funtion to call when there is a lexical error
void printError();
// the funtions that creates nodes from tokens data for the parse tree to be created by the parser
void setValue(string type,char* value);
%}

%option yylineno
%option noyywrap

num              ([0-9]+([.][0-9]+)?)
id               ([A-Za-z][A-Za-z0-9]*)
str              ([\"][^\"\n\r]*[\"])
comment          ([/][/].*)
whitespace       ([\t\n \r])
saved            "real"|"integer"|"write"|"read"|"while"|"do"|"if"|"then"|"else"|"main"|"var"|"call"|"return"|"defstruct"|"extern"
sign             [\(\)\[\]\{\}\,\:\;] 
relop            (==)|(<>)|(<)|(<=)|(>)|(>=)
addop            [+-]
mulop            [*]|[/]     
assign           [=]
and              ("&&")
or               ("||")
not              [!]

%%
{num} {
			    setValue("num", yytext);
			    return TK_num;                 
      }
{saved} {
            // There are many saved words thus to create an easy to modify structure
            //  we made a case that checks the lexma the scanner got and returns the right token.
            setValue(yytext, NULL);
            if(!strcmp(yytext,"real"))      return TK_real;
            if(!strcmp(yytext,"integer"))   return TK_integer;
            if(!strcmp(yytext,"write"))     return TK_write;
            if(!strcmp(yytext,"read"))      return TK_read;
            if(!strcmp(yytext,"while"))     return TK_while;
            if(!strcmp(yytext,"do"))        return TK_do;
            if(!strcmp(yytext,"if"))        return TK_if;
            if(!strcmp(yytext,"then"))      return TK_then;
            if(!strcmp(yytext,"else"))      return TK_else;
            if(!strcmp(yytext,"main"))      return TK_main;
            if(!strcmp(yytext,"var"))       return TK_var;
            if(!strcmp(yytext,"call"))      return TK_call;
            if(!strcmp(yytext,"return"))    return TK_return;
            if(!strcmp(yytext,"defstruct")) return TK_defstruct;
            if(!strcmp(yytext,"extern"))    return TK_extern;
        }
{comment} {}
{id}    {
            setValue("id", yytext);
            return TK_id;                    
        }
{whitespace} {}
{str} {

	char * buff = (char*)malloc(strlen(yytext-2));
	strncpy(buff, &yytext[1], strlen(yytext) - 2 );
	setValue("str", buff);
        free(buff);  
	return TK_str;                                  
      } 
{relop}	{
			      setValue("relop", yytext);
			      return TK_relop;
			  }
{addop}		{
		        	setValue("addop", yytext);
			        return TK_addop;
			    }
{mulop}		{
		        	setValue("mulop", yytext);
			        return TK_mulop;
			    }
{assign}	{
			        setValue("assign", yytext);
			        return TK_assign;
			    }		
{and}		{
		        	setValue("and",  yytext);
			        return TK_and;
			  }
{or}		{
			        setValue("or",  yytext);
			        return TK_or;
			  }		
{not}		{
			        setValue("not",  yytext);
			        return TK_not;
			  }
{sign} { 			              
              setValue(yytext,  NULL);
			        return  yytext[0];                        
       }
.			{
              printError();			   
			}

%%

void showToken(char* name){

  printf("<%s,%s>",name,yytext);

}

void showStr(){
  printf("<str,");
  for(int j = 1; j < yyleng - 1 ; j++){
     printf("%c",yytext[j]);
  }
  printf(">");
}

void printError(){
  printf("\n");
  printf("Lexical error: '%s' in line number %d\n",yytext ,yylineno);
  exit(1);
}

// Creates and Sets the value of the node according to the lexema
void setValue (string type,char* value) {

//initialize type
 if(type == "real") 
    yylval.type = REAL;
 else if (type == "integer") 
    yylval.type = INT;
  else 
    yylval.type = NONE;
    
    //initialize value
  yylval.value = value ? value : "" ; 

}


