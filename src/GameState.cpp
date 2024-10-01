//
// Created by Voric and tobisdev on 11/08/2024.
//

#include "../include/GameState.h"
#include "../include/PauseState.h"
#include "../include/DeathState.h"
#include "../include/Car.h"
#include "../include/Game.h"

GameState::GameState(Game& game, const std::string& levelFile) : car(game.getCar()) {
    loadLevelFromCSV(levelFile);  // Load level from CSV file
}

void GameState::handleInput(Game& game) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            game.window.close();
        }
        if (isPauseKeyPressed(event)) {
            game.pushState(std::make_shared<PauseState>());
        }
    }
    car.handleInput();
}

void GameState::loadLevelFromCSV(const std::string& filename) {
    // Assuming you are reading wall positions from the CSV
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        float x, y, width, height;
        ss >> x >> y >> width >> height;

        sf::RectangleShape wallSegment(sf::Vector2f(width, height));
        wallSegment.setPosition(sf::Vector2f(x, y));

        // Create a Wall object from the wallSegment and push it to walls
        walls.push_back(Wall(wallSegment));
    }
}


void GameState::update(Game& game) {
    car.update(game.dt);

    // Collision Detection

    // if (car.getBounds().left < 100 || car.getBounds().left + car.getBounds().width > 700) {
    //     game.changeState(std::make_shared<DeathState>());
    // }
}

void GameState::render(Game& game) {
    game.window.clear();
    for (const auto& wall : walls) {
        game.window.draw(wall );
    }
    car.render(game.window);

}

void GameState::initializeCar() {
    sf::Sprite &carSprite = car.getCarSprite();
    carSprite.setOrigin(carSprite.getLocalBounds().width / 2, carSprite.getLocalBounds().height / 2);
    carSprite.setPosition(400, 400);
    car.setPreviousPosition({carSprite.getPosition().x, carSprite.getPosition().y});
    car.setCurrentPosition({carSprite.getPosition().x, carSprite.getPosition().y});
}

bool GameState::isPauseKeyPressed(const sf::Event& event) const {
    return (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P);
}

sf::RectangleShape GameState::createRoad(Game& game) const {
    sf::RectangleShape road(sf::Vector2f(game.window.getSize().x - 20, game.window.getSize().y - 20));
    road.setPosition(10, 10);
    road.setFillColor(sf::Color{80, 80, 80});
    return road;
}
