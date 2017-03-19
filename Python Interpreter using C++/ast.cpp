// Companion source code for "flex & bison", published by O'Reilly
// helper functions for fb3-1
#  include <iostream>
#  include <stdlib.h>
#  include <cmath>
#  include <iomanip>
#  include <typeinfo>
#  include <sstream>
#  include "ast.h"
#  include <fstream>
#  include "Symboltable.h"
#  include "tablemanager.h" 


double CallFuncNode::eval()
{
  //std::cout<<"call eval called";
  TableManager& instance = TableManager::getInstance();
  Ast* ast=instance.getAstTable(name);
  //std::cout<<ast->getNodetype();
  if(!(dynamic_cast<AstNumber*>(ast)))
  {
    //std::cout<<"call eval passed";
    //std::cout<<ast->eval();
     ast->eval();
  }
  else
  {
    std::cout<<"variable not defined"<<name;
  }

  return 0;
}

double SuiteNode::eval()
{
  //std::cout<<"suite eval called";
  TableManager& instance = TableManager::getInstance();
  instance.incrScope();
  instance.createSymbolTable();
  //std::cout<<instance.getCurrentScope();
  
  std::vector<Ast*>::const_iterator it=v->end();
  while(it!=v->begin())
  {
    --it;
    (*it)->eval();
  }

  instance.destroySymbolTable();
  instance.decrScope();

return 0;
}


double AstFunc::eval()
{
  //std::cout<<"func eval called";
  TableManager& instance = TableManager::getInstance();
  instance.InsertAstTable(n,left);
  
  return 0;
}

double AstName::eval()
{
  TableManager& instance = TableManager::getInstance();
      return instance.getCurrentTable()->getAst(name)->getNumber();
}
      

double ExprNode::eval() {
  double temp=right->eval();
  //std::cout<<"here";
    if(std::isinf(temp) || temp != temp) 
    {
      std::cout << "ZeroDivisionerror" << std::endl;
    }
    TableManager& instance = TableManager::getInstance();
    instance.getCurrentTable()->CreateAst(left->getName(), temp,checkpoints(right));
    //std::cout<<"inserted";
    return 0;
}


void treeFree(Ast *a) {
  switch(a->getNodetype()) {
   // two subtrees
  case 'B':
  case 'P':

    treeFree(a->getRight());

   // one subtrees
  case 'U':
  
    treeFree(a->getLeft());

   //no subtree
   
  case 'I':
  case 'D':
  case 'C':
    delete a;
    break;

  default: std::cout << "internal error: bad node "
                << a->getNodetype() << std::endl;;
  }
}


bool Ast::checkInt(const Ast* a) const{
  double l =left->eval() ,
                    r = right->eval();

    return !checkpoints(a) && !std::isinf(l) && !std::isinf(r);

}
bool Ast::checkpoints(const Ast* ast)const{

    if(ast == NULL) return false;

    if(ast->getNodetype()=='D')
    {
      return true;
    }
    else if(ast->getNodetype()=='I')
    {
      return false;
    }
     else if(ast->getNodetype()=='C')
    {
       TableManager& instance = TableManager::getInstance();
            //return eval(instance.getAst(a->getName()));

      //Symboltable instance;
            return (instance.getCurrentTable()->getAst(ast->getName())->getNodetype() == 'D');
    }
     else if(ast->getNodetype()=='^')
    {
      if(right->eval() < 0 ) return true;
    }
    else if(ast->getNodetype()=='M' || ast->getNodetype()=='P' || ast->getNodetype()=='T')
    {
      if(checkpoints(ast->getLeft()))
              return true;
            else 
              return false;
    }
    else
    {
      if(checkpoints(ast->getLeft()) || checkpoints(ast->getRight()) ) return true;
    }
    return false;
  }
