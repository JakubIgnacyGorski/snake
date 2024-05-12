//
// Created by jakub on 09.05.24.
//

#include "snakeViewer.h"
#include <iostream>

snakeViewer::snakeViewer(snakeBody &s, sf::RenderWindow const & window) : snake(s) {
    windowWidth = window.getSize().x;
    windowHeight = window.getSize().y;
    newSnake();
}

void snakeViewer::newSnake() {
    snakeBodySize = std::max(windowWidth, windowHeight)/std::max(snake.getBoardSize().x, snake.getBoardSize().y);
    setupSnakeView();
    updateSnakeView();
    setupFruitView();
    updateFruitView();
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
    int tmpSnakePositionY = snakeHeadPointer->y * (snakeBodySize);

    snakeHeadShape.setPosition(tmpSnakePositionX, tmpSnakePositionY);
//    std::cout<<"-1: "<<tmpSnakePositionX<<','<<tmpSnakePositionY<<std::endl;


    for (int bodyPart=0; bodyPart< static_cast<int>(snakeBodyShape.size()); bodyPart++){
        snakeHeadPointer++;
        tmpSnakePositionX = snakeHeadPointer->x * (snakeBodySize);
        tmpSnakePositionY = snakeHeadPointer->y * (snakeBodySize);
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
    int tmpFruitPositionY = fruit.y *(snakeBodySize);

    fruitShape.setPosition(tmpFruitPositionX, tmpFruitPositionY);

}

void snakeViewer::drawGame(sf::RenderWindow &window) const {
    window.clear(sf::Color(250, 250, 250));
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




