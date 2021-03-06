#pragma once
#include <SFML/Window.hpp>
#include <array>
#include <iostream>
#include "Common.h"
#include "Memory.h"

namespace gb
{

class Memory;

class Gamepad
{
public:
    Gamepad(Memory& _memory) : memory(_memory) {}

    void init();

    byte readByte();
    void writeByte(const byte& value);

    void keyDown(sf::Keyboard::Key key);
    void keyUp(sf::Keyboard::Key key);

private:
    Memory& memory;

    std::array<byte, 2> row;
    byte                col;

    void requestInterrupt();
};

}  // namespace gb