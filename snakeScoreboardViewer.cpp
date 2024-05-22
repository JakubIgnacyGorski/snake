//
// Created by jakub on 20.05.24.
//

#include "snakeScoreboardViewer.h"

snakeScoreboardViewer::snakeScoreboardViewer(snakeBody & s, FontManager & f, snakeScoreboard & scb, const sf::RenderWindow & window ) : snake(s), fontmgr(f), scoreboard(scb){
    windowWidth = window.getSize().x;
    windowHeight = window.getSize().y;
    textSpaceY=windowHeight/(scoreboardSize+4);

    setupViewText();
    updateViewText();
    setupWriteText();
}

void snakeScoreboardViewer::setupViewText() {
    ScoreboardTitle.setCharacterSize(textSpaceY*0.8);
    ScoreboardTitle.setFont(fontmgr.getFont());
    ScoreboardTitle.setFillColor(sf::Color::Black);
    ScoreboardTitle.setString("Scoreboard:");
    unsigned int x=(windowWidth-ScoreboardTitle.getLocalBounds().width)*0.5;
    ScoreboardTitle.setPosition(x,textSpaceY*0.2);

    for (sf::Text & text : ScoreboardText) {
        text.setCharacterSize(textSpaceY*0.5);
        text.setFont(fontmgr.getFont());
        text.setFillColor(sf::Color::Black);
    }
}

void snakeScoreboardViewer::setupWriteText() {
    ScoreTitle.setCharacterSize(textSpaceY*0.8);
    ScoreTitle.setFont(fontmgr.getFont());
    ScoreTitle.setFillColor(sf::Color::Black);

    playerNick.setCharacterSize(textSpaceY*0.6);
    playerNick.setFont(fontmgr.getFont());
    playerNick.setFillColor(sf::Color::Black);

    const unsigned int x=(windowWidth-playerNick.getCharacterSize()*playerNickLength)*0.5;

    playerNick.setPosition(x,(windowHeight+playerNick.getLocalBounds().height)*0.5);
}

void snakeScoreboardViewer::drawScoreboard(sf::RenderWindow &window) const {
    window.clear(sf::Color(250, 250, 250));
    window.draw(ScoreboardTitle);
    for (const sf::Text & text : ScoreboardText) {
        window.draw(text);
    }
}

void snakeScoreboardViewer::drawScoreboardSave(sf::RenderWindow &window) const {
    window.clear(sf::Color(250, 250, 250));
    window.draw(ScoreTitle);
    window.draw(playerNick);
}

void snakeScoreboardViewer::updateViewText() {
    const unsigned int x=(windowWidth-ScoreboardText[0].getCharacterSize()*(5 + playerNickLength + playerScoreLength))*0.5;
    unsigned int y;
    std::string tmpString;
    for (int text=0; text<scoreboard.getScoreboardCount(); text++) {
        if (text<9) tmpString.append("  ");                                     // Dodanie spacji żeby . liczb się zgadzały
        tmpString.append(std::to_string(text+1));                          // numeracja
        tmpString.append(". ");                                                 // kropka od numeracji
        tmpString.append(scoreboard.getPlayerdata(text).name);
        while (tmpString.size() < 5 + playerNickLength) tmpString.append(".");  // kropki po nazwie gracza
        if (text == 9) tmpString.pop_back();                                       // jeśli to jest 10 osoba usuń 1 kropkę (ponieważ 1 == dwie spacje)
        tmpString.append(" ");                                                  // spacja po kropkach
        tmpString.append(std::to_string(scoreboard.getPlayerdata(text).score));

        y=textSpaceY*(text+2);
        ScoreboardText[text].setString(tmpString);
        ScoreboardText[text].setPosition(x, y);
        tmpString.clear();
    }
}

void snakeScoreboardViewer::updateWriteText() {
    std::string tmpString="Your score was: ";
    tmpString.append(std::to_string(snake.getScore()));

    ScoreTitle.setString(tmpString);
    ScoreTitle.setPosition(50,50);

}


// Return true when successfully wrote to file
bool snakeScoreboardViewer::inputText(sf::Event & event) {
    sf::String input = playerNick.getString();
    std::cout<<event.text.unicode<<std::endl;
    switch (event.text.unicode) {
        case 8:
            if (input.isEmpty()) return false;
            input.erase(input.getSize() - 1, 1);
            break;
        case 13:
            if (input.isEmpty()) return false;
            scoreboard.addPlayerToScoreboard(input.operator std::string(), snake.getScore());
            return true;
        default:
            if ((event.text.unicode<48 || event.text.unicode>57) && // źródło: https://en.wikipedia.org/wiki/List_of_Unicode_characters
                (event.text.unicode<65 || event.text.unicode>90) &&
                (event.text.unicode<97 || event.text.unicode>122)) {
                return false;
            }
            if (input.getSize() >= playerNickLength) return false;
            input += event.text.unicode; //źródło: https://en.sfml-dev.org/forums/index.php?topic=19965.0
            break;
    }
    playerNick.setString(input);
    return false;
}
