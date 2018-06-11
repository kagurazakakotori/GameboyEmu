#include "Gameboy.h"

namespace gb
{

Gameboy::Gameboy()
    : gamepad(), memory(gamepad), cpu(memory), display(memory)
{
    std::cout << "[INFO] Gameboy Running!" << std::endl;
}

}  // namespace gb