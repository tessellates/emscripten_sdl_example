#pragma once

#include "ModelContext.hpp"
#include "ApplicationContext.hpp"

inline void populate_idgrid(IDGrid& idgrid, SDL_Surface* surface)
{
    int width = surface->w;
    int height = surface->h;
    Uint32* pixels = (Uint32*)surface->pixels;
    idgrid = IDGrid(width, height);
    for (int i = 0; i < width*height; i++)
    {
        Uint32 pixel = pixels[i];
        Uint8 r, g, b, a;
        SDL_GetRGBA(pixel, SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888), &r, &g, &b, &a);
        if (r == 0 && b == 0 && g == 0 && a == 255)
        {
            idgrid(i) = 0;
            std::cout << "hit at" << i << std::endl;
        }
    }
    delete[] pixels;
}

inline void init_model()
{
    populate_idgrid(APP_MODEL.idgrid, APP_CONTEXT.visualContext.backdrop);
}