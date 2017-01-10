# Makefile for Project part 2
all: part2

part2.tab.c part2.tab.h:	part2_bison.y
	bison -d part2_bison.y

lex.yy.c: part2_lex.lex part2.tab.h
	flex part2_lex.lex

part2: lex.yy.c part2.tab.c part2.tab.h part2_helpers.c part2_helpers.h
	gcc -o part2 part2_bison.tab.c lex.yy.c part2_helpers.c part2_helpers.h

clean:
	rm part2 part2_bison.tab.c lex.yy.c part2_bison.tab.h


