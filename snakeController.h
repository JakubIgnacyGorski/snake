    //
// Created by jakub on 09.05.24.
//

#ifndef SNAKE_SNAKECONTROLLER_H
#define SNAKE_SNAKECONTROLLER_H
#include <SFML/Graphics.hpp>
#include "snakeBody.h"
#include "snakeViewer.h"

class snakeController {
    snakeBody & snake;
    snakeViewer & viewer;
    sf::Clock clock;
    sf::Time moveDelay;
    void keyboard(sf::Event & event);
    void timeMove();
    void changeDirection(speed newDir);
public:
    snakeController(snakeBody & b, snakeViewer & v);
    void play(sf::RenderWindow & window);
};


#endif //SNAKE_SNAKECONTROLLER_H
