#pragma once

#include "ApplicationContext.hpp"
#include "Utilities.hpp"
#include "config.hpp"
#include "cast_utils.hpp"

inline void initalize_context()
{
    auto& rcontext = APP_CONTEXT.visualContext.renderContexts;
    APP_TEXTURES.push_back(create_texture_from_file(APP_RENDERER, "assets/gba5.png"));
    rcontext.push_back(std::nullopt);
    APP_CONTEXT.visualContext.backdrop = create_surface_from_file("assets/modbackdrop.png");
    APP_TEXTURES.push_back(create_texture_from_surface(APP_RENDERER, APP_CONTEXT.visualContext.backdrop));
    APP_TEXTURES.push_back(create_texture_from_file(APP_RENDERER, "assets/guy.png"));
    // size of the small screen in the gameboy
    int basew = 114 * config::window_multiple;
    int baseh = 76 * config::window_multiple;
    int yoff = 39 * config::window_multiple;
    int xoff = (config::gameboy_width * config::window_multiple - basew)/2;
    rcontext.push_back(RenderContext{SDL_Rect{xoff, yoff, basew, baseh}});
    int guyw = 7 * config::window_multiple;
    int guyh = 8 * config::window_multiple;
    int xguy = xoff + basew/2;
    int yguy = yoff + baseh - 3*config::window_multiple - guyh;
    rcontext.push_back(RenderContext{SDL_Rect{xguy, yguy, guyw, guyh}});

    APP_CONTEXT.visualContext.grid = GridContext(glm::ivec4{xoff, yoff, basew, baseh}, 114/2, 76/2);
};
