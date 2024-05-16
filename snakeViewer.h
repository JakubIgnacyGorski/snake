//
// Created by jakub on 09.05.24.
//

#ifndef SNAKE_SNAKEVIEWER_H
#define SNAKE_SNAKEVIEWER_H
#include "snakeBody.h"
#include <SFML/Graphics.hpp>
#include "FontManager.h"




class snakeViewer {
    snakeBody & snake;
    FontManager & fontmgr;
    sf::Text Score;
    sf::Text ScoreText;
    sf::RectangleShape snakeHeadShape;
    std::vector<sf::RectangleShape> snakeBodyShape;
    sf::CircleShape fruitShape;
    int snakeBodySize;
    int windowWidth;
    int windowHeight;
    int offsetY;
    void setupSnakeView();
    void updateSnakeView();
    void setupFruitView();
    void updateFruitView();
    void setupScoreCounter();
public:
    explicit snakeViewer(snakeBody & s, FontManager & f, const sf::RenderWindow & window);
    void newSnake();
    void drawGame(sf::RenderWindow & window) const;
    void updateView();
    void addSnakePart();
    int getOffsetY() const;
};


#endif //SNAKE_SNAKEVIEWER_H
