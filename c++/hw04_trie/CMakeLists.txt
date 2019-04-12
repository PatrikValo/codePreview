cmake_minimum_required(VERSION 3.1)
project(mini01)

# Configure compiler warnings
if (CMAKE_CXX_COMPILER_ID MATCHES Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  # using regular Clang or AppleClang or GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic -Wold-style-cast")
  # the following two lines switch coverage analysis on
  # uncomment them if you want to use coverage analysis
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
  # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "/permissive- /W4 /EHsc")
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()


add_executable(trie morse.cpp)
add_executable(trie_tests main.cpp student_tests.cpp)
