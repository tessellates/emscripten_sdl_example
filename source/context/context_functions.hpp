#pragma once

#include "ApplicationContext.hpp"
#include "config.hpp"


inline void render(SDL_Texture* texture, std::optional<RenderContext>& renderContext)
{
    if (renderContext)
    {
        SDL_RenderCopy(APP_RENDERER, texture, NULL, &renderContext->dstrect);
    }
    else
    {
        SDL_RenderCopy(APP_RENDERER, texture, NULL, NULL);
    }
}

inline void render_loop()
{
    render(APP_TEXTURES[0], APP_RENDER_CONTEXTS[0]);
    render(APP_TEXTURES[1], APP_RENDER_CONTEXTS[1]);
    render(APP_TEXTURES[2], APP_RENDER_CONTEXTS[2]);
}

inline void parse_events()
{
    auto& running = APP_CONTEXT.running;
    auto& pos = APP_RENDER_CONTEXTS[2]->dstrect;
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
                pos.y -= config::window_multiple;
            }
            if (APP_EVENT.key.keysym.sym == SDLK_DOWN) {
                pos.y += config::window_multiple;
            }
            if (APP_EVENT.key.keysym.sym == SDLK_RIGHT) {
                pos.x += config::window_multiple;

            }
            if (APP_EVENT.key.keysym.sym == SDLK_LEFT) {
                pos.x -= config::window_multiple;
            }
        }
    }
}
