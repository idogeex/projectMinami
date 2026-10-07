#pragma once
#include <cmath>

struct Vec2
{
    float x = 0.0f;
    float y = 0.0f;
};

inline Vec2 normalize(Vec2 vec)
{
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);

    if(length > 0)
    {
        vec.x /= length;
        vec.y /= length;
    }

    return vec;
}