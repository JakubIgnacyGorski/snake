//
// Created by jakub on 08.05.24.
//

#include "snakeBody.h"
#include <iostream>
#include <random>
snakeBody::snakeBody() {
    score = 0;
    snakeSpeed = {0, 0};
    boardWidth = 10;
    boardHeight = 8;
    State = MENU;


    point setupPosition{};

    for (int len=0; len < 4; len++) {
        setupPosition = {5-len, 4};
        bodyPosition.emplace_back(setupPosition);
    }

    fruitPoint = {7, 4};
}

snakeBody::snakeBody(int width, int height, int snakeLength, GameState startupState) {
    score = 0;
    snakeSpeed={0,0};
    State = startupState;
    boardWidth = width;
    boardHeight = height;

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
    if (State!=RUNNING) return;
    std::random_device rd;
    std::default_random_engine randomEngine(rd());
    std::uniform_int_distribution<int> x(0, boardWidth - 1);
    std::uniform_int_distribution<int> y(0, boardHeight - 1);

    do {
        fruitPoint = {x(randomEngine), y(randomEngine)};
    } while (isPartOfSnake(fruitPoint) != '-');
}

bool snakeBody::isOnMap(point const & item) const {
    if (item.x >= boardWidth || item.x < 0) return false;
    if (item.y >= boardHeight || item.y < 0) return false;
    return true;
}

bool snakeBody::snakeMove(speed const & newSnakeSpeed) {
    if (State!=RUNNING) return false;
    point newHead = {bodyPosition.front().x+newSnakeSpeed.Vx,
                     bodyPosition.front().y+newSnakeSpeed.Vy};
    if (collisionDetection(newHead)) {
        State=LOSE;
        return false;
    }

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
    for (int y=0; y < boardHeight; y++) {
        lookingPoint.y=y;
        for (int x=0; x < boardWidth; x++){
            lookingPoint.x=x;
            field=isPartOfSnake(lookingPoint);
            if (point{x,y} == fruitPoint) field='f';
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
    if (State!=RUNNING) return false;
    if (isSnakeCanEat(bodyPosition.front())) {
        score++;
        placeFruit();
//        std::cout<<"Punkty: "<<score<<std::endl;
        return true;
    }
    return false;
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

GameState snakeBody::getGameState() const {
    return State;
}

//void snakeBody::changeGameState(GameState newGameState) {
//    State = newGameState;
//}

point snakeBody::getBoardSize() const {
    return point{boardWidth, boardHeight};
}

unsigned int snakeBody::getScore() const {
    return score;
}





