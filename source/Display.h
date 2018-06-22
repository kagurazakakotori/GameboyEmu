#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Common.h"
#include "Memory.h"

namespace gb
{

class Display
{
public:
    Display(Memory& _memory);

    void refresh();
    void renderScanline(const int& scanline);

    sf::RenderWindow screen;

private:
    static const word LCDC_ADDR = 0xff40;
    static const word SCX_ADDR  = 0xff43;
    static const word SCY_ADDR  = 0xff42;
    static const word BGP_ADDR  = 0xff47;
    static const word WX_ADDR   = 0xff4b;
    static const word WY_ADDR   = 0xff4a;

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

    void drawSprite(const int& scanline, const byte& lcdc);

    std::array<sf::Color, 8> drawTile(const word& tileAddr, const byte& palette, int tileY, bool isSprite);
    sf::Color                getColor(int bit, const byte& higher, const byte& lower, const byte& palette, bool isSprite);

    // void updateStat();
    // Moved to timer for better timer sync
};

}  // namespace gb