//
// Created by jakub on 20.05.24.
//

#include "snakeScoreboardViewer.h"
#include "ColorsConsts.h"

snakeScoreboardViewer::snakeScoreboardViewer(snakeBody & s, FontManager & f, snakeScoreboard & scb, const sf::RenderWindow & window ) : snake(s), fontmgr(f), scoreboard(scb){
    windowWidth = window.getSize().x;
    windowHeight = window.getSize().y;
    textSpace= std::min(windowHeight, windowWidth) / (scoreboardSize + 4);

    setupViewText();
    updateViewText();
    setupWriteText();
}

void snakeScoreboardViewer::setupViewText() {
    ScoreboardTitle.setCharacterSize(textSpace * 0.8);
    ScoreboardTitle.setFont(fontmgr.getFont());
    ScoreboardTitle.setFillColor(textColor);
    ScoreboardTitle.setString("Scoreboard:");
    unsigned int x=(windowWidth-ScoreboardTitle.getLocalBounds().width)*0.5;
    ScoreboardTitle.setPosition(x, textSpace * 0.2);

    for (sf::Text & text : ScoreboardText) {
        text.setCharacterSize(textSpace * 0.5);
        text.setFont(fontmgr.getFont());
        text.setFillColor(textColor);
    }
}

void snakeScoreboardViewer::setupWriteText() {
    ScoreTitle.setCharacterSize(textSpace * 0.7);
    ScoreTitle.setFont(fontmgr.getFont());
    ScoreTitle.setFillColor(textColor);

    playerNick.setCharacterSize(textSpace * 0.5);
    playerNick.setFont(fontmgr.getFont());
    playerNick.setFillColor(textColor);

    const unsigned int x=(windowWidth-playerNick.getCharacterSize()*playerNickLength)*0.5;
    const unsigned int nickYPos=(windowHeight-playerNick.getLocalBounds().height)*0.5;

    playerNick.setPosition(x,nickYPos);

    enterNick.setCharacterSize(textSpace * 0.6);
    enterNick.setFont(fontmgr.getFont());
    enterNick.setFillColor(textColor);
    enterNick.setString("Enter your nickname:");
    enterNick.setPosition((windowWidth-enterNick.getLocalBounds().width)*0.5, nickYPos - textSpace);
}

void snakeScoreboardViewer::drawScoreboard(sf::RenderWindow &window) const {
    window.clear(scoreboardViewBackgroundColor);
    window.draw(ScoreboardTitle);
    for (const sf::Text & text : ScoreboardText) {
        window.draw(text);
    }
}

void snakeScoreboardViewer::drawScoreboardSave(sf::RenderWindow &window) const {
    window.clear(scoreboardWriteBackgroundColor);
    window.draw(ScoreTitle);
    window.draw(playerNick);
    window.draw(enterNick);
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

        y= textSpace * (text + 2);
        ScoreboardText[text].setString(tmpString);
        ScoreboardText[text].setPosition(x, y);
        tmpString.clear();
    }
}

void snakeScoreboardViewer::updateWriteText() {
    std::string tmpString="Your score was: ";
    tmpString.append(std::to_string(snake.getScore()));

    ScoreTitle.setString(tmpString);
    ScoreTitle.setPosition((windowWidth-ScoreTitle.getLocalBounds().width)*0.5, textSpace * 0.5);

}


// Return true when pressed enter
bool snakeScoreboardViewer::inputText(sf::Event & event) {
    sf::String input = playerNick.getString();
    switch (event.text.unicode) {
        case 8:
            if (input.isEmpty()) return false;
            input.erase(input.getSize() - 1, 1);
            break;
        case 13:
            if (!input.isEmpty()) {
                scoreboard.addPlayerToScoreboard(input.operator std::string(), snake.getScore());
            }
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
