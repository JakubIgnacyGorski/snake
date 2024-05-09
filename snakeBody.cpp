//
// Created by jakub on 08.05.24.
//

#include "snakeBody.h"
#include <iostream>

snakeBody::snakeBody() {
    point setupPosition{};

    for (int len=1; len<4; len++) {
        setupPosition = {1,len};
        bodyPosition.emplace_back(setupPosition);
    }

    snakeSpeed = {1, 0};

    width = 10;
    height = 7;

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
    if (!isOnMap(newHead)) return false;
    bodyPosition.push_front(newHead);
    return true;
}

char snakeBody::isPartOfSnake(point lookingPoint) const {
    auto snakeHeadPointer = bodyPosition.begin();
    auto snakeBackPointer = bodyPosition.end();
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
    for (int y=0; y<height; y++) {
        lookingPoint.y=y;
        for (int x=0; x<width; x++){
            lookingPoint.x=x;
            std::cout<<isPartOfSnake(lookingPoint);
        }
        std::cout<<std::endl;
    }
}


