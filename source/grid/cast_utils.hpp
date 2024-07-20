#pragma once

#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
//#include "imgui.h"
#include <SDL2/SDL.h>

// Macro to cast glm::vec4 (float) to glm::ivec4 (int)
#define TO_IVECT4(vec) glm::ivec4(static_cast<int>((vec).x), static_cast<int>((vec).y), static_cast<int>((vec).z), static_cast<int>((vec).w))
#define TO_IVECT2(vec) glm::ivec2(static_cast<int>((vec).x), static_cast<int>((vec).y))
// Define the macro for reinterpret casting glm::ivec4 to SDL_Rect
#define TO_SDL_RECT(rect) reinterpret_cast<const SDL_Rect*>(&rect)
// Define the macro for reinterpret casting glm::ivec2 to SDL_Point
#define TO_SDL_POINT(point) reinterpret_cast<const SDL_Point*>(&point)
// Define the macro for reinterpret casting glm::vec4 to ImVec4
//#define TO_IM_VEC4(vec) reinterpret_cast<const ImVec4*>(&vec)