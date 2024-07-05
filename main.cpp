#include <algorithm> // std::equal
#include <any>       // std::any_cast
#include <cctype>    // std::tolower
#include <cstdlib>   // std::exit
#include <exception> // std::exception
#include <fstream>   // std::ifstream, std::ofstream
#include <iostream>  // std::cin, std::cout, std::cerr
#include <string>    // std::getline, std::string

#include <argparse/argparse.hpp> // argparse::ArgumentParser

#include "EvaluationVisitor.h"
#include "ExpressionLexer.h"
#include "ExpressionParser.h"
#include "antlr4-runtime.h"
#include "config.hpp"

int parse(std::string const& input) {
  antlr4::ANTLRInputStream stream(input);
  ExpressionLexer lexer(&stream);
  antlr4::CommonTokenStream tokens(&lexer);
  ExpressionParser parser(&tokens);

  EvaluationVisitor visitor;

  return std::any_cast<int>(visitor.visitStart(parser.start()));
}

bool ignore_case_char_equals(char a, char b) {
  return std::tolower(a) == std::tolower(b);
}

bool ignore_case_string_equals(std::string const& a, std::string const& b) {
  return std::equal(a.begin(), a.end(), b.begin(), b.end(), ignore_case_char_equals);
}

int main(int argc, char const* argv[]) {
  argparse::ArgumentParser program(PROJECT_EXECUTABLE, PROJECT_VERSION);
  program.add_argument("-o", "--output")
      .help("write output to OUTPUT_FILE")
      .metavar("OUTPUT_FILE");
  program.add_description(
      "Evaluate an arithmetic expression and output its result. The "
      "expressions can consist of natural numbers, the operators '+' and '*'. "
      "Subexpressions can be grouped with parenthesis.");
  program.add_epilog(
      "The parser for this program was generated using ANTLR 4 and the "
      "generated parser is a LL(1) parser.");

  auto& group = program.add_mutually_exclusive_group();
  group.add_argument("-f", "--file")
      .help("read input from INPUT_FILE")
      .metavar("INPUT_FILE");
  group.add_argument("-i", "--interactive")
      .help("run the program in interactive mode")
      .flag();
  group.add_argument("-e", "--expression")
      .help("supply expression as command line parameter")
      .metavar("EXPRESSION");

  try {
    program.parse_args(argc, argv);
  } catch (std::exception const& e) {
    std::cerr << e.what() << "\n\n" << HELP_HINT;
    std::exit(EXIT_FAILURE);
  }

  std::string input;
  if (program.get<bool>("--interactive")) {
    if (program.present("--output")) {
      std::cerr << "Argument '-o/--output OUTPUT_FILE' not allowed with "
                   "'-i/--interactive'"
                << "\n\n"
                << HELP_HINT;
      std::exit(EXIT_FAILURE);
    }
    std::string const quit = "quit";
    std::string const exit = "exit";
    while (true) {
      std::cout << "Enter an expression to be evaluated." << '\n';
      std::getline(std::cin, input);
      if (ignore_case_string_equals(input, quit) || ignore_case_string_equals(input, exit))
      {
        std::cout << "Exiting...\n";
        std::exit(EXIT_SUCCESS);
      }
      std::cout << parse(input) << "\n\n";
    }
  } else if (auto expression = program.present("--expression")) {
    input = *expression;
  } else if (auto input_file = program.present("--file")) {
    std::ifstream file_stream(*input_file);
    file_stream >> input;
  } else {
    std::cin >> input;
  }

  if (auto output_file = program.present("--output")) {
    std::ofstream file_stream(*output_file);
    file_stream << parse(input) << '\n';
  } else {
    std::cout << parse(input) << '\n';
  }

  return EXIT_SUCCESS;
}
