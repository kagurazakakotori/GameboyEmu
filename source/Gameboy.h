#pragma once
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include "CPU.h"
#include "Common.h"
#include "Display.h"
#include "Gamepad.h"
#include "Memory.h"

namespace gb
{

class Gameboy
{
public:
    Gameboy();

    void loadRom(std::string path);
    void init();
    void run();

private:
    static const int FREQUENCY = 4194304;
    static const int CYCLE_PER_FRAME = 69905;
    static const sf::Int64 FRAME_INTERVAL = 16667;

    Memory  memory;
    CPU     cpu;
    Display display;
    Gamepad gamepad;

    bool romloaded   = false;
    bool initialized = false;

    void handleEvents();
};

}  // namespace gb