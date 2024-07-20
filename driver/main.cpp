#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "ApplicationContext.hpp"
#include "config.hpp"
#include "initialize_context.hpp"
#include "context_functions.hpp"
#include "model_init.hpp"

void clean_up()
{
    SDL_DestroyRenderer(APP_RENDERER);
    SDL_DestroyWindow(APP_WINDOW);
    SDL_Quit();
    std::cout << "Shutting down SDL2..." << std::endl;
}

void main_loop() {
    // Set swap interval after creating the renderer
    parse_events();
    SDL_SetRenderDrawColor(APP_RENDERER, 155, 88, 95, 255);
    SDL_RenderClear(APP_RENDERER);

    render_loop();

    SDL_RenderPresent(APP_RENDERER);  // Present the renderer

    if (!APP_CONTEXT.running) {
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

    int multiple = config::window_multiple;
    APP_WINDOW = SDL_CreateWindow("Hello SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config::gameboy_width*multiple, config::gameboy_height*multiple, SDL_WINDOW_SHOWN);
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

    initalize_context();
    init_model();

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
