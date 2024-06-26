#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "Utilities.hpp"

SDL_Renderer *ren;
SDL_Window *win;
SDL_Texture *test;
bool run = true;
SDL_Event event;
int dex = 0;
int dey = 0;

void clean_up()
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    std::cout << "Shutting down SDL2..." << std::endl;
}

void main_loop() {
    // Set swap interval after creating the renderer

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            run = false;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(win))
            run = false;
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_f) {
                run = false;
            }
            if (event.key.keysym.sym == SDLK_UP) {
                dey--;
                dey--;
            }

            if (event.key.keysym.sym == SDLK_DOWN) {
                dey++;
                dey++;
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                dex++;
                dex++;
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
                dex--;
                dex--;
            }
        }
    }

    SDL_SetRenderDrawColor(ren, 155, 88, 95, 255);
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, test, NULL, NULL);
    SDL_RenderPresent(ren);  // Present the renderer

    if (!run) {
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
    win = SDL_CreateWindow("Hello SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 256*multiple, 160*multiple, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    ren = SDL_CreateRenderer(win, -1, 0);
    if (ren == nullptr) {
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    std::cout << "SDL2 setup complete. Running main loop..." << std::endl;
    test = create_texture_from_file(ren, "assets/gba4.png");
    if (test == nullptr)
    {
        std::cout <<"not texture" << std::endl;
    }
    #ifdef __EMSCRIPTEN__
    // Use Emscripten's main loop
    emscripten_set_main_loop(main_loop, 0, 1);
    #else
    while(run)
    {
        main_loop();
    }
    #endif
    std::cout << "Shutdown finished" << std::endl;
    return 0;
}
