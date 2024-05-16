//
// Created by jakub on 09.05.24.
//

#include "snakeViewer.h"
#include <iostream>

snakeViewer::snakeViewer(snakeBody &s, FontManager & f, const sf::RenderWindow & window) : snake(s), fontmgr(f) {
    windowWidth = window.getSize().x;
    windowHeight = window.getSize().y;
    offsetY=windowHeight*0.1;
    newSnake();
}

void snakeViewer::newSnake() {
    snakeBodySize = std::max(windowWidth, windowHeight-offsetY)/std::max(snake.getBoardSize().x, snake.getBoardSize().y);
    setupSnakeView();
    updateSnakeView();
    setupFruitView();
    updateFruitView();
    setupBackground();
    setupScoreCounter();
}

void snakeViewer::setupSnakeView() {
    snakeBodyShape.clear();
    snakeHeadShape.setFillColor(sf::Color::Green);
    snakeHeadShape.setSize(sf::Vector2f(snakeBodySize,snakeBodySize));
    int snakeLength=snake.getSnakeLength();
    snakeBodyShape.reserve(snakeLength-1);
    sf::RectangleShape tmpBody;
    tmpBody.setFillColor(sf::Color::Blue);
    tmpBody.setSize(sf::Vector2f(snakeBodySize, snakeBodySize));
    for (int bodyPart=0; bodyPart<snakeLength-1; bodyPart++) {
        snakeBodyShape.push_back(tmpBody);
    }
}

void snakeViewer::updateSnakeView() {
    std::list<point>snakePosition = snake.snakePosition();
    auto snakeHeadPointer = snakePosition.begin();

    int tmpSnakePositionX = snakeHeadPointer->x * (snakeBodySize);
    int tmpSnakePositionY = snakeHeadPointer->y * (snakeBodySize)+offsetY;

    snakeHeadShape.setPosition(tmpSnakePositionX, tmpSnakePositionY);
//    std::cout<<"-1: "<<tmpSnakePositionX<<','<<tmpSnakePositionY<<std::endl;


    for (int bodyPart=0; bodyPart< static_cast<int>(snakeBodyShape.size()); bodyPart++){
        snakeHeadPointer++;
        tmpSnakePositionX = snakeHeadPointer->x * (snakeBodySize);
        tmpSnakePositionY = snakeHeadPointer->y * (snakeBodySize)+offsetY;
        snakeBodyShape[bodyPart].setPosition(tmpSnakePositionX, tmpSnakePositionY);
//        std::cout<<bodyPart<<": "<<tmpSnakePositionX<<','<<tmpSnakePositionY<<std::endl;
    }

}

void snakeViewer::setupFruitView() {
    fruitShape.setFillColor(sf::Color::Red);
    fruitShape.setRadius(snakeBodySize*0.5);
}

void snakeViewer::updateFruitView() {
    point fruit=snake.getFruitPoint();
    int tmpFruitPositionX = fruit.x *(snakeBodySize);
    int tmpFruitPositionY = fruit.y *(snakeBodySize)+offsetY;

    fruitShape.setPosition(tmpFruitPositionX, tmpFruitPositionY);

}

void snakeViewer::setupBackground() {
    background.setFillColor(sf::Color(150, 150, 150));
    background.setSize(sf::Vector2f(windowWidth,windowHeight-offsetY));
    background.setPosition(0.f, offsetY);
}

void snakeViewer::setupScoreCounter() {
    ScoreText.setFont(fontmgr.getFont());
    ScoreText.setCharacterSize(offsetY*0.5);
    ScoreText.setFillColor(sf::Color::Black);
    ScoreText.setString("Score:");

    int test = snake.getScore();

    Score.setFont(fontmgr.getFont());
    Score.setCharacterSize(offsetY*0.5);
    Score.setFillColor(sf::Color::Black);
    Score.setString("00");
}

void snakeViewer::drawGame(sf::RenderWindow &window) const {
    window.clear(sf::Color(250, 250, 250));
    window.draw(background);
    window.draw(snakeHeadShape);
    for (int bodyPart=0; bodyPart< static_cast<int>(snakeBodyShape.size()); bodyPart++){
        window.draw(snakeBodyShape[bodyPart]);
    }

    window.draw(fruitShape);

}

void snakeViewer::updateView() {
    updateSnakeView();
    updateFruitView();
//    std::cout<<std::endl;
//    snake.debug_display();
}

void snakeViewer::addSnakePart() {
    sf::RectangleShape tmpBody;
    tmpBody.setFillColor(sf::Color::Blue);
    tmpBody.setSize(sf::Vector2f(snakeBodySize, snakeBodySize));
    snakeBodyShape.push_back(tmpBody);
    updateSnakeView();
}

int snakeViewer::getOffsetY() const {
    return offsetY;
}




