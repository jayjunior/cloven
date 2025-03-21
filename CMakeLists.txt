cmake_minimum_required(VERSION 3.30)
project(cloven)

set(CMAKE_CXX_STANDARD 20)
add_executable(cloven Cloven.cpp
        Scanner/Scanner.cpp
        Tokens/Token.cpp
)
add_executable(generateAst tool/GenerateAst.cpp tool/GenerateAst.h)
add_executable(astPrinter Operations/AstPrinter.cpp)
