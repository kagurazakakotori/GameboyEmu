#include "Display.h"

namespace gb
{

Display::Display(Memory& _memory) : memory(_memory)
{
    // initialize colorset
    colorSet[0] = sf::Color(255, 255, 255);
    colorSet[1] = sf::Color(192, 192, 192);
    colorSet[2] = sf::Color(96, 96, 96);
    colorSet[3] = sf::Color(0, 0, 0);

    screen.create(sf::VideoMode(160, 144), "screen");

    background.create(160, 144, sf::Color::Transparent);
    window.create(160, 144, sf::Color::Transparent);
    sprite.create(160, 144, sf::Color::Transparent);

    std::cout << "[INFO] Display module initialized" << std::endl;
}

void Display::renderFrame()
{
    bool isLcdcOn = getBit(memory.readByte(LCDC_ADDR), 7);
    if (!isLcdcOn) {
        return;
    }
    screen.clear();

    sf::Texture backgroundTexture;
    sf::Texture windowTexture;
    sf::Texture spriteTexture;

    backgroundTexture.loadFromImage(background);
    windowTexture.loadFromImage(window);
    spriteTexture.loadFromImage(sprite);

    sf::Sprite backgroundSprite(backgroundTexture);
    sf::Sprite windowSprite(windowTexture);
    sf::Sprite spriteSprite(spriteTexture);

    screen.draw(backgroundSprite);
    screen.draw(windowSprite);
    screen.draw(spriteSprite);

    screen.display();
}

void Display::renderScanline(const int& scanline)
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

    scanlineRendered++;
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

void Display::drawWindow(const int& scanline, const byte& lcdc)
{
    // Get window code area
    bool windowCodeAreaFlag = getBit(lcdc, 6);
    word tileMapAddr        = (windowCodeAreaFlag) ? 0x9c00 : 0x9800;

    // Read register info
    byte windowX = memory.readByte(WX_ADDR);
    byte windowY = memory.readByte(WY_ADDR);
    byte palette = memory.readByte(BGP_ADDR);

    int screenY = scanline;
    for (int screenX = 0; screenX < 160; screenX++) {
        if (scanline < static_cast<int>(windowY)) {
            window.setPixel(screenX, screenY, sf::Color::Transparent);
        }
        else {
            int mapX = screenX + windowX - 7;
            int mapY = screenY + windowY;

            // Get character code
            int  blockCol  = mapX / 8;
            int  blockRow  = mapY / 8;
            int  block     = (blockRow * 32) + blockCol;
            word blockAddr = tileMapAddr + block;
            byte chrCode   = memory.readByte(blockAddr);

            // Get pixel position in tile
            int tileX = screenX % 8;  // X always comes with 0, and its stored in reverse
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
            sf::Color color = getColor(7 - tileX, higher, lower, palette);
            window.setPixel(screenX, screenY, color);
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

void Display::updateStat()
{
    byte stat        = memory.readByte(STAT_ADDR);
    byte scanline    = memory.readByte(LY_ADDR);  // LY
    int  modeCurrent = stat & 0x03;
    int  modeToSet;
    bool requestInterruptFlag;

    int oamThreshold  = 456 - 80;        // One line - Scanline(OAM)
    int vramThreshold = 456 - 80 - 172;  // One line - Scanline(OAM) - Scanline(VRAM)

    if (scanline >= 144) {  // V-Blank
        modeToSet = 1;
        setMode(stat, 0, 1);
        requestInterruptFlag = getBit(stat, 4);
    }
    else {
        if (scanlineCount >= oamThreshold) {  // OAM
            modeToSet = 2;
            setMode(stat, 1, 0);
            requestInterruptFlag = getBit(stat, 5);
        }
        else if (scanlineCount >= vramThreshold) {  // VRAM
            modeToSet = 3;
            setMode(stat, 1, 1);
        }
        else {  // H-Blank
            modeToSet = 0;
            // If first time for H-blank, update scanline
            if (modeToSet != modeCurrent) {
                if (scanline < 144 && scanlineRendered <= 144) {
                    renderScanline(scanline);
                }
            }
            setMode(stat, 0, 0);
            requestInterruptFlag = getBit(stat, 3);
        }
    }

    // If enter new mode, request STAT interrupt
    if (requestInterruptFlag && (modeToSet != modeCurrent)) {
        requestInterrupt(1);
    }

    // Update LYC status
    if (scanline == memory.readByte(LYC_ADDR)) {
        setBit(stat, 2, 1);
        if (getBit(stat, 6)) {
            requestInterrupt(1);
        }
    }
    else {
        setBit(stat, 2, 0);
    }

    memory.writeByte(STAT_ADDR, stat);
}

void Display::setMode(byte& stat, const bool& bit1, const bool& bit0)
{
    setBit(stat, 1, bit1);
    setBit(stat, 0, bit0);
}

void Display::requestInterrupt(const int& interruptType)
{
    // 0: V-Blank Interrupt
    // 1: LCD STAT Interrupt
    byte interruptFlag = memory.readByte(IF_ADDR);
    setBit(interruptFlag, interruptType, 1);
    memory.writeByte(IF_ADDR, interruptFlag);
}

}  // namespace gb