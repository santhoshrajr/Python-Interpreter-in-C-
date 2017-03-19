#include "ast.h"
#include "Symboltable.h"
#include <iostream>
#include "parse.tab.hpp"

extern FILE * yyin;
extern int keywords;
extern int identifiers;
extern int numbers;
extern int yydebug;
extern int yylineno;

int yylex(void);
extern int yyparse();


void openFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
      std::cerr << "Could not open file \"" 
                << filename 
                << "\"" << std::endl;
      exit(1);
    }
    yyin = file;
}

void printInfo(void)
{
 // std::cout << "keywords: " << keywords << std::endl;
  /*std::cout << "identifiers: " << identifiers << std::endl;
  std::cout << "numbers: " << numbers << std::endl;
  std::cout << "lines: " << yylineno << std::endl;*/
  // 
}

int main(int argc, char * argv[]) {
  try{
  if (argc > 1) { // user-supplied filename
    openFile(argv[1]);
  }
   yydebug =0;
  int parseErrors = yyparse();
  
 // Symboltable& instance = Symboltable::getInstance();
  //instance.freeMap();
  if ( parseErrors ) {
    std::cerr << "Abnormal termination" << std::endl;
    return 1;
  }
  printInfo();
  return 0;
}
catch(std::string const &exec)
{
  std::cout << "Exception caught " << exec << "\n";
}
}

int oldMain() {
  yylex();
  printInfo();
  return 0;
}
