#include "SDLApplication/SDLApplication.hpp"

int main(int argc, char** argv) {
    SDLApplication sdl_app{"Game Window"};
    sdl_app.MainLoop();
    return 0;
}