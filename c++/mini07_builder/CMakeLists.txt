cmake_minimum_required(VERSION 3.0)

project(mini07)

if (CMAKE_CXX_COMPILER_ID MATCHES Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  # using regular Clang or AppleClang or GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic -Wold-style-cast")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std=c++14 /W4 /WX")
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

add_executable(mini07_test Print.cpp test-student.cpp test-main.cpp)
add_executable(mini07_playground Print.cpp main.cpp)
