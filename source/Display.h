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
    Display(Memory& _memory);

    void render();
    void renderScanline(byte scanline);

private:
    static const word LCDC_ADDR = 0xff40;
    static const word SCX_ADDR  = 0xff43;
    static const word SCY_ADDR  = 0xff42;
    static const word BGP_ADDR  = 0xff47;
    static const word WX_ADDR   = 0xff4b;
    static const word WY_ADDR   = 0xff4a;

    Memory& memory;

    sf::RenderWindow mainWindow;

    sf::Image background;
    sf::Image window;
    sf::Image sprite;

    std::array<sf::Color, 4> colorSet;

    void drawBackground(const int& scanline, const byte& lcdc);
    void drawWindow(const int& scanline, const byte& lcdc);
    void drawSprite(const int& scanline, const byte& lcdc);

    sf::Color getColor(int bit, byte higher, byte lower, byte palette);
};

}  // namespace gb