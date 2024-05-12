//
// Created by jakub on 12.05.24.
//

#include "snakeScoreboard.h"
#include <fstream> // źródło: https://cplusplus.com/doc/tutorial/files/
#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include <algorithm>

snakeScoreboard::snakeScoreboard() {
    std::ifstream scoreboardFile;
    std::string line;
    scoreboardCount=0;
    scoreboardFile.open(saveFileName);

    if (!scoreboardFile.is_open()) abort(); //Dodać komunikat błędu

    while (std::getline(scoreboardFile, line)){
        std::istringstream iss(line); //źródło: https://cplusplus.com/reference/sstream/istringstream/istringstream/
        iss >> player[scoreboardCount].name >> player[scoreboardCount].score;
//        std::cout << "Nazwa: " << player[scoreboardCount].name << " Punkty: " << player[scoreboardCount].score << std::endl;
        scoreboardCount++;
    }
    scoreboardFile.close();



    sortPlayerScoreboard();
    saveScoreboardToFile();
}

void snakeScoreboard::sortPlayerScoreboard() {
    struct { //źródło: https://en.cppreference.com/w/cpp/algorithm/sort
        bool operator()(playerScoreboard const & a, playerScoreboard const & b) const { return  a.score> b.score; }
    } sortCompare;

    std::sort(player.begin(), player.begin()+scoreboardCount, sortCompare);
}

bool snakeScoreboard::saveScoreboardToFile() {
    std::ofstream scoreboardFile;
    std::string line;
    scoreboardFile.open(saveFileName , std::ios::trunc);

    if (!scoreboardFile.is_open()) abort();

    for (int lineCount=0; lineCount<scoreboardCount; lineCount++) {
        scoreboardFile << player[lineCount].name << ' ' <<player[lineCount].score<<std::endl;
    }
    scoreboardFile.close();

    return false;
}
