//
// Created by jakub on 08.05.24.
//

#ifndef SNAKE_SNAKEBODY_H
#define SNAKE_SNAKEBODY_H
#include <list>
#include <vector>

struct point {
    int x,y;
    bool operator==(const point &p) const {return (x==p.x && y==p.y);}
    bool operator!=(const point &p) const {return (x!=p.x || y!=p.y);}
};

struct speed {
    int Vx, Vy;
    bool operator==(const speed &s) const {return (Vx==s.Vx && Vy==s.Vy);}
    bool operator!=(const speed &s) const {return (Vx!=s.Vx || Vy!=s.Vy);}
};

class snakeBody {
    std::list<point> bodyPosition;
    speed snakeSpeed;
    int score;

    point fruitPoint;
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
    bool snakeEating();
    std::list<point> snakePosition() const;
    int getSnakeLength() const;
    point getFruitPoint() const;
    speed getSnakeSpeed() const;
    void setSnakeSpeed(speed newSpeed);
};


#endif //SNAKE_SNAKEBODY_H
