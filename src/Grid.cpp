#include "Grid.h"

Grid::Grid(int width, int height): m_width(width), m_height(height), m_tiles(width * height, TileType::Wall)
{

}

TileType Grid::get(int x, int y) const
{
    if(!inBounds(x, y))
        return TileType::Wall;

    return m_tiles[getIndex(x, y)];
}

void Grid::set(int x, int y, TileType type)
{
    if(inBounds(x, y))
        m_tiles[getIndex(x, y)] = type;
}

bool Grid::inBounds(int x, int y) const
{
    return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

void Grid::render(SDL_Renderer* renderer) const
{
    for(int y = 0; y < m_height; y++)
    {
        for(int x = 0; x < m_width; x++)
        {
            SDL_FRect tile;
            tile.x = x * TILE_SIZE;
            tile.y = y * TILE_SIZE;
            tile.h = TILE_SIZE;
            tile.w = TILE_SIZE;

            switch(get(x, y))
            {
            case TileType::Wall:
                SDL_SetRenderDrawColor(renderer, 148, 0, 211, 255);
                break;

            case TileType::Floor:
                SDL_SetRenderDrawColor(renderer, 26, 26, 26, 255);
                break;
            }

            SDL_RenderFillRect(renderer, &tile);
        }
    }
}