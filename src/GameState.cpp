//
// Created by Voric on 11/08/2024.
//

#include "../include/GameState.h"
#include "../include/PauseState.h"
#include "../include/DeathState.h"
#include "../include/Car.h"
#include "../include/Game.h"

GameState::GameState(Game& game) : car() {
    car.setTexture(game.getSelectedCarTexture());
}

void GameState::handleInput(Game& game) {
    sf::Event event;
    while (game.window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            game.window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
            game.pushState(std::make_shared<PauseState>());
        }
    }

    car.handleInput();
}

void GameState::update(Game& game) {
    car.update(game.dt);
    if (car.getBounds().left < 100 || car.getBounds().left + car.getBounds().width > 700) {
        game.changeState(std::make_shared<DeathState>());
    }
}

void GameState::render(Game& game) {
    sf::RectangleShape road(sf::Vector2f(600, 600));
    road.setPosition(100, 0);
    road.setFillColor(sf::Color{ 0x808080 });
    game.window.draw(road);

    car.render(game.window);
}