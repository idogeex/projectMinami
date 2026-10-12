#include "Grid.h"
#include <SDL3/SDL.h>
#include <cmath>

Grid::Grid(int width, int height): m_width(width), m_height(height), m_tiles(width * height, TileType::Wall)
{

}

TileType Grid::get(int x, int y) const
{
    if(!inBounds(x, y))
        return TileType::Wall;

    return m_tiles[getIndex(x, y)];
}

TileType Grid::getAtPixel(float x, float y) const
{
    int px = static_cast<int>(std::floor(x / TILE_SIZE));
    int py = static_cast<int>(std::floor(y / TILE_SIZE));
    return get(px, py);
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

void Grid::render(SDL_Renderer* renderer, const Camera& camera) const
{
    int firstX = static_cast<int>(std::floor(camera.cameraPosition.x / TILE_SIZE));
    int lastX = static_cast<int>(std::floor((camera.cameraPosition.x + camera.viewPortWidth) / TILE_SIZE));
    int firstY = static_cast<int>(std::floor(camera.cameraPosition.y / TILE_SIZE));
    int lastY = static_cast<int>(std::floor((camera.cameraPosition.y + camera.viewPortHeight) / TILE_SIZE)); 

    firstX = std::clamp(firstX, 0, m_width - 1);
    lastX = std::clamp(lastX, 0, m_width - 1);
    firstY = std::clamp(firstY, 0, m_height - 1);
    lastY = std::clamp(lastY, 0, m_height - 1);

    for(int y = firstY; y <= lastY; y++)
    {
        for(int x = firstX; x <= lastX; x++)
        {
            SDL_FRect tile = camera.worldToScreen({static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE),
                                                 TILE_SIZE, TILE_SIZE});

            switch(get(x, y))
            {
                case TileType::Wall:
                {
                    SDL_SetRenderDrawColor(renderer, 148, 0, 211, 255);
                    break;
                }
                case TileType::Floor:
                {
                    SDL_SetRenderDrawColor(renderer, 26, 26, 26, 255);
                    break;
                }
                case TileType::Exit:
                {
                    SDL_SetRenderDrawColor(renderer, 46, 139, 87, 255);
                    break;
                }    
            }   

            SDL_RenderFillRect(renderer, &tile);
        }
    }
}

void Grid::fill(TileType type)
{
    std::fill(m_tiles.begin(), m_tiles.end(), type);
}

int Grid::count(TileType type) const
{   
    return std::count(m_tiles.begin(), m_tiles.end(), type);
}

bool Grid::collidesWith(const SDL_FRect& rect) const
{
    int left = static_cast<int>(std::floor(rect.x / TILE_SIZE));
    int right = static_cast<int>(std::floor((rect.x + rect.w - 0.001f) / TILE_SIZE));
    int up = static_cast<int>(std::floor(rect.y / TILE_SIZE));
    int down = static_cast<int>(std::floor((rect.y + rect.h - 0.001f) / TILE_SIZE));

    for(int y = up; y <= down; y++)
    {
        for(int x = left; x <= right; x++)
        {
            if(get(x, y) == TileType::Wall)
            {
                SDL_FRect tile;
                tile.w = TILE_SIZE;
                tile.h = TILE_SIZE;
                tile.x = x * TILE_SIZE;
                tile.y = y * TILE_SIZE;
                if(SDL_HasRectIntersectionFloat(&tile, &rect))
                    return true;
            } 
        }
    }
    return false;
}