//
// Created by Voric on 11/08/2024.
//

#include "../include/Game.h"
#include <iostream>
#include <../include/MenuState.h>
#include <SFML/System/Clock.hpp>

Game::Game() : window(sf::VideoMode(800, 600), "IntelliDrive")
{
    car = std::make_shared<Car>();
  pushState(std::make_shared<MenuState>());
}

void Game::run() {
    sf::Time deltaTime = clock.restart();
    dt = deltaTime.asSeconds();
    while (window.isOpen()) {

        auto currentState = getCurrentState();
        if (currentState) {
            std::cout<<"Game1" << std::endl;
            currentState->handleInput(*this);
            currentState->update(*this);
            window.clear();
            currentState->render(*this);
            window.display();
        }
    }
}

void Game::pushState(std::shared_ptr<State> state) {
    states.push_back(state);
}

void Game::popState() {
    states.pop_back();
}

void Game::changeState(std::shared_ptr<State> state) {
    if (!states.empty()) {
        states.pop_back();
    }
    states.push_back(state);
}

std::shared_ptr<State> Game::getCurrentState() {
    if (states.empty()) return nullptr;
    return states.back();
}
