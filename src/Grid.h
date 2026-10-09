#pragma once
#include "Constants.h"

#include <vector>
#include <algorithm>
#include <SDL3/SDL.h>

class Grid
{
public:
    Grid(int width, int height);

    TileType get(int x, int y) const;
    void set(int x, int y, TileType type);
    bool inBounds(int x, int y) const;
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    void render(SDL_Renderer* renderer) const;
    void fill(TileType type);
    int count(TileType type) const;

private:
    std::vector<TileType> m_tiles;
    int m_width = 0, m_height = 0;

    inline size_t getIndex(int x, int y) const { return static_cast<size_t>(y) * m_width + x; }
};