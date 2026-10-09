#pragma once
#include <SDL3/SDL.h>
#include "Player.h"
#include "Vec2.h"
#include "Grid.h"
#include "MazeGenerator.h"

class Game
{
public:

    Game() = default;
    ~Game();
    bool Init();
    void Run();

private:
    bool m_running = true;
    SDL_Renderer* m_renderer = nullptr;
    SDL_Window* m_window = nullptr;
    Player m_player;
    Grid m_grid{LAB_WIDTH, LAB_HEIGHT};

    Vec2 readMovementInput();
    
    void startNewLevel();

    void update(float deltaTime);
    void render();
    void handleEvents();
};