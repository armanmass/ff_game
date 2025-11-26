#pragma once

#include <SDL3/SDL.h>
#include <cassert>
#include <string>

#include "Config/Config.hpp"
#include "ParticleSystem/ParticleSystem.hpp"

struct SDLApplication {

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    SDL_Texture* mBackground;
    SDL_Surface* mSurface;
    ParticleSystem mPartSystem;
    Config config;
    bool mRunning{true};

    SDLApplication(const char* name) {
        SDL_Init(SDL_INIT_VIDEO);
        mWindow =
            SDL_CreateWindow(name, Config::windowStartWidth,
                             Config::windowStartHeight, SDL_WINDOW_RESIZABLE);

        mRenderer = SDL_CreateRenderer(mWindow, nullptr);
        if (mRenderer == nullptr) {
            assert(false && "Error creating renderer.");
        } else {
            SDL_Log("Renderer: %s", SDL_GetRendererName(mRenderer));
            SDL_Log("Available renderer drivers:");
            for (int i{}; i < SDL_GetNumRenderDrivers(); i++) {
                SDL_Log("%d. %s", i + 1, SDL_GetRenderDriver(i));
            }
        }

        mSurface = SDL_LoadBMP("assets/orig.bmp");
        if (mSurface == nullptr) {
            assert(false && "Error loading surface.");
        }

        mBackground = SDL_CreateTextureFromSurface(mRenderer, mSurface);
        if (mBackground == nullptr) {
            assert(false && "Error creating background texture from surface.");
        }

        SDL_SetRenderLogicalPresentation(mRenderer, Config::windowStartWidth,
                                         Config::windowStartHeight,
                                         SDL_LOGICAL_PRESENTATION_STRETCH);
    }

    ~SDLApplication() { SDL_Quit(); }

    void Tick() {
        Input();
        Update();
        Render();
    }

    void Input() {
        SDL_Event event;
        // Event Loop
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    mRunning = false;
                    break;

                case SDL_EVENT_KEY_DOWN:
                    if (event.key.key == SDLK_F11) {
                        toggleFullscreen();
                    }
                    SDL_Log("Key pressed: %d", event.key.key);
                    break;

                case SDL_EVENT_MOUSE_MOTION:
                    // SDL_Log("(x, y): (%f, %f)", event.motion.xrel,
                    //         event.motion.yrel);
                    break;

                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    SDL_Log("Button clicked: %d", event.button.button);
                    SDL_Log("Clicks: %d", event.button.clicks);
                    break;
            }
            // Application/Game Logic
        }
    }

    void Update() { mPartSystem.update(); }

    void Render() {
        //clear frame
        SDL_SetRenderDrawColor(mRenderer, 0x00, 0xAA, 0xFF, 0xFF);
        SDL_RenderClear(mRenderer);

        //draw background
        SDL_RenderTexture(mRenderer, mBackground, NULL, NULL);

        //draw particles
        mPartSystem.render(mRenderer);

        //draw frame
        SDL_RenderPresent(mRenderer);
    }

    void MainLoop() {
        Uint64 framesRendered{};
        Uint64 lastTime{};

        while (mRunning) {
            Uint64 currentTime = SDL_GetTicks();
            Tick();
            ++framesRendered;
            SDL_Delay(16);

            // FPS Calculation
            if (currentTime > lastTime + Config::fpsUpdateIntervalMS) {
                std::string title{"Game Window - FPS: " +
                                  std::to_string(framesRendered)};
                SDL_SetWindowTitle(mWindow, title.c_str());

                lastTime = currentTime;
                framesRendered = 0;
            }
        }
    }
    void toggleFullscreen() {
        config.isFullscreen = !config.isFullscreen;
        SDL_SetWindowFullscreen(mWindow, config.isFullscreen);
    }
};
