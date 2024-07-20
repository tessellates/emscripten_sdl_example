#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <optional>
#include "GridContext.hpp"

struct RenderContext
{
    SDL_Rect dstrect;
    bool isClip = false;
    SDL_Rect srcrect;
};

struct VisualContext
{
    std::vector<SDL_Texture*> textures;
    std::vector<std::optional<RenderContext>> renderContexts;
    GridContext grid;
    SDL_Rect draw;
    SDL_Surface* backdrop;
};
