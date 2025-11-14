#pragma once
#include <SDL3/SDL_rect.h>
#include <vector>

struct ParticleSystem {
    struct ParticleAttributes {
        float speed;
        float velocity;
    };
    std::vector<SDL_FPoint> particles;
    std::vector<ParticleAttributes> attributes;
    ParticleSystem(size_t numPoints) {}
};