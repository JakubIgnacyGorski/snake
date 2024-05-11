//
// Created by jakub on 09.05.24.
//

#include "snakeController.h"
#include <iostream>

snakeController::snakeController(snakeBody &b, snakeViewer &v, snakeMenu &m) : snake(b), viewer(v), menu(m){}

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
//    std::cout<<moveDelay.asMilliseconds()<<": "<<snake.snakePosition().front().x<<','<<snake.snakePosition().front().y<<std::endl;
//    std::cout<<"Snake speed: "<<snakeSpeed.Vx <<','<< snakeSpeed.Vy<<std::endl;
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
}

void snakeController::mouse(sf::Event &event) {
    if (event.mouseButton.button != sf::Mouse::Button::Left) return;

    std::string test = menu.buttonPressed(event.mouseButton.x, event.mouseButton.y);
    std::cout<<test<<std::endl;
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
                case sf::Event::MouseButtonPressed:
                    mouse(event);
                    break;
                default:
                    break;
            }
        }

        switch (snake.getGameState()) {
            case RUNNING:
                timeMove();
                viewer.drawGame(window);
                break;
            case MENU:
                menu.drawMenu(window);
                break;
            case LOSE:
                break;
            case SCOREBOARD:
                break;
        }
        window.display();
    }
}








