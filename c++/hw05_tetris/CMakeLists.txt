cmake_minimum_required(VERSION 3.5)
project(tetris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp Cube.h Tetromino.cpp Tetromino.h Game.h SDLWrapper.h SDLWrapper.cpp Engine.h Game.cpp Textures.h Textures.cpp TextureRef.h RandomGenerator.h RandomGenerator.cpp Factory.h Engine.cpp Dimension.h Dimension.cpp Geometry.h Geometry.cpp Stock.h Score.h Score.cpp Stock.cpp)

add_executable(tetris ${SOURCE_FILES})
target_link_libraries(tetris ${SDL2_LIBRARIES})