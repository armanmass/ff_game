#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>
#include <vector>

#include "Config/Config.hpp"

struct ParticleSystem {
    static constexpr size_t numParticles{100};
    struct ParticleAttributes {
        float dx;
        float dy;
    };
    std::vector<SDL_FPoint> particles;
    std::vector<ParticleAttributes> attributes;
    ParticleSystem(size_t numPoints = numParticles) {
        particles.reserve(numPoints);
        attributes.reserve(numPoints);
        for (int i{}; i < numPoints; ++i) {
            particles.emplace_back(
                SDL_FPoint{.x = SDL_randf() * Config::windowStartWidth,
                           .y = SDL_randf() * (SDL_rand(11) - 10)});
        }
    }

    // TODO: loop and update
    void update() {
        for (int i{}; i < (int)particles.size(); ++i) {
            particles[i].x += SDL_randf() * (SDL_rand(21) - 10);
            particles[i].y += SDL_randf() * 10;

            if (particles[i].x > Config::windowStartWidth ||
                particles[i].x < 0.0f)
                particles[i].x =
                    static_cast<float>(SDL_rand(Config::windowStartWidth));

            if (particles[i].y > Config::windowStartHeight)
                particles[i].y = 0.0f;
        }
    };
    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);  // white
        SDL_RenderPoints(renderer, particles.data(), (int)particles.size());
    };
};