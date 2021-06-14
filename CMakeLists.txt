#指定需要CMAKE的最小版本
cmake_minimum_required(VERSION 3.4.1)

project(SubSchemeCompiler)

# add_compile_options(-fexceptions)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0 -g ")

set(CMAKE_CXX_COMPILER "/usr/bin/g++")

# if ((CMAKE_BUILD_TYPE MATCHES "Debug"))

#     add_definitions(-DDEBUG)

# endif()

# set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
# set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

include_directories(
  ${CMAKE_SOURCE_DIR}/
)

set(myparser_src
  ${CMAKE_SOURCE_DIR}/src/global.h
  ${CMAKE_SOURCE_DIR}/src/exception.h
  ${CMAKE_SOURCE_DIR}/src/scanner.h
  ${CMAKE_SOURCE_DIR}/src/scanner.cc
  ${CMAKE_SOURCE_DIR}/src/ast.h
  ${CMAKE_SOURCE_DIR}/src/ast-inl.h
  ${CMAKE_SOURCE_DIR}/src/ast.cc
  ${CMAKE_SOURCE_DIR}/src/parser.h
  ${CMAKE_SOURCE_DIR}/src/parser.cc
  ${CMAKE_SOURCE_DIR}/src/ast-visitor.h
  ${CMAKE_SOURCE_DIR}/src/code-generator.h
  ${CMAKE_SOURCE_DIR}/src/code-generator.cc
  ${CMAKE_SOURCE_DIR}/src/value.h
  ${CMAKE_SOURCE_DIR}/src/value.cc
  ${CMAKE_SOURCE_DIR}/src/compiler.h
  ${CMAKE_SOURCE_DIR}/src/compiler.cc
)

add_executable(cctest
  ${myparser_src}
  ${CMAKE_SOURCE_DIR}/cctest/test_main.cc
)