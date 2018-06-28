#pragma once
#include <SFML/Window.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include "CPU.h"
#include "Common.h"
#include "Display.h"
#include "Gamepad.h"
#include "Memory.h"
#include "Timer.h"

namespace gb
{

class Gameboy
{
public:
    Gameboy();

    void loadRom(std::string path);
    void init(float scale = 1);
    void run();

private:
    static const int FREQUENCY       = 4194304;
    static const int CYCLE_PER_FRAME = 70224;
    const std::chrono::microseconds FRAME_INTERVAL = std::chrono::microseconds(16600);

    Memory  memory;
    CPU     cpu;
    Display display;
    Gamepad gamepad;
    Timer   timer;

    bool romloaded   = false;
    bool initialized = false;

    void handleEvents();
};

}  // namespace gb