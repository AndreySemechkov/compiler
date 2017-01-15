%{
	#include "Common.hpp"
	#include "Parser.hpp"
	
	extern "C" int yylex();
	void setVal(std::string type, const char* content);
	
	using namespace std;
%}

%option outfile = "Scanner.cpp"
%option yylineno
%option noyywrap
%option nounput

/* regular definitions */
delim		[ \t\n]
letter		[A-Za-z]
digit		[0-9]

ws			{delim}+
id			{letter}({letter}|{digit})*
number		{digit}+(\.{digit}+)?
string		\"(\\.|[^"\n\t])*\"
comment 	"/*"([^*]|\*+[^*/])*\*+"/"
relop		"=="|"<>"|<|>|"<="|">="
addop		[+-]
mulop		[*/]
assign		[=]
and			"&&"
or			"||"
not			[!]
		
%%


program		{
			setVal("res", yytext);
			return tk_program;
			}
begin		{
			setVal("res", yytext);
			return tk_begin;
			}
end			{
			setVal("res", yytext);
			return tk_end;
			}
include		{
			setVal("res", yytext);
			return tk_include;
			}
real		{
			setVal("res", yytext);
			return tk_real;
			}
integer 	{
			setVal("res", yytext);
			return tk_integer;
			}
write 		{
			setVal("res", yytext);
			return tk_write;
			}
read 		{
			setVal("res", yytext);
			return tk_read;
			}
while 		{
			setVal("res", yytext);
			return tk_while;
			}

do 			{
			setVal("res", yytext);
			return tk_do;
			}
if			{
			setVal("res", yytext);
			return tk_if;
			}
then		{
			setVal("res", yytext);
			return tk_then;
			}
else		{
			setVal("res", yytext);
			return tk_else;
			}

			
var			{
			setVal("res", yytext);
			return tk_var;
			}

call		{
			setVal("res", yytext);
			return tk_call;
			}
return		{
			setVal("res", yytext);
			return tk_return;
			}
"("			{
			setVal("", yytext);
			return tk_leftparen;
			}
")"			{
			setVal("", yytext);
			return tk_rightparen;
			}
"["			{
			setVal("", yytext);
			return tk_leftbracket;
			}
"]"			{
			setVal("", yytext);
			return tk_rightbracket;
			}
","			{
			setVal("", yytext);
			return tk_comma;
			}
";"			{
			setVal("", yytext);
			return tk_semicolon;
			}
":"			{
			setVal("", yytext);
			return tk_colon;
			}
 
{id}		{
			setVal("id", yytext);
			return tk_identifier;
			}
{number}	{
			setVal("num", yytext);
			return tk_num;
			}
{string}	{
			char *c = yytext;
			c[yyleng-1] = '\0';
			c++;
			setVal("str", c);
			return tk_str;
			}

{comment}	;
{ws}		; 

{relop}		{
			setVal("relop", yytext);
			return tk_relop;
			}
{addop}		{
			setVal("addop", yytext);
			return tk_addop;
			}
{mulop}		{
			setVal("mulop", yytext);
			return tk_mulop;
			}
{assign}	{
			setVal("assign", yytext);
			return tk_assign;
			}		
{and}		{
			setVal("and", yytext);
			return tk_and;
			}
{or}		{
			setVal("or", yytext);
			return tk_or;
			}		
{not}		{
			setVal("not", yytext);
			return tk_not;
			}
.			{
			cerr << "Lexical error: '" << yytext << "' in line number " << yylineno << endl;
			exit(EXIT_LEXICAL_FAILURE);
			}

%%

void setVal(std::string type, const char* content) {
	//yylval.type = type;
	yylval.content = content;
}


