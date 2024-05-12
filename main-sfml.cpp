#include <iostream>
#include <SFML/Graphics.hpp>
#include "snakeBody.h"
#include "snakeViewer.h"
#include "snakeController.h"


int main() {

    sf::RenderWindow window (sf::VideoMode(800,600), "Snake");

    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    snakeBody body;
    snakeViewer viewer(body, window);
    snakeMenu menu{window};
    snakeController ctr(body, viewer, menu, window);
//    body.debug_display();

    ctr.play(window);

    return 0;
}
