#pragma once
#include "Constants.h"
#include "Grid.h"
#include <vector>
#include <queue>
#include <array>

class Pathfinding
{
public:
    static int shortestPathLength(const Grid& grid, Point start, Point goal);
};