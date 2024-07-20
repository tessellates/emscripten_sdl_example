#include "IDGrid.hpp"
#include <cassert>
#include <algorithm>

// Constructor to initialize the grid with given dimensions
IDGrid::IDGrid(int xdim, int ydim)
    : xdim(xdim), ydim(ydim), grid(xdim * ydim, -1) // Initializing the grid with zeros
{
}

// Function to compute the index in the 1D vector from 2D coordinates
int IDGrid::index(int x, int y) const
{
    assert(x >= 0 && x < xdim);
    assert(y >= 0 && y < ydim);
    return y * xdim + x;
}

const std::vector<int>& IDGrid::getGrid() const
{
    return grid;
}

// Function to swap elements in the grid using their indices
void IDGrid::swap(int index1, int index2)
{
    std::swap(grid[index1], grid[index2]);
}

// Function to swap elements in the grid using their coordinates
void IDGrid::swap(const Coordinate& c1, const Coordinate& c2)
{
    int idx1 = index(c1.x, c1.y);
    int idx2 = index(c2.x, c2.y);
    swap(idx1, idx2);
}

int& IDGrid::operator()(int x, int y) {
    return grid[index(x, y)];
}

const int& IDGrid::operator()(int x, int y) const {
    return grid[index(x, y)];
}

int& IDGrid::operator()(const Coordinate& c) {
   return grid[index(c.x, c.y)];
}

const int& IDGrid::operator()(const Coordinate& c) const {
   return grid[index(c.x, c.y)];
}

int& IDGrid::operator()(int i) {
   return grid[i];
}

const int& IDGrid::operator()(int i) const {
   return grid[i];
}

void IDGrid::print() const
{
    for (int i = 0; i < ydim; i++)
    {
        for (int j = 0; j < xdim; j++)
        {
            std::cout << grid[index(j,i)] << " ";
        }
        std::cout << std::endl;
    }
}