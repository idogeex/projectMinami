#pragma once
#include "Grid.h"
#include <random>
#include <algorithm>

struct Point
{
    int x;
    int y;
};

class MazeGenerator
{
public:
    static void createMaze(Grid &grid, unsigned int seed);
private:

};