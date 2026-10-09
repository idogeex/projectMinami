#pragma once
#include "Grid.h"
#include <random>
#include <algorithm>

struct Point
{
    int x;
    int y;
};

namespace MazeGenerator
{
    void createMaze(Grid &grid, unsigned int seed);
}