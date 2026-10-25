#pragma once
#include <SDL3/SDL.h>
#include "Player.h"
#include "Vec2.h"
#include "Grid.h"
#include "MazeGenerator.h"
#include "Camera.h"
#include "LevelConfig.h"
#include "Hud.h"

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
    Grid m_grid;
    Hud m_hud;
    GameState m_state = GameState::Playing;
    Vec2 readMovementInput();
    Camera m_camera;
    int m_level = 1;
    float m_levelTime = 0;
        
    void startNewLevel();

    void update(float deltaTime);
    void render();
    void handleEvents();
};