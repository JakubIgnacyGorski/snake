//
// Created by jakub on 09.05.24.
//

#include "snakeViewer.h"
#include <iostream>

snakeViewer::snakeViewer(snakeBody &s) : snake(s) {
    setupSnakeView();
    updateSnakeView();
    setupFruitView();
    updateFruitView();
}

void snakeViewer::setupSnakeView() {
    snakeHeadShape.setFillColor(sf::Color::Green);
    snakeHeadShape.setSize(sf::Vector2f(snakeBodySize,snakeBodySize));
    int snakeLength=snake.getSnakeLength();
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

    int tmpSnakePositionX = snakeHeadPointer->x * (snakeBodySize+10);
    int tmpSnakePositionY = snakeHeadPointer->y * (snakeBodySize+10);

    snakeHeadShape.setPosition(tmpSnakePositionX, tmpSnakePositionY);
//    std::cout<<"-1: "<<tmpSnakePositionX<<','<<tmpSnakePositionY<<std::endl;


    for (int bodyPart=0; bodyPart< static_cast<int>(snakeBodyShape.size()); bodyPart++){
        snakeHeadPointer++;
        tmpSnakePositionX = snakeHeadPointer->x * (snakeBodySize+10);
        tmpSnakePositionY = snakeHeadPointer->y * (snakeBodySize+10);
        snakeBodyShape[bodyPart].setPosition(tmpSnakePositionX, tmpSnakePositionY);
//        std::cout<<bodyPart<<": "<<tmpSnakePositionX<<','<<tmpSnakePositionY<<std::endl;
    }

}

void snakeViewer::setupFruitView() {
    fruitShape.setFillColor(sf::Color::Red);
    fruitShape.setRadius(25);
}

void snakeViewer::updateFruitView() {
    point fruit=snake.getFruitPoint();
    int tmpFruitPositionX = fruit.x *(snakeBodySize+10);
    int tmpFruitPositionY = fruit.y *(snakeBodySize+10);

    fruitShape.setPosition(tmpFruitPositionX, tmpFruitPositionY);

}

void snakeViewer::draw(sf::RenderWindow &window) const {
    window.clear(sf::Color(250, 250, 250));
    drawGame(window);
    window.display();
}

void snakeViewer::drawGame(sf::RenderWindow &window) const {
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


