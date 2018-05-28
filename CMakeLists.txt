cmake_minimum_required(VERSION 3.8)
project(IPZ)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp lexer/lexer.cpp lexer/lexer.h front_end/out.cpp front_end/out.h front_end/error.cpp front_end/error.h syntax/syntax.cpp syntax/syntax.h)
add_executable(IPZ ${SOURCE_FILES})