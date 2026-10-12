#pragma once
#include "Vec2.h"
#include "Constants.h"
#include <SDL3/SDL.h>
#include <cmath>
#include <algorithm>

struct Camera
{
    Vec2 cameraPosition {0.0f, 0.0f};
    int viewPortWidth = WINDOW_WIDTH;
    int viewPortHeight = WINDOW_HEIGHT;
    int worldWidth = 0;
    int worldHeight = 0;

    void centerOn(SDL_FRect target)
    {
        cameraPosition.x = std::round((target.x + target.w / 2.0f) - viewPortWidth / 2.0f);
        cameraPosition.y = std::round((target.y + target.h / 2.0f) - viewPortHeight / 2.0f);

        if(worldWidth - viewPortWidth < 0)
        {
            cameraPosition.x = 0;
        }
        else
        {
            cameraPosition.x = std::clamp(static_cast<int>(cameraPosition.x), 0, worldWidth - viewPortWidth);
        }
        if(worldHeight - viewPortHeight < 0)
        {
            cameraPosition.y = 0;
        }
        else
        {
            cameraPosition.y = std::clamp(static_cast<int>(cameraPosition.y), 0, worldHeight - viewPortHeight);
        }
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
