#include "tablemanager.h"


TableManager& TableManager::getInstance()
{
	static TableManager instance;
	return instance;
}

TableManager::~TableManager()
{
	for(unsigned int i=0;i<vecSymbolTable.size();i++)
	{
		delete vecSymbolTable[i];
	}
	/*std::vector<Symboltable*>::iterator it=vecSymbolTable.begin();
	while(it!=vecSymbolTable.end)
	{
		delete *it;
		++it;
	}*/
}


Ast* TableManager::getAstTable(const std::string& fnname)
{
//std::cout<<"no variable";
	for(int i=vecSymbolTable.size()-1;i>=0;--i)
	{
		Symboltable* st=(vecSymbolTable[i]);
		Ast* ast=st->getAst(fnname);
		if(ast!=NULL) return ast;
	}
	//std::cout<<"no variable here";
	Ast* ast=new AstNumber('I',0);
	InsertAstTable(fnname,ast);
			return ast;
}

void TableManager::CreateAstTable(std::string Id, double num, bool checkpoints)
{
	Ast* ast;

		if((std::floor(num) - num) || checkpoints)  

			ast = new AstNumber('D',num);
          
          else 

          	ast = new AstNumber('I',num);

        InsertAstTable(Id, ast);
}

void TableManager::InsertAstTable(std::string Id, Ast* ast){
	Symboltable* st=(getCurrentTable());
		st->InsertAst(Id,ast);

}