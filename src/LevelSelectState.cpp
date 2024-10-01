//
// Created by Devrim on 30.09.2024.
//

#include "../include/LevelSelectState.h"
#include "../include/GameState.h"
#include <filesystem>

LevelSelectState::LevelSelectState() : currentPage(0) {
    if (!font.loadFromFile("resources/Rubik-Regular.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    loadLevelFiles();
    createLevelButtons();
}

void LevelSelectState::loadLevelFiles() {
    std::string path = "resources/";
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == ".csv") {
            std::string filename = entry.path().filename().string();
            if (filename != "cars.csv") { 
                levelFiles.push_back(filename);
            }
        }
    }
    totalPages = (levelFiles.size() + levelsPerPage - 1) / levelsPerPage;
}



void LevelSelectState::handleInput(Game& game) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game.window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(game.window);

            for (int i = 0; i < levelsPerPage; ++i) {
                if (i + currentPage * levelsPerPage >= levelFiles.size()) break;
                if (levelButtons[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    std::string selectedLevel = "resources/" + levelFiles[i + currentPage * levelsPerPage];
                    game.changeState(std::make_shared<GameState>(game, selectedLevel)); // Pass the selected level to GameState
                }
            }


            if (nextPageButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                currentPage = (currentPage + 1) % totalPages;
                createLevelButtons();
            }
            if (prevPageButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                currentPage = (currentPage - 1 + totalPages) % totalPages;
                createLevelButtons();
            }
        }
    }
}


void LevelSelectState::update(Game& game) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(game.window);
    for (auto& button : levelButtons) {
        button.setFillColor(sf::Color::White);
        if (button.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            button.setFillColor(sf::Color(255, 215, 0));
        }
    }
}

void LevelSelectState::render(Game& game) {
    game.window.clear();

    for (int i = 0; i < 4; ++i) {
        if (i + currentPage * levelsPerPage >= levelFiles.size()) break;
        game.window.draw(levelButtons[i]);
        game.window.draw(levelTexts[i]);

        sf::RectangleShape preview(sf::Vector2f(50.0f, 50.0f));
        preview.setFillColor(sf::Color::Blue); // Set color to make it visible
        loadLevelPreview("resources/" + levelFiles[i + currentPage * levelsPerPage], preview);
        preview.setPosition(levelButtons[i].getPosition().x + 420.0f, levelButtons[i].getPosition().y);
        game.window.draw(preview);
    }

    game.window.draw(nextPageButton);
    game.window.draw(prevPageButton);
}



void LevelSelectState::loadLevelPreview(const std::string& filename, sf::RectangleShape& preview) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening level preview: " << filename << std::endl;
        return;
    }

    std::string line;
    int count = 0;
    while (std::getline(file, line) && count < 10) {
        std::stringstream ss(line);
        std::string xStr, yStr;

        if (std::getline(ss, xStr, ',') && std::getline(ss, yStr, ',')) {
            try {
                if (!xStr.empty() && !yStr.empty()) {
                    float x = std::stof(xStr);
                    float y = std::stof(yStr);
                    preview.setPosition(x, y);
                } else {
                    std::cerr << "Invalid coordinates in line: " << line << std::endl;
                }
            } catch (const std::invalid_argument&) {
                std::cerr << "Invalid argument in line: " << line << std::endl;
            } catch (const std::out_of_range&) {
                std::cerr << "Out of range in line: " << line << std::endl;
            }
        } else {
            std::cerr << "Could not read two values from line: " << line << std::endl;
        }
        count++;
    }
    file.close();
}



void LevelSelectState::createLevelButtons() {
    levelButtons.clear();
    levelTexts.clear();

    float startX = 100.0f, startY = 150.0f;
    float offsetY = 100.0f;

    for (int i = 0; i < levelsPerPage; ++i) {
        sf::RectangleShape button;
        button.setSize({400.0f, 50.0f});
        button.setPosition(startX, startY + i * offsetY);
        button.setFillColor(sf::Color::White);

        sf::Text buttonText;
        buttonText.setFont(font);
        buttonText.setFillColor(sf::Color::Black);
        buttonText.setCharacterSize(20);
        buttonText.setPosition(startX + 10.0f, startY + i * offsetY + 10.0f);

        if (i + currentPage * levelsPerPage < levelFiles.size()) {
            buttonText.setString(levelFiles[i + currentPage * levelsPerPage]);
        } else {
            buttonText.setString("N/A");
        }

        levelButtons.push_back(button);
        levelTexts.push_back(buttonText);
    }


    nextPageButton.setSize({200.0f, 50.0f});
    nextPageButton.setPosition(700.0f, 600.0f);
    nextPageButton.setFillColor(sf::Color::Green);

    prevPageButton.setSize({200.0f, 50.0f});
    prevPageButton.setPosition(100.0f, 600.0f);
    prevPageButton.setFillColor(sf::Color::Green);
}

