#include "Gameboy.h"

namespace gb
{

Gameboy::Gameboy()
    : memory(), cpu(memory), display(memory), gamepad(memory), timer(memory, display)
{
    std::cout << "[INFO] Gameboy Started!" << std::endl;
}

void Gameboy::init()
{
    cpu.init();
    memory.init(&gamepad);
    std::cout << termcolor::green << "[INFO] Gameboy Running!" << termcolor::reset << std::endl;
}

void Gameboy::run()
{
    while (display.screen.isOpen()) {
        int cycleElasped = 0;
        handleEvents();
        while (cycleElasped < CYCLE_PER_FRAME) {
            cpu.exec();
            cycleElasped += cpu.cycle;
            cpu.handleInterrupt();

            timer.updateTimer(cpu.cycle);
            timer.updateDisplay(cpu.cycle);

            cpu.cycle = 0;
        }

        display.refresh();

        cycleElasped = 0;
    }
}

void Gameboy::loadRom(std::string path)
{
    memory.loadRom(path);
}

void Gameboy::handleEvents()
{
    sf::Event event;
    while (display.screen.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            display.screen.close();
        }
        // Input handler
        if (event.type == sf::Event::KeyPressed) {
            gamepad.keyDown(event.key.code);
        }
        else if (event.type == sf::Event::KeyReleased) {
            gamepad.keyUp(event.key.code);
        }
    }
}

}  // namespace gb