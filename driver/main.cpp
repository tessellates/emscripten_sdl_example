#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "Utilities.hpp"
#include "ApplicationContext.hpp"

void clean_up()
{
    SDL_DestroyRenderer(APP_RENDERER);
    SDL_DestroyWindow(APP_WINDOW);
    SDL_Quit();
    std::cout << "Shutting down SDL2..." << std::endl;
}

void main_loop() {
    // Set swap interval after creating the renderer
    auto& running = APP_CONTEXT.running;
    auto test = APP_CONTEXT.test;
    while (SDL_PollEvent(&APP_EVENT)) {
        if (APP_EVENT.type == SDL_QUIT)
            running = false;
        if (APP_EVENT.type == SDL_WINDOWEVENT && APP_EVENT.window.event == SDL_WINDOWEVENT_CLOSE && APP_EVENT.window.windowID == SDL_GetWindowID(APP_WINDOW))
            running = false;
        if (APP_EVENT.type == SDL_KEYDOWN) {
            if (APP_EVENT.key.keysym.sym == SDLK_f) {
                running = false;
            }
            if (APP_EVENT.key.keysym.sym == SDLK_UP) {
            }
            if (APP_EVENT.key.keysym.sym == SDLK_DOWN) {
            }
            if (APP_EVENT.key.keysym.sym == SDLK_RIGHT) {
            }
            if (APP_EVENT.key.keysym.sym == SDLK_LEFT) {
            }
        }
    }

    SDL_SetRenderDrawColor(APP_RENDERER, 155, 88, 95, 255);
    SDL_RenderClear(APP_RENDERER);
    SDL_RenderCopy(APP_RENDERER, test, NULL, NULL);
    SDL_RenderPresent(APP_RENDERER);  // Present the renderer

    if (!running) {
        #ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
        #endif
        clean_up();
    }
}


int main(int argc, char* argv[]) {
    std::cout << "Initializing SDL2..." << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image initialization failed: " << IMG_GetError() << std::endl;
    }

    // From 2.0.18: Enable native IME.
    #ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    #endif

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
        SDL_Quit(); // Clean up SDL before exiting
    }

    int multiple = 5;
    APP_WINDOW = SDL_CreateWindow("Hello SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 256*multiple, 160*multiple, SDL_WINDOW_SHOWN);
    if (APP_WINDOW == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    APP_RENDERER = SDL_CreateRenderer(APP_WINDOW, -1, 0);
    if (APP_RENDERER == nullptr) {
        SDL_DestroyWindow(APP_WINDOW);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    std::cout << "SDL2 setup complete. Running main loop..." << std::endl;
    APP_CONTEXT.test = create_texture_from_file(APP_RENDERER, "assets/gba4.png");
    if (APP_CONTEXT.test == nullptr)
    {
        std::cout <<"not texture" << std::endl;
    }
    #ifdef __EMSCRIPTEN__
    // Use Emscripten's main loop
    emscripten_set_main_loop(main_loop, 0, 1);
    #else
    while(APP_CONTEXT.running)
    {
        main_loop();
    }
    #endif
    std::cout << "Shutdown finished" << std::endl;
    return 0;
}
