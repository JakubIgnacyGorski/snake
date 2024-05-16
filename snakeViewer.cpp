//
// Created by jakub on 09.05.24.
//

#include "snakeViewer.h"
#include <iostream>
#include <string>

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
    updateScoreCounter();
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
    const unsigned int textSize = offsetY*0.3;
    ScoreText.setFont(fontmgr.getFont());
    ScoreText.setCharacterSize(textSize);
    ScoreText.setFillColor(sf::Color::Black);
    ScoreText.setString("Score:");

    Score.setFont(fontmgr.getFont());
    Score.setCharacterSize(textSize);
    Score.setFillColor(sf::Color::Black);
    Score.setString("00");

    const float XPosition = static_cast<float>((windowWidth - ScoreText.getLocalBounds().width - Score.getLocalBounds().width) * 0.5);
    const float YPosition = static_cast<float>((offsetY-ScoreText.getLocalBounds().height)*0.5);

    ScoreText.setPosition(XPosition, YPosition);
    Score.setPosition(XPosition + ScoreText.getLocalBounds().width + offsetY * 0.1, YPosition);
}

void snakeViewer::updateScoreCounter() {
    Score.setString(std::to_string(snake.getScore()));
}

void snakeViewer::drawGame(sf::RenderWindow &window) const {
    window.clear(sf::Color(250, 250, 250));

    window.draw(background);
    window.draw(ScoreText);
    window.draw(Score);
    window.draw(fruitShape);

    window.draw(snakeHeadShape);
    for (const sf::RectangleShape & bodyPart : snakeBodyShape) {
        window.draw(bodyPart);
    }
}

void snakeViewer::updateView() {
    updateSnakeView();
    updateFruitView();
    updateScoreCounter();
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




