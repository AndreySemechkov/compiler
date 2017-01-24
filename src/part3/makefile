# Makefile for Project part 3
all: rx-cc 

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d parser.ypp

lex.yy.c: scanner.lex parser.tab.hpp
	flex scanner.lex

rx-cc: lex.yy.c parser.tab.cpp parser.tab.hpp common.cpp common.h buffer.h buffer.cpp registersBank.h registersBank.cpp memHandler.h memHandler.cpp tableOfSymbols.h CmmStruct.h CmmStruct.cpp Function.h 
	g++ -std=c++11 -g -o rx-cc parser.tab.cpp lex.yy.c common.cpp buffer.cpp registersBank.cpp memHandler.cpp tableOfSymbols.cpp CmmStruct.cpp Function.h

clean:
	rm rx-cc parser.tab.cpp lex.yy.c parser.tab.hpp


