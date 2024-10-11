//
// Created by Devrim on 30.09.2024.
//
// LevelCreator.cpp

#include "../include/LevelCreator.h"
#include "../include/ResourceManager.h" // Include ResourceManager
#include "../include/MenuState.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>
#include <string>

LevelCreator::LevelCreator(Game& game) {

    ResourceManager& resourceManager = ResourceManager::getInstance();

    resourceManager.loadTexturesInBulk("resources/Tiles/Asphalt road/", "road_asphalt", ".png");
    tiles = resourceManager.getBulkTextures();

    resourceManager.loadFont("Rubik-Regular", "resources/Fonts/Rubik-Regular.ttf");
    font = resourceManager.getFont("Rubik-Regular");

    createSaveButton(game);

    sf::Sprite s;
    s.setTexture(tiles[0]);
    s.setScale(game.getTileSize() / s.getLocalBounds().height, game.getTileSize() / s.getLocalBounds().height);
    placedTiles.emplace_back(s);
}

void LevelCreator::createSaveButton(Game& game) {
    saveButton.setSize({100.0f, 30.0f});
    saveButton.setPosition(game.window.getSize().x - 120.0f, game.window.getSize().y - 40.0f);
    saveButton.setFillColor(sf::Color::Green);

    buttonText.setFont(font);
    buttonText.setString("Save");
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(saveButton.getPosition().x + 10.0f, saveButton.getPosition().y + 5.0f);
}

void LevelCreator::handleInput(Game& game) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game.window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            mouseDown = true;
            if (saveButton.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
                nameInputWindow.create(sf::VideoMode(300, 100), "Enter filename", sf::Style::Close);
                inputFileName.clear();
                mouseDown = false;
            }
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            mouseDown = false;
        }

        if (mouseDown) {
            sf::Sprite s;
            s.setTexture(tiles[selectedTile]);
            s.setScale(game.getTileSize() / s.getLocalBounds().height, game.getTileSize() / s.getLocalBounds().height);

            textureIDs.emplace_back(selectedTile);
            placedTiles.emplace_back(s);
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Key::Right || event.key.code == sf::Keyboard::Key::D) {
                selectedTile = (selectedTile + 1) % tiles.size();
            }
            if (event.key.code == sf::Keyboard::Key::Left || event.key.code == sf::Keyboard::Key::A) {
                selectedTile = (selectedTile == 0) ? tiles.size() - 1 : selectedTile - 1;
            }
        }
    }

    if (nameInputWindow.isOpen()) {
        sf::Event nameEvent;
        while (nameInputWindow.pollEvent(nameEvent)) {
            if (nameEvent.type == sf::Event::Closed) {
                nameInputWindow.close();
            }

            if (nameEvent.type == sf::Event::TextEntered) {
                if (nameEvent.text.unicode < 128) {
                    if (nameEvent.text.unicode == '\b' && !inputFileName.empty()) {
                        inputFileName.pop_back();
                    } else if (nameEvent.text.unicode != '\b') {
                        inputFileName += static_cast<char>(nameEvent.text.unicode);
                    }
                }
            }

            if (nameEvent.type == sf::Event::KeyPressed && nameEvent.key.code == sf::Keyboard::Enter) {
                saveWallToCSV(inputFileName + ".csv");
                clearDrawing(game);
                nameInputWindow.close();
            }
        }
    }
}

void LevelCreator::update(Game& game) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(game.window);

    float snappedX = static_cast<int>(mousePos.x / game.getTileSize()) * game.getTileSize();
    float snappedY = static_cast<int>(mousePos.y / game.getTileSize()) * game.getTileSize();

    if (!placedTiles.empty()) {
        placedTiles.back().setPosition(snappedX, snappedY);
        placedTiles.back().setTexture(tiles[selectedTile]);
    }
}

void LevelCreator::render(Game& game) {
    game.window.clear();

    for (const auto& tile : placedTiles) {
        game.window.draw(tile);
    }

    game.window.draw(saveButton);
    game.window.draw(buttonText);

    if (nameInputWindow.isOpen()) {
        nameInputWindow.clear(sf::Color::White);

        sf::Text inputText;
        inputText.setFont(font);
        inputText.setString(inputFileName);
        inputText.setCharacterSize(20);
        inputText.setFillColor(sf::Color::Black);
        inputText.setPosition(10.0f, 40.0f);

        nameInputWindow.draw(inputText);
        nameInputWindow.display();
    }
}

void LevelCreator::saveWallToCSV(const std::string& filename) {
    std::ofstream file("resources/" + filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file to save" << std::endl;
        return;
    }


    for (size_t i = 0; i < placedTiles.size(); ++i) {
        sf::Vector2f position = placedTiles[i].getPosition();
        file << static_cast<int>(position.x) << "," << static_cast<int>(position.y) << "," << textureIDs[i] << std::endl;
    }

    file.close();
}

void LevelCreator::clearDrawing(Game& game) {
    placedTiles.clear();
    textureIDs.clear();

    game.changeState(std::make_shared<MenuState>());
}
