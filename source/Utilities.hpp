#pragma once

#include <SDL2/SDL.h>
#include <SDL_image.h>

SDL_Texture* create_texture_from_file(SDL_Renderer* renderer, const char* filePath);