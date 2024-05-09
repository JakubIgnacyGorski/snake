//
// Created by jakub on 08.05.24.
//

#ifndef SNAKE_SNAKEBODY_H
#define SNAKE_SNAKEBODY_H
#include <list>
#include <vector>

struct point {
    int x,y;
};

struct speed {
    int Vx, Vy;
};

class snakeBody {
    std::list<point> bodyPosition;
    speed snakeSpeed;

    std::vector<point> fruitPosition;
    int width;
    int height;
    void setupFruits(int fruitCount);
    bool isItFruit(point item) const;
public:
    snakeBody();
    [[nodiscard]] bool isOnMap(point item) const;
    bool snakeMove(speed newSnakeSpeed);
    char isPartOfSnake(point lookingPoint) const;
    void debug_display() const;
    bool collisionDetection(point item) const;
    bool isSnakeCanEat(point item) const;
};


#endif //SNAKE_SNAKEBODY_H
