#pragma once
#include <SDL3/SDL.h>

struct Config {
    static constexpr int windowStartWidth{1000};
    static constexpr int windowStartHeight{600};
    static constexpr Uint64 fpsUpdateIntervalMS{1000};
    bool isFullscreen{false};
};