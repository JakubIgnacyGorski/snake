//
// Created by jakub on 08.05.24.
//

#include "snakeBody.h"
#include <iostream>
#include <random>


snakeBody::snakeBody() {
    point setupPosition{};

    for (int len=1; len<4; len++) {
        setupPosition = {1,len};
        bodyPosition.emplace_back(setupPosition);
    }

    snakeSpeed = {1, 0};

    width = 10;
    height = 7;

    setupFruits(10);

}

void snakeBody::setupFruits(int fruitCount) {

    std::random_device rd;
    std::default_random_engine randomEngine(rd());
    std::uniform_int_distribution<int> x(0, width-1);
    std::uniform_int_distribution<int> y(0, height-1);

    point fruitPoint;

    for (int i=0; i<fruitCount; i++) {
        fruitPoint={x(randomEngine), y(randomEngine)};
        if (isItFruit(fruitPoint)) i--;
        else fruitPosition.push_back(fruitPoint);
//        std::cout<<fruitPosition[i].x<<' '<<fruitPosition[i].y<<std::endl;
    }
    fruitPosition.shrink_to_fit();
}

bool snakeBody::isItFruit(point item) const {
    auto fruitCount=static_cast<int>(fruitPosition.size());
    for (int i=0; i<fruitCount; i++) {
        if (fruitPosition[i].x == item.x &&
            fruitPosition[i].y == item.y) {
            return true;
        }
    }
    return false;
}

bool snakeBody::isOnMap(point item) const {
    if (item.x >= width || item.x < 0) return false;
    if (item.y >=height || item.y <0) return false;
    return true;
}

bool snakeBody::snakeMove(speed newSnakeSpeed) {
    bodyPosition.pop_back();
    point newHead = {bodyPosition.front().x+newSnakeSpeed.Vx,
                     bodyPosition.front().y+newSnakeSpeed.Vy};
    if (collisionDetection(newHead)) return false;
    bodyPosition.push_front(newHead);
    return true;
}

char snakeBody::isPartOfSnake(point lookingPoint) const {
    auto snakeHeadPointer = bodyPosition.begin();
    auto snakeBackPointer = (--bodyPosition.end());
    if ((*snakeHeadPointer).x == lookingPoint.x &&
        (*snakeHeadPointer).y == lookingPoint.y) return 'G';
    while (snakeHeadPointer!=snakeBackPointer) {
        snakeHeadPointer++;
        if ((*snakeHeadPointer).x == lookingPoint.x &&
            (*snakeHeadPointer).y == lookingPoint.y) return 'o';
    }
    return '-';
}

void snakeBody::debug_display() const {
    point lookingPoint{};
    char field;
    for (int y=0; y<height; y++) {
        lookingPoint.y=y;
        for (int x=0; x<width; x++){
            lookingPoint.x=x;
            field=isPartOfSnake(lookingPoint);
            if (isItFruit(lookingPoint)) field='f';
            std::cout<<' '<<field<<' ';
        }
        std::cout<<std::endl;
    }
}

bool snakeBody::collisionDetection(point item) const {
    if (!isOnMap(item)) return true;
    if (isPartOfSnake(item) == 'o') return true;
    return false;
}

bool snakeBody::isSnakeCanEat(point item) const {
    if (fruitPosition.back().x == item.x &&
        fruitPosition.back().y == item.y) {
        return true;
    }
    return false;
}




