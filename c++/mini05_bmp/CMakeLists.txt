cmake_minimum_required(VERSION 3.1)
project(mini05)

# Configure compiler warnings
if (CMAKE_CXX_COMPILER_ID MATCHES Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  # using regular Clang or AppleClang or GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic -Wold-style-cast")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "/permissive- /W4 /EHsc")
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

set(SOURCES bmp/bmp.cpp bmp_image.cpp)
add_library(mini05_bmp_image ${SOURCES})

add_executable(mini05_main main.cpp)
target_link_libraries(mini05_main mini05_bmp_image)

file(GLOB TEST_SOURCES test*.cpp)
add_executable(mini05_tests ${TEST_SOURCES})
target_link_libraries(mini05_tests mini05_bmp_image)

# copy example.bmp to build directory
configure_file(example.bmp example.bmp COPYONLY)
