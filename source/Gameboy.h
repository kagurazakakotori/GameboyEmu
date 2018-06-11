#pragma once
#include <iostream>
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

private:
    Gamepad gamepad;
    Memory  memory;
    CPU     cpu;
    Display display;
};

}  // namespace gb