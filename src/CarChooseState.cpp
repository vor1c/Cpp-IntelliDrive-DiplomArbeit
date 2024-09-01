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
    if (!font.loadFromFile("resources/Rubik-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    titleText.setFont(font);
    titleText.setString("Choose Your Car");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(100, 50);

    loadCars(); // This should only be called once, during initialization
    selectCar(0); // Select the first car initially
}

void CarChoosingState::loadCars() {
    if (carSprites.empty()) { // Check if cars have already been loaded
        carTextures.reserve(5);  // Reserve space for 5 textures to avoid reallocations
        for (int i = 1; i <= 5; ++i) {
            sf::Texture texture;
            if (texture.loadFromFile("resources/Car" + std::to_string(i) + ".png")) {
                carTextures.push_back(texture); // Store the texture in the vector

                sf::Sprite sprite;
                sprite.setTexture(carTextures.back()); // Use the texture just added
                sprite.setScale(2.0f, 2.0f); // Adjust the scale as needed to fit your layout
                sprite.setPosition(100.0f + (i - 1) * 350.0f, 300.0f); // Position them in a row with space between
                carSprites.push_back(sprite); // Add sprite to vector
            } else {
                std::cerr << "Failed to load car " << i << " texture!" << std::endl;
                carTextures.emplace_back();  // Add a default/empty texture to keep indexing consistent
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
                    // Store the selected car texture in the Game object
                    game.setSelectedCarTexture(carTextures[selectedCarIndex]);
                    // Transition to the MenuState
                    game.changeState(std::make_shared<MenuState>());
                } else {
                    confirmPressed = true; // Require a second press to confirm
                    std::cout << "Press Enter again to confirm." << std::endl;
                }
            }
        }
    }
}

void CarChoosingState::update(Game& game) {

}

void CarChoosingState::render(Game& game) {
    game.window.clear(sf::Color::Black); // Ensure the screen is properly cleared
    game.window.draw(titleText);
   for (const auto& sprite : carSprites) {
        game.window.draw(sprite);
    }
    game.window.display();
    std::cout << "Displayed." << std::endl;
}

void CarChoosingState::selectCar(int index) {
    for (size_t i = 0; i < carSprites.size(); ++i) {
        carSprites[i].setColor(sf::Color::White); // Reset color
    }
    if (index < carSprites.size()) {
        carSprites[index].setColor(sf::Color::Yellow); // Highlight selected car
    }
}
