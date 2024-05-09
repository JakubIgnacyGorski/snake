#include <iostream>
#include "snakeBody.h"

int main() {

    snakeBody test;

    test.debug_display();
    speed direction={1,0};
    test.snakeMove(direction);
    std::cout<<std::endl;
    test.debug_display();

    return 0;
}
