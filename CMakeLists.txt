cmake_minimum_required(VERSION 4.1)
project(ff_game)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
find_package(sdl3 REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(ff_game ${SOURCES})

target_link_libraries(ff_game PRIVATE sdl3)
target_include_directories(ff_game PRIVATE 
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/src"
)

add_custom_command(TARGET ff_game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:ff_game>/assets"
    COMMENT "Copying assets directory"
)