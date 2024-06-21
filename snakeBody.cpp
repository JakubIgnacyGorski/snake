//
// Created by jakub on 08.05.24.
//

#include "snakeBody.h"
#include <iostream>
#include <random>
#include <chrono>

snakeBody::snakeBody() {
    score = 0;
    snakeSpeed = {0, 0};
    boardWidth = 10;
    boardHeight = 8;
    state = MENU;
    difficulty = NORMAL;


    point setupPosition{};

    for (int len=0; len < 4; len++) {
        setupPosition = {5-len, 4};
        bodyPosition.emplace_back(snakeBodyPart{setupPosition, speed{0,0}});
    }

    fruitPoint = {7, 4};
}

snakeBody::snakeBody(int width, int height, int snakeLength, GameState startupState) {
    score = 0;
    snakeSpeed={0,0};
    state = startupState;
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
        bodyPosition.emplace_back(snakeBodyPart{setupPosition, speed{0,0}});
    }

    placeFruit();
}


void snakeBody::placeFruit() {
    if (state != RUNNING) return;
    std::default_random_engine randomEngine(std::chrono::high_resolution_clock::now().time_since_epoch().count());
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
    if (state != RUNNING) return false;
    point newHead = {bodyPosition.front().position.x+newSnakeSpeed.Vx,
                     bodyPosition.front().position.y+newSnakeSpeed.Vy};
    if (collisionDetection(newHead)) {
        state=SCOREBOARD_WRITE;
        return false;
    }

    bodyPosition.push_front(snakeBodyPart{newHead, newSnakeSpeed});
    if (!isSnakeCanEat(newHead)) {
        bodyPosition.pop_back();
    }

    setSnakeSpeed(newSnakeSpeed);
    return true;
}

char snakeBody::isPartOfSnake(point const & lookingPoint) const {
    auto snakeHeadPointer = bodyPosition.begin();
    auto snakeBackPointer = (--bodyPosition.end());
    if ((snakeHeadPointer->position) == lookingPoint) return 'G';
    if ((snakeBackPointer->position) == lookingPoint) return 'b';
    snakeBackPointer--;
    while (snakeHeadPointer!=snakeBackPointer) {
        snakeHeadPointer++;
        if ((snakeHeadPointer->position) == lookingPoint) return 'o';
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
    if (state != RUNNING) return false;
    if (!isSnakeCanEat(bodyPosition.front().position)) return false;

    switch (difficulty) {
        case EASY:
            score++;
            break;
        case NORMAL:
            score+=2;
            break;
        case HARD:
            score+=3;
            break;
    }
    placeFruit();
    return true;
}

const std::list<snakeBodyPart> & snakeBody::snakePosition() {
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
    return state;
}

point snakeBody::getBoardSize() const {
    return point{boardWidth, boardHeight};
}

unsigned int snakeBody::getScore() const {
    return score;
}

GameDifficulty snakeBody::getGameDifficulty() const {
    return difficulty;
}

void snakeBody::setGameDifficulty(GameDifficulty newDif) {
    difficulty=newDif;
}





