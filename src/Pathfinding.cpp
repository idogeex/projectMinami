#include "Pathfinding.h"

int Pathfinding::shortestPathLength(const Grid& grid, Point start, Point goal)
{
    const int width = grid.getWidth();
    std::vector<int> distances(width * grid.getHeight(), -1);
    std::queue<Point> toVisit;

    auto index = [width](Point p) { return p.y * width + p.x; };

    distances[index(start)] = 0;
    toVisit.push(start);
    
    const std::array<Point, 4> directions = {{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}};

    while(!toVisit.empty())
    {
        Point current = toVisit.front();
        toVisit.pop();
        
        if(current.x == goal.x && current.y == goal.y)
        {
            return distances[index(current)];
        }

        for(const Point& d : directions)
        {
            Point next = {current.x + d.x, current.y + d.y};

            if(grid.get(next.x, next.y) == TileType::Wall || distances[index(next)] != -1)
            {
                continue;
            }

            distances[index(next)] = distances[index(current)] + 1;
            toVisit.push(next);
        }
    }

    return -1;
}