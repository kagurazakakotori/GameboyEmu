#pragma once 
#include <SFML/Window.hpp>
#include <array>
#include <iostream>
#include "Common.h"

namespace gb
{

class Gamepad
{
public:
    Gamepad();

    byte readByte();
    void writeByte(const byte& value);

private:
    std::array<byte, 2> row;
    byte                col;

    void keyDown(sf::Keyboard::Key key);
    void keyUp(sf::Keyboard::Key key);
};

}  // namespace gb