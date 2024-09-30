//
// Created by Devrim on 30.09.2024.
//
// LevelCreator.cpp

#include "../include/LevelCreator.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>
#include <string>

LevelCreator::LevelCreator(Game& game) {
    createSaveButton(game); // Create the Save button
}

void LevelCreator::createSaveButton(Game& game) {
    saveButton.setSize({100.0f, 30.0f});
    saveButton.setPosition(game.window.getSize().x - 120.0f, game.window.getSize().y - 40.0f);
    saveButton.setFillColor(sf::Color::Green);

    if (!font.loadFromFile("resources/Rubik-Regular.ttf")) { // Load a font
        std::cerr << "Error loading font" << std::endl;
    }

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

        // Start drawing on mouse press
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            isDrawing = true;
            wallPoints.push_back(static_cast<sf::Vector2f>(sf::Mouse::getPosition(game.window)));
        }

        // Stop drawing on mouse release
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            isDrawing = false;
        }

        // Check if the button was pressed
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (saveButton.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
                // Create a new window for entering the filename
                nameInputWindow.create(sf::VideoMode(300, 100), "Enter filename", sf::Style::Close);
                inputFileName.clear(); // Clear the filename for new input
            }
        }
    }

    // Process input in the name input window
    if (nameInputWindow.isOpen()) {
        sf::Event nameEvent;
        while (nameInputWindow.pollEvent(nameEvent)) {
            if (nameEvent.type == sf::Event::Closed) {
                nameInputWindow.close();
            }

            if (nameEvent.type == sf::Event::TextEntered) {
                if (nameEvent.text.unicode < 128) { // Allow only ASCII characters
                    if (nameEvent.text.unicode == '\b' && !inputFileName.empty()) {
                        inputFileName.pop_back(); // Backspace
                    } else if (nameEvent.text.unicode != '\b') {
                        inputFileName += nameEvent.text.unicode; // Add character
                    }
                }
            }

            // Save and close the window
            if (nameEvent.type == sf::Event::KeyPressed && nameEvent.key.code == sf::Keyboard::Enter) {
                saveWallToCSV(inputFileName + ".csv");
                clearDrawing();
                nameInputWindow.close();
            }
        }
    }
}

void LevelCreator::update(Game& game) {
    if (isDrawing) {
        // Continuously add the current mouse position while drawing
        sf::Vector2f currentMousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(game.window));

        // Only add the point if it's significantly different from the last point
        if (wallPoints.empty() || (currentMousePos != wallPoints.back())) {
            wallPoints.push_back(currentMousePos);
        }
    }
}

void LevelCreator::render(Game& game) {
    game.window.clear();

    // Draw wall segments
    for (size_t i = 1; i < wallPoints.size(); ++i) {
        sf::Vertex line[] = {
            sf::Vertex(wallPoints[i - 1], sf::Color::Red),
            sf::Vertex(wallPoints[i], sf::Color::Red)
        };
        game.window.draw(line, 2, sf::PrimitiveType::Lines);
    }

    // Draw the Save button
    game.window.draw(saveButton);
    game.window.draw(buttonText);

    // Draw the input window
    if (nameInputWindow.isOpen()) {
        nameInputWindow.clear(sf::Color::White); // Clear with a white background

        // Create and configure the text to display the current input
        sf::Text inputText;
        inputText.setFont(font);
        inputText.setString(inputFileName); // Show the current input
        inputText.setCharacterSize(20);
        inputText.setFillColor(sf::Color::Black);
        inputText.setPosition(10.0f, 40.0f); // Position for the input text

        // Draw the input text on the input window
        nameInputWindow.draw(inputText);
        nameInputWindow.display(); // Display the changes in the input window
    }

}

void LevelCreator::saveWallToCSV(const std::string& filename) {
    std::ofstream file("resources/" + filename); // Save in the resources folder

    if (!file.is_open()) {
        std::cerr << "Error opening file to save" << std::endl;
        return;
    }

    for (const auto& point : wallPoints) {
        file << point.x << "," << point.y << std::endl; // Save as CSV
    }

    file.close();
}

void LevelCreator::clearDrawing() {
    wallPoints.clear(); // Clear the drawn points
}
