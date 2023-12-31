cmake_minimum_required(VERSION 3.15)
project(Kollision LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)
find_package(SDL2 REQUIRED)

set(SRCS
    src/main.cpp
    src/game.cpp
    src/board.cpp
    src/player.cpp
    src/ball.cpp
    src/movingball.cpp
    src/renderer.cpp
)
set(HEADERS
    include/game.hpp
    include/board.hpp
    include/player.hpp
    include/ball.hpp
    include/movingball.hpp
    include/renderer.hpp
    include/vector.hpp
    include/utils.hpp
    include/config.h
)
set(ASSETS
    # ...
)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter -Wno-missing-field-initializers")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
find_package(SDL2 REQUIRED)
find_package(SDL2_gfx REQUIRED)

add_executable(Kollision ${SRCS} ${HEADERS})
set_target_properties(Kollision PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(Kollision PRIVATE -Wall -Wextra -O0 -g)
target_link_libraries(Kollision PRIVATE SDL2::Main SDL2::GFX)

