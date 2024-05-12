//
// Created by jakub on 12.05.24.
//

#ifndef SNAKE_SNAKESCOREBOARD_H
#define SNAKE_SNAKESCOREBOARD_H
#include <iostream>
#include <array>

const unsigned int scoreboardSize = 10;

struct playerScoreboard {
    std::string name;
    unsigned int score;
};

class snakeScoreboard {
    std::array<playerScoreboard, scoreboardSize> player;
    unsigned short int scoreboardCount;
    std::string const saveFileName="scoreboard.save";
    void sortPlayerScoreboard();
    bool saveScoreboardToFile();
public:
    snakeScoreboard();
    void addPlayerToScoreboard(const std::string & playerName, int unsigned playerScore);
};


#endif //SNAKE_SNAKESCOREBOARD_H
