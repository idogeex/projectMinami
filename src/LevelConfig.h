#pragma once
#include <algorithm>

struct LevelConfig
{
    int width = 0;
    int height = 0;
    float timeFactor = 1.0f;

    static LevelConfig getLevelConfig(int level)
    {
        level = std::max(level, 1);
        int cellsW = 2 * level + 6;
        int cellsH = 2 * level + 4;

        LevelConfig config;
        config.width = 2 * cellsW + 1;
        config.height = 2 * cellsH + 1;
        config.timeFactor = std::max(1.4f, 3.0f - 0.15f * (level - 1));
        return config;
    }
};