#include <any>
#include <cstddef>
#include <iostream>
#include <string>
#include <sstream>

#include "antlr4-runtime.h"
#include "ExpressionLexer.h"
#include "ExpressionParser.h"
#include "EvaluationVisitor.h"

int main(int argc, char const* argv[])
{
  std::string input;
  if (1 < argc) {
    std::stringstream argumentStream;
    for (size_t index = 1; index < argc; ++index) {
      argumentStream << argv[index];
    }
    input = argumentStream.str();
  }
  else {
    std::getline(std::cin, input);
  }
  antlr4::ANTLRInputStream stream(input);
  ExpressionLexer lexer(&stream);
  antlr4::CommonTokenStream tokens(&lexer);
  ExpressionParser parser(&tokens);

  EvaluationVisitor visitor;
  
  int result = std::any_cast<int>(visitor.visitStart(parser.start()));

  std::cout << result << std::endl;
  return 0;
}
