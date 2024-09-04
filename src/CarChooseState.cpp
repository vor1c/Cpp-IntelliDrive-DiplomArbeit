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

    defaultWindowSize = sf::Vector2u(1920, 1080);


    if (!font.loadFromFile("resources/Rubik-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    if (!titlefont.loadFromFile("resources/UpheavalPRO.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    loadCars();
    loadLogos();

    dividerline.setSize(sf::Vector2f(1920.0f, 5.0f));
    dividerline.setFillColor(sf::Color(80,80,80));
    dividerline.setPosition(0, 850);

    legendheight =  (dividerline.getGlobalBounds().height + dividerline.getPosition().y + 1080) / 2;

    titleText.setFont(titlefont);
    titleText.setString("CAR SELECTION");
    titleText.setCharacterSize(125);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(defaultWindowSize.x / 2.0f - (titleText.getLocalBounds().width / 2), 40);



    selectCar(0);
}

void CarChoosingState::loadCars() {
    if (carSprites.empty()) {
        carTextures.reserve(5);
        carNames = {"Diablo GT 1999", "E-Type 4.2 1967", "GT40 1968", "911 Carrera 2022", "P1 2015"};
        maxSpeeds = {10, 5, 7, 6, 10};
        handlings = {6, 9, 3, 7, 10};
        accelerations = {4, 6, 10, 7, 10};
        weights = {1460, 1310, 1205, 1650, 1520};
        maxPowers = {575, 265, 500, 480, 916};
        torques = {64.2, 38.7, 54.1, 54.0, 91.8};
        driveTypes = {"2WD", "4WD", "4WD", "4WD", "2WD"};

        for (int i = 1; i <= 5; ++i) {
            sf::Texture texture;
            if (texture.loadFromFile("resources/Car" + std::to_string(i) + ".png")) {
                carTextures.push_back(texture);
                sf::Sprite sprite;
                sprite.setTexture(carTextures.back());
                sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
                sprite.setScale(2.0f, 2.0f);
                sprite.setPosition(defaultWindowSize.x / 2.0f , 600.0f);
                sprite.setScale(3.3f, 3.3f);
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
                game.setSelectedCarTexture(carTextures[selectedCarIndex]);
                game.changeState(std::make_shared<MenuState>());
            }
        }
    }
}
// https://www.sfml-dev.org/tutorials/2.6/graphics-transform.php
void CarChoosingState::update(Game& game) {
    sf::Sprite &selectedCar = carSprites[selectedCarIndex];
    rotationAngle += 0.02f;
    if (rotationAngle >= 360.0f) {
        rotationAngle = 0.0f;
    }
    selectedCar.setRotation(rotationAngle);
}

void CarChoosingState::loadLogos() {
    std::vector<std::string> logoFiles = {
        "resources/lambologo.png",
        "resources/jaguarlogo.png",
        "resources/fordlogo.png",
        "resources/porschelogo.png",
        "resources/mclarenlogo.png"
    };
    for (const auto& file : logoFiles) {
        sf::Texture texture;
        if (texture.loadFromFile(file)) {
            carLogos.push_back(texture);
        } else {
            std::cerr << "Failed to load logo: " << file << std::endl;
            carLogos.emplace_back();
        }
    }
}

void CarChoosingState::renderLogos(Game& game) {
    sf::Sprite sprite;
    sf::Text carNameText;

    if (carLogos.empty() || selectedCarIndex >= carLogos.size()) {
        std::cerr << "No logos loaded or selectedCarIndex out of bounds!" << std::endl;
        return;
    }
    sprite.setTexture(carLogos[selectedCarIndex]);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sf::Vector2f carPosition = carSprites[selectedCarIndex].getPosition();
    sprite.setPosition(carPosition.x + carSprites[selectedCarIndex].getLocalBounds().width / 2 - 200.0f, carPosition.y - 300.0f);
    sprite.setScale(0.1f, 0.1f);

    carNameText.setFont(font);
    carNameText.setString(carNames[selectedCarIndex]);
    carNameText.setCharacterSize(30);
    carNameText.setFillColor(sf::Color::White);

    float logoCenterY = sprite.getPosition().y;
    float textCenterY = carNameText.getLocalBounds().height / 2;
    carNameText.setPosition(sprite.getPosition().x + sprite.getGlobalBounds().width / 2 + 10.0f, logoCenterY - textCenterY);

    game.window.draw(sprite);
    game.window.draw(carNameText);
}


void CarChoosingState::render(Game& game) {
    game.window.clear(sf::Color::Black);
    game.window.draw(titleText);
    game.window.draw(carSprites[selectedCarIndex]);
    game.window.draw(driveTypeText);
    renderLogos(game);
    game.window.draw(dividerline);
    renderBottomLine(game);
}

void CarChoosingState::selectCar(int index) {
    for (size_t i = 0; i < carSprites.size(); ++i) {
        carSprites[i].setColor(sf::Color::White);
    }
}

void CarChoosingState::renderBottomLine(Game& game) {

    float leftbounds = 0.0f;
    legendheight =  (dividerline.getGlobalBounds().height + dividerline.getPosition().y + 1080) / 2;

    statBarsLabel.setFont(font);
    statBarsLabel.setCharacterSize(25);
    statBarsLabel.setFillColor(sf::Color::White);

    carStatsText.setFont(font);
    carStatsText.setCharacterSize(25);
    carStatsText.setFillColor(sf::Color::White);

    driveTypeText.setFont(font);
    driveTypeText.setCharacterSize(30);
    driveTypeText.setFillColor(sf::Color::White);


    statBarsLabel.setString("Max Speed");
    float barWidth = 20.0f * maxSpeeds[selectedCarIndex];
    sf::RectangleShape speedBar(sf::Vector2f(barWidth, 20.0f));
    speedBar.setFillColor(sf::Color::Red);
    speedBar.setPosition(315.0f, legendheight - 60);
    statBarsLabel.setPosition(300.0f - statBarsLabel.getGlobalBounds().width, legendheight - 65);
    game.window.draw(speedBar);
    game.window.draw(statBarsLabel);

    statBarsLabel.setString("Handling");
    barWidth = 20.0f * handlings[selectedCarIndex];
    sf::RectangleShape handlingBar(sf::Vector2f(barWidth, 20.0f));
    handlingBar.setFillColor(sf::Color::Yellow);
    handlingBar.setPosition(315.0f, legendheight - 10);
    statBarsLabel.setPosition(300.0f - statBarsLabel.getGlobalBounds().width, legendheight - 15);
    game.window.draw(handlingBar);
    game.window.draw(statBarsLabel);

    statBarsLabel.setString("Acceleration");
    barWidth = 20.0f * accelerations[selectedCarIndex];
    sf::RectangleShape accelerationBar(sf::Vector2f(barWidth, 20.0f));
    accelerationBar.setFillColor(sf::Color::Blue);
    accelerationBar.setPosition(315.0f, legendheight + 40);
    statBarsLabel.setPosition(300.0f - statBarsLabel.getGlobalBounds().width, legendheight + 35);
    leftbounds = statBarsLabel.getPosition().x;
    game.window.draw(accelerationBar);
    game.window.draw(statBarsLabel);


    carStatsText.setString("Weight: " + std::to_string(weights[selectedCarIndex]) + " kg\n");
    carStatsText.setPosition(1920.0f - leftbounds - carStatsText.getGlobalBounds().width, legendheight - 65);
    game.window.draw(carStatsText);

    carStatsText.setString("Max Power: " + std::to_string(maxPowers[selectedCarIndex]) + " PS\n");
    carStatsText.setPosition(1920.0f - leftbounds - carStatsText.getGlobalBounds().width, legendheight - 15);
    game.window.draw(carStatsText);

    carStatsText.setString("Max Torque: " + std::to_string(torques[selectedCarIndex]) + " kgm");
    carStatsText.setPosition(1920.0f - leftbounds - carStatsText.getGlobalBounds().width, legendheight + 35);
    game.window.draw(carStatsText);


    driveTypeText.setPosition(800, legendheight - 15);
    driveTypeText.setString(driveTypes[selectedCarIndex] + " " + std::to_string(maxPowers[selectedCarIndex]) + "ps");
}
