#pragma once

#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>
#include "Coordinate.hpp"

template<typename T>
class GenericGrid
{
public:
    GenericGrid() = default;
    GenericGrid(int xdim, int ydim);

    int index(int x, int y) const;
    const std::vector<T>& getGrid() const;

    // Overload the subscript operator for read/write access
    T& operator()(int x, int y);
    const T& operator()(int x, int y) const;

    // Overload the subscript operator for read/write access
    T& operator()(const Coordinate& c);
    const T& operator()(const Coordinate& c) const;

    // Overload the subscript operator for read/write access
    T& operator()(int index);
    const T& operator()(int index) const;

    void swap(int index1, int index2);
    void swap(const Coordinate& c1, const Coordinate& c2);

    void print() const;

private:
    int xdim;
    int ydim;
    std::vector<T> grid;
};

// Implementation

template<typename T>
GenericGrid<T>::GenericGrid(int xdim, int ydim)
    : xdim(xdim), ydim(ydim), grid(xdim * ydim, T()) // Initializing the grid with default values of T
{
}

template<typename T>
int GenericGrid<T>::index(int x, int y) const {
    assert(x >= 0 && x < xdim);
    assert(y >= 0 && y < ydim);
    return y * xdim + x;
}

template<typename T>
const std::vector<T>& GenericGrid<T>::getGrid() const {
    return grid;
}

template<typename T>
T& GenericGrid<T>::operator()(int x, int y) {
    return grid[index(x, y)];
}

template<typename T>
const T& GenericGrid<T>::operator()(int x, int y) const {
    return grid[index(x, y)];
}

template<typename T>
T& GenericGrid<T>::operator()(const Coordinate& c) {
    return grid[index(c.x, c.y)];
}

template<typename T>
const T& GenericGrid<T>::operator()(const Coordinate& c) const {
    return grid[index(c.x, c.y)];
}

template<typename T>
T& GenericGrid<T>::operator()(int index) {
    return grid[index];
}

template<typename T>
const T& GenericGrid<T>::operator()(int index) const {
    return grid[index];
}

template<typename T>
void GenericGrid<T>::swap(int index1, int index2) {
    std::swap(grid[index1], grid[index2]);
}

template<typename T>
void GenericGrid<T>::swap(const Coordinate& c1, const Coordinate& c2) {
    int idx1 = index(c1.x, c1.y);
    int idx2 = index(c2.x, c2.y);
    swap(idx1, idx2);
}

template<typename T>
void GenericGrid<T>::print() const {
    for (int i = 0; i < ydim; i++)
    {
        for (int j = 0; j < xdim; j++)
        {
            std::cout << grid[index(j, i)] << " ";
        }
        std::cout << std::endl;
    }
}

using IDGrid = GenericGrid<int>;