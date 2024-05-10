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
    int score;

    point fruit;
    int width;
    int height;
    void placeFruit();
public:
    snakeBody();
    snakeBody(int width, int height, int snakeLength);
    [[nodiscard]] bool isOnMap(point const & item) const;
    bool snakeMove(speed const & newSnakeSpeed);
    char isPartOfSnake(point const & lookingPoint) const;
    void debug_display() const;
    bool collisionDetection(point const & item) const;
    bool isSnakeCanEat(point const & item) const;
    bool snakeEating(point const & item);
    std::list<point> snakePosition() const;
    int getSnakeLength() const;
    point getFruitPoint() const;
    speed getSnakeSpeed() const;
};


#endif //SNAKE_SNAKEBODY_H
