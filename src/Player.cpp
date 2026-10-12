#include "Player.h"
#include "Constants.h"

void Player::render(SDL_Renderer* renderer, const Camera& camera) const
{
    SDL_FRect rect = getBounds();
    rect = camera.worldToScreen(rect);
    SDL_SetRenderDrawColor(renderer, 74, 74, 74, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Player::update(float deltaTime, Vec2 direction, const Grid& grid)
{
    float tempX = m_x;
    m_x += direction.x * m_speed * deltaTime;
    if(grid.collidesWith(getBounds()))
    {
        if(direction.x > 0)
        {
            int col = static_cast<int>(std::floor((m_x + m_size - 0.001f) / TILE_SIZE));
            m_x = col * TILE_SIZE - m_size;
        }
        else if(direction.x < 0)
        {
            int col = static_cast<int>(std::floor(m_x / TILE_SIZE));
            m_x = (col + 1) * TILE_SIZE;
        }
        else if(direction.y > 0)
        {
            int row = static_cast<int>(std::floor((m_y + m_size - 0.001f) / TILE_SIZE));
            m_y = row * TILE_SIZE - m_size;
        }
        else if (direction.y < 0)
        {
            int row = static_cast<int>(std::floor(m_y / TILE_SIZE));
            m_y = (row + 1) * TILE_SIZE;
        }
    }

    float tempY = m_y;
    m_y += direction.y * m_speed * deltaTime;
    if(grid.collidesWith(getBounds()))
    {
        m_y = tempY;
    }
}

void Player::takeDamage(int amount)
{
    m_currentHP -= amount;
    if(m_currentHP <= 0)
    {
        m_currentHP = 0;
    }
    SDL_Log("Player received damage: %d, Current HP: %d, %s", amount, m_currentHP, isAlive() ? "true" : "false");
}

SDL_FRect Player::getBounds() const
{
    SDL_FRect rect;
    rect.x = m_x;
    rect.y = m_y;
    rect.w = m_size;
    rect.h = m_size;

    return rect;
}