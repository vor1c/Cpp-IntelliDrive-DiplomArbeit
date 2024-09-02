//
// Created by Voric on 31/08/2024.
//

#include "../include/CarChooseState.h"
#include "../include/Game.h"
#include "../include/GameState.h"
#include <iostream>
#include <MenuState.h>
#include <chrono>
#include <thread>

CarChoosingState::CarChoosingState() : selectedCarIndex(0) {
    sf::Vector2u defaultWindowSize(1920, 1080);
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
    titleText.setPosition(defaultWindowSize.x / 2.0f - 350, (defaultWindowSize.y / 4.0f - 200.f));

    // Set up car stats text
    carStatsText.setFont(font);
    carStatsText.setCharacterSize(25);
    carStatsText.setFillColor(sf::Color::White);
    carStatsText.setPosition(100, 750);  // Placed near the bottom left

    // Drive type and power text
    driveTypeText.setFont(font);
    driveTypeText.setCharacterSize(30);
    driveTypeText.setFillColor(sf::Color::White);
    driveTypeText.setPosition(1000, 900);  // Positioned above the stats bars

    loadCars();
    selectCar(0);
}

void CarChoosingState::loadCars() {
    if (carSprites.empty()) {
        carTextures.reserve(5);
        carNames = {"Car 1", "Car 2", "Car 3", "Car 4", "Car 5"};
        maxSpeeds = {10, 5, 7, 6, 10};
        handlings = {6, 9, 3, 7, 10};
        accelerations = {4, 6, 10, 7, 10};
        weights = {1560, 1600, 1580, 1550, 1520};
        maxPowers = {280, 220, 250, 260, 300};
        torques = {40.0, 38.0, 42.0, 39.0, 45.0};
        driveTypes = {"4WD", "4WD", "4WD", "4WD", "4WD"};

        for (int i = 1; i <= 5; ++i) {
            sf::Texture texture;
            if (texture.loadFromFile("resources/Car" + std::to_string(i) + ".png")) {
                carTextures.push_back(texture);

                sf::Sprite sprite;
                sprite.setTexture(carTextures.back());
                sprite.setScale(2.0f, 2.0f);
                sprite.setPosition(860.0f, 300.0f); // Centered horizontally, with space above
                carSprites.push_back(sprite);
            } else {
                std::cerr << "Failed to load car " << i << " texture!" << std::endl;
                carTextures.emplace_back();
            }
        }
    }
}

void CarChoosingState::handleInput(Game& game) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game.window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) {
                selectedCarIndex = (selectedCarIndex - 1 + carSprites.size()) % carSprites.size();
                selectCar(selectedCarIndex);
            }
            if (event.key.code == sf::Keyboard::Right) {
                selectedCarIndex = (selectedCarIndex + 1) % carSprites.size();
                selectCar(selectedCarIndex);
            }
            if (event.key.code == sf::Keyboard::Enter) {
                static bool confirmPressed = false;
                if (confirmPressed) {
                    game.setSelectedCarTexture(carTextures[selectedCarIndex]);
                    game.changeState(std::make_shared<MenuState>());
                } else {
                    confirmPressed = true;
                    std::cout << "Press Enter again to confirm." << std::endl;
                }
            }
        }
    }
}

void CarChoosingState::update(Game& game) {

}

void CarChoosingState::render(Game& game) {
    game.window.clear(sf::Color::Black);
    game.window.draw(titleText);
    game.window.draw(carSprites[selectedCarIndex]);
    game.window.draw(driveTypeText);
    game.window.draw(carStatsText);
    renderStatsBars(game);
    std::cout << "Displayed." << std::endl;
}

void CarChoosingState::selectCar(int index) {
    for (size_t i = 0; i < carSprites.size(); ++i) {
        carSprites[i].setColor(sf::Color::White);
    }
    if (index < carSprites.size()) {
        carSprites[index].setColor(sf::Color::Yellow);
    }

    carStatsText.setString(
        carNames[index] + "\n\n" +
        "Weight: " + std::to_string(weights[index]) + " kg\n" +
        "Max Power: " + std::to_string(maxPowers[index]) + " PS\n" +
        "Max Torque: " + std::to_string(torques[index]) + " kgm"
    );

    // Update drive type and power display
    driveTypeText.setString(driveTypes[index] + " " + std::to_string(maxPowers[index]) + "ps");
}

void CarChoosingState::renderStatsBars(Game& game) {
    float barWidth = 20.0f * maxSpeeds[selectedCarIndex];
    sf::RectangleShape speedBar(sf::Vector2f(barWidth, 20.0f));
    speedBar.setFillColor(sf::Color::Red);
    speedBar.setPosition(400.0f, 850.0f);
    game.window.draw(speedBar);

    barWidth = 20.0f * handlings[selectedCarIndex];
    sf::RectangleShape handlingBar(sf::Vector2f(barWidth, 20.0f));
    handlingBar.setFillColor(sf::Color::Yellow);
    handlingBar.setPosition(400.0f, 900.0f);
    game.window.draw(handlingBar);

    barWidth = 20.0f * accelerations[selectedCarIndex];
    sf::RectangleShape accelerationBar(sf::Vector2f(barWidth, 20.0f));
    accelerationBar.setFillColor(sf::Color::Blue);
    accelerationBar.setPosition(400.0f, 950.0f);
    game.window.draw(accelerationBar);
}
