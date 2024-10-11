 //
// Created by Voric and tobisdev on 11/08/2024.
//

#include "../include/GameState.h"
#include "../include/PauseState.h"
#include "../include/DeathState.h"
#include "../include/Car.h"
#include "../include/Game.h"

GameState::GameState(Game& game, const std::string& levelFile) : car(game.getCar()) {
    initializeCar();
    placedTiles.clear();


    ResourceManager& resourceManager = ResourceManager::getInstance();
    resourceManager.loadTexturesInBulk("resources/Tiles/Asphalt road/", "road_asphalt", ".png");
    tiles = resourceManager.getBulkTextures();

    loadLevelFromCSV(levelFile, game);
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

void GameState::loadLevelFromCSV(const std::string& filename, Game &game) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        float x, y;
        int texture;
        char comma;

        ss >> x >> comma >> y >> comma >> texture;

        std::cout << "xxxx " << x << " " << y << " " <<texture << "\n";

        sf::Sprite s;
        s.setTexture(tiles[texture]);
        s.setScale(game.getTileSize() / s.getLocalBounds().height, game.getTileSize() / s.getLocalBounds().height);
        s.setPosition(x, y);
        placedTiles.emplace_back(s);

        std::cout << "HALLO!\n";

    }

}

void GameState::update(Game& game) {
    car.update(game.dt);
}

void GameState::render(Game& game) {
    game.window.clear();
    for (int i = 1; i < placedTiles.size(); ++i) {
        game.window.draw(placedTiles[i]);
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
