find_path(SDL3_INCLUDE_DIR
    NAMES SDL3/SDL.h
    PATHS ${CMAKE_SOURCE_DIR}/include/thirdparty
    NO_DEFAULT_PATH
)

find_library(SDL3_LIBRARY
    NAMES SDL3 libSDL3.so libSDL3.a
    PATHS 
        /usr/local/lib
        /usr/lib
        /usr/lib/x86_64-linux-gnu
        ${CMAKE_SOURCE_DIR}/lib
)

if(SDL3_INCLUDE_DIR AND SDL3_LIBRARY)
    add_library(sdl3 INTERFACE IMPORTED)
    set_target_properties(sdl3 PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${SDL3_INCLUDE_DIR}"
        INTERFACE_LINK_LIBRARIES "${SDL3_LIBRARY}"
    )
    set(sdl3_FOUND TRUE)
else()
    set(sdl3_FOUND FALSE)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(sdl3 
    REQUIRED_VARS SDL3_LIBRARY SDL3_INCLUDE_DIR
)
