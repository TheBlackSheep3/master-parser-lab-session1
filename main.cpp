#include <any>
#include <iostream>
#include <string>

#include "antlr4-runtime.h"
#include "ExpressionLexer.h"
#include "ExpressionParser.h"
#include "EvaluationVisitor.h"

int main(int argc, char const* agrv[])
{
  std::string input;
  std::getline(std::cin, input);
  antlr4::ANTLRInputStream stream(input);
  ExpressionLexer lexer(&stream);
  antlr4::CommonTokenStream tokens(&lexer);
  ExpressionParser parser(&tokens);

  EvaluationVisitor visitor;
  
  int result = std::any_cast<int>(visitor.visitExpression(parser.expression()));

  std::cout << result << std::endl;
  return 0;
}
