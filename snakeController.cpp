//
// Created by jakub on 09.05.24.
//

#include "snakeController.h"
#include <iostream>

snakeController::snakeController(snakeBody &b, snakeViewer &v) : snake(b), viewer(v) {

}

void snakeController::keyboard(sf::Event &event) {
    switch (event.key.code) {
        case (sf::Keyboard::Key::Right):
            changeDirection(speed{1, 0});
            break;
        case (sf::Keyboard::Key::Left):
            changeDirection(speed{-1, 0});
            break;
        case (sf::Keyboard::Key::Up):
            changeDirection(speed{0, -1});
            break;
        case (sf::Keyboard::Key::Down):
            changeDirection(speed{0, 1});
            break;
        default:
            return;
    }
    viewer.updateView();
}

void snakeController::timeMove() {
    speed snakeSpeed = snake.getSnakeSpeed();
    if (snakeSpeed.Vx == 0 && snakeSpeed.Vy == 0) return;

//    sf::Time moveDelay;
    moveDelay = clock.getElapsedTime();

    if (moveDelay.asMilliseconds()<=200) return;

    snake.snakeMove(snakeSpeed);
    std::cout<<moveDelay.asMilliseconds()<<": "<<snake.snakePosition().front().x<<','<<snake.snakePosition().front().y<<std::endl;
    std::cout<<"Snake speed: "<<snakeSpeed.Vx <<','<< snakeSpeed.Vy<<std::endl;
    if (snake.snakeEating()) viewer.addSnakePart();
    viewer.updateView();
    moveDelay = clock.restart();
}

void snakeController::changeDirection(speed newDir) {
    speed reversDir {-newDir.Vx, -newDir.Vy};
    if (snake.getSnakeSpeed()==newDir || snake.getSnakeSpeed()==reversDir) return;
    snake.snakeMove(newDir);
    if (snake.snakeEating()) viewer.addSnakePart();
    moveDelay=clock.restart();
//    snake.setSnakeSpeed(newDir);
}


void snakeController::play(sf::RenderWindow & window) {
    while (window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    keyboard(event);
                    break;
                default:
                    break;
            }
        }
        timeMove();
        viewer.draw(window);
    }
}






