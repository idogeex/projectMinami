#pragma once
#include "Grid.h"
#include <random>
#include <algorithm>

namespace MazeGenerator
{
    void createMaze(Grid &grid, unsigned int seed);
}