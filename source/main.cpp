#include <iostream>
#include <SFML/Graphics.hpp>
#include "CPU.h"
#include "Memory.h"

gb::CPU cpu;
gb::Memory memory;

int main()
{
    cpu.init();

    // A simple SFML test
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape  shape(100.f);
    shape.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}