#include "Game.h"

#include <cmath>
#include <algorithm>
#include <random>

bool Game::Init()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL_Video init failed: %s", SDL_GetError());
        return false;
    }
    
    m_window = SDL_CreateWindow("Minami", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    
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

    startNewLevel();

    return true;
}

void Game::startNewLevel()
{
    m_player.setCenter(1.5f * TILE_SIZE, 1.5f * TILE_SIZE);
    unsigned int seed = std::random_device{}();
    SDL_Log("Current seed: %u", seed);
    MazeGenerator::createMaze(m_grid, seed);
    SDL_Log("Floor tiles: %d", m_grid.count(TileType::Floor));
}

void Game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 153, 204, 255, 255);
    SDL_RenderClear(m_renderer);

    m_grid.render(m_renderer);
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

    Vec2 direction = normalize({directionX, directionY});

    return direction;
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
            if(event.key.key == SDLK_R)
            {
                startNewLevel();
            }
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