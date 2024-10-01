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
#include <filesystem> // For reading file names

class LevelSelectState : public State {
public:
    LevelSelectState();

    void loadLevelFiles();  // Load all available level files
    void handleInput(Game& game) override;  // Handle user input
    void update(Game& game) override;  // Update the state
    void render(Game& game) override;  // Render the level selection menu

private:
    std::vector<std::string> levelFiles;  // List of level file names
    std::vector<sf::RectangleShape> levelButtons;  // Buttons for selecting levels
    std::vector<sf::Text> levelTexts;  // Text for the level buttons
    unsigned int currentPage;  // Keeps track of the current page
    unsigned int totalPages;  // Total number of pages
    const unsigned int levelsPerPage = 4;  // Levels displayed per page

    sf::Font font;
    sf::RectangleShape nextPageButton, prevPageButton;  // Buttons to navigate pages

    // Utility function to create the level selection buttons
    void createLevelButtons();

    // Loads a small preview of the level based on the CSV file
    void loadLevelPreview(const std::string& filename, sf::RectangleShape& preview);
};

#endif

