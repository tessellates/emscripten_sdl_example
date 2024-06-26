#pragma once

#include "Singleton.hpp"
#include <SDL2/SDL.h>

class ApplicationContext : public Singleton<ApplicationContext>
{
   friend class Singleton<ApplicationContext>; // Grant base access to constructor.
public:
    // boiler-plate singleton
    ApplicationContext(ApplicationContext &other) = delete;
    void operator=(const ApplicationContext &) = delete;

    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture *test;
    SDL_Event event;
    bool running = true;

private:
    ApplicationContext() = default;
    ~ApplicationContext() = default;
public:
};

#define APP_CONTEXT (*ApplicationContext::instance())
#define APP_RENDERER APP_CONTEXT.renderer
#define APP_WINDOW APP_CONTEXT.window
#define APP_EVENT APP_CONTEXT.event