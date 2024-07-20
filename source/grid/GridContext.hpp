#pragma once

#include "Coordinate.hpp"
#include "cast_utils.hpp"

inline bool pointInRect(const glm::ivec2& point, const glm::ivec4& rect)  
{
    return point.x >= rect.x && point.x <= (rect.x + rect.z) &&
           point.y >= rect.y && point.y <= (rect.y + rect.w);
}

struct GridContext
{
    glm::ivec4 rect;
    int xdim;
    int ydim;
    float xsize;
    float ysize;

    GridContext() = default;
    GridContext(const glm::ivec4& rect, int nx, int ny) : rect(rect), xdim(nx), ydim(ny)
    {
        xsize = (float)(rect.z)/nx;
        ysize = (float)(rect.w)/ny;
    }

    Coordinate coordinate(const glm::ivec2& point) const
    {
        glm::ivec2 relative = {int(point.x - rect.x), int(point.y - rect.y)};
        int x = (relative.x) / xsize;
        int y = (relative.y) / ysize;
        return Coordinate(x, y);
    }

    glm::vec2 point(const Coordinate& pos) const
    {
        return {rect.x + pos.x * xsize, rect.y + pos.y * ysize};
    }

    bool pointInGrid(const glm::ivec2& point)
    {
        return pointInRect(point, this->rect);
    }
};
