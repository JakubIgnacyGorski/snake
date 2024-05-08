//
// Created by jakub on 08.05.24.
//

#ifndef SNAKE_SNAKEBODY_H
#define SNAKE_SNAKEBODY_H
#include <list>
#include <vector>

class snakeBody {
    std::list<std::pair<int,int>> bodyPosition;
    float speed;
    std::vector<std::pair<int,int>> fruitPosition;
};


#endif //SNAKE_SNAKEBODY_H
