#include "ast.h"
#include "Symboltable.h"
Symboltable::~Symboltable()
{
	//std::cout << "Deleting Symboltable" << std::endl;
  std::map<std::string, Ast*>::iterator itAst = mapIds.begin();
  while ( itAst != mapIds.end() ) {
    delete itAst->second ;

    ++itAst;
  }
  mapIds.clear();
}

/*Symboltable& Symboltable::getInstance() {
  static Symboltable table;
  return table;
}*/

//Insert ast for the identifier
void Symboltable::InsertAst(std::string Id, Ast* ast){
		std::map<std::string, Ast*>::iterator itAst = mapIds.begin();
		if(mapIds.find(Id) == mapIds.end())
			
			mapIds.insert(std::make_pair(Id, ast));
		
		else
			
			mapIds.find(Id)->second = ast;
	}

	void Symboltable::CreateAst(std::string Id, double num, bool checkpoints){
		

		Ast* ast;

		if((std::floor(num) - num) || checkpoints)  

			ast = new AstNumber('D',num);
          
          else 

          	ast = new AstNumber('I',num);

        InsertAst(Id, ast);
	}

	//Find The Identifier else create
	Ast* Symboltable::getAst(std::string Id){
		
		std::map<std::string, Ast*>::iterator it = mapIds.find(Id);

		if( it != mapIds.end() )
			return it->second;
		else{
			Ast* ast = new AstNumber('I',0);
			InsertAst(Id, ast);
			return ast;
		}
	}


	void Symboltable::freeMap(){
		/*for(std::map<std::string, Ast*>::iterator it = mapIds.begin(),
			e=mapIds.end();it!=e;++it)
		{
			delete it->second;
		}*/
		std::map<std::string, Ast*>::iterator it = mapIds.begin();
		while(it != mapIds.end()){
			delete it->second;
			//mapIds.erase(it);
			++it;
		}
		mapIds.clear();
	}