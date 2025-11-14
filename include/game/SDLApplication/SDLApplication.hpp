#pragma once
#include <SDL3/SDL.h>
#include <cassert>
#include <string>

struct SDLApplication {
    static constexpr int width{1000};
    static constexpr int height{600};
    static constexpr size_t numParticles{100};

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    SDL_Texture* mBackground;
    SDL_Surface* mSurface;

    bool mRunning{true};

    SDLApplication(const char* name) {
        SDL_Init(SDL_INIT_VIDEO);
        mWindow = SDL_CreateWindow(name, width, height, SDL_WINDOW_RESIZABLE);

        mRenderer = SDL_CreateRenderer(mWindow, nullptr);
        if (mRenderer == nullptr) {
            assert(false && "Error creating renderer.");
        } else {
            SDL_Log("Renderer: %s", SDL_GetRendererName(mRenderer));
            SDL_Log("Available renderer drivers:");
            for (int i = 0; i < SDL_GetNumRenderDrivers(); i++) {
                SDL_Log("%d. %s", i + 1, SDL_GetRenderDriver(i));
            }
        }

        mSurface = SDL_LoadBMP("../assets/orig.bmp");
        if (mSurface == nullptr) {
            assert(false && "Error loading surface.");
        }
        mBackground = SDL_CreateTextureFromSurface(mRenderer, mSurface);
        if (mSurface == nullptr) {
            assert(false && "Error creating background texture from surface.");
        }
        SDL_SetRenderLogicalPresentation(mRenderer, width, height,
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
            if (event.type == SDL_EVENT_QUIT) {
                mRunning = false;
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                SDL_Log("A key was pressed %c", event.key.key);
            } else if (event.type == SDL_EVENT_MOUSE_MOTION) {
                // SDL_Log("(x, y): (%f, %f)", event.motion.xrel,
                //         event.motion.yrel);
            } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                SDL_Log("Button clicked: %d", event.button.button);
                SDL_Log("Clicks: %d", event.button.clicks);
            }
        }
        // Application/Game Logic
    }

    void Update() {
        for (int i{}; i < 100; ++i) {}
    }
    void Render() {
        //clear frame
        SDL_SetRenderDrawColor(mRenderer, 0x00, 0xAA, 0xFF, 0xFF);
        SDL_RenderClear(mRenderer);

        //draw background
        SDL_RenderTexture(mRenderer, mBackground, NULL, NULL);

        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderLine(mRenderer, 0.0f, 0.0f, 100.0f, 50.0f);

        SDL_FRect r{.x = 100.0f, .y = 50.0f, .w = 200.0f, .h = 200.0f};
        SDL_RenderRect(mRenderer, &r);

        //draw frame
        SDL_RenderPresent(mRenderer);
    }

    void MainLoop() {
        static constexpr Uint64 fpsUpdateIntervalMS{1000};
        Uint64 fps{};
        Uint64 lastTime{};

        while (mRunning) {
            Uint64 currentTime = SDL_GetTicks();
            Tick();
            ++fps;
            SDL_Delay(16);
            Uint64 deltaTime = SDL_GetTicks() - currentTime;

            // FPS Calculation
            if (currentTime > lastTime + fpsUpdateIntervalMS) {
                std::string title{"Game Window - FPS: "};
                title += std::to_string(fps);
                SDL_SetWindowTitle(mWindow, title.c_str());
                lastTime = currentTime;
                fps = 0;
            }
        }
    }
};