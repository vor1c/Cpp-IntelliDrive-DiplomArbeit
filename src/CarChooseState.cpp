//
// Created by Voric and tobisdev on 31/08/2024.
//

#include "../include/CarChooseState.h"
#include "../include/Game.h"
#include "../include/GameState.h"
#include <iostream>
#include <MenuState.h>
#include <chrono>
#include <thread>

CarChoosingState::CarChoosingState() : selectedCarIndex(0) {
    defaultWindowSize = sf::Vector2u(1920, 1080);

    if (!font.loadFromFile("resources/Rubik-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    if (!titlefont.loadFromFile("resources/UpheavalPRO.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    titleText.setFont(titlefont);
    titleText.setString("CAR SELECTION");
    titleText.setCharacterSize(125);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(defaultWindowSize.x / 2.0f - (titleText.getLocalBounds().width / 2), 40);

    carStatsText.setFont(font);
    carStatsText.setCharacterSize(25);
    carStatsText.setFillColor(sf::Color::White);
    carStatsText.setPosition(100, 750);

    driveTypeText.setFont(font);
    driveTypeText.setCharacterSize(30);
    driveTypeText.setFillColor(sf::Color::White);
    driveTypeText.setPosition(1000, 900);

    dividerline.setSize(sf::Vector2f(1920.0f, 5.0f));
    dividerline.setFillColor(sf::Color(80,80,80));
    dividerline.setPosition(0, 850);
}

void CarChoosingState::handleInput(Game& game) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game.window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
                selectedCarIndex = (selectedCarIndex - 1 + game.cars.size()) % game.cars.size();
            }
            if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                selectedCarIndex = (selectedCarIndex + 1) % game.cars.size();
            }
            if (event.key.code == sf::Keyboard::Enter) {
                //game.setSelectedCarTexture(carTextures[selectedCarIndex]);
                game.changeState(std::make_shared<MenuState>());
            }
        }
    }
}
// https://www.sfml-dev.org/tutorials/2.6/graphics-transform.php
void CarChoosingState::update(Game& game) {
    selectedCar.setTexture(game.cars[selectedCarIndex].texture);
    selectedCar.setColor(sf::Color::White);
    rotationAngle += 0.01f;
    if (rotationAngle >= 360.0f) {
        rotationAngle = 0.0f;
    }
    selectedCar.setRotation(rotationAngle);
    selectedCar.setOrigin(selectedCar.getLocalBounds().width / 2, selectedCar.getLocalBounds().height / 2);
    selectedCar.setPosition(game.window.getSize().x / 2, game.window.getSize().y / 2);
    selectedCar.setScale(3.3f, 3.3f);
}

void CarChoosingState::render(Game& game) {
    game.window.clear(sf::Color::Black);
    game.window.draw(titleText);
    game.window.draw(selectedCar);
    game.window.draw(dividerline);
    renderStatsBars(game);
    std::cout << "Displayed." << std::endl;
}

void CarChoosingState::renderStatsBars(Game& game) {
    float legendheight =  (dividerline.getGlobalBounds().height + dividerline.getPosition().y + 1080) / 2;

    carStatsText.setString(
            game.cars[selectedCarIndex].name + "\n\n" +
            "Weight: " + std::to_string(game.cars[selectedCarIndex].weight) + " kg\n" +
            "Max Power: " + std::to_string(game.cars[selectedCarIndex].power) + " PS\n" +
            "Max Torque: " + std::to_string(game.cars[selectedCarIndex].torque) + " kgm"
    );
    game.window.draw(carStatsText);

    driveTypeText.setString(game.cars[selectedCarIndex].driveType + " " + std::to_string(game.cars[selectedCarIndex].power) + "ps");
    game.window.draw(driveTypeText);


    sf::Text statBarsLabel;
    statBarsLabel.setFont(font);
    statBarsLabel.setCharacterSize(25);
    statBarsLabel.setFillColor(sf::Color::White);

    statBarsLabel.setString("Max Speed");
    float barWidth = 20.0f * game.cars[selectedCarIndex].maxSpeed;
    sf::RectangleShape speedBar(sf::Vector2f(barWidth, 20.0f));
    speedBar.setFillColor(sf::Color::Red);
    speedBar.setPosition(315.0f, legendheight - 60);
    statBarsLabel.setPosition(300.0f - statBarsLabel.getGlobalBounds().width, legendheight - 65);
    game.window.draw(speedBar);
    game.window.draw(statBarsLabel);

    statBarsLabel.setString("Handling");
    barWidth = 20.0f * game.cars[selectedCarIndex].handling;
    sf::RectangleShape handlingBar(sf::Vector2f(barWidth, 20.0f));
    handlingBar.setFillColor(sf::Color::Yellow);
    handlingBar.setPosition(315.0f, legendheight - 10);
    statBarsLabel.setPosition(300.0f - statBarsLabel.getGlobalBounds().width, legendheight - 15);
    game.window.draw(handlingBar);
    game.window.draw(statBarsLabel);

    statBarsLabel.setString("Acceleration");
    barWidth = 20.0f * game.cars[selectedCarIndex].acceleration;
    sf::RectangleShape accelerationBar(sf::Vector2f(barWidth, 20.0f));
    accelerationBar.setFillColor(sf::Color::Blue);
    accelerationBar.setPosition(315.0f, legendheight + 40);
    statBarsLabel.setPosition(300.0f - statBarsLabel.getGlobalBounds().width, legendheight + 35);
    game.window.draw(accelerationBar);
    game.window.draw(statBarsLabel);
}
