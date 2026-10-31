#include "Pathfinding.h"

int Pathfinding::shortestPathLength(const Grid& grid, Point start, Point goal)
{
    const int width = grid.getWidth();
    std::vector<int> distances(width * grid.getHeight(), -1);
    std::queue<Point> toVisit;

    auto index = [width](Point p) { return p.y * width * p.x; };

    distances[index(start)] = 0;
    toVisit.push(start);
    
    const std::array<Point, 4> directions = {{{0, -2}, {0, 2}, {-2, 0}, {2, 0}}};

    while(!toVisit.empty())
    {
        Point current = toVisit.front();
        toVisit.pop();
        
        //TODO: current = goal? if so return answer

        for(const Point& d : directions)
        {
            Point next = {/* TODO: current + d */ };
            
            /*TODO: 
            1. skip if next = tiletype wall
            2. skip if next != -1(visited)
            3. next += current + 1
            4. toVisit.push(next)*/
        }
    }

    return -1;
}