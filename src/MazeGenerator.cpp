#include "MazeGenerator.h"
#include <cassert>
#include <array>

void MazeGenerator::createMaze(Grid& grid, unsigned int seed)
{
    assert(grid.getWidth() % 2 == 1 && grid.getHeight() % 2 == 1);
    grid.fill(TileType::Wall);

    std::mt19937 rng(seed);

    std::vector<Point> stack;
    std::array<Point, 4> directions = {{{0, -2}, {0, 2}, {-2, 0}, {2, 0}}};

    grid.set(1, 1, TileType::Floor);
    stack.push_back({1, 1});

    while(!stack.empty())
    {
        Point current = stack.back();
        int currentX = current.x;
        int currentY = current.y;
        
        std::shuffle(directions.begin(), directions.end(), rng);
        bool moved = false;
        for (const auto& dir : directions)
        {
            int nextX = currentX + dir.x;
            int nextY = currentY + dir.y;

            if(grid.inBounds(nextX, nextY) && grid.get(nextX, nextY) == TileType::Wall)
            {
                grid.set(currentX + dir.x / 2, currentY + dir.y / 2, TileType::Floor);
                grid.set(nextX, nextY, TileType::Floor);
                stack.push_back({nextX, nextY});
                moved = true;
                break;
            }
        }

        if(!moved)
            stack.pop_back();
    }
}