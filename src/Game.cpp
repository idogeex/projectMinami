#include "Game.h"

#include <cmath>
#include <algorithm>

bool Game::Init()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL_Video init failed: %s", SDL_GetError());
        return false;
    }
    
    m_window = SDL_CreateWindow("Minami", 1280, 720, 0);
    
    if(m_window == nullptr)
    {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    
    if(m_renderer == nullptr)
    {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderVSync(m_renderer, 1);

    return true;
}

void Game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 153, 204, 255, 255);
    SDL_RenderClear(m_renderer);

    m_player.render(m_renderer);

    SDL_RenderPresent(m_renderer);
}

void Game::update(float deltaTime)
{
    m_player.update(deltaTime, readMovementInput());
}

Vec2 Game::readMovementInput()
{
    float directionX = 0.0f, directionY = 0.0f;
    const bool* keyboardState = SDL_GetKeyboardState(nullptr);

    if(keyboardState[SDL_SCANCODE_W])
        directionY -= 1;

    if(keyboardState[SDL_SCANCODE_S])
        directionY += 1;

    if(keyboardState[SDL_SCANCODE_A])
        directionX -= 1;

    if(keyboardState[SDL_SCANCODE_D])
        directionX += 1;

    normalize({directionX, directionY});

    return {directionX, directionY};
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if(event.type == SDL_EVENT_QUIT)
            m_running = false;

        if(event.type == SDL_EVENT_KEY_DOWN)
        {
            if(event.key.key == SDLK_ESCAPE)
                m_running = false;
            if(event.key.key == SDLK_SPACE)
                m_player.takeDamage(50);
        }
    }
}

void Game::Run()
{
    float deltaTime = 0.0f;
    Uint64 previousTime = SDL_GetTicks();
    while(m_running)
    {
        Uint64 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - previousTime) / 1000.0f;
        deltaTime = std::min(deltaTime, 0.05f);
        
        handleEvents();
        update(deltaTime);
        render();

        previousTime = currentTime;
    }
}

Game::~Game()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}