//
// Created by Devrim on 30.09.2024.
//
// LevelCreator.cpp

#include "../include/LevelCreator.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>
#include <MenuState.h>
#include <string>

LevelCreator::LevelCreator(Game& game) {
    createSaveButton(game);

    sf::Sprite s;
    s.setTexture(tiles[0]);
    placedTiles.emplace_back(s);
    placedTiles[0].setScale(tileSize / placedTiles[0].getLocalBounds().height, tileSize / placedTiles[0].getLocalBounds().height);
}

void LevelCreator::createSaveButton(Game& game) {
    saveButton.setSize({100.0f, 30.0f});
    saveButton.setPosition(game.window.getSize().x - 120.0f, game.window.getSize().y - 40.0f);
    saveButton.setFillColor(sf::Color::Green);

    if (!font.loadFromFile("resources/Fonts/Rubik-Regular.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    buttonText.setFont(font);
    buttonText.setString("Save");
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(saveButton.getPosition().x + 10.0f, saveButton.getPosition().y + 5.0f);

    // Load tile textures
    ResourceManager resourceManager;
    tiles = resourceManager.loadImagesInBulk("resources/Tiles/Asphalt road/", "road_asphalt", ".png");
}

void LevelCreator::handleInput(Game& game) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game.window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            mouseDown = true;
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            mouseDown = false;
        }

        if(mouseDown){
            sf::Sprite s;
            s.setTexture(tiles[0]);
            s.setScale(tileSize / placedTiles[0].getLocalBounds().height, tileSize / placedTiles[0].getLocalBounds().height);
            placedTiles.emplace_back(s);
        }

        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Key::Right || event.key.code == sf::Keyboard::Key::D){
                selectedTile = (selectedTile + 1 < tiles.size()) ? selectedTile + 1 : 0;
            }
            if(event.key.code == sf::Keyboard::Key::Left || event.key.code == sf::Keyboard::Key::A){
                selectedTile = (selectedTile - 1 < 0) ? tiles.size() - 1 : selectedTile - 1;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (saveButton.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
                nameInputWindow.create(sf::VideoMode(300, 100), "Enter filename", sf::Style::Close);
                inputFileName.clear();
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
                        inputFileName += nameEvent.text.unicode;
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
    if (isDrawing) {
        sf::Vector2f currentMousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(game.window));
        if (wallPoints.empty() || (currentMousePos != wallPoints.back())) {
            wallPoints.push_back(currentMousePos);
        }
    }

    sf::Vector2i mousePos = sf::Mouse::getPosition();

    float snappedX = (int)(mousePos.x / tileSize) * tileSize;
    float snappedY = (int)(mousePos.y / tileSize) * tileSize;

    placedTiles[placedTiles.size() - 1].setPosition(snappedX, snappedY);
    placedTiles[placedTiles.size() - 1].setTexture(tiles[selectedTile]);
}

void LevelCreator::render(Game& game) {
    game.window.clear();

    for (size_t i = 1; i < wallPoints.size(); ++i) {
        sf::Vertex line[] = {
            sf::Vertex(wallPoints[i - 1], sf::Color::Red),
            sf::Vertex(wallPoints[i], sf::Color::Red)
        };
        game.window.draw(line, 2, sf::PrimitiveType::Lines);
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

    for (int i = 0; i < placedTiles.size(); ++i) {
        game.window.draw(placedTiles[i]);
    }

}

void LevelCreator::saveWallToCSV(const std::string& filename) {
    std::ofstream file("resources/" + filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file to save" << std::endl;
        return;
    }

    for (const auto& point : wallPoints) {
        file << point.x << "," << point.y << std::endl;
    }

    file.close();
}

void LevelCreator::clearDrawing(Game &game) {
    wallPoints.clear();
    game.changeState(std::make_shared<MenuState>());
}
