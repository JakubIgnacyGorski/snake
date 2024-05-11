//
// Created by jakub on 08.05.24.
//

#include "snakeBody.h"
#include <iostream>
#include <random>
snakeBody::snakeBody() {
    score = 0;
    snakeSpeed = {0, 0};
    width = 10;
    height = 8;


    point setupPosition{};

    for (int len=0; len < 4; len++) {
        setupPosition = {5-len, 4};
        bodyPosition.emplace_back(setupPosition);
    }

    fruitPoint = {7, 4};
}

snakeBody::snakeBody(int width, int height, int snakeLength) {
    score = 0;
    snakeSpeed={0,0};
    this->width = width;
    this->height = height;

    point setupPosition{};
    int startPlace= snakeLength + 1;

    if (snakeLength >= width) {
        std::cerr << "Snake too long to fit on board" << std::endl;
        abort();
    }

    for (int len=0; len < snakeLength; len++) {
        setupPosition = {startPlace-len, static_cast<int>(height*0.5)};
        bodyPosition.emplace_back(setupPosition);
    }

    placeFruit();
}


void snakeBody::placeFruit() {

    std::random_device rd;
    std::default_random_engine randomEngine(rd());
    std::uniform_int_distribution<int> x(0, width-1);
    std::uniform_int_distribution<int> y(0, height-1);

    do {
        fruitPoint = {x(randomEngine), y(randomEngine)};
    } while (isPartOfSnake(fruitPoint) != '-');
}

bool snakeBody::isOnMap(point const & item) const {
    if (item.x >= width || item.x < 0) return false;
    if (item.y >=height || item.y <0) return false;
    return true;
}

bool snakeBody::snakeMove(speed const & newSnakeSpeed) {
    point newHead = {bodyPosition.front().x+newSnakeSpeed.Vx,
                     bodyPosition.front().y+newSnakeSpeed.Vy};
    if (collisionDetection(newHead)) return false;

    bodyPosition.push_front(newHead);
    if (!isSnakeCanEat(newHead)) {
        bodyPosition.pop_back();
    }

    setSnakeSpeed(newSnakeSpeed);
    return true;
}

char snakeBody::isPartOfSnake(point const & lookingPoint) const {
    auto snakeHeadPointer = bodyPosition.begin();
    auto snakeBackPointer = (--bodyPosition.end());
    if ((*snakeHeadPointer) == lookingPoint) return 'G';
    if ((*snakeBackPointer) == lookingPoint) return 'b';
    snakeBackPointer--;
    while (snakeHeadPointer!=snakeBackPointer) {
        snakeHeadPointer++;
        if ((*snakeHeadPointer) == lookingPoint) return 'o';
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
            if (y == fruitPoint.y && x == fruitPoint.x) field='f';
            std::cout<<' '<<field<<' ';
        }
        std::cout<<std::endl;
    }
}

bool snakeBody::collisionDetection(point const & item) const {
    if (!isOnMap(item)) return true;
    if (isPartOfSnake(item) == 'G' || isPartOfSnake(item) == 'o') return true;
    return false;
}

bool snakeBody::isSnakeCanEat(point const & item) const {
    return (fruitPoint == item);
}

bool snakeBody::snakeEating() {
    if (isSnakeCanEat(bodyPosition.front())) {
        score++;
        placeFruit();
        return true;
    } else {
        return false;
    }
}

std::list<point> snakeBody::snakePosition() const {
    return bodyPosition;
}

int snakeBody::getSnakeLength() const {
    return static_cast<int>(bodyPosition.size());
}

point snakeBody::getFruitPoint() const {
    return fruitPoint;
}

speed snakeBody::getSnakeSpeed() const {
    return snakeSpeed;
}

void snakeBody::setSnakeSpeed(speed newSpeed) {
    snakeSpeed = newSpeed;
}



