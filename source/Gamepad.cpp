#include "Gamepad.h"

namespace gb
{

/* Note: In gamepad, 0 is pressed! */

Gamepad::Gamepad(Memory& _memory) : memory(_memory)
{
    col = 0x00;
    row.fill(0x0f);
    
    // Print key mapping info
    std::cout<< "[INFO] Current key mapping:" << std::endl;
    std::cout<< "[INFO] W-UP  A-LEFT  S-DOWN    D-RIGHT" << std::endl;
    std::cout<< "[INFO] J-A   K-B     B-SELECT  N-START" << std::endl;
    std::cout<< "[INFO] This version does NOT support custom key mapping" << std::endl;
}

/* Note: When both P14 & P15 set to 0, the joypad resets(maybe) */
byte Gamepad::readByte()
{
    switch (col) {
        case 0x20:  // P14 on
            return row[0];
        case 0x10:  // P15 on
            return row[1];
        case 0x00:
        default:
            return 0x00;
    }
}

void Gamepad::writeByte(const byte& value)
{
    col = value & 0b00110000;
    // Note: lower 4 bits are read only
}

void Gamepad::keyDown(sf::Keyboard::Key key)
{
    requestInterrupt();
    
    switch (key) {
        case sf::Keyboard::D:  // P14+P10 RIGHT
            row[0] &= 0b1110;
            return;
        case sf::Keyboard::A:  // P14+P11 LEFT
            row[0] &= 0b1101;
            return;
        case sf::Keyboard::W:  // P14+P12 UP
            row[0] &= 0b1011;
            return;
        case sf::Keyboard::S:  // P14+P13 DOWN
            row[0] &= 0b0111;
            return;
        case sf::Keyboard::J:  // P15+P10 A
            row[1] &= 0b1110;
            return;
        case sf::Keyboard::K:  // P15+P11 B
            row[1] &= 0b1101;
            return;
        case sf::Keyboard::B:  // P15+P12 SELECT
            row[1] &= 0b1011;
            return;
        case sf::Keyboard::N:  // P15+P13 START
            row[1] &= 0b0111;
            return;
    }
}

void Gamepad::keyUp(sf::Keyboard::Key key)
{
    switch (key) {
        case sf::Keyboard::D:  // P14+P10 RIGHT
            row[0] |= 0b0001;
            return;
        case sf::Keyboard::A:  // P14+P11 LEFT
            row[0] |= 0b0010;
            return;
        case sf::Keyboard::W:  // P14+P12 UP
            row[0] |= 0b0100;
            return;
        case sf::Keyboard::S:  // P14+P13 DOWN
            row[0] |= 0b1000;
            return;
        case sf::Keyboard::J:  // P15+P10 A
            row[1] |= 0b0001;
            return;
        case sf::Keyboard::K:  // P15+P11 B
            row[1] |= 0b0010;
            return;
        case sf::Keyboard::B:  // P15+P12 SELECT
            row[1] |= 0b0100;
            return;
        case sf::Keyboard::N:  // P15+P13 START
            row[1] |= 0b1000;
            return;
    }
}

void Gamepad::requestInterrupt(){
    byte interruptFlag = memory.readByte(IF_ADDR);
    setBit(interruptFlag, 4, 1);
    memory.writeByte(IF_ADDR, interruptFlag);
}

}  // namespace gb