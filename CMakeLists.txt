# minimum required CMAKE version
CMAKE_MINIMUM_REQUIRED(VERSION 3.14 FATAL_ERROR)

project("parser-lab1-expression" VERSION 1.1)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# compiler must be 17
set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_NAME expression)
configure_file(config.hpp.in config.hpp)

include(cmake/CPM.cmake)

CPMAddPackage(
	NAME argparse
	VERSION 3.0
	GITHUB_REPOSITORY p-ranav/argparse
)

# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)

option(PRINT_COMPILER "if the used compiler should be printed" OFF)

# Specify the version of the antlr4 library needed for this project.
# By default the latest version of antlr4 will be used.  You can specify a
# specific, stable version by setting a repository tag value or a link
# to a zip file containing the libary source.
# set(ANTLR4_TAG 4.13.1)
# set(ANTLR4_ZIP_REPOSITORY https://github.com/antlr/antlr4/archive/refs/tags/4.13.1.zip)

# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

# set variable pointing to the antlr tool that supports C++
# this is not required if the jar file can be found under PATH environment
set(ANTLR_EXECUTABLE /opt/homebrew/Cellar/antlr/4.13.1/antlr-4.13.1-complete.jar CACHE FILEPATH "path to ANTLR4 JAR")
# add macros to generate ANTLR Cpp code from grammar
find_package(ANTLR REQUIRED)

# Call macro to add lexer and grammar to your build dependencies.
antlr_target(ExpressionGrammarParser Expression.g4 LEXER PARSER VISITOR)

if(PRINT_COMPILER)
        message("compiling using ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")
endif()

# include generated files in project environment
include_directories(${ANTLR_ExpressionGrammarParser_OUTPUT_DIR})

# add generated grammar to demo binary target
add_library(EvaluationVisitor OBJECT EvaluationVisitor.cpp ${ANTLR_ExpressionGrammarParser_CXX_OUTPUTS})
target_link_libraries(EvaluationVisitor antlr4_static)

add_executable(${EXECUTABLE_NAME} main.cpp)
target_link_libraries(${EXECUTABLE_NAME} EvaluationVisitor argparse)
target_include_directories(${EXECUTABLE_NAME}
  PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR})

# enable testing
include(CTest)

# define a function to simplify adding tests
function(do_test name target arg result)
  add_test(NAME ${name} COMMAND ${target} --expression ${arg})
  set_tests_properties(${name}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endfunction()

# do a bunch of result based tests
do_test(Number expression "11" "11")
do_test(Addition expression "1+2" "3")
do_test(Multiplication expression "3*5" "15")
do_test(Composition expression "3+4*(13+11)" "99")
