//
// Created by jakub on 09.05.24.
//

#include "snakeViewer.h"
#include <iostream>
#include <string>
#include "ColorsConsts.h"

snakeViewer::snakeViewer(snakeBody &s, FontManager & f, TextureManager & t, const sf::RenderWindow & window) : snake(s), fontmgr(f), texmgr(t) {
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
    snakeHeadShape.setFillColor(snakeHeadColor);
    snakeHeadShape.setSize(sf::Vector2f(snakeBodySize,snakeBodySize));
    int snakeLength=snake.getSnakeLength();
    snakeBodyShape.reserve(snakeLength-1);
    sf::RectangleShape tmpBody;
    tmpBody.setFillColor(snakeBodyColor);
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


    for (sf::RectangleShape & bodyPart : snakeBodyShape){
        snakeHeadPointer++;
        tmpSnakePositionX = snakeHeadPointer->x * (snakeBodySize);
        tmpSnakePositionY = snakeHeadPointer->y * snakeBodySize+offsetY;
        bodyPart.setPosition(tmpSnakePositionX, tmpSnakePositionY);
//        std::cout<<bodyPart<<": "<<tmpSnakePositionX<<','<<tmpSnakePositionY<<std::endl;
    }

}

void snakeViewer::setupFruitView() {
    fruitShape.setFillColor(snakeFoodColor);
    fruitShape.setRadius(snakeBodySize*0.5);
}

void snakeViewer::updateFruitView() {
    point fruit=snake.getFruitPoint();
    int tmpFruitPositionX = fruit.x *(snakeBodySize);
    int tmpFruitPositionY = fruit.y *(snakeBodySize)+offsetY;

    fruitShape.setPosition(tmpFruitPositionX, tmpFruitPositionY);

}

void snakeViewer::setupBackground() {
    const sf::Texture * backgroundTex = texmgr.getBackgroundTexture();
    background.setFillColor(backgroundColor);
    background.setTexture(backgroundTex);
    background.setTextureRect(sf::IntRect(0,0,(snakeBodySize*0.2)*backgroundTex->getSize().x,(snakeBodySize*0.2)*backgroundTex->getSize().y));
    background.setSize(sf::Vector2f(windowWidth,windowHeight-offsetY));
    background.setPosition(0.f, offsetY);
}

void snakeViewer::setupScoreCounter() {
    const unsigned int textSize = offsetY*0.3;
    ScoreText.setFont(fontmgr.getFont());
    ScoreText.setCharacterSize(textSize);
    ScoreText.setFillColor(textColor);
    ScoreText.setString("Score:");

    Score.setFont(fontmgr.getFont());
    Score.setCharacterSize(textSize);
    Score.setFillColor(textColor);
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
    window.clear(scoreBackgroundColor);

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
    tmpBody.setFillColor(snakeBodyShape[0].getFillColor());
    tmpBody.setSize(sf::Vector2f(snakeBodySize, snakeBodySize));
    snakeBodyShape.push_back(tmpBody);
    updateSnakeView();
}

int snakeViewer::getOffsetY() const {
    return offsetY;
}




