#include "Display.h"

namespace gb
{

Display::Display(Memory& _memory) : memory(_memory)
{
    frame.create(160, 144);
    backgroundArray.fill(sf::Color::White);
    windowArray.fill(sf::Color::White);
    //spriteArray.fill(sf::Color::White);

    // initialize colorset
    colorSet[0] = sf::Color(255, 255, 255);
    colorSet[1] = sf::Color(192, 192, 192);
    colorSet[2] = sf::Color(96, 96, 96);
    colorSet[3] = sf::Color(0, 0, 0);

    screen.create(sf::VideoMode(160, 144), "screen");

    std::cout << "[INFO] Display module initialized" << std::endl;
}

void Display::refresh()
{
    renderFrame();

    screen.clear(sf::Color::Green);

    sf::Texture frameTexture;
    frameTexture.loadFromImage(frame);
    sf::Sprite frameSprite;
    frameSprite.setTexture(frameTexture);

    screen.draw(frameSprite);
    screen.display();
}

void Display::renderFrame()
{
    byte lcdc = memory.readByte(LCDC_ADDR);

    if (getBit(lcdc, 7)) {
        for (int x = 0; x < 160; x++) {
            for (int y = 0; y < 144; y++) {
                if (backgroundEnable[y * 160 + x]) {
                    frame.setPixel(x, y, backgroundArray[y * 160 + x]);
                }

                if (windowEnable[y * 160 + x]) {
                    frame.setPixel(x, y, windowArray[y * 160 + x]);
                }

                /* TODO: Sprite
                if (spriteEnable[y * 160 + x]) {
                    frame.setPixel(x, y, spriteArray[y * 160 + x]);
                }
                */
            }
        }
    }

    // Disable all pixels
    backgroundEnable.fill(false);
    windowEnable.fill(false);
    spriteEnable.fill(false);
}

void Display::renderScanline(const int& scanline)
{
    byte lcdc = memory.readByte(LCDC_ADDR);

    if (getBit(lcdc, 0)) {  // Background on flag
        drawBackground(scanline, lcdc);
    }

    if (getBit(lcdc, 5)) {  // Window on flag
        drawWindow(scanline, lcdc);
    }

    /* TODO: Sprite
    if (getBit(lcdc, 1)) {  // Sprite on flag
        drawSprite(scanline, lcdc);
    }
    */
}

// Background and Window are drawn in the same way
void Display::drawBackground(const int& scanline, const byte& lcdc)
{
    drawBackgroundOrWindow(scanline, lcdc, true);
}

void Display::drawWindow(const int& scanline, const byte& lcdc)
{
    drawBackgroundOrWindow(scanline, lcdc, false);
}

void Display::drawBackgroundOrWindow(const int& scanline, const byte& lcdc, bool isBackground)
{
    // Select tile map
    word tileMapAddr;
    if (isBackground) {
        tileMapAddr = (getBit(lcdc, 3)) ? 0x9c00 : 0x9800;
    }
    else {
        tileMapAddr = (getBit(lcdc, 6)) ? 0x9c00 : 0x9800;
    }

    // Select tile set
    word tileSetAddr;
    int  tileSetOffset;
    if (getBit(lcdc, 4)) {
        tileSetAddr   = 0x8000;
        tileSetOffset = 0;
    }
    else {
        tileSetAddr   = 0x9000;
        tileSetOffset = 256;
    }

    // Judge the line of tile to draw
    int scrollY  = (isBackground) ? memory.readByte(SCY_ADDR) : memory.readByte(WY_ADDR);
    int tileLine = (isBackground) ? ((scrollY + scanline) % 8) : (scanline % 8);
    int tileRow  = (isBackground) ? (((scrollY + scanline) / 8) % 32) : ((scanline % 8) / 32);

    // Draw by tile(32 * 8)
    byte palette = memory.readByte(BGP_ADDR);
    for (int tileX = 0; tileX < 32; tileX++) {
        int tileNumber = memory.readByte(tileMapAddr + (32 * tileRow) + tileX);
        if (tileNumber > 127) {
            tileNumber -= tileSetOffset;
        }

        word tileAddr      = tileSetAddr + (tileNumber * 16);
        auto tileLineArray = drawTile(tileAddr, palette, tileLine, false);

        // Write back to background array
        int bit = 7;
        for (auto pixel : tileLineArray) {
            int scrollX = (isBackground) ? memory.readByte(SCX_ADDR) : memory.readByte(WX_ADDR);

            unsigned int x = (isBackground) ? ((tileX * 8) + bit + (256 - scrollX) % 256) : ((tileX * 8) + bit + scrollX - 7);
            unsigned int y = (isBackground) ? scanline : (scanline + scrollY);
            if (x < 160 && y < 144) {
                if (isBackground) {
                    backgroundArray[y * 160 + x]  = pixel;
                    backgroundEnable[y * 160 + x] = true;
                }
                else {
                    windowArray[y * 160 + x]  = pixel;
                    windowEnable[y * 160 + x] = true;
                }
            }
            bit--;
        }
    }
}

std::array<sf::Color, 8> Display::drawTile(const word& tileAddr, const byte& palette, int tileLine, bool isSprite)
{
    word tileLineAddr   = tileAddr + 2 * tileLine;
    byte tileLineLower  = memory.readByte(tileLineAddr);
    byte tileLineHigher = memory.readByte(tileLineAddr + 1);

    std::array<sf::Color, 8> tileLineArray;
    for (int bit = 7; bit >= 0; bit--) {
        tileLineArray[bit] = getColor(bit, tileLineHigher, tileLineLower, palette, isSprite);
    }

    return tileLineArray;
}

sf::Color Display::getColor(int bit, const byte& higher, const byte& lower, const byte& palette, bool isSprite)
{
    int color0 = palette & 0x03;
    int color1 = (palette >> 2) & 0x03;
    int color2 = (palette >> 4) & 0x03;
    int color3 = (palette >> 6) & 0x03;

    int color = (((higher >> bit) & 1u) << 1u) | ((lower >> bit) & 1u);

    switch (color) {
        case 0:
            return isSprite ? sf::Color::Transparent : colorSet[color0];
        case 1:
            return colorSet[color1];
        case 2:
            return colorSet[color2];
        case 3:
            return colorSet[color3];
    }
}

}  // namespace gb