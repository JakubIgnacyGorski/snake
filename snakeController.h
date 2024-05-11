    //
// Created by jakub on 09.05.24.
//

#ifndef SNAKE_SNAKECONTROLLER_H
#define SNAKE_SNAKECONTROLLER_H
#include <SFML/Graphics.hpp>
#include "snakeBody.h"
#include "snakeViewer.h"
#include "snakeMenu.h"

class snakeController {
    snakeBody & snake;
    snakeViewer & viewer;
    snakeMenu & menu;
    sf::Clock clock;
    sf::Time moveDelay;
    void keyboard(sf::Event & event);
    void timeMove();
    void changeDirection(speed newDir);
    void mouse(sf::Event & event);
public:
    snakeController(snakeBody & b, snakeViewer & v, snakeMenu & m);
    void play(sf::RenderWindow & window);
};


#endif //SNAKE_SNAKECONTROLLER_H
