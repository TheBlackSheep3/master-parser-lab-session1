# Parser Lab Session 1 - Calculator

## Task
Build parser for “calculator”
- Input is arithmetic expression
- Output should be value of the expression
- Error handling is not required, but appreciated
- Minimal set of expressions:
    - Terms over natural numbers
    - with `+` and `*` and parentheses `(`, `)`

## Prerequisites
The tool used for generating the lexer and parser is [ANTLR v4](https://github.com/antlr/antlr4). To compile and run the software the following tools are needed
- Java (because ANTLR is written in Java)
- ANTLR v4 (the JAR-file can be downloaded [here](https://www.antlr.org/download.html))
- [CMake](https://cmake.org/download/) (at least version 3.7)
- C++ compiler supporting C++17 (e.g. Apple Clang [used to develop this program], Clang, g++, MSVC)

## Build
To build the project run
```shell
cmake -B bld
cmake --build bld
```
The path to ANTLR JAR-file can be set with the option `ANTLR_EXECUTABLE` like so
```shell
cmake -B bld -DANTLR_EXECUTABLE=/opt/homebrew/Cellar/antlr/4.13.1/antlr-4.13.1-complete.jar
```
The default value is `/opt/homebrew/Cellar/antlr/4.13.1/antlr-4.13.1-complete.jar`.

## Usage
After compilation the binary is located in the `bld` directory. After running it the user has to input the expression which is to be evaluated and press enter. The result of the expression will be displayed on the next line.
```shell
./bld/expression
3+4*(13+11)
99
```

## Accepted expressions
The program accepts and evaluated the following grammar of expressions.
```
<expression> ::= <term> | <term> "+" <expression>
<term> ::= <factor> | <factor> "*" <term>
<factor> ::= <number> | "(" <expression> ")"
<number> ::= <digit> | <number><digit>
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
```

## Tools used for solution

## Statements about final CFG
