#include "Gameboy.h"

namespace gb
{

Gameboy::Gameboy()
    : memory(), cpu(memory), display(memory), gamepad(memory)
{
    std::cout << "[INFO] Gameboy Running!" << std::endl;
}

void Gameboy::init(){
    cpu.init();
    memory.init(&gamepad);
}

void Gameboy::run()
{
    while (display.screen.isOpen()) {
        handleEvents();
        display.renderFrame();
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