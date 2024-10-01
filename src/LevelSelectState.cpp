//
// Created by Devrim on 30.09.2024.
//

#include "../include/LevelSelectState.h"
#include "../include/GameState.h"
#include <filesystem>

LevelSelectState::LevelSelectState() : currentPage(0) {
    if (!font.loadFromFile("resources/Fonts/Rubik-Regular.ttf")) {
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
                    game.changeState(std::make_shared<GameState>(game, selectedLevel));
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

    float previewSize = 200.0f;
    float verticalSpacing = 30.0f;

    for (int i = 0; i < 4; ++i) {
        if (i + currentPage * levelsPerPage >= levelFiles.size()) break;

        int row = i / 2;
        int col = i % 2;

        // Vorschau für das Level
        sf::RectangleShape preview(sf::Vector2f(previewSize, previewSize));
        preview.setPosition(levelButtons[i].getPosition().x + (levelButtons[i].getSize().x - previewSize) / 2,
                            levelButtons[i].getPosition().y + levelButtons[i].getSize().y + verticalSpacing);

        // Zeichne Level-Buttons und Texte
        game.window.draw(levelButtons[i]);
        game.window.draw(levelTexts[i]);

        // Lade und zeichne die Levelvorschau
        loadLevelPreview(game,"resources/" + levelFiles[i + currentPage * levelsPerPage], preview);
        game.window.draw(preview); // Vorschau zeichnen
    }

    game.window.draw(nextPageButton);
    game.window.draw(prevPageButton);
}

void LevelSelectState::loadLevelPreview(Game &game,const std::string& filename, sf::RectangleShape& preview) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening level preview: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string xStr, yStr;

        if (std::getline(ss, xStr, ',') && std::getline(ss, yStr, ',')) {
            try {
                if (!xStr.empty() && !yStr.empty()) {
                    float x = std::stof(xStr);
                    float y = std::stof(yStr);

                    // Zeichne die Level-Elemente an den entsprechenden Positionen
                    sf::CircleShape element(10.0f); // Beispiel für einen Level-Element
                    element.setPosition(x, y);
                    element.setFillColor(sf::Color::Green); // Beispiel-Farbe

                    game.window.draw(element); // Level-Element zeichnen
                }
            } catch (const std::invalid_argument&) {
                // Fehler beim Konvertieren ignorieren
            } catch (const std::out_of_range&) {
                // Fehler beim Konvertieren ignorieren
            }
        }
    }
    file.close();
}


void LevelSelectState::createLevelButtons() {
    levelButtons.clear();
    levelTexts.clear();

    float windowHeight = 1080.0f;
    float windowWidth = 1920.0f;

    float buttonWidth = 400.0f;
    float buttonHeight = 50.0f;
    float previewSize = 200.0f;
    float verticalSpacing = (windowHeight - (2 * buttonHeight + 2 * previewSize)) / 3;

    for (int i = 0; i < levelsPerPage; ++i) {
        int row = i / 2;
        int col = i % 2;

        sf::RectangleShape button;
        button.setSize({buttonWidth, buttonHeight});
        button.setPosition(col * (windowWidth / 2) + (windowWidth / 4) - (buttonWidth / 2),
                           verticalSpacing + row * (buttonHeight + previewSize + verticalSpacing));
        button.setFillColor(sf::Color::White);

        sf::Text buttonText;
        buttonText.setFont(font);
        buttonText.setFillColor(sf::Color::Black);
        buttonText.setCharacterSize(20);
        buttonText.setPosition(button.getPosition().x + 10.0f, button.getPosition().y + 10.0f);

        if (i + currentPage * levelsPerPage < levelFiles.size()) {
            buttonText.setString(levelFiles[i + currentPage * levelsPerPage]);
        } else {
            buttonText.setString("N/A");
        }

        levelButtons.push_back(button);
        levelTexts.push_back(buttonText);
    }

    nextPageButton.setSize({200.0f, 50.0f});
    nextPageButton.setPosition(windowWidth / 2 - nextPageButton.getSize().x / 2 - 100.0f, windowHeight - 100.0f);
    nextPageButton.setFillColor(sf::Color::Red);

    prevPageButton.setSize({200.0f, 50.0f});
    prevPageButton.setPosition(windowWidth / 2 - prevPageButton.getSize().x / 2 + 100.0f, windowHeight - 100.0f);
    prevPageButton.setFillColor(sf::Color::Green);
}
