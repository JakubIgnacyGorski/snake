#include <iostream>
#include <SFML/Graphics.hpp>
#include "snakeBody.h"
#include "snakeViewer.h"
#include "snakeController.h"


int main() {

    sf::RenderWindow window (sf::VideoMode(800,600), "Snake");

    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    snakeBody body{10, 10, 8};
    snakeViewer viewer(body);
    snakeController ctr(body, viewer);


    ctr.play(window);

    return 0;
}
