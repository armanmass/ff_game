#include <SDL3/SDL.h>
#include <cassert>
#include "SDLApplication.hpp"

int main(int argc, char** argv) {
    SDLApplication sdl_app{"Game Window"};
    sdl_app.MainLoop();
    return 0;
}