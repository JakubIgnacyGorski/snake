#include <iostream>
#include <SFML/Graphics.hpp>
#include "snakeBody.h"
#include "snakeViewer.h"
#include "snakeController.h"


int main() {

    sf::RenderWindow window (sf::VideoMode(800,600), "Snake");

    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    snakeBody body;
    snakeViewer viewer(body);

    sf::Event event;
    while (window.isOpen()) {
        while(window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }
        viewer.draw(window);
    }


    return 0;
}
