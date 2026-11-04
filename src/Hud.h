#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <string>

class Hud
{
public:
    Hud() = default;
    bool init();
    void render(SDL_Renderer* renderer, int level, int seconds);
    void renderMessage(SDL_Renderer* renderer, const std::string& text);
    void shutDown();
private:
    struct CachedText
    {
        std::string text;
        SDL_Texture* texture = nullptr; 
    };
    SDL_Color textColor = {192, 255, 120, 255};

    CachedText m_levelText;
    CachedText m_timeText;
    CachedText m_messageText;
    TTF_Font* m_font = nullptr;

    bool drawText(SDL_Renderer* renderer, CachedText &slot, 
        const std::string& text, float x, float y, SDL_Color color, bool centered);
    void freeSlot(CachedText& slot)
    {
        if(slot.texture != nullptr)
        {
            SDL_DestroyTexture(slot.texture);
            slot.text.clear();
        }
    }
};