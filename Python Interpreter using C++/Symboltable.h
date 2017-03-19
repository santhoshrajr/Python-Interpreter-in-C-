#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <utility>
#include <cmath>
#include "ast.h"
#include <iostream>
#include <map>
class Symboltable
{
public:
	//static Symboltable& getInstance();
	~Symboltable();
	void InsertAst(std::string Id, Ast* ast);
	Ast* getAst(std::string Id);
	void CreateAst(std::string Id, double num, bool checkpoints);
	void freeMap();
	Symboltable():
		mapIds()
	{}
private:
	std::map<std::string, Ast*> mapIds;
	
	Symboltable(const Symboltable&);
  Symboltable& operator=(const Symboltable&);
};
#endif