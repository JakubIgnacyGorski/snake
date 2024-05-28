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
    const sf::Vector2f snakeBodySizeVector {static_cast<float>(snakeBodySize), static_cast<float>(snakeBodySize)};
    snakeBodyShape.clear();
    snakeHeadShape.setFillColor(snakeHeadColor);
    snakeHeadShape.setSize(snakeBodySizeVector);
    int snakeLength=snake.getSnakeLength()-2;
    snakeBodyShape.reserve(snakeLength);
    sf::RectangleShape tmpBody;
    tmpBody.setFillColor(snakeBodyColor);
    tmpBody.setSize(snakeBodySizeVector);
    for (int bodyPart=0; bodyPart<snakeLength; bodyPart++) {
        snakeBodyShape.push_back(tmpBody);
    }
    snakeBackShape.setFillColor(snakeBackColor);
    snakeBackShape.setSize(snakeBodySizeVector);

}

void snakeViewer::setupHeadTexture() {
    const speed snakeSpeed=snake.getSnakeSpeed();
    snakeHeadShape.setTexture(texmgr.getSnakeHead(RIGHT));
    snakeHeadShape.setRotation(180);
    snakeHeadShape.move(snakeHeadShape.getSize().x,snakeHeadShape.getSize().y);

//    if (snakeSpeed==speed{0,-1})
//        snakeHeadShape.setTexture(texmgr.getSnakeHead(UP));
//    else if (snakeSpeed==speed{1,0} || snakeSpeed==speed{0,0})
//        snakeHeadShape.setTexture(texmgr.getSnakeHead(RIGHT));
//    else if (snakeSpeed==speed{0,1})
//        snakeHeadShape.setTexture(texmgr.getSnakeHead(DOWN));
//    else if (snakeSpeed==speed{-1,0})
//        snakeHeadShape.setTexture(texmgr.getSnakeHead(LEFT));

}

void snakeViewer::setupBodyTexture(const int bodyPart) {
    const speed snakeSpeed = snake.getSnakeSpeed();
    if (bodyPart==0) {
        if (snakeSpeed.Vx==0)
            snakeBodyShape[bodyPart].setTexture(texmgr.getSnakeBody(UP));
        else
            snakeBodyShape[bodyPart].setTexture(texmgr.getSnakeBody(RIGHT));
        return;
    }

    if (snakeSpeed.Vx==0)
        snakeBodyShape[bodyPart].setTexture(texmgr.getSnakeBody(UP));
    else
        snakeBodyShape[bodyPart].setTexture(texmgr.getSnakeBody(RIGHT));
}

void snakeViewer::updateSnakeView() {
    std::list<point>snakePosition = snake.snakePosition();
    auto snakeHeadPointer = snakePosition.begin();

    int tmpSnakePositionX = snakeHeadPointer->x * (snakeBodySize);
    int tmpSnakePositionY = snakeHeadPointer->y * (snakeBodySize)+offsetY;

    snakeHeadShape.setPosition(tmpSnakePositionX, tmpSnakePositionY);
    setupHeadTexture();
//    std::cout<<"-1: "<<tmpSnakePositionX<<','<<tmpSnakePositionY<<std::endl;

    for (int bodyPart=0; bodyPart<static_cast<int>(snakeBodyShape.size()); bodyPart++) {
        snakeHeadPointer++;
        tmpSnakePositionX = snakeHeadPointer->x * (snakeBodySize);
        tmpSnakePositionY = snakeHeadPointer->y * snakeBodySize+offsetY;
        snakeBodyShape[bodyPart].setPosition(tmpSnakePositionX, tmpSnakePositionY);
//        setupBodyTexture(bodyPart);
//        std::cout<<bodyPart<<": "<<tmpSnakePositionX<<','<<tmpSnakePositionY<<std::endl;
    }
    snakeHeadPointer++;
    tmpSnakePositionX = snakeHeadPointer->x * (snakeBodySize);
    tmpSnakePositionY = snakeHeadPointer->y * snakeBodySize+offsetY;
    snakeBackShape.setPosition(tmpSnakePositionX, tmpSnakePositionY);
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
    window.draw(snakeBackShape);
}

void snakeViewer::updateView() {
    updateSnakeView();
    updateFruitView();
    updateScoreCounter();
}

void snakeViewer::addSnakePart() {
    snakeBodyShape.push_back(snakeBackShape);
    snakeBodyShape.back().setTexture(snakeBodyShape.begin()->getTexture());
    snakeBodyShape.back().setFillColor(snakeBodyShape.begin()->getFillColor());
    snakeBodyShape.back().setSize(snakeBodyShape.begin()->getSize());

    updateSnakeView();
}

int snakeViewer::getOffsetY() const {
    return offsetY;
}





