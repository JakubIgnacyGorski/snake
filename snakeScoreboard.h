//
// Created by jakub on 12.05.24.
//

#ifndef SNAKE_SNAKESCOREBOARD_H
#define SNAKE_SNAKESCOREBOARD_H
#include <iostream>
#include <array>

struct playerScoreboard {
    std::string name;
    unsigned int score;
};

class snakeScoreboard {
    std::array<playerScoreboard, 10> player;
    unsigned short int scoreboardCount;
    std::string const saveFileName="scoreboard.save";
public:
    snakeScoreboard();
    void sortPlayerScoreboard();
    bool saveScoreboardToFile();
};


#endif //SNAKE_SNAKESCOREBOARD_H
