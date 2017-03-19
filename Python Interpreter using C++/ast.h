//  Declarations for an AST calculator
//  From "flex & bison", fb3-1, by John Levine
//  Adapted by Brian Malloy
#ifndef AST_H
#define AST_H
#include <string>
#include <vector>
#include <iostream>
#  include <cmath>
extern void yyerror(const char*);
extern void yyerror(const char*, const char);

class Ast {
public:
  Ast(int n) : nodetype(n) {}
  Ast(char node,Ast* l,Ast* r):nodetype(node),left(l),right(r){}
  virtual ~Ast() {}
  char getNodetype() const { return nodetype; }
  bool checkInt(const Ast*) const;
  bool checkpoints(const Ast*) const;
  virtual double eval() 
  {
    std::cout<<" eval called";
    throw std::string("no eval");
  }
  virtual Ast* getLeft() const 
  { return left; }
  virtual Ast* getRight() const 
  { 
    return right;
    //throw std::string("No Right"); 
  }
  virtual double getNumber() const { throw std::string("No Number"); }
  virtual std::string getName() const { throw std::string("No Name");}
  //virtual std::vector<Ast*>* getFunc() const {throw std::string("No Func");}
protected:
  char nodetype;
  Ast* left;
  Ast* right;
};


class ExprNode:public Ast{
public:
  ExprNode(char nodetype,Ast* l,Ast* r):Ast('X',l,r){}
  virtual double eval();
 /* {
    double temp=right->eval();
    return temp;
  }
  Symboltable& instance = Symboltable::getInstance();
    instance.CreateAst(l, temp,checkpoints(r));
    
    treeFree(ast);*/

};

class AstNode : public Ast {
public:
  AstNode(char nodetype, Ast* l, Ast* r) : 
    Ast(nodetype), left(l), right(r) 
  {}
  virtual ~AstNode() {}
  virtual Ast* getLeft() const  { return left; }
  virtual Ast* getRight() const { return right; }
private:
  Ast *left;
  Ast *right;
};

class BinaryNode : public Ast {
public:
  BinaryNode(char nodetype, Ast* l, Ast* r) : 
    Ast(nodetype), left(l), right(r) 
  {}
  virtual ~BinaryNode() {}
  virtual Ast* getLeft() const  { return left; }
  virtual Ast* getRight() const { return right; }
private:
  Ast *left;
  Ast *right;
};


class BinaryAddNode : public Ast {
public:
  BinaryAddNode(char nodetype, Ast* l, Ast* r) : 
    Ast('B',l,r)
  {}
  virtual ~BinaryAddNode() {}
  virtual double eval()
  {
    
    return  left->eval() + right->eval(); 
  }
  

};

class BinaryMinNode : public Ast {
public:
  BinaryMinNode(char nodetype, Ast* l, Ast* r) : 
    Ast('B',l,r)
  {}
  virtual ~BinaryMinNode() {}
  virtual double eval()
  {
    return  left->eval()-right->eval(); 
  }
  
};

class BinaryMulNode : public Ast {
public:
  BinaryMulNode(char nodetype, Ast* l, Ast* r) : 
    Ast('B',l,r) 
  {}
  virtual ~BinaryMulNode() {}
  double v=0;
  virtual double eval()
  {
    double l = left->eval(), r = right->eval();
            if(checkInt(this))
                v= (int)l * (int)r;
            else
                v= l * r;
    return v;
  }
 
};

class BinaryPowNode : public Ast {
public:
  BinaryPowNode(char nodetype, Ast* l, Ast* r) : 
    Ast('P',l,r)
  {}
  virtual ~BinaryPowNode() {}
  virtual double eval()
  {
    return std::pow(left->eval(),right->eval());
  }

};


class BinaryModNode : public Ast {
public:
  BinaryModNode(char nodetype, Ast* l, Ast* r) : 
    Ast('B',l,r) 
  {}
  virtual ~BinaryModNode() {}
  virtual double eval()
  {
    double l = left->eval(), r = right->eval();          
            if( (l >=0 && r >= 0) ||
                (l <=0 && r <= 0) )
              {
                return std::fmod( l, r);
              }
            else
            {
                double temp = std::fmod(l, r);
                if(temp) return r + temp;
                else   return 0;
            }
  }
  
};

class BinaryDivNode : public Ast {
public:
  BinaryDivNode(char nodetype, Ast* l, Ast* r) : 
    Ast('B',l,r)
  {}
  virtual ~BinaryDivNode() {}
  double v = 0;
  virtual double eval()
  {
    double l = left->eval(), 
                  r = right->eval();
            if( (checkInt(this)) && right->eval())
            {
             
                v= (double)l / r;
                v= std::floor(v);
            }
            else
                v= l / r;
            return v;

  }
  
};

class BinaryDslashNode : public Ast {
public:
  BinaryDslashNode(char nodetype, Ast* l, Ast* r) : 
    Ast('B',l,r) 
  {}
  virtual ~BinaryDslashNode() {}
  double v;
  virtual double eval()
  {
    double l = left->eval(), 
                  r = right->eval();
            if(right->eval())
            {
                v = (double)l / r;
                v = std::floor(v);
            }
            else
                v = l / r;
      return v;
  }
  
};

class UnaryMinNode : public Ast {
public:
  UnaryMinNode(char nodetype, Ast* l,Ast* r) : 
    Ast('U',l,NULL)
  {}
  virtual ~UnaryMinNode() {}
  virtual double eval()
  {
    return -left->eval(); 
  }
  


  
};

class UnaryPlusNode : public Ast {
public:
  UnaryPlusNode(char nodetype, Ast* l,Ast* r) : 
    Ast('U',l,NULL)
  {}
  virtual ~UnaryPlusNode() {}
  virtual double eval()
  {
    return left->eval(); 
  }
  
  
};

class UnaryTildaNode : public Ast {
public:
  UnaryTildaNode(char nodetype, Ast* l,Ast* r) : 
    Ast('U',l,NULL)
  {}

  virtual ~UnaryTildaNode() {}
  virtual double eval()
  {
    double v=0;
    v = (-1) * ( 1+ left->eval());
            if(!v) v= v*v; 
    return v; 
  }
 
  
};





class CallFuncNode:public Ast{
public:
  CallFuncNode(std::string nam):
  Ast('R'),name(nam){//std::cout<<"func call  called"
  ;}
  virtual double eval();
private:
  std::string name;

};
class SuiteNode:public Ast
{
public:
  SuiteNode(std::vector<Ast*>* vec):
  Ast('R'),v(vec)
  {//std::cout<<"suite  called"
  ;}
  virtual ~SuiteNode()
  {
    std::vector<Ast*>::iterator it=v->begin();
    while(it!=v->end())
    {
      delete *it;
      ++it;
    }
  }
  virtual double eval();
private:
  std::vector<Ast*>* v;
};


class AstFunc:public Ast{
public:

  AstFunc(char nodetype,const std::string name,Ast* vec):

  Ast(nodetype,vec,NULL),n(name)
  {//std::cout<<"func const called"
  ;}
  virtual ~AstFunc(){}
  virtual double eval();
  //virtual std::vector<Ast*>* getFunc() const {return v;}
private:
  std::string n;
  

};

class PrintNode:public Ast{
public:
  PrintNode(Ast* ast ):Ast('P',ast,NULL){}
  virtual double eval()
  {
    
    double value = left->eval();

        if(std::isinf(value) || value != value) 
        {
              std::cout << "ZeroDivisionerror" << std::endl;
               
        }
      else
        {
             
              double evaluate = left->eval();

              std::cout << evaluate;
             

              if(!(floor(evaluate) - evaluate) && checkpoints(left))  std::cout << ".0";
              
              std::cout << std::endl;
              
              
          }
        

      return 0;
  }

};



class AstNumber : public Ast {
public:
  AstNumber(char nodetype, double n) : Ast(nodetype), number(n) {} 
  virtual ~AstNumber() {}
  virtual double getNumber() const
  {
    return number;
  }
  virtual double eval()
  {
    return number;
  }
private:
  double number;
};

class AstName : public Ast{
public:
    AstName(char nodetype, std::string name) : Ast(nodetype), name(name) {}
    virtual ~AstName() {}
    virtual double eval(); 
    virtual std::string getName() const  { return name; }
private:
    std::string name;
};



//double eval();   // Evaluate an AST
void treeFree(Ast*); // delete and free an AST 
//bool checkpoints(const Ast*);

#endif //AST_H