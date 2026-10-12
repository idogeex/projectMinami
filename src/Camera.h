#pragma once
#include "Vec2.h"
#include "Constants.h"
#include <SDL3/SDL.h>
#include <cmath>

struct Camera
{
    Vec2 cameraPosition {0.0f, 0.0f};
    int viewPortWidth = WINDOW_WIDTH;
    int viewPortHeight = WINDOW_HEIGHT;

    void centerOn(SDL_FRect target)
    {
        cameraPosition.x = std::round((target.x + target.w / 2.0f) - viewPortWidth / 2);
        cameraPosition.y = std::round((target.y + target.h / 2.0f) - viewPortHeight / 2);
    }

    SDL_FRect worldToScreen(SDL_FRect world) const
    {
        SDL_FRect positionOnViewPort;
        positionOnViewPort.x = world.x - cameraPosition.x;
        positionOnViewPort.y = world.y - cameraPosition.y;
        positionOnViewPort.w = world.w;
        positionOnViewPort.h = world.h;

        return positionOnViewPort;
    } 
};
