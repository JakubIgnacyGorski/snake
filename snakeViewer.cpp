//
// Created by jakub on 09.05.24.
//

#include "snakeViewer.h"
#include <iostream>

snakeViewer::snakeViewer(snakeBody &s) : snake(s) {
    setupSnakeView();
    updateSnakeView();
}

void snakeViewer::setupSnakeView() {
    snakeHeadShape.setFillColor(sf::Color::Green);
    snakeHeadShape.setSize(sf::Vector2f(snakeBodySize,snakeBodySize));
    int snakeLength=snake.getSnakeLength();
    sf::RectangleShape tmpBody;
    tmpBody.setFillColor(sf::Color::Blue);
    tmpBody.setSize(sf::Vector2f(snakeBodySize, snakeBodySize));
    for (int bodyPart=0; bodyPart<snakeLength; bodyPart++) {
        snakeBodyShape.push_back(tmpBody);
    }
}

void snakeViewer::updateSnakeView() {
    snakePosition = snake.snakePosition();
    auto snakeHeadPointer = snakePosition.begin();
    auto snakeBackPointer = (--snakePosition.end());

    int tmpSnakePositionX = snakeHeadPointer->x * (snakeBodySize+10);
    int tmpSnakePositionY = snakeHeadPointer->y * (snakeBodySize+10);

    snakeHeadShape.setPosition(tmpSnakePositionX, tmpSnakePositionY);


    for (int bodyPart=0; bodyPart< static_cast<int>(snakePosition.size()-1); bodyPart++){
        snakeHeadPointer++;
        tmpSnakePositionX = snakeHeadPointer->x * (snakeBodySize+10);
        tmpSnakePositionY = snakeHeadPointer->y * (snakeBodySize+10);
        snakeBodyShape[bodyPart].setPosition(tmpSnakePositionX, tmpSnakePositionY);
//        std::cout<<bodyPart<<": "<<tmpSnakePositionX<<','<<tmpSnakePositionY<<std::endl;
    }

}

void snakeViewer::setupFruitView() {

}

void snakeViewer::updateFruitView() {

}

void snakeViewer::draw(sf::RenderWindow &window) const {
    window.clear(sf::Color(250, 250, 250));
    drawGame(window);
    window.display();
}

void snakeViewer::drawGame(sf::RenderWindow &window) const {
    window.draw(snakeHeadShape);
    auto snakeHeadPointer = snakePosition.begin();
    auto snakeBackPointer = (--snakePosition.end());
    if (snakeHeadPointer!=snakeBackPointer) {
        snakeHeadPointer++;
        int bodyPart=0;
        while (snakeHeadPointer!=snakeBackPointer){
            window.draw(snakeBodyShape[bodyPart]);
            snakeHeadPointer++;
            bodyPart++;
//            std::cout<<bodyPart<<std::endl;
        }
    }

}

void snakeViewer::updateView() {

}


