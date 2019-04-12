cmake_minimum_required(VERSION 3.1)
project(mini06)

# Configure compiler warnings
if (CMAKE_CXX_COMPILER_ID MATCHES Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  # using regular Clang or AppleClang or GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic -Wold-style-cast")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "/permissive- /W4 /EHsc")
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

add_library(mini06_matrix matrix.cpp)
target_include_directories(mini06_matrix PUBLIC ".")

add_executable(mini06_main main.cpp)
target_link_libraries(mini06_main mini06_matrix)

add_executable(mini06_test test-main.cpp test-student.cpp)
target_link_libraries(mini06_test mini06_matrix)
