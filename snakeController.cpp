//
// Created by jakub on 09.05.24.
//

#include "snakeController.h"

snakeController::snakeController(snakeBody &b, snakeViewer &v) : body(b), viewer(v) {

}

void snakeController::play(sf::RenderWindow & window) {
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
}
