//
// Created by jakub on 09.05.24.
//

#include "snakeController.h"
#include <iostream>

snakeController::snakeController(snakeBody &b, snakeViewer &v) : snake(b), viewer(v) {

}

void snakeController::keyboard(sf::Event &event) {
    switch (event.key.code) {
        case (sf::Keyboard::Key::Right):
            snake.snakeMove(speed{1, 0});
            break;
        case (sf::Keyboard::Key::Left):
            snake.snakeMove(speed{-1, 0});
            break;
        case (sf::Keyboard::Key::Up):
            snake.snakeMove(speed{0, -1});
            break;
        case (sf::Keyboard::Key::Down):
            snake.snakeMove(speed{0, 1});
            break;
        default:
            return;
    }
    viewer.updateView();
}


void snakeController::play(sf::RenderWindow & window) {

    while (window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    keyboard(event);
                    break;
                default:
                    break;
            }
        }

        viewer.draw(window);
    }
}



