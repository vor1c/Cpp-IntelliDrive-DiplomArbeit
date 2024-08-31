//
// Created by Voric on 31/08/2024.
//
#include "../include/CarChooseState.h"
#include "../include/Game.h"
#include "../include/GameState.h"
#include <iostream>

CarChoosingState::CarChoosingState() : selectedCarIndex(0) {
    if (!font.loadFromFile("resources/Rubik-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    titleText.setFont(font);
    titleText.setString("Choose Your Car");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(100, 50);

    loadCars();
    selectCar(0);
}

void CarChoosingState::loadCars() {
    for (int i = 1; i <= 5; ++i) {
        sf::Texture texture;
        if (texture.loadFromFile("resources/Car" + std::to_string(i) + ".png")) {
            carTextures.push_back(texture);

            sf::Sprite sprite;
            sprite.setTexture(carTextures.back());
            sprite.setScale(2.0f, 2.0f); // Adjust the scale as needed to fit your layout
            sprite.setPosition(100.0f + (i - 1) * 350.0f, 300.0f); // Position them in a row with space between
            carSprites.push_back(sprite);
        } else {
            std::cerr << "Failed to load car " << i << " texture!" << std::endl;
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
                // Store the selected car texture in the Game object
                game.setSelectedCarTexture(carTextures[selectedCarIndex]);
                // Transition to the GameState
                game.changeState(std::make_shared<GameState>());
            }
        }
    }
}


void CarChoosingState::update(Game& game) {
    // Update logic if needed
}

void CarChoosingState::render(Game& game) {
    game.window.clear();

    game.window.draw(titleText);

    for (const auto& sprite : carSprites) {
        game.window.draw(sprite);
    }

    game.window.display();
}

void CarChoosingState::selectCar(int index) {
    for (size_t i = 0; i < carSprites.size(); ++i) {
        carSprites[i].setColor(sf::Color::White); // Reset color
    }
    carSprites[index].setColor(sf::Color::Yellow); // Highlight selected car
}
