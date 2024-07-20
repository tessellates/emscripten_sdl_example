#pragma once

#include <vector>
#include "Coordinate.hpp"

// Class representing a grid of IDs.
class IDGrid
{
public:
    IDGrid() = default;
    IDGrid(int xdim, int ydim);

    int index(int x, int y) const;
    const std::vector<int>& getGrid() const;

    // Overload the subscript operator for read/write access
    int& operator()(int x, int y);
    const int& operator()(int x, int y) const;

    // Overload the subscript operator for read/write access
    int& operator()(const Coordinate& c);
    const int& operator()(const Coordinate& c) const;

    // Overload the subscript operator for read/write access
    int& operator()(int index);
    const int& operator()(int index) const;

    void swap(int index1, int index2);
    void swap(const Coordinate& c1, const Coordinate& c2);

    void print() const;

private:
    int xdim;
    int ydim;
    std::vector<int> grid;    
};