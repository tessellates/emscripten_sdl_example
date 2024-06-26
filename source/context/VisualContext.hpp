#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <optional>

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
};
