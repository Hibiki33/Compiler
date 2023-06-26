cmake_minimum_required(VERSION 3.24)

project(Compiler)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/
)

add_executable(
        Compiler
        main.cpp
        src/Lexer.cpp
        src/Parser.cpp
        src/Token.cpp
        src/Ast.cpp )
