#pragma once
#include <cstdint>

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;
constexpr int TILE_SIZE = 40;

enum class TileType : uint8_t
{
    Floor,
    Wall
};

//notes
/*
    SDL_SetRenderDrawColor(m_renderer, 26, 26, 26, 255); // deep charcoal for the floor
    SDL_SetRenderDrawColor(m_renderer, 51, 0, 102, 255); // walls deep violet
    SDL_SetRenderDrawColor(m_renderer, 148, 0, 211, 255); // or dark violet
*/