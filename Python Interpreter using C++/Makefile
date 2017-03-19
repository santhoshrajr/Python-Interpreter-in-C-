CCC = g++
LEX = flex
YACC = bison
CFLAGS = -Wall -std=c++11
LEXFLAGS = -Wno-unused

YACCDEBUG = -vtd

OBJS = main.o tablemanager.o Symboltable.o ast.o parse.tab.o lex.yy.o 

run: $(OBJS)
	$(CCC) $(CFLAGS) -o run $(OBJS)

main.o: main.cpp parse.y scan.l parse.tab.cpp lex.yy.cpp tablemanager.cpp Symboltable.cpp 
	$(CCC) $(CFLAGS) -c main.cpp

parse.tab.cpp: parse.y ast.h Symboltable.h tablemanager.h
	$(YACC) $(YACCDEBUG) -oparse.tab.cpp -d parse.y

tree.o: tree.cpp tree.h
	$(CCC) $(CFLAGS) -c tree.cpp

ast.o: ast.cpp ast.h Symboltable.h tablemanager.h
	$(CCC) $(CFLAGS) -c ast.cpp

parse.tab.o: parse.tab.cpp
	$(CCC) $(CFLAGS) -c parse.tab.cpp

lex.yy.cpp: scan.l parse.tab.o
	$(LEX) -olex.yy.cpp scan.l

lex.yy.o: lex.yy.cpp
	$(CCC) $(CFLAGS) $(LEXFLAGS) -c lex.yy.cpp
Symboltable.o: Symboltable.h
	$(CCC) $(CFLAGS) -c Symboltable.cpp
tablemanager.o: tablemanager.h 
	$(CCC) $(CFLAGS) -c tablemanager.cpp
	
clean:
	rm -f run *.o  parse.tab.cpp lex.yy.cpp
	rm -f parse.tab.hpp
	rm -f parse.output
