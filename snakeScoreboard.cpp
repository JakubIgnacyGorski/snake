//
// Created by jakub on 12.05.24.
//

#include "snakeScoreboard.h"
#include <fstream> // źródło: https://cplusplus.com/doc/tutorial/files/
#include <sstream>
#include <algorithm>

snakeScoreboard::snakeScoreboard() {
    std::ifstream scoreboardFile;
    std::string line;
    scoreboardCount=0;
    scoreboardFile.open(saveFileName);

    if (!scoreboardFile.is_open()) abort(); //Dodać komunikat błędu

    while (std::getline(scoreboardFile, line) && scoreboardCount<scoreboardSize){
        std::istringstream iss(line); //źródło: https://cplusplus.com/reference/sstream/istringstream/istringstream/
        iss >> player[scoreboardCount].name >> player[scoreboardCount].score;
//        std::cout << "Nazwa: " << player[scoreboardCount].name << " Punkty: " << player[scoreboardCount].score << std::endl;
        scoreboardCount++;
    }
    scoreboardFile.close();
    sortPlayerScoreboard();

    addPlayerToScoreboard("Niety", 3);
}

void snakeScoreboard::sortPlayerScoreboard() {
    struct { //źródło: https://en.cppreference.com/w/cpp/algorithm/sort
        bool operator()(playerScoreboard const & a, playerScoreboard const & b) const { return  a.score> b.score; }
    } sortCompare;

    std::sort(player.begin(), player.begin()+scoreboardCount, sortCompare);
}

bool snakeScoreboard::saveScoreboardToFile() {
    std::ofstream scoreboardFile;
    scoreboardFile.open(saveFileName, std::ios::trunc);

    if (!scoreboardFile.is_open()) return false;

    for (int lineCount=0; lineCount<scoreboardCount; lineCount++) {
        scoreboardFile << player[lineCount].name << ' ' <<player[lineCount].score<<std::endl;
    }
    scoreboardFile.close();

    return true;
}

bool snakeScoreboard::compareName(const std::string &playerName, const unsigned int playerScore) {
    for (int playerCount=0; playerCount<scoreboardCount; playerCount++) {
        if (std::equal(player[playerCount].name.begin(), player[playerCount].name.end(),
                       playerName.begin(), playerName.end())){
            if (playerScore>player[playerCount].score) player[playerCount].score = playerScore;
            return true;
        }
    }
    return false;
}

bool snakeScoreboard::compareScore(const std::string &playerName, const unsigned int playerScore) {
    for (int playerCount=0; playerCount<scoreboardCount; playerCount++) {
        if (playerScore > player[playerCount].score) {
            player[playerCount].name = playerName;
            player[playerCount].score = playerScore;
            return true;
        }
    }
    return false;
}

void snakeScoreboard::addPlayerToScoreboard(const std::string &playerName, const unsigned int playerScore) {
    if (scoreboardCount==scoreboardSize) {
        if (!compareName(playerName, playerScore)) {
            compareScore(playerName, playerScore);
        }
    } else {
        player[scoreboardCount].name=playerName;
        player[scoreboardCount].score=playerScore;
        scoreboardCount++;
    }

    sortPlayerScoreboard();
    saveScoreboardToFile();
}




