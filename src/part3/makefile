# Makefile for Project part 3
all: part3

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d parser.ypp

lex.yy.c: scanner.lex parser.tab.hpp
	flex scanner.lex

part3: lex.yy.c parser.tab.cpp parser.tab.hpp common.cpp common.h buffer.h buffer.cpp registersBank.h registersBank.cpp memHandler.h memHandler.cpp tableOfSymbols.h CmmStruct.h CmmStruct.cpp tableOfStructs.h 
	g++ -std=c++11 -o part3 parser.tab.cpp lex.yy.c common.cpp buffer.cpp registersBank.cpp memHnadler.cpp tableOfSymbols.cpp CmmStruct.cpp tableOfStructs.cpp

clean:
	rm part3 parser.tab.cpp lex.yy.c parser.tab.hpp


