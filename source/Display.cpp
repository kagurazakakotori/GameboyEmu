#include "Display.h"

namespace Gameboy
{

Display::Display()
{
    // initialize colorset
    colorSet[0] = sf::Color(255, 255, 255);
    colorSet[1] = sf::Color(192, 192, 192);
    colorSet[2] = sf::Color(96, 96, 96);
    colorSet[3] = sf::Color(0, 0, 0);

    mainWindow.create(sf::VideoMode(160, 144), "screen0");

    background.create(160, 144, sf::Color::Transparent);
    window.create(160, 144, sf::Color::Transparent);
    sprite.create(160, 144, sf::Color::Transparent);
}

void Display::renderScanline(byte scanline)
{
    byte lcdc = memory.readByte(LCDC_ADDR);

    bool backgroundOnFlag = getBit(lcdc, 0);
    bool windowOnFlag     = getBit(lcdc, 5);

    if (backgroundOnFlag) {
        drawBackground(scanline, lcdc);
    }

    if (windowOnFlag) {
        drawWindow(scanline, lcdc);
    }

    // TODO: Sprite
    //drawSprite(scanline);
}

void Display::drawBackground(const int& scanline, const byte& lcdc)
{
    // Get BG code area (Tile map)
    bool bgCodeAreaFlag = getBit(lcdc, 3);
    word tileMapAddr    = (bgCodeAreaFlag) ? 0x9c00 : 0x9800;

    // Read register info
    byte scollX  = memory.readByte(SCX_ADDR);
    byte scollY  = memory.readByte(SCY_ADDR);
    byte palette = memory.readByte(BGP_ADDR);

    // For every 8 pixel (a line of tile) in current scanline
    int screenY = scanline;
    for (int screenX = 0; screenX < 160; screenX += 8) {
        int mapX = screenX + scollX;
        int mapY = screenX + scollY;

        // handle overflow
        mapX = (mapX >= 256) ? mapX - 256 : mapX;
        mapY = (mapY >= 256) ? mapY - 256 : mapY;

        // Get character code
        int  blockCol  = mapX / 8;
        int  blockRow  = mapY / 8;
        int  block     = (blockRow * 32) + blockCol;
        word blockAddr = tileMapAddr + block;
        byte chrCode   = memory.readByte(blockAddr);

        // Get pixel position in tile
        int tileX = 7;  // X always comes with 0, and its stored in reverse
        int tileY = screenY % 8;

        // Get BG character area
        bool bgCharDataFlag = getBit(lcdc, 4);
        byte bgCharDataAddr;
        if (bgCharDataFlag) {
            bgCharDataAddr = 0x8000 + (chrCode * 16);
        }
        else {
            bgCharDataAddr = 0x9000 + (static_cast<int8_t>(chrCode) * 16);
        }

        // Get tile data
        byte higher = memory.readByte(bgCharDataAddr + (tileY * 2) + 1);
        byte lower  = memory.readByte(bgCharDataAddr + (tileY * 2));

        // draw!
        for (int i = 0; i < 8; i++) {
            sf::Color color = getColor(tileX - i, higher, lower, palette);
            background.setPixel(screenX + i, screenY, color);
        }
    }
}

sf::Color Display::getColor(int bit, byte higher, byte lower, byte palette)
{
    int color0 = palette & 0x03;
    int color1 = (palette >> 2) & 0x03;
    int color2 = (palette >> 4) & 0x03;
    int color3 = (palette >> 6) & 0x03;

    int color = (((higher >> bit) & 1u) << 1u) | ((lower >> bit) & 1u);

    switch (color) {
        case 0:
            return colorSet[color0];
        case 1:
            return colorSet[color1];
        case 2:
            return colorSet[color3];
        case 3:
            return colorSet[color3];
    }
}

}  // namespace Gameboy