//
// Created by jakub on 09.05.24.
//

#ifndef SNAKE_SNAKEVIEWER_H
#define SNAKE_SNAKEVIEWER_H
#include "snakeBody.h"
#include <SFML/Graphics.hpp>

const int snakeBodySize = 50;


class snakeViewer {
    snakeBody & snake;
    sf::RectangleShape snakeHeadShape;
    std::vector<sf::RectangleShape> snakeBodyShape;
    sf::CircleShape fruitShape;
    void setupSnakeView();
    void updateSnakeView();
    void setupFruitView();
    void updateFruitView();
public:
    explicit snakeViewer(snakeBody & s);
    void draw(sf::RenderWindow & window) const;
    void drawGame(sf::RenderWindow & window) const;
    void updateView();
    void addSnakePart();
};


#endif //SNAKE_SNAKEVIEWER_H
