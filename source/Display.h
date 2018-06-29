#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Common.h"
#include "Memory.h"

namespace gb
{

class Memory;

struct Sprite
{
    int  x;
    int  y;
    int  tileNumber;
    int  paletteId;
    bool xFlip;
    bool yFlip;
    bool priority;
    int  height;
};

class Display
{
public:
    Display(Memory& _memory) : memory(_memory) {}

    void init(float scale);

    void refresh();
    void sync(const int& cycles);

    sf::RenderWindow screen;

    void updateSpriteCache(const word& address, const byte& value);

private:
    Memory& memory;

    sf::Image frame;

    std::array<sf::Color, 160 * 144> backgroundArray;
    std::array<sf::Color, 160 * 144> windowArray;
    std::array<sf::Color, 160 * 144> spriteArray;

    std::array<bool, 160 * 144> backgroundEnable;
    std::array<bool, 160 * 144> windowEnable;
    std::array<bool, 160 * 144> spriteEnable;

    std::array<sf::Color, 4> colorSet;

    void renderFrame();

    void drawBackground(const int& scanline, const byte& lcdc);
    void drawWindow(const int& scanline, const byte& lcdc);
    void drawBackgroundOrWindow(const int& scanline, const byte& lcdc, bool isBackground);

    // Sprite
    std::array<Sprite, 40> spriteCache;

    void                 parseSpriteAttribute(Sprite& sprite, const byte& attribute);
    std::vector<Sprite*> loadSprite();  // load sprites to be drawn from cache, use pointer for better performance
    void                 drawSprite(const int& scanline, const byte& lcdc, std::vector<Sprite*> sprite);

    // Common
    std::array<sf::Color, 8> drawTile(const word& tileAddr, const byte& palette, int tileY, bool isSprite);
    sf::Color                getColor(int bit, const byte& higher, const byte& lower, const byte& palette, bool isSprite);

    // Timing (Sync cycles with CPU)
    unsigned int scanlineTracker;
    bool         vblank;

    void renderScanline(const int& scanline);
    void requestInterrupt(const int& interruptType);
};

}  // namespace gb