#pragma once
#include <SDL3/SDL.h>
#include "Vec2.h"

class Player
{
public:
    Player() = default;
    void setPosition(float x, float y) { m_x = x, m_y = y; }
    void render(SDL_Renderer* renderer) const;
    void update(float deltaTime, Vec2 direction);
    void takeDamage(int amount);
    bool isAlive() const { return m_currentHP > 0; }
    int getHP() const { return m_currentHP; }
    SDL_FRect getBounds() const;

private:
    float m_x = 0.0f, m_y = 0.0f;
    float m_size = 28;
    float m_speed = 100.0f;
    int m_maxHP = 100;
    int m_currentHP = 100;
    int m_damage;
};