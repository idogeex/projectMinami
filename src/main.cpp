#include <iostream>
#include <SDL3/SDL.h>
#include <random>


std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(1, 100);

class Player
{
public:
    Player(float startX, float startY);

    void render(SDL_Renderer* renderer);
    void update();
    float getX() const { return x; }
    float getY() const { return y; }
private:
    float speed;
    float x;
    float y;
};
Player::Player(float startX, float startY)
{
    x = startX;
    y = startY;
    speed = 50.0f;
}

void Player::update()
{
    
}

void Player::render(SDL_Renderer* renderer)
{
    SDL_FRect rect;
    rect.x = x;
    rect.y = y;
    rect.w = 25;
    rect.h = 25;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void positionMap(SDL_Renderer* renderer, int x, int y)
{
    SDL_FRect rect;
    rect.x = x * 25;
    rect.y = y * 25;
    rect.w = 25;
    rect.h = 25;

    int randomNumber = dist(gen);

    if(randomNumber > 50)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    else
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    
    SDL_RenderFillRect(renderer, &rect);
}

void updateGame(Player& player)
{
    player.update();
}

void renderGame(SDL_Renderer* renderer, Player& player)
{
    SDL_SetRenderDrawColor(renderer, 153, 204, 255, 255);
    SDL_RenderClear(renderer);

    for(int y = 0; y < 24; y++)
    {
        for(int x = 0; x < 32; x++)
        positionMap(renderer, x, y);
    }
    
    player.render(renderer);

    SDL_RenderPresent(renderer);
}

void handleEvents(bool& running)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if(event.type == SDL_EVENT_QUIT)
            running = false;
    }
}

int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL_Video init failed.\n");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Minami", 800, 600, 0);
    if(window == nullptr)
    {
        SDL_Log("Window creation failed.\n");
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if(renderer == nullptr)
    {
        SDL_Log("Renderer creation failed.\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    
    Player player(0.0f, 0.0f);

    while(running)
    {
        handleEvents(running);
        updateGame(player);
        renderGame(renderer, player);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}