//
// Created by jakub on 09.05.24.
//

#include "snakeController.h"
#include <iostream>

snakeController::snakeController(snakeBody &b, snakeViewer &v, snakeMenu &m,snakeScoreboard &s, snakeScoreboardViewer & scb) : snake(b), viewer(v), menu(m), scoreboard(s), scbViewer(scb) {
    timeToMove = 200;
    Difficulty=NORMAL;
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
    if (snakeSpeed == speed{0,0}) return;

    moveDelay = clock.getElapsedTime();
    if (moveDelay.asMilliseconds()<=timeToMove) return;

    snake.snakeMove(snakeSpeed);
//    std::cout<<moveDelay.asMilliseconds()<<": "<<snake.snakePosition().front().x<<','<<snake.snakePosition().front().y<<std::endl;
//    std::cout<<"Snake speed: "<<snakeSpeed.Vx <<','<< snakeSpeed.Vy<<std::endl;
    if (snake.snakeEating()) viewer.addSnakePart();
    viewer.updateView();
    moveDelay = clock.restart();
}

void snakeController::changeDirection(speed newDir) {
    const speed reversDir {-newDir.Vx, -newDir.Vy};
    speed snakeSpeed = snake.getSnakeSpeed();
    if (snakeSpeed == newDir || snake.getSnakeSpeed()==reversDir) return;
    if (snakeSpeed == speed{0,0} && newDir.Vx<0) return;
    snake.snakeMove(newDir);
    if (snake.snakeEating()) viewer.addSnakePart();
    moveDelay=clock.restart();
}

void snakeController::mouse(sf::Event &event, sf::RenderWindow & window) {
    if (event.mouseButton.button != sf::Mouse::Button::Left) return;
    if (snake.getGameState() != MENU) return;

    std::string button = menu.buttonPressed(event.mouseButton.x, event.mouseButton.y);

    if (button == "EXIT") {
        window.close();
    } else if (button == "EASY") {
        Difficulty = EASY;
        createNewGame(window, RUNNING);
    } else if (button == "NORMAL") {
        Difficulty = NORMAL;
        createNewGame(window, RUNNING);
    } else if (button == "HARD") {
        Difficulty = HARD;
        createNewGame(window, RUNNING);
    } else if (button == "SCOREBOARD") {
        createNewGame(window, SCOREBOARD);
    }

}

void snakeController::createNewGame(const sf::RenderWindow & window, const GameState State) {
    int width = static_cast<int>(window.getSize().x*0.05);
    int height = static_cast<int>((window.getSize().y-viewer.getOffsetY())*0.05);
    int snakeLength;

    switch (Difficulty) {
        case EASY:
            snakeLength = static_cast<int>(width*0.3);
            timeToMove = 125;
            break;
        case NORMAL:
            snakeLength = static_cast<int>(width*0.5);
            timeToMove = 75;
            break;
        case HARD:
            snakeLength = static_cast<int>(width*0.7);
            timeToMove = 25;
            break;
    }

    snake = snakeBody(width, height, snakeLength, State);
    viewer.newSnake();
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
                    mouse(event, window);
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
                createNewGame(window, MENU);
                break;
            case SCOREBOARD:
                scbViewer.drawScoreboard(window);
                break;
        }
        window.display();
    }
}








