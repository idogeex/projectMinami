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

    if(!m_hud.init())
    {
        SDL_Log("Couldnt init TTF: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderVSync(m_renderer, 1);

    return true;
}

void Game::startNewLevel()
{
    m_state = GameState::Playing;
    unsigned int seed = std::random_device{}();

    LevelConfig config = LevelConfig::getLevelConfig(m_level);
    m_grid = Grid(config.width, config.height);

    MazeGenerator::createMaze(m_grid, seed);

    Point start = {1, 1};
    Point goal = {m_grid.getWidth() - 2, m_grid.getHeight() - 2};

    int steps = Pathfinding::shortestPathLength(m_grid, start, goal);
    if(steps == -1)
    {
        m_timeLeft = 60.0f;
    }
    else
    {
        m_timeLeft = steps * TILE_SIZE / m_player.getSpeed() * config.timeFactor;
    }

    m_camera.worldWidth = m_grid.getWidth() * TILE_SIZE;
    m_camera.worldHeight = m_grid.getHeight() * TILE_SIZE;
    SDL_Log("Level: %d, Seed: %u, Width: %d, Height: %d, Floor: %d", 
            m_level, seed, config.width, config.height, m_grid.count(TileType::Floor));
    m_player.setCenter(1.5f * TILE_SIZE, 1.5f * TILE_SIZE);
    m_camera.centerOn(m_player.getBounds());
}

void Game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 153, 204, 255, 255);
    SDL_RenderClear(m_renderer);

    if(m_state != GameState::Menu)
    {
        m_grid.render(m_renderer, m_camera);
        m_player.render(m_renderer, m_camera);
        m_hud.render(m_renderer, m_level, static_cast<int>(std::ceil(m_timeLeft)));
    }

    switch(m_state)
    {
        case GameState::Won:
        {
            renderOverlay({0, 255, 0, 128}, "Level complete! Press SPACE.");
            break;
        }
        case GameState::Lost:
        {
            renderOverlay({255, 0, 0, 128}, "Time is up! Press SPACE.");
            break;
        }
        case GameState::Paused:
        {
            renderOverlay({128, 128, 0, 128}, "PAUSED");
            break;
        }
        case GameState::Menu:
        {
            renderOverlay({0, 0, 0, 0}, "PRESS ENTER TO START");
            break;
        }
        case GameState::Playing:
        {
            break;
        }
    }    
    SDL_RenderPresent(m_renderer);
}

void Game::renderOverlay(SDL_Color color, const std::string& message)
{
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_FRect solidRect = { WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 200, 400, 400 };
    SDL_RenderFillRect(m_renderer, &solidRect);
    m_hud.renderMessage(m_renderer, message);
}

void Game::update(float deltaTime)
{   
    switch(m_state)
    {
        case GameState::Playing:
        {
            m_player.update(deltaTime, readMovementInput(), m_grid);
            SDL_FRect pBounds = m_player.getBounds();
            m_camera.centerOn(pBounds);
            if(m_grid.getAtPixel(pBounds.x + pBounds.w / 2, pBounds.y + pBounds.h / 2) == TileType::Exit)
            {
                m_state = GameState::Won;
            }
            else
            {
                m_timeLeft -= deltaTime;
                if(m_timeLeft <= 0)
                {
                    m_timeLeft = 0;
                    m_state = GameState::Lost;
                }   
            }
            break;
        }
        case GameState::Won:
        {
            break;
        }
        case GameState::Lost:
        {
            break;
        }
        case GameState::Paused:
        {
            break;
        }
        case GameState::Menu:
        {
            break;
        }
    }
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

        if(event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat)
        {
            switch(m_state)
            {
            case GameState::Menu:
            {
                if(event.key.key == SDLK_RETURN)
                {
                    m_level = 1;
                    startNewLevel();
                }

                if(event.key.key == SDLK_ESCAPE)
                {
                    m_running = false;
                }
                break;
            }
            case GameState::Playing:
            {
                if(event.key.key == SDLK_ESCAPE)
                {
                    m_state = GameState::Paused;
                }
                break;
            }
            case GameState::Paused:
            {
                if(event.key.key == SDLK_ESCAPE)
                {
                    m_state = GameState::Playing;
                }
                
                if(event.key.key == SDLK_R)
                {
                    startNewLevel();
                }

                if(event.key.key == SDLK_N)
                {
                    m_level = 1;
                    startNewLevel();
                }

                break;
            }
            case GameState::Won:
            {
                if(event.key.key == SDLK_SPACE)
                {
                    m_level++;
                    startNewLevel();
                }

                if(event.key.key == SDLK_ESCAPE)
                {
                    m_running = false;
                }
                break;
            }
            case GameState::Lost:
            {
                if(event.key.key == SDLK_SPACE)
                {
                    m_level = 1;
                    startNewLevel();
                }
                break;
            }
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
    m_hud.shutDown();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}