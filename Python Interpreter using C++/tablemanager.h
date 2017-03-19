#ifndef TABLE_MANAGER_H
#define TABLE_MANAGER_H
#include <iostream>
#include <vector> 
#include <map>
#include <list>
#include "ast.h"
#include "Symboltable.h"
//class Symboltable;
class TableManager{
public:
	static TableManager& getInstance();
	void InsertAstTable(std::string Id, Ast* st);
	void CreateAstTable(std::string Id, double num, bool checkpoints);
	~TableManager();
	void destroySymbolTable()
	{
		delete vecSymbolTable.back();
		vecSymbolTable.pop_back();
	}

	int Symboltablesize(){
		return vecSymbolTable.size();
	}

	void createSymbolTable(){
		vecSymbolTable.push_back(new Symboltable());
	}
	
	void incrScope(){
		++currentScope;
	}
	void decrScope()
	{
		--currentScope;
	}
	void setCurrentScope(int index)
	{
		currentScope=index;
	}
	int getCurrentScope()
	{
		return currentScope;
	}
	Symboltable* getSymbolTable(int index)
	{
		return vecSymbolTable[index];
	}
	Symboltable* getCurrentTable(){
		return vecSymbolTable[currentScope];
	}
	Ast* getAstTable(const std::string&);
private:
	
	int currentScope=0;
	std::vector<Symboltable*> vecSymbolTable;
	TableManager(){
		vecSymbolTable.push_back(new Symboltable());
	}
	TableManager(const TableManager&);
  	TableManager& operator=(const TableManager&);
};
#endif