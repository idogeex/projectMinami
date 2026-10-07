#pragma once
#include <SDL3/SDL.h>
#include "Player.h"
#include "Math.h"

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

    Vec2 readMovementInput();

    void update(float deltaTime);
    void render();
    void handleEvents();
};