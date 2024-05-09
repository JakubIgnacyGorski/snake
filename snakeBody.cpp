//
// Created by jakub on 08.05.24.
//

#include "snakeBody.h"


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

void snakeBody::snakeMove(speed newSnakeSpeed) {
    
}
