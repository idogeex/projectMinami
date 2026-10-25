#include "Hud.h"

bool Hud::init()
{

    if(!TTF_Init())
    {
        SDL_Log("TTF_Init failed: %s", SDL_GetError());
        return false;
    }

    const char* rawBasePath = SDL_GetBasePath(); 
    if(rawBasePath == nullptr)
    {
        SDL_Log("Couldnt find base path: %s", SDL_GetError());
        return false;
    }
    std::string path(rawBasePath);
    std::string assetPath = path + "assets/Frostfang-Regular.ttf";
    m_font = TTF_OpenFont(assetPath.c_str(), 36);
    if(!m_font)
    {
        SDL_Log("Couldnt open font: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Hud::render(SDL_Renderer* renderer, int level, int hp, int seconds)
{
    drawText(renderer, m_levelText, "Level: " + std::to_string(level), 5, 10, textColor, false);
    drawText(renderer, m_timeText, "Time: " + std::to_string(seconds), 5, 40, textColor, false);
    drawText(renderer, m_HPText, "HP: " + std::to_string(hp), 5, 70, textColor, false);
}

void Hud::renderMessage(SDL_Renderer* renderer, const std::string& text)
{
    int sw = 0; int sh = 0;

    SDL_GetCurrentRenderOutputSize(renderer, &sw, &sh);

    drawText(renderer, m_messageText, text, sw / 2, sh / 2, textColor, true);
}

bool Hud::drawText(SDL_Renderer* renderer, CachedText &slot, 
    const std::string& text, float x, float y, SDL_Color color, bool centered)
{

    if(slot.texture == nullptr || slot.text != text)
    {
        if(slot.texture != nullptr)
        {
            SDL_DestroyTexture(slot.texture);
        }

        SDL_Surface* textSurface = TTF_RenderText_Blended(m_font, text.c_str(), 0, color);
        if(!textSurface)
        {
            SDL_Log("Couldnt create surface: %s", SDL_GetError());
            return false;
        }
        slot.texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(!slot.texture)
        {
            SDL_Log("Couldnt create texture: %s", SDL_GetError());
            return false;
        }
        SDL_DestroySurface(textSurface);
        slot.text = text;
    }

    SDL_FRect dest;

    SDL_GetTextureSize(slot.texture, &dest.w, &dest.h);
    
    if(centered)
    {
        dest.x = x - dest.w / 2;
        dest.y = y - dest.h / 2;
    }
    else
    {
        dest.x = x;
        dest.y = y;
    }

    SDL_RenderTexture(renderer, slot.texture, nullptr, &dest);
    return true;
}

void Hud::shutDown()
{
    freeSlot(m_HPText);
    freeSlot(m_levelText);
    freeSlot(m_messageText);
    freeSlot(m_timeText);
    TTF_CloseFont(m_font);
    TTF_Quit();
}