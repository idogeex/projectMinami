#include "Player.h"
#include "Constants.h"

void Player::render(SDL_Renderer* renderer) const
{
    SDL_FRect rect = getBounds();
    SDL_SetRenderDrawColor(renderer, 74, 74, 74, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Player::update(float deltaTime, Vec2 direction)
{
    m_y += direction.y * m_speed * deltaTime;
    m_x += direction.x * m_speed * deltaTime;

    if (m_x < 0)
        m_x = 0;

    if (m_x > WINDOW_WIDTH - m_size)
        m_x = WINDOW_WIDTH - m_size;

    if (m_y < 0)
        m_y = 0;
    
    if (m_y > WINDOW_HEIGHT - m_size)
        m_y = WINDOW_HEIGHT - m_size;
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