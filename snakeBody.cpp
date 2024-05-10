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

    fruit = {7, 4};
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
        fruit = {x(randomEngine), y(randomEngine)};
    } while (isPartOfSnake(fruit) != '-');
}

bool snakeBody::isOnMap(point item) const {
    if (item.x >= width || item.x < 0) return false;
    if (item.y >=height || item.y <0) return false;
    return true;
}

bool snakeBody::snakeMove(speed newSnakeSpeed) {
    point newHead = {bodyPosition.front().x+newSnakeSpeed.Vx,
                     bodyPosition.front().y+newSnakeSpeed.Vy};
    if (collisionDetection(newHead)) return false;

    if (isSnakeCanEat(newHead)) {
        snakeEating();
    } else {
        bodyPosition.pop_back();
    }

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
            if (y==fruit.y && x==fruit.x) field='f';
            std::cout<<' '<<field<<' ';
        }
        std::cout<<std::endl;
    }
}

bool snakeBody::collisionDetection(point item) const {
    if (!isOnMap(item)) return true;
    if (isPartOfSnake(item) != '-') return true;
    return false;
}

bool snakeBody::isSnakeCanEat(point item) const {
    if (fruit.y == item.y && fruit.x == item.x) return true;
    return false;
}

void snakeBody::snakeEating() {
    score++;
    placeFruit();
}

std::list<point> snakeBody::snakePosition() const {
    return std::list<point>(bodyPosition);
}

int snakeBody::getSnakeLength() const {
    return static_cast<int>(bodyPosition.size());
}




