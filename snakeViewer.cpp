//
// Created by jakub on 09.05.24.
//

#include "snakeViewer.h"
#include <iostream>
#include <string>
#include <random>
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

void snakeViewer::rotateBodyPart(speed dir, sf::RectangleShape & bodyPart) {
    if (dir==speed{0,-1}) {
        bodyPart.setRotation(90);
        bodyPart.setScale(-1.f, 1.f);
        bodyPart.move(bodyPart.getSize().x, bodyPart.getSize().y);
    } else if (dir==speed{1,0} || dir==speed{0,0}) {
        bodyPart.setRotation(0);
        bodyPart.setScale(1.f, 1.f);
    }
    else if (dir==speed{0,1}) {
        bodyPart.setRotation(90);
        bodyPart.setScale(sf::Vector2f (1.f,1.f));
        bodyPart.move(bodyPart.getSize().x,0);
    }
    else if (dir==speed{-1,0}){
        bodyPart.setRotation(0);
        bodyPart.setScale(-1.f,1.f);
        bodyPart.move(bodyPart.getSize().x,0);
    }
}

void snakeViewer::setupHeadTexture() {
    snakeHeadShape.setTexture(texmgr.getSnakeHead());
    rotateBodyPart(snake.getSnakeSpeed(), snakeHeadShape);
}

void snakeViewer::setupTurnTexture(sf::RectangleShape &bodyPart, std::list<snakeBodyPart>::const_iterator snakeBody) {
    auto afterBodyPartSpeed = --snakeBody;
    snakeBody++;
    if ((snakeBody->bodySpeed.Vx == 1 && afterBodyPartSpeed->bodySpeed.Vy == -1) ||
        (snakeBody->bodySpeed.Vy == 1 && afterBodyPartSpeed->bodySpeed.Vx == -1) ||
        (snakeBody->bodySpeed == speed{0,0} && afterBodyPartSpeed->bodySpeed.Vy == -1) ||
        (snakeBody->bodySpeed == speed{0,0} && afterBodyPartSpeed->bodySpeed.Vx == -1)) {
        bodyPart.setTexture(texmgr.getSnakeTurn(DOWNRIGHT));
    } else if ((snakeBody->bodySpeed.Vy == 1 && afterBodyPartSpeed->bodySpeed.Vx == 1) ||
               (snakeBody->bodySpeed.Vx == -1 && afterBodyPartSpeed->bodySpeed.Vy == -1) ||
               (snakeBody->bodySpeed == speed{0,0} && afterBodyPartSpeed->bodySpeed.Vx == 1) ||
               (snakeBody->bodySpeed == speed{0,0} && afterBodyPartSpeed->bodySpeed.Vy == -1)) {
        bodyPart.setTexture(texmgr.getSnakeTurn(DOWNLEFT));
    } else if ((snakeBody->bodySpeed.Vx == 1 && afterBodyPartSpeed->bodySpeed.Vy == 1) ||
               (snakeBody->bodySpeed.Vy == -1 && afterBodyPartSpeed->bodySpeed.Vx == -1) ||
               (snakeBody->bodySpeed == speed{0,0} && afterBodyPartSpeed->bodySpeed.Vy == 1) ||
               (snakeBody->bodySpeed == speed{0,0} && afterBodyPartSpeed->bodySpeed.Vx == -1)) {
        bodyPart.setTexture(texmgr.getSnakeTurn(UPRIGHT));
    } else if ((snakeBody->bodySpeed.Vy == -1 && afterBodyPartSpeed->bodySpeed.Vx == 1) ||
               (snakeBody->bodySpeed.Vx == -1 && afterBodyPartSpeed->bodySpeed.Vy == 1) ||
               (snakeBody->bodySpeed == speed{0,0} && afterBodyPartSpeed->bodySpeed.Vx == 1) ||
               (snakeBody->bodySpeed == speed{0,0} && afterBodyPartSpeed->bodySpeed.Vy == 1)) {
        bodyPart.setTexture(texmgr.getSnakeTurn(UPLEFT));
    } else {
        return;
    }
    bodyPart.setRotation(0);
    int tmpSnakePositionX = (snakeBody->position.x) * (snakeBodySize);
    int tmpSnakePositionY = (snakeBody->position.y) * (snakeBodySize)+offsetY;
    bodyPart.setPosition(tmpSnakePositionX, tmpSnakePositionY);
}

void snakeViewer::setupBodyTexture(const int bodyPart) {
    snakeBodyShape[bodyPart].setTexture(texmgr.getSnakeBody());
    auto snakeBodyPartSpeed = snake.snakePosition().begin();
    for (int part=0; part<bodyPart; part++) {
        snakeBodyPartSpeed++;
    }
    if (bodyPart==0) {
        if (snakeBodyPartSpeed->bodySpeed.Vy==0) {
            snakeBodyShape[bodyPart].setRotation(0);
        } else {
            snakeBodyShape[bodyPart].setRotation(90);
            snakeBodyShape[bodyPart].move(snakeBodyShape[bodyPart].getSize().x,0);
        }
        return;
    }

    if (snakeBodyPartSpeed->bodySpeed.Vy==0) {
        snakeBodyShape[bodyPart].setRotation(0);
    } else {
        snakeBodyShape[bodyPart].setRotation(90);
        snakeBodyShape[bodyPart].move(snakeBodyShape[bodyPart].getSize().x,0);
    }

    setupTurnTexture(snakeBodyShape[bodyPart-1], snakeBodyPartSpeed);

}

void snakeViewer::setupBackTexture() {
    snakeBackShape.setTexture(texmgr.getSnakeBack());
    rotateBodyPart((++++snake.snakePosition().rend())->bodySpeed, snakeBackShape);
}

void snakeViewer::updateSnakeView() {
    const std::list<snakeBodyPart> & snakePosition = snake.snakePosition();
    auto snakeHeadPointer = snakePosition.begin();

    int tmpSnakePositionX = snakeHeadPointer->position.x * (snakeBodySize);
    int tmpSnakePositionY = snakeHeadPointer->position.y * (snakeBodySize)+offsetY;

    snakeHeadShape.setPosition(tmpSnakePositionX, tmpSnakePositionY);
    setupHeadTexture();

    for (int bodyPart=0; bodyPart<static_cast<int>(snakeBodyShape.size()); bodyPart++) {
        snakeHeadPointer++;
        tmpSnakePositionX = (snakeHeadPointer->position.x) * (snakeBodySize);
        tmpSnakePositionY = (snakeHeadPointer->position.y) * (snakeBodySize)+offsetY;
        snakeBodyShape[bodyPart].setPosition(tmpSnakePositionX, tmpSnakePositionY);
        setupBodyTexture(bodyPart);
    }
    tmpSnakePositionX = snakePosition.back().position.x * (snakeBodySize);
    tmpSnakePositionY = snakePosition.back().position.y * snakeBodySize+offsetY;
    snakeBackShape.setPosition(tmpSnakePositionX, tmpSnakePositionY);

    setupBackTexture();
    setupTurnTexture(snakeBodyShape.back(), snakeHeadPointer);
}

void snakeViewer::setupFruitView() {
    fruitShape.setFillColor(snakeFoodColor);
    fruitShape.setSize(sf::Vector2f(static_cast<float>(snakeBodySize), static_cast<float>(snakeBodySize)));
}

void snakeViewer::randomFruitTexture() {
    std::random_device rd;
    std::default_random_engine randomEngine(rd());
    std::uniform_int_distribution<int> texture(0, fruitCount-1);

    fruitShape.setTexture(texmgr.getFruitTexture(texture(randomEngine)));
}

void snakeViewer::updateFruitView() {
    point fruit=snake.getFruitPoint();
    int tmpFruitPositionX = fruit.x *(snakeBodySize);
    int tmpFruitPositionY = fruit.y *(snakeBodySize)+offsetY;

    fruitShape.setPosition(tmpFruitPositionX, tmpFruitPositionY);
    randomFruitTexture();

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
    updateScoreCounter();
}

void snakeViewer::addSnakePart() {
    snakeBodyShape.push_back(snakeBackShape);
    snakeBodyShape.back().setTexture(snakeBodyShape.begin()->getTexture());
    snakeBodyShape.back().setFillColor(snakeBodyShape.begin()->getFillColor());
    snakeBodyShape.back().setSize(snakeBodyShape.begin()->getSize());
    snakeBodyShape.back().setScale(1.f, 1.f);
    snakeBodyShape.back().setRotation(0);

    updateSnakeView();
    updateFruitView();
}

int snakeViewer::getOffsetY() const {
    return offsetY;
}





