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
    Gamepad gamepad;
    Memory  memory;
    CPU     cpu;
    Display display;

    bool romloaded   = false;
    bool initialized = false;

    void handleEvents();
};

}  // namespace gb