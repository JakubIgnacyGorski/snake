//
// Created by jakub on 09.05.24.
//

#ifndef SNAKE_SNAKEVIEWER_H
#define SNAKE_SNAKEVIEWER_H
#include "snakeBody.h"
#include <SFML/Graphics.hpp>
#include "FontManager.h"
#include "TextureManager.h"




class snakeViewer {
    snakeBody & snake;
    FontManager & fontmgr;
    TextureManager & texmgr;
    sf::Text Score;
    sf::Text ScoreText;
    sf::RectangleShape snakeHeadShape;
    std::vector<sf::RectangleShape> snakeBodyShape;
    sf::RectangleShape snakeBackShape;
    sf::CircleShape fruitShape;
    sf::RectangleShape background;
    int snakeBodySize;
    int windowWidth;
    int windowHeight;
    int offsetY;
    void setupSnakeView();
    void setupHeadTexture();
    void setupBodyTexture(int bodyPart);
    void updateSnakeView();
    void setupFruitView();
    void updateFruitView();
    void setupBackground();
    void setupScoreCounter();
    void updateScoreCounter();
public:
    explicit snakeViewer(snakeBody & s, FontManager & f, TextureManager & t, const sf::RenderWindow & window);
    void newSnake();
    void drawGame(sf::RenderWindow & window) const;
    void updateView();
    void addSnakePart();
    int getOffsetY() const;
};


#endif //SNAKE_SNAKEVIEWER_H
