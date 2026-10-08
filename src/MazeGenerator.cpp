#include "MazeGenerator.h"

void MazeGenerator::createMaze(Grid& grid, unsigned int seed)
{
    std::mt19937 rng(seed);

    std::vector<Point> stack;
    std::vector<Point> directions = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};

    stack.clear();

    grid.set(1, 1, TileType::Floor);
    stack.push_back({1, 1});

    while(!stack.empty())
    {
        Point current = stack.back();
        int cx = current.x;
        int cy = current.y;
        
        std::shuffle(directions.begin(), directions.end(), rng);
        bool moved = false;
        for (const auto& dir : directions)
        {
            int nextX = cx + dir.x;
            int nextY = cy + dir.y;

            if(grid.inBounds(nextX, nextY) && grid.get(nextX, nextY) == TileType::Wall)
            {
                grid.set(cx + dir.x / 2, cy + dir.y / 2, TileType::Floor);
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