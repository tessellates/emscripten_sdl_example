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
    for (int i = 0; i < APP_TEXTURES.size(); ++i)
    {
        render(APP_TEXTURES[i], APP_RENDER_CONTEXTS[i]);
    }
    SDL_SetRenderDrawColor(APP_RENDERER, 255, 255, 255, 255);
    SDL_RenderDrawRect(APP_RENDERER, &APP_CONTEXT.visualContext.draw);
}

inline void parse_click()
{
    auto& grid = APP_CONTEXT.visualContext.grid;
    if (APP_EVENT.button.button == SDL_BUTTON_LEFT) 
    {
        int mouseX = APP_EVENT.button.x;
        int mouseY = APP_EVENT.button.y;
        auto point = glm::ivec2{mouseX, mouseY};
        if (point.x >= 0)
        {
            if (grid.pointInGrid(point))
            {
                auto n_point = TO_IVECT2(grid.point(grid.coordinate(point)));
                if (glm::ivec2{n_point.x, n_point.y} == glm::ivec2{APP_CONTEXT.visualContext.draw.x, APP_CONTEXT.visualContext.draw.y})
                {
                    APP_CONTEXT.visualContext.draw = {};
                }
                else
                {
                    APP_CONTEXT.visualContext.draw = {n_point.x, n_point.y, config::window_multiple*2, config::window_multiple*2};
                }
            }
        }
    }
    
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
        if (APP_EVENT.type == SDL_MOUSEBUTTONDOWN)
        {
            parse_click();
        }
    }
}

inline void time_loop()
{
    
}