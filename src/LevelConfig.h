#pragma once
#include <utility>

struct LevelConfig
{
    static std::pair <int, int> getLevelConfig(int level)
    {
        level = std::max(level, 1);
        int cellsW = 2 * level + 7;
        int cellsH = 2 * level + 5;
        return {cellsW, cellsH};
    }
};