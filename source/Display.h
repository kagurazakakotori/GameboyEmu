#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include "Common.h"
#include "Memory.h"

namespace gb
{

class Display
{
public:
    int scanlineRendered = 0;

    Display(Memory& _memory);

    void refresh(const int& cycle);

    sf::RenderWindow screen;

private:
    static const word LCDC_ADDR = 0xff40;
    static const word STAT_ADDR = 0xff41;
    static const word SCX_ADDR  = 0xff43;
    static const word SCY_ADDR  = 0xff42;
    static const word BGP_ADDR  = 0xff47;
    static const word WX_ADDR   = 0xff4b;
    static const word WY_ADDR   = 0xff4a;
    static const word LY_ADDR   = 0xff44;
    static const word LYC_ADDR  = 0xff45;

    Memory& memory;

    sf::Image background;
    sf::Image window;
    sf::Image sprite;

    std::array<sf::Color, 4> colorSet;

    int scanlineCount = 456;

    void renderFrame();
    void renderScanline(const int& scanline);
    void drawBackground(const int& scanline, const byte& lcdc);
    void drawWindow(const int& scanline, const byte& lcdc);
    void drawSprite(const int& scanline, const byte& lcdc);

    sf::Color getColor(int bit, byte higher, byte lower, byte palette);

    void updateStat();
    void setMode(byte& stat, const bool& bit1, const bool& bit0);
    void requestInterrupt(const int& interruptType);
};

}  // namespace gb