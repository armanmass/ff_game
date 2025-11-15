cmake_minimum_required(VERSION 4.1)
project(ff_game)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
find_package(sdl3 REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(ff_game ${SOURCES})

target_link_libraries(ff_game PRIVATE sdl3)
target_include_directories(ff_game PRIVATE 
    "${CMAKE_SOURCE_DIR}/include"  # So you can do #include "game/SDLApplication/..."
    "${CMAKE_SOURCE_DIR}/src"      # For headers next to .cpp files
)