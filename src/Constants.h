#pragma once
#include <cstdint>

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;
constexpr int TILE_SIZE = 40;

enum class TileType : uint8_t
{
    Floor,
    Wall,
    Exit
};

enum class GameState
{
    Playing,
    Won,
    Lost,
    Menu,
    Paused
};

struct Point
{
    int x;
    int y;
};