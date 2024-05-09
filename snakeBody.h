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
public:
    snakeBody();
    [[nodiscard]] bool isOnMap(point item) const;
    void snakeMove(speed newSnakeSpeed);
};


#endif //SNAKE_SNAKEBODY_H
