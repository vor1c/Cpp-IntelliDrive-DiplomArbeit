//
// Created by Devrim on 30.09.2024.
//

#ifndef LEVELSELECTSTATE_H
#define LEVELSELECTSTATE_H

#include "State.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <filesystem>

class LevelSelectState : public State {
public:
    LevelSelectState();
    void loadLevelFiles();
    void handleInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

    std::vector<std::string> levelFiles;

private:
    std::vector<sf::RectangleShape> levelButtons;
    std::vector<sf::Text> levelTexts;
    unsigned int currentPage;
    unsigned int totalPages;
    const unsigned int levelsPerPage = 4;

    sf::Font font;
    sf::RectangleShape nextPageButton, prevPageButton;

    void createLevelButtons();
    void loadLevelPreview(const std::string& filename, sf::RectangleShape& preview);
};

#endif
