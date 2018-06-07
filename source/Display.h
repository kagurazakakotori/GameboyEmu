#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Common.h"
#include "Memory.h"

extern Gameboy::Memory memory;

namespace Gameboy
{

class Display
{
public:
    Display();

    void render();
    void renderScanline(byte scanline);

private:
    static const word LCDC_ADDR = 0xff40;
    static const word SCX_ADDR  = 0xff43;
    static const word SCY_ADDR  = 0xff42;
    static const word BGP_ADDR  = 0xff47;

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

}  // namespace Gameboy