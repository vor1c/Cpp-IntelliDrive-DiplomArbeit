//
// Created by Voric and tobisdev on 11/08/2024.
//

#include "../include/GameState.h"
#include "../include/PauseState.h"
#include "../include/DeathState.h"
#include "../include/Car.h"
#include "../include/Game.h"

GameState::GameState(Game& game, const std::string& levelFile) : car(game.getCar()) {
    loadLevelFromCSV(levelFile);
    resetGameState(levelFile);
}

void GameState::resetGameState(const std::string& levelFile) {
    walls.clear();
    loadLevelFromCSV(levelFile);
    initializeCar();
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
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        float x, y;
        char comma;  // To store and ignore the comma

        // Extract x, the comma, and y
        ss >> x >> comma >> y;

        // Output the values for debugging
        std::cout << "x: " << x << " y: " << y << "\n";

        // Create a wall segment at the parsed x, y coordinates
        sf::RectangleShape wallSegment(sf::Vector2f(10, 10));
        wallSegment.setPosition(sf::Vector2f(x, y));

        // Add the wall segment to the wall collection
        walls.push_back(Wall(wallSegment));
    }

}

void GameState::update(Game& game) {
    car.update(game.dt);
}

void GameState::render(Game& game) {
    game.window.clear();
    for (int i = 1; i < walls.size(); ++i) {
        sf::Vertex line[] = {
                sf::Vertex(walls[i - 1].shape.getPosition(), sf::Color::Red),
                sf::Vertex(walls[i].shape.getPosition(), sf::Color::Red)
        };
        game.window.draw(line, 2, sf::PrimitiveType::Lines);
    }
    car.render(game.window);
}

void GameState::initializeCar() {
    sf::Sprite &carSprite = car.getCarSprite();
    carSprite.setOrigin(carSprite.getLocalBounds().width / 2, carSprite.getLocalBounds().height / 2);
    carSprite.setPosition(400, 400);
    car.resetRotationAngle();
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
